/*
Actual setup
SPI - 1
--> 
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI

SPI2 - 2
PB12 --> SS
PB13 --> SCLK
PB14 --> MISO
PB15 --> MOSI
*/
#ifndef SPI_DRIVE_H
#define SPI_DRIVE_H

#include <stm32f103x6.h>

#define SPI1_SS 4
#define SPI1_SCLK 5
#define SPI1_MISO 6
#define SPI1_MOSI 7

void spi_init(void);
void spi_tx(uint8_t tx_char);
void spi_tx_msg(const uint8_t* str,uint8_t);

#endif
