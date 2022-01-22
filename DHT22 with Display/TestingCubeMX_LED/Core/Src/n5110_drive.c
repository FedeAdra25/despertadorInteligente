#include "systick_time.h"
#include "gp_drive.h" 
#include "SPI_drive.h"
#include "n5110_drive.h"
#include "stm32f1xx_hal.h"

/* Code for init of the N5110.
You MUST have the SPI init beforehand.
This is not tested for SPI2 but should work!*/
void n5110_init(unsigned short spi){
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
	

void n5110_clear(void){
	int j;
	n5110_pos(0,0);
	W_GP(PA,1,HIGH);
	
	for(j=0;j<504;j++){
		spi_tx(1,0x00);
	}
	
}
/* Function to clear the Buffer */
void n5110_clear_buffer(unsigned char screen_buffer[][84]){
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<64;j++){
			screen_buffer[i][j] = 0;
		}
	}
}


void n5110_print_buffer(unsigned char screen_buffer[][84]){
	n5110_clear();
	n5110_pos(0,0);
	
	int i,j;
	W_GP(PA,1,HIGH);
	for(i=0;i<6;i++){
		for(j=0;j<84;j++){
			spi_tx(1,screen_buffer[i][j]);
		}
	}
	W_GP(PA,1,LOW);

}


/* Function to update the Buffer*/
void n5110_update_buffer(ImgType img, unsigned short img_number, unsigned char screen_buffer[][84]){
	int x_dir, y_dir, x_end, y_end, counter;
	
	if( (img.w + img.x) > 84){
		x_end = 83;
	}else{
		x_end = img.w + img.x - 1;
	}
	
	if( (img.h + img.y) > 5){
		y_end = 5;
	}else{
		y_end = img.h + img.y - 1;
	}
	
	counter = 0;
	
	for(y_dir = img.y; y_dir <= y_end ; y_dir++){
		for(x_dir = img.x; x_dir <= x_end; x_dir++){
			/*Es una forma optimizada de acceder a las imagenes. */
			counter = (y_dir - img.y) * img.w + x_dir - img.x;
			screen_buffer[y_dir][x_dir] = img.image[img_number][counter];
		}
	}


}

void n5110_update_str_buffer(short y, short x,char str[], unsigned char screen_buffer[][84]){
	int i,j, cnt_col,cnt_row;
		
	cnt_col = x;
	cnt_row = y;
	i=0;
	
	while(str[i]){
		if(cnt_row > 5){ break;} //!!!!!!!!!
		for(j=0; j<5; j++){
			screen_buffer[cnt_row][cnt_col] = ASCII[str[i]-32][j];
			if ( (cnt_col + 1 ) > 83){
				if ( (cnt_row + 1) > 5 ){ break;}
				else{
					cnt_row++;
					cnt_col = x;	//Restart
				}
				
			}else{
				cnt_col++;
			}
			
		}
		i++;
	
	
	}


}