#include "stm32f10x.h" 
#include "gp_drive.h" 
#include "SPI_drive.h"

void spi_init(unsigned short spi){
RCC->APB2ENR |= 1; //Enable AFIO function

if(spi ==1)
{
	/* SPI1 PINS SETUP CODE*/
	RCC->APB2ENR |= 1; //Enable AFIO function
	RCC->APB2ENR |= 0x1000; // Enabling the SPI-1 periph
	
	/* PINS SETUP */
	init_GP(PA,4,OUT50,O_GP_PP);
	init_GP(PA,5,OUT50,O_AF_PP);
	init_GP(PA,6,IN,I_PP);
	init_GP(PA,7,OUT50,O_AF_PP);
	
	/* SPI1 PERIPHERAL SETUP CODE*/
	SPI1->CR1 |= 0x4;	 // Master Mode
	SPI1->CR1 |= 0x38; // Fclock / 256
	SPI1->CR2 |= 0x4;		
	SPI1->CR1 |= 0x40; // Enabling SPI peripheral
	
	/* PIN PA4 HIGH*/
	W_GP(PA,4,HIGH);
	
}else if(spi == 2){
	
	/* SPI2 PINS SETUP CODE*/
	RCC->APB1ENR |= 0x4000; // Enabling the SPI-2 periph
	
	/* PINS SETUP */
	init_GP(PB,12,OUT50,O_GP_PP);
	init_GP(PB,13,OUT50,O_AF_PP);
	init_GP(PB,14,IN,I_PP);
	init_GP(PB,15,OUT50,O_AF_PP);

	/* SPI1 PERIPHERAL SETUP CODE*/
	SPI2->CR1 |= 0x4; 	// Master Mode
	SPI2->CR1 |= 0x38; 	// Fclock / 256
	SPI2->CR2 |= 0x4;		// SSOE Enabled
	SPI2->CR1 |= 0x40;	// Enabling SPI peripheral
	W_GP(PB,12,HIGH);
}
	
	

}


/* Transmission of a Single Character by SPI 
	spi -> 1 or 2
	tx_char -> Char Data
*/
void spi_tx(unsigned short spi, char tx_char)
{
	if (spi ==1 )
	{
		/* SPI1 SEND CHAR */
		W_GP(PA,4,LOW);
		SPI1->DR = tx_char;
		while(SPI1->SR & 0x80){}
		W_GP(PA,4,HIGH);
	}else if (spi ==2 )
	{
		/* SPI2 SEND CHAR */
		W_GP(PB,12,LOW);
		SPI2->DR = tx_char;
		while(SPI2->SR & 0x80){}
		W_GP(PB,12,HIGH);
	}
}

/* Transmission of a String by SPI 
	spi -> 1 or 2
	str -> String Data
*/
void spi_msg(unsigned short spi, char str[])
{
int i =0;
	if (spi==1){
		/* SPI1 SEND STRING */
		W_GP(PA,4,LOW);
		while(str[i]){
			SPI1->DR = str[i];
			while(SPI1->SR & 0x80){}
			i++;
		}
		W_GP(PA,4,HIGH);
	}
	else if (spi==2){
		/* SPI2 SEND STRING */
		W_GP(PB,12,LOW);
		while(str[i]){
			SPI2->DR = str[i];
			while(SPI2->SR & 0x80){}
			i++;
		}
		W_GP(PB,12,HIGH);
	}
}