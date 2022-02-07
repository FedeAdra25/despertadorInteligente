#include "ds1307.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void DS1307_config(void);
static uint8_t bcd2int(uint8_t);
static uint8_t int2bcd(uint8_t);
static uint8_t* day2string(uint8_t);


void DS1307_Init(void)
{
    I2C_Init();
    DS1307_config();
}

void DS1307_set_full_time(RTC_TIME_t *time, RTC_DATE_t *date)
{
    DS1307_set_date(date);
    DS1307_set_time(time);
}

void DS1307_set_time(RTC_TIME_t *time)
{
    do
	{
	    I2C_SendStart();					   /* generate a start condition */
	} while (I2C_SendAddrForWrite(0x68) == 0); /* repeat if returned false */

	I2C_SendData(0x0);	/* set addr. pointer to 0 */
	I2C_SendData(int2bcd(time->seconds) & 0x7F); /* seconds without 7th bit */
	I2C_SendData(int2bcd(time->minutes)); /* min */
	I2C_SendData(int2bcd(time->hours)); /* hour in 24-h format*/
}

void DS1307_get_time(RTC_TIME_t *time)
{
    if (time == 0)
        return;

    do
    {
        I2C_SendStart();                       /* generate a start condition */
    } while (I2C_SendAddrForWrite(0x68) == 0); /* repeat if returned false */

    I2C_SendData(0x00); /* set addr. pointer to 0 */

    do
    {
        I2C_SendStart();                      /* generate a REPEATED START condition */
    } while (I2C_SendAddrForRead(0x68) == 0); /* repeat if returned false */

    time->seconds = bcd2int(I2C_ReadData(0));
    time->minutes = bcd2int(I2C_ReadData(0));
    //Clean hours 6th bit by masking it
    time->hours = bcd2int(I2C_ReadData(1) & 0xBF); //send nack

    I2C_SendStop(); /* generate a stop condition */
}

void DS1307_set_date(RTC_DATE_t *date)
{
    do
	{
	    I2C_SendStart();					   /* generate a start condition */
	} while (I2C_SendAddrForWrite(0x68) == 0); /* repeat if returned false */

	I2C_SendData(0x0);	/* set addr. pointer to 0 */
	I2C_SendData(int2bcd(date->day)); /* day of week */
	I2C_SendData(int2bcd(date->date)); /* day of month */
	I2C_SendData(int2bcd(date->month)); /* month */
	I2C_SendData(int2bcd(date->year)); /* year */
	I2C_SendStop(); /* generate a stop condition */
}

void DS1307_get_date(RTC_DATE_t *date)
{
    if (date == 0)
        return;

    do
    {
        I2C_SendStart();                       /* generate a start condition */
    } while (I2C_SendAddrForWrite(0x68) == 0); /* repeat if returned false */

    I2C_SendData(0x03); /* set addr. pointer to 0 */

    do
    {
        I2C_SendStart();                      /* generate a REPEATED START condition */
    } while (I2C_SendAddrForRead(0x68) == 0); /* repeat if returned false */

    date->day = bcd2int(I2C_ReadData(0));
    date->date = bcd2int(I2C_ReadData(0));
    date->month = bcd2int(I2C_ReadData(0));
    date->year = bcd2int(I2C_ReadData(1));

    I2C_SendStop(); /* generate a stop condition */
}

uint8_t * DS1307_get_time_string(RTC_TIME_t time){
    uint8_t *time_string = (uint8_t *) malloc(sizeof(uint8_t) * 6);
    if (time_string == 0)
        return 0;
    sprintf((char*)time_string, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
    return time_string;
    
}
uint8_t * DS1307_get_date_string(RTC_DATE_t date){
    uint8_t *date_string = (uint8_t *) malloc(sizeof(uint8_t) * 11);
    if (date_string == 0)
        return 0;
    
    sprintf((char*)date_string, "%02d/%02d/%02d", date.date, date.month, date.year);
    return date_string;
}
uint8_t * DS1307_get_date_string_with_day(RTC_DATE_t date){
    uint8_t *date_string = (uint8_t *) malloc(sizeof(uint8_t) * 11);
    uint8_t *day = day2string(date.day);
    if (date_string == 0)
        return 0;
    sprintf((char *)date_string, "%s %s", day, DS1307_get_date_string(date));
    free(day);
    return date_string;
}


//private functions
static void DS1307_config(){
    do
	{
		I2C_SendStart();					   /* generate a start condition */
	} while (I2C_SendAddrForWrite(0x68) == 0); /* repeat if returned false */

	I2C_SendData(0x0);	/* set addr. pointer to 0 */
	I2C_SendData(0x00); /* second */
	I2C_SendData(0x00); /* min */
	I2C_SendData(0x40); /* hour in 24-h format*/
	I2C_SendData(MONDAY); /* day of week */
	I2C_SendData(0x14); /* day of month */
	I2C_SendData(0x02); /* month */
	I2C_SendData(0x22); /* year */
	I2C_SendStop(); /* generate a stop condition */
}

void DS1307_get_full_time(RTC_TIME_t *time, RTC_DATE_t *date)
{

	if (date == NULL || time == NULL)
		return;

    DS1307_get_date(date);
    DS1307_get_time(time);
}
/* The function gets a BCD number and converts it to binary */
static uint8_t bcd2int(uint8_t n)
{
	return ((n & 0xF0) >> 4) * 10 + (n & 0x0F);
}
static uint8_t int2bcd(uint8_t n)
{
    return ((n / 10) << 4) + (n % 10);
}

static uint8_t* day2string(uint8_t day_r){
    uint8_t * day = (uint8_t *) malloc(sizeof(uint8_t) * 3);
    switch(day_r){
        case MONDAY:
            strcpy((char*)day, "LUN");
            break;
        case TUESDAY:
            strcpy((char*)day, "MAR");
            break;
        case WEDNESDAY:
            strcpy((char*)day, "MIE");
            break;
        case THURSDAY:
            strcpy((char*)day, "JUE");
            break;
        case FRIDAY:
            strcpy((char*)day, "VIE");
            break;
        case SATURDAY:
            strcpy((char*)day, "SAB");
            break;
        case SUNDAY:
            strcpy((char*)day, "DOM");
            break;
        default:
            strcpy((char*)day, "ERR");
            break;
    }
    return day;
}
uint8_t DS1307_dateEquals(RTC_DATE_t *date1, RTC_DATE_t *date2){
    return (date1->day == date2->day && date1->date == date2->date && date1->month == date2->month && date1->year == date2->year);
}
uint8_t DS1307_timeEquals(RTC_TIME_t *time1, RTC_TIME_t *time2){
    return (time1->hours == time2->hours && time1->minutes == time2->minutes && time1->seconds == time2->seconds);
}

void DS1307_copyTime(RTC_TIME_t *dest, RTC_TIME_t *src){
    dest->hours = src->hours;
    dest->minutes = src->minutes;
    dest->seconds = src->seconds;
}
void DS1307_copyDate(RTC_DATE_t *dest, RTC_DATE_t *src){
    dest->day = src->day;
    dest->date = src->date;
    dest->month = src->month;
    dest->year = src->year;
}

