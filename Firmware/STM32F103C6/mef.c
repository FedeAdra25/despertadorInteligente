#include "mef.h"


static uint8_t buttonPressed=0;
static uint8_t firstTime = 1; //first time bit to avoid rendering stuff more than once
static MEF_state system_state;
static RTC_TIME_t time,time_old;
static RTC_DATE_t date,date_old;
static float temperature,humidity;
static char str[100];


//private functions (not static because proteus breaks)
void switchToSetAlarm(void);
void switchToSetDate(void);
void switchToIDLE(void);
void switchToIDLEActive(void);

void renderIDLE(void);
void renderIDLEActive(void);
void renderSetDate(void);
void renderSetAlarm(void);

void disableBuzzer(void);
void enableBuzzer(void);

void renderDay(uint8_t day);
void renderDate(uint8_t);
void renderTime(uint8_t);
void renderTemperatureAndHumidity(uint8_t);



//TODO: ver de mover esto a una librería
static uint8_t GPIOS_getButtonPressed(void);
#define BUTTON_NONE 0
#define BUTTON_OK 1
#define BUTTON_CANCEL 2
#define BUTTON_UP 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_RIGHT 6
#define getPB8() (GPIOB->IDR & (1<<8))
#define getPB9() (GPIOB->IDR & (1<<9))
#define getPB10() (GPIOB->IDR & (1<<10))
#define getPB11() (GPIOB->IDR & (1<<11))
#define getPB12() (GPIOB->IDR & (1<<12))
#define getPB13() (GPIOB->IDR & (1<<13))
#define setPB15() {GPIOB->ODR |= (1<<15);}
#define resetPB15() {GPIOB->ODR &= ~(1<<15);}
//---


void MEF_Init(void){
    system_state=IDLE_ACTIVE;
    //TODO move this logic to a library
    //WARNING: this SETS gpiob CRL register, so it must be called before any other GPIO init
    GPIOB->CRH = 0x34888888; //PB8,9,10,11,12,13 as input with pull-up
    //---                   PB15 as output with push-pull (1100)
}

void MEF_Update (void)
{
    buttonPressed = GPIOS_getButtonPressed();
    switch(system_state){
        case IDLE:
            renderIDLE();
            if(buttonPressed==BUTTON_NONE)
                return;
            if(buttonPressed==BUTTON_UP){
                switchToSetAlarm();
                return;
            }
            if(buttonPressed==BUTTON_DOWN){
                switchToSetDate();
                return;
            }
            if(buttonPressed==BUTTON_RIGHT){
                switchToIDLEActive();
            }
            
        break;
        case IDLE_ACTIVE:
            renderIDLEActive();
            if(buttonPressed==BUTTON_NONE)
                return;
            
            disableBuzzer(); //first disable buzzer
            switchToIDLE(); //then switch to idle
            /*xd*/
        break;
        case SETTING_DATE:
            renderSetDate();
            if(buttonPressed==BUTTON_NONE)
                return;
            if(buttonPressed==BUTTON_CANCEL){
                switchToIDLE();
                return;
            }
            /*TODO*/
        break;
        case SETTING_ALARM:
            renderSetAlarm();
            if(buttonPressed==BUTTON_NONE)
                return;
            if(buttonPressed==BUTTON_CANCEL){
                switchToIDLE();
                return;
            }
            /*TODO*/
        break;
    }
}



//RETURNS BUTTON_MENU or BUTTON_SELECT
static uint8_t GPIOS_getButtonPressed(void){
    //TODO: ver de mover esto a una librería
    //Also, order of this ifs matters. CANCEL has priority
    if(getPB9()!=0){
        return BUTTON_CANCEL;
    }
    if(getPB8()!=0){
        return BUTTON_OK;
    }
    if(getPB10()!=0){
        return BUTTON_UP;
    }
    if(getPB11()!=0){
        return BUTTON_DOWN;
    }
    if(getPB12()!=0){
        return BUTTON_LEFT;
    }
    if(getPB13()!=0){
        return BUTTON_RIGHT;
    }
    return BUTTON_NONE;
}

//This function switchs state from IDLE to SET_ALARM
void switchToSetAlarm(void){
    system_state=SETTING_ALARM;
    firstTime=1;
    return;
}
//This function switchs state from IDLE to SET_DATE
void switchToSetDate(void){
    system_state=SETTING_DATE;
    firstTime=1;
    return;
}

//This function returns to IDLE state
void switchToIDLE(void){
    system_state=IDLE;
    firstTime=1;
    return;
}

//This function switchs to IDLEActive state, which is a state where the buzzer is sounding
void switchToIDLEActive(void){
    system_state=IDLE_ACTIVE;
    firstTime=1;
    return;
}

//This function renders the IDLE
void renderIDLE(void){
    uint8_t force = firstTime;
    if(firstTime){
        GLCD_drawImage(0,0,(uint8_t *)display,GLCD_WIDTH,GLCD_HEIGHT);
        firstTime=0;
    }
    renderDate(force);
    renderTime(force);
    renderTemperatureAndHumidity(force);
}

void renderDate(uint8_t force){
    DS1307_get_date(&date);
    if(DS1307_dateEquals(&date,&date_old) && !force){
        return; //no need to render
    }
    date_old=date;
    renderDay(date.day);
    sprintf(str,"%02d/%02d/%02d",date.date,date.month,date.year);
    GLCD_setXY(25,3);
    GLCD_sendString(str);
}

void renderDay(uint8_t day){
    GLCD_setXY(24,2);
    switch(day){
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
            GLCD_sendString("  JUEVES  ");
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

void renderTime(uint8_t force){
    DS1307_get_time(&time);
    if(DS1307_timeEquals(&time,&time_old) && !force){
        return; //no need to render
    }
    time_old=time;
    sprintf(str,"%02d:%02d:%02d",time.hours,time.minutes,time.seconds);
    GLCD_setXY(25,4);
    GLCD_sendString(str);
}

void renderTemperatureAndHumidity(uint8_t force){
    DHT22_GetTemp_Humidity(&temperature,&humidity);
    sprintf(str,"%.2f*C",temperature);
    GLCD_setXY(3,1);
    GLCD_sendString(str);
    sprintf(str,"%.1f%%H",humidity);
    GLCD_setXY(50,1);
    GLCD_sendString(str);

}

//This function renders the IDLEActive
void renderIDLEActive(void){
    if(firstTime==1){
        GLCD_drawImage(0,0,(uint8_t *)welcome_screen,GLCD_WIDTH,GLCD_HEIGHT);
        enableBuzzer();
        firstTime=0;
    }
}

//This function renders the SET_DATE
void renderSetDate(void){
    if(firstTime){
        GLCD_drawImage(0,0,(uint8_t *)display,GLCD_WIDTH,GLCD_HEIGHT);
        firstTime=0;
    }
    renderDate(0);
    renderTime(0);
}

//This function renders the SET_ALARM
void renderSetAlarm(void){
    if(firstTime){
        GLCD_drawImage(0,0,(uint8_t *)display,GLCD_WIDTH,GLCD_HEIGHT);
        firstTime=0;
    }
    renderTime(0);
}


//This function disables the buzzer
void disableBuzzer(void){
    resetPB15();
}

//This function enables the buzzer
void enableBuzzer(void){
    setPB15();
}
