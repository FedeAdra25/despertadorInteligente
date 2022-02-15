#include <utils.h>


static unsigned long ms_delay_const = CONST_FOR_MS_DELAY ; 
static unsigned long us_delay_const = CONST_FOR_US_DELAY;

void delay_us(unsigned long amount){
	unsigned long i,l;
	for(i=0;i<amount;i++)
		for(l=0;l<us_delay_const;l++);
}

void delay_ms(unsigned long amount){
	unsigned long i,l;
	for(i=0;i<amount;i++)
		for(l=0;l<ms_delay_const;l++);
}


