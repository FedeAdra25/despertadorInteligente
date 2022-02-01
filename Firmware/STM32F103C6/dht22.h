#ifndef DHT22_H
#define DHT22_H

#include <stm32f103x6.h>
#include "utils.h"
#ifndef DHT22_RESPONSE_TOLERANCE
#define DHT22_RESPONSE_TOLERANCE 1000000UL //at 72MHZ clock this is about 2ms
#endif

#define DHT22_DATA_PIN 15
#define DHT22_DATA_PORT GPIOA
#define DHT22_DR DHT22_DATA_PORT->ODR
#define DHT22_DR_IN DHT22_DATA_PORT->IDR



//*** Functions prototypes ***//
//OneWire Initialise
void DHT22_Init(void);

//Get Temperature and Humidity data
uint8_t DHT22_GetTemp_Humidity(float *, float *);

#endif
