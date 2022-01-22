#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"
#include "stm32f1xx_hal.h"

/* Code for init of the N5110.
You MUST have the SPI init beforehand.
This is not tested for SPI2 but should work!*/
void n5110_init(unsigned short spi)
{
		/* DISPLAY CODE */
	init_GP(PA,0,OUT50,O_GP_PP);	//RST Pin Setup
	W_GP(PA,0,HIGH);							//Set RST HIGH
	//DelayMs(10);	
	HAL_Delay(10);								//10ms Delay
	W_GP(PA,0,LOW);								//Set RST LOW
	//DelayMs(10);
	HAL_Delay(10);
	W_GP(PA,0,HIGH);							//Set RST HIGH
	
	//Setup DC Pin and Set LOW
	init_GP(PA,1,OUT50,O_GP_PP);
	W_GP(PA,1,LOW);
	
	//Setup Screenlight Pin
	/*Proteus always shows the light on*/
	init_GP(PA,2,OUT50,O_GP_PP);
	init_GP(PA,1,OUT50,O_GP_PP);
	W_GP(PA,2,HIGH);
	HAL_Delay(1000);								//1s Delay
	W_GP(PA,2,LOW);
	

	
	//Init the LCD ITS A HOLE SEQUENCE
	spi_tx(spi,0x21);
	spi_tx(spi,0xC0);
	
	spi_tx(spi,0x20); //Basic Instruction Set
	spi_tx(spi,0x0C);

}


/* Code for printing a String in the Display
Send the X,Y Coordinates
the String and the SPI you're using
-Recommended to use SPI=1
*/
void n5110_print(short x, short y, char str[],unsigned short spi){
	
	/* Aux Variables */
	int i,j;
	i = 0;

	
	/* Clear the screen of n5110 */
	n5110_pos(0,0);				//Start Clearing from (0,0)
	W_GP(PA,1,HIGH);			//Display Control ON
	//48 * 84 = 4032 (48x84 Display)
	//4032 / 8 = 504
	for(j=0;j<504;j++){
			spi_tx(spi,0x00);
		}
	W_GP(PA,1,LOW);			//Display Control OFF
	
	
	
	/* Write String to n5110 */
	
	n5110_pos(x,y);				//SET the position to start writing
		
	W_GP(PA,1,HIGH);			//Display Control ON
	while(str[i]){
		for(j=0;j<5;j++){
			
			spi_tx(spi,ASCII[str[i]-32][j]);	
			//El -32 era porque vos mandabas un Char y lo formatea
			//a HEXA, y con -32 lo ponias en decimal o algo asi. Revisa
			//Igual anda
		}
		i++;
	}
	W_GP(PA,1,LOW);			//Display Control OFF
}




/* This is kind of provided by the Display.
You can check the datasheet
'Set Y address of RAM'
'Set X address of RAM'
*/
void n5110_pos(short x, short y){
	
	W_GP(PA,1,LOW);			//Display Control OFF (Just in case)
	
	spi_tx(1,0x20);
	spi_tx(1,(0x40 | y));
	spi_tx(1,(0x80 | x));
	
	

}
	
