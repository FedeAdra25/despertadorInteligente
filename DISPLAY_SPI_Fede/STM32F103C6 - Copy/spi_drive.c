//#include "stm32f10x.h"
#include "stm32f1xx.h"
#include "gp_drive.h"
#include "spi_drive.h"

#define spi_set_ss() {GPIOA->BSRR = (1 << SPI1_SS);}
#define spi_clear_ss() {GPIOA->BRR = (1 << SPI1_SS);}

void spi_init()
{
	RCC->APB2ENR |= 1; //Enable AFIO function
	/* SPI1 PINS SETUP CODE*/
	RCC->APB2ENR |= 0x1000; // Enabling the SPI1 periph

	/* PINS SETUP */
	GPIOA->CRL = 0xB2B34444; //PA7 - DIN | PA6 - DOUT | PA5 - CLK | PA4 - NSS

	/* SPI1 PERIPHERAL SETUP CODE*/
	//SPI1 enabled, Master mode, BR = 36MHz/16 = 2.25MHz (GLCD supports up to 4MHz)
	SPI1->CR1 = (1<<2) | (0x18) | (1<<6); 
	SPI1->CR2 |= 0x4; //SSOE = 1 (SS output enabled)
	/* SS HIGH */
	spi_set_ss();
}

/* Transmission of a Single Character by SPI 
	spi -> 1 or 2
	tx_char -> Char Data
*/
void spi_tx(uint8_t tx_char)
{
	/* SPI1 SEND CHAR */
	spi_clear_ss(); //CS to low
	SPI1->DR = tx_char; //Data register set
	while ((SPI1->SR & (1<<0))==0); //Wait until RXNE is set
	spi_set_ss();
}

/* Transmission of a String of databy SPI 
	str -> String Data
*/
void spi_tx_msg(const uint8_t* str,uint8_t size)
{
	uint8_t i=0;
	/* SPI1 SEND STRING */
	spi_clear_ss(); //CS to low
	while (i++<size || str)
	{
		SPI1->DR = *str;
		//while (SPI1->SR & 0x80); //wait for BSY to be cleared
		while ((SPI1->SR & (1<<0))==0); //Wait until RXNE is set
		str++;
	}
	spi_set_ss();
}