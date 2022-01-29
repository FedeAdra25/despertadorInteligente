/* Main.c file generated by New Project wizard
 *
 * Created:   vie. ene. 21 2022
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include "main.h"

static RTC_TIME_t time;
static RTC_DATE_t date;
static uint8_t * string_for_date;
static uint8_t * string_for_time;

void DS1307_ReadDate(uint8_t *);
void DS1307_ReadFullDate(uint8_t *data);
uint8_t bcd2int(uint8_t n);


void start_system()
{
	//Inicializacion del LCD
	LCDinit();
	DS1307_Init();

	//Enviar un string al LCD
	LCDstring("Hello Mundo!", 12);
}

void set_rtc()
{
	time.seconds = 0;
	time.minutes = 0;
	time.hours = 10;
	DS1307_set_time(&time);
	date.day = SATURDAY;
	date.date = 29;
	date.month = 1;
	date.year = 22;
	DS1307_set_date(&date);
}

void print_time(){
	DS1307_get_date(&date);
	DS1307_get_time(&time);
	LCDclr();
	LCDGotoXY(1, 0);
	string_for_time=DS1307_get_time_string(time);
	LCDstring(string_for_time, 9);
	LCDGotoXY(1, 1);
	string_for_date=DS1307_get_date_string(date);
	LCDstring(string_for_date, 9);
	free(string_for_time);
	free(string_for_date);
}

int main()
{

	// RCC first cuz simulation crashes otherwise :(
	RCC->APB2ENR |= 0xFC; //enable clock for GPIO

	start_system();
	set_rtc();
	print_time();
	while (1)
	{
		delay_ms(1000);
		print_time();
	}
	return 0;
}
