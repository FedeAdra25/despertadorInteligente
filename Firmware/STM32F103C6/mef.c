#include "mef.h"

static uint8_t buttonPressed = 0;
static uint8_t firstTime = 1; //first time bit to avoid rendering stuff more than once
static MEF_state system_state;
static RTC_TIME_t time, time_old,time_alarm,time_alarm_old;
static RTC_DATE_t date, date_old;
static float temperature, humidity;
static char str[100];
static uint8_t current_selection;

//private functions (not static because proteus breaks)
void switchToSetAlarm(void);
void switchToSetDate(void);
void switchToIDLE(void);
void switchToIDLEActive(void);

void updateDate(void);
void updateTime(void);
void renderIDLE(void);
void renderIDLEActive(void);
void renderSetDate(void);
void renderSetAlarm(void);


uint8_t checkAlarm(void);
void disableBuzzer(void);
void enableBuzzer(void);

void renderDay(uint8_t day);
void renderDate(uint8_t);
void renderTime(uint8_t);

void updateTemperatureAndHumidity(void);
void renderTemperatureAndHumidity(uint8_t);

void animateCurrentSelection(void);
void animateCurrentSelection_alarm(void);
//Functions for setDate and setAlarm states
void writeTime(RTC_TIME_t);
void writeDate(RTC_DATE_t);
void modify_date(uint8_t selection, int8_t increment);
void modify_alarm(uint8_t selection, int8_t increment);
void renderTime_alarm(uint8_t force);

//TODO: ver de mover esto a una librería
static uint8_t GPIOS_getButtonPressed(void);
#define BUTTON_NONE 0
#define BUTTON_OK 1
#define BUTTON_CANCEL 2
#define BUTTON_UP 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_RIGHT 6
#define getPB8() (GPIOB->IDR & (1 << 8))
#define getPB9() (GPIOB->IDR & (1 << 9))
#define getPB10() (GPIOB->IDR & (1 << 10))
#define getPB11() (GPIOB->IDR & (1 << 11))
#define getPB12() (GPIOB->IDR & (1 << 12))
#define getPB13() (GPIOB->IDR & (1 << 13))
#define setPB15()              \
    {                          \
        GPIOB->ODR |= 1 << 15; \
    }
#define resetPB15()               \
    {                             \
        GPIOB->ODR &= ~(1 << 15); \
    }
//---

void MEF_Init(void)
{
    system_state = IDLE;
    //TODO move this logic to a library
    //WARNING: this SETS gpiob CRL register, so it must be called before any other GPIO init
    GPIOB->CRH = 0x34888888; //PB8,9,10,11,12,13 as input with pull-up
    //---                   PB15 as output with push-pull (1100)
    time_alarm.hours = 0;
    time_alarm.minutes = 0;
    time_alarm.seconds = 0;
    time_alarm_old=time_alarm;
}

