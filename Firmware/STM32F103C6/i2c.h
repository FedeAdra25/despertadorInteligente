#ifndef i2c_h
#define i2c_h

#include <stm32f103x6.h>
#include "utils.h"


#define I2C_SCL_PIN 6 //Pin de SCL
#define I2C_SDA_PIN 7 //Pin de SDA
#define I2C_DR GPIOB->ODR //Dirección del registro
#define I2C_DR_IN GPIOB->IDR //Dirección del registro de entrada


void I2C_Init(void);
void I2C_SendStart(void);
void I2C_SendStop(void);
unsigned char I2C_SendAddrForWrite(unsigned char);
unsigned char I2C_SendAddrForRead(unsigned char);
unsigned char I2C_SendData(unsigned char);
unsigned char I2C_ReadData(unsigned char);



#endif
