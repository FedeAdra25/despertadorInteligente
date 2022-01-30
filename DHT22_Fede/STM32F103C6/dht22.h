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
/*
//Change pin mode
static void ONE_WIRE_PinMode(OnePinMode_Typedef mode);
//One Wire pin HIGH/LOW Write
static void ONE_WIRE_Pin_Write(bool state);
static bool ONE_WIRE_Pin_Read(void);
//Microsecond delay
static void DelayMicroSeconds(uint32_t uSec);
//Begin function
static void DHT22_StartAcquisition(void);
//Read 5 bytes
static void DHT22_ReadRaw(uint8_t *data);

//Get Temperature and Humidity data
bool DHT22_GetTemp_Humidity(float *Temp, float *Humidity);
*/
#endif