void MEF_Update(void)
{
    buttonPressed = GPIOS_getButtonPressed();
    switch (system_state)
    {
    case IDLE:
        //check if alarm must be activated AFTER first time render
        if(checkAlarm() && !firstTime){
            switchToIDLEActive();
            return;
        }
        //get data from sensors and RTC
        updateTime();
        updateDate();
        updateTemperatureAndHumidity();
        //render it
        renderIDLE();
        if (buttonPressed == BUTTON_NONE)
            return;
        if (buttonPressed == BUTTON_UP)
        {
            switchToSetAlarm();
            return;
        }
        if (buttonPressed == BUTTON_DOWN)
        {
            switchToSetDate();
            return;
        }
        if (buttonPressed == BUTTON_RIGHT)
        {
            switchToIDLEActive();
        }
        break;
    case IDLE_ACTIVE:
        renderIDLEActive();
        if (buttonPressed == BUTTON_NONE)
            return;

        disableBuzzer(); //first disable buzzer
        switchToIDLE();  //then switch to idle
        break;
    case SETTING_DATE:
        renderSetDate();
        if (buttonPressed == BUTTON_NONE)
            return;
        //CANCEL -> IDLE, don't save
        if (buttonPressed == BUTTON_CANCEL)
        {
            switchToIDLE();
            return;
        }
        //OK -> IDLE, save
        if (buttonPressed == BUTTON_OK)
        {
            writeDate(date);
            writeTime(time);
            switchToIDLE();
            return;
        }
        //UP -> increment
        if (buttonPressed == BUTTON_UP)
        {
            modify_date(current_selection, 1);
        }
        //DOWN -> decrement
        if (buttonPressed == BUTTON_DOWN)
        {
            modify_date(current_selection, -1);
        }
        //LEFT -> select next value
        if (buttonPressed == BUTTON_LEFT)
        {
            current_selection++;
            if (current_selection > SELECTION_END)
                current_selection = SELECTION_START;
        }
        //RIGHT -> select previous value
        if (buttonPressed == BUTTON_RIGHT)
        {
            current_selection--;
            if (current_selection < SELECTION_START)
                current_selection = SELECTION_END;
        }
        animateCurrentSelection();
        break;
    case SETTING_ALARM:
        renderSetAlarm();
        if (buttonPressed == BUTTON_NONE)
            return;
        //CANCEL -> IDLE, don't save
        if (buttonPressed == BUTTON_CANCEL)
        {
            time_alarm=time_alarm_old;
            switchToIDLE();
            return;
        }
        //OK -> IDLE, save
        if (buttonPressed == BUTTON_OK)
        {
            time_alarm_old=time_alarm;
            switchToIDLE();
            return;
        }
        //UP -> increment
        if (buttonPressed == BUTTON_UP)
        {
            modify_alarm(current_selection, 1);
        }
        //DOWN -> decrement
        if (buttonPressed == BUTTON_DOWN)
        {
            modify_alarm(current_selection, -1);
        }
        //LEFT -> select next value
        if (buttonPressed == BUTTON_LEFT)
        {
            current_selection++;
            if (current_selection > SELECTION_END_ALARM)
                current_selection = SELECTION_START_ALARM;
        }
        //RIGHT -> select previous value
        if (buttonPressed == BUTTON_RIGHT)
        {
            current_selection--;
            if (current_selection < SELECTION_START_ALARM)
                current_selection = SELECTION_END_ALARM;
        }
        animateCurrentSelection_alarm();
        /*TODO*/
        break;
    }
}

//Returns 1 if alarm must be sounding
uint8_t checkAlarm(void){
    if(DS1307_timeEquals(&time, &time_alarm)){
        return 1;
    }
    return 0;
}

//RETURNS BUTTON_MENU or BUTTON_SELECT
static uint8_t GPIOS_getButtonPressed(void)
{
    //TODO: ver de mover esto a una librería
    //Also, order of this ifs matters. CANCEL has priority
    if (getPB9() != 0)
    {
        return BUTTON_CANCEL;
    }
    if (getPB8() != 0)
    {
        return BUTTON_OK;
    }
    if (getPB10() != 0)
    {
        return BUTTON_UP;
    }
    if (getPB11() != 0)
    {
        return BUTTON_DOWN;
    }
    if (getPB12() != 0)
    {
        return BUTTON_LEFT;
    }
    if (getPB13() != 0)
    {
        return BUTTON_RIGHT;
    }
    return BUTTON_NONE;
}

//This function switchs state from IDLE to SET_ALARM
void switchToSetAlarm(void)
{
    system_state = SETTING_ALARM;
    current_selection=SELECTION_START_ALARM;
    firstTime = 1;
    return;
}
//This function switchs state from IDLE to SET_DATE
void switchToSetDate(void)
{
    system_state = SETTING_DATE;
    current_selection = SELECTION_NONE;
    firstTime = 1;
    return;
}

//This function returns to IDLE state
void switchToIDLE(void)
{
    system_state = IDLE;
    firstTime = 1;
    return;
}

