/**
 * @file ds1307.h
 * RTC DS1307 driver implemented in 24h format. Using I2C protocol.
 * 
 * 
 * 
 */

#ifndef ds1307_h
#define ds1307_h
#include <stm32f103x6.h>

#include "i2c.h"

#define DS1307_ADDRESS 0x68 // 7 bit address (add )
#define DS1307_SECONDS_REGISTER 0x00
#define DS1307_MINUTES_REGISTER 0x01
#define DS1307_HOURS_REGISTER 0x02
#define DS1307_DAY_REGISTER 0x03
#define DS1307_DATE_REGISTER 0x04
#define DS1307_MONTH_REGISTER 0x05
#define DS1307_YEAR_REGISTER 0x06
#define DS1307_CONTROL_REGISTER 0x07

#define MONDAY 0
#define TUESDAY 1
#define WEDNESDAY 2 
#define THURSDAY 3
#define FRIDAY 4
#define SATURDAY 5
#define SUNDAY 6


typedef struct{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
}RTC_TIME_t;

typedef struct{
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
}RTC_DATE_t;


void DS1307_Init(void);
void DS1307_set_time(RTC_TIME_t *time);
void DS1307_get_time(RTC_TIME_t *time);
void DS1307_set_date(RTC_DATE_t *date);
void DS1307_get_date(RTC_DATE_t *date);
void DS1307_set_full_time(RTC_TIME_t *time, RTC_DATE_t *date);
uint8_t * DS1307_get_time_string(RTC_TIME_t time);
uint8_t * DS1307_get_date_string(RTC_DATE_t date);
uint8_t * DS1307_get_date_string_with_day(RTC_DATE_t date);



#endif