//This function switchs to IDLEActive state, which is a state where the buzzer is sounding
void switchToIDLEActive(void)
{
    system_state = IDLE_ACTIVE;
    firstTime = 1;
    return;
}

//This function renders the IDLE
void renderIDLE(void)
{
    uint8_t force = firstTime;
    if (firstTime)
    {
        GLCD_drawImage(0, 0, (uint8_t *)display, GLCD_WIDTH, GLCD_HEIGHT);
        firstTime = 0;
    }
    renderDate(force);
    renderTime(force);
    renderTemperatureAndHumidity(force);
}

void renderDate(uint8_t force)
{
    if (DS1307_dateEquals(&date, &date_old) && !force)
    {
        return; //no need to render
    }
    date_old = date;
    renderDay(date.day);
    sprintf(str, "%02d/%02d/%02d", date.date, date.month, date.year);
    GLCD_setXY(23, 3);
    GLCD_sendString(str);
}

void renderDay(uint8_t day)
{
    GLCD_setXY(23, 2);
    switch (day)
    {
    case MONDAY:
        GLCD_sendString("  LUNES  ");
        break;
    case TUESDAY:
        GLCD_sendString(" MARTES  ");
        break;
    case WEDNESDAY:
        GLCD_sendString("MIERCOLES");
        break;
    case THURSDAY:
        GLCD_sendString(" JUEVES  ");
        break;
    case FRIDAY:
        GLCD_sendString(" VIERNES ");
        break;
    case SATURDAY:
        GLCD_sendString(" SABADO  ");
        break;
    case SUNDAY:
        GLCD_sendString(" DOMINGO ");
        break;
    }
}
void updateTime()
{
    DS1307_get_time(&time);
}
void updateDate()
{
    DS1307_get_date(&date);
}

void renderTime(uint8_t force)
{
    if (DS1307_timeEquals(&time, &time_old) && !force)
    {
        return; //no need to render
    }
    time_old = time;
    sprintf(str, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
    GLCD_setXY(23, 4);
    GLCD_sendString(str);
}

void updateTemperatureAndHumidity(void)
{
    DHT22_GetTemp_Humidity(&temperature, &humidity);
}

void renderTemperatureAndHumidity(uint8_t force)
{
    sprintf(str, "%.2f*C", temperature);
    GLCD_setXY(3, 1);
    GLCD_sendString(str);
    sprintf(str, "%.1f%%H", humidity);
    GLCD_setXY(48, 1);
    GLCD_sendString(str);
}

//This function renders the IDLEActive
void renderIDLEActive(void)
{
    if (firstTime == 1)
    {
        GLCD_drawImage(0, 0, (uint8_t *)welcome_screen, GLCD_WIDTH, GLCD_HEIGHT);
        enableBuzzer();
        firstTime = 0;
    }
}

//This function renders the SET_DATE
void renderSetDate(void)
{
    uint8_t force = firstTime;
    if (firstTime)
    {
        GLCD_drawImage(0, 0, (uint8_t *)display, GLCD_WIDTH, GLCD_HEIGHT);
        firstTime = 0;
    }
    renderDate(force);
    renderTime(force); 
}

//This function renders the SET_ALARM
void renderSetAlarm(void)
{
    if (firstTime)
    {
        GLCD_drawImage(0, 0, (uint8_t *)display, GLCD_WIDTH, GLCD_HEIGHT);
        renderTime_alarm(1); //force render
        firstTime = 0;
        return;
    }
    renderTime_alarm(firstTime);
}

//This function disables the buzzer
void disableBuzzer(void)
{
    resetPB15();
}

//This function enables the buzzer
void enableBuzzer(void)
{
    setPB15();
}

//Functions for setting date and alarm

void writeDate(RTC_DATE_t date){
    DS1307_set_date(&date);
}


void writeTime(RTC_TIME_t timeR){
    DS1307_set_time(&timeR);
}

void modify_date(uint8_t selection, int8_t increment){
    switch (selection)
    {
    case SELECTION_YEAR:
        date.year += increment;
        if (date.year > 99)
            date.year = 0;
        break;
    case SELECTION_MONTH:
        date.month += increment;
        if (date.month > 12)
            date.month = 1;
        if (date.month < 1)
            date.month = 12;
        break;
    case SELECTION_DATE:
        date.date += increment;
        if (date.date > 31)
            date.year = 1;
        if (date.date < 1)
            date.date = 31;
        break;
    case SELECTION_DAY:
        date.day += increment;
        if (date.day > 6)
            date.day = 0;
        break;
    case SELECTION_HOUR:
        time.hours += increment;
        if (time.hours > 24)
            time.hours = 0;
        break;
    case SELECTION_MINUTE:
        time.minutes += increment;
        if (time.minutes > 60)
            time.minutes = 0;
        break;
    case SELECTION_SECOND:
        time.seconds += increment;
        if (time.seconds > 60)
            time.seconds = 0;
        break;
    default: break;
    }
    return;
}
void modify_alarm(uint8_t selection, int8_t increment){
    switch (selection)
    {
    case SELECTION_HOUR:
        time_alarm.hours += increment;
        if (time_alarm.hours > 24)
            time_alarm.hours = 0;
        break;
    case SELECTION_MINUTE:
        time_alarm.minutes += increment;
        if (time_alarm.minutes > 60)
            time_alarm.minutes = 0;
        break;
    case SELECTION_SECOND:
        time_alarm.seconds += increment;
        if (time_alarm.seconds > 60)
            time_alarm.seconds = 0;
        break;
    default: break;
    }
    return;
}
void renderTime_alarm(uint8_t force)
{
    if (DS1307_timeEquals(&time_alarm, &time_old) && !force)
    {
        return; //no need to render
    }
    time_old = time_alarm;
    sprintf(str, "%02d:%02d:%02d", time_alarm.hours, time_alarm.minutes, time_alarm.seconds);
    GLCD_setXY(23, 4);
    GLCD_sendString(str);
}

void animateCurrentSelection(void){
    GLCD_setXY(13,1);
    switch(current_selection){
        case SELECTION_YEAR:
            sprintf(str,"SEL A'O: %2d",date.year);
        break;
        case SELECTION_MONTH:
            sprintf(str,"SEL MES: %2d",date.month);
            //TODO: animate month
        break;
        case SELECTION_DATE:
            sprintf(str,"SEL DIA: %2d",date.date);
            //TODO: animate date
        break;
        case SELECTION_DAY:
            sprintf(str,"SEL: DIASEM");
            //TODO: animate day
        break;
        case SELECTION_HOUR:
            sprintf(str,"SEL HS: %2d ",time.hours);
            //TODO: animate hour
        break;
        case SELECTION_MINUTE:
            sprintf(str,"SEL MIN: %2d",time.minutes);
            //TODO: animate minute
        break;
        case SELECTION_SECOND:
            sprintf(str,"SEL SEG: %2d",time.seconds);
            //TODO: animate second
        break;
        case SELECTION_NONE:
            sprintf(str," SEL: NONE ");
        default: break;
    }
    GLCD_sendString(str);
}
void animateCurrentSelection_alarm(void){
    GLCD_setXY(13,1);
    switch(current_selection){
        case SELECTION_HOUR:
            sprintf(str,"SEL HS: %2d ",time_alarm.hours);
            //TODO: animate hour
        break;
        case SELECTION_MINUTE:
            sprintf(str,"SEL MIN: %2d",time_alarm.minutes);
            //TODO: animate minute
        break;
        case SELECTION_SECOND:
            sprintf(str,"SEL SEG: %2d",time_alarm.seconds);
            //TODO: animate second
        break;
        default: break;
    }
    GLCD_sendString(str);
}
