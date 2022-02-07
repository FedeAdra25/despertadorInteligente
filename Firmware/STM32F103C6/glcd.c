#include "glcd.h"

#define GLCD_clear_CS() {GPIOA->BRR = (1 << GLCD_CS);}
#define GLCD_set_CS() {GPIOA->BSRR = (1 << GLCD_CS);}
#define GLCD_clear_DC() {GPIOA->BRR = (1 << GLCD_DC);}
#define GLCD_set_DC() {GPIOA->BSRR = (1 << GLCD_DC);}
#define GLCD_clear_RST() {GPIOA->BRR = (1 << GLCD_RST);}
#define GLCD_set_RST() {GPIOA->BSRR = (1 << GLCD_RST);}

/*Private functions prototyps*/
void glcd_sendCommand(uint8_t);
void glcd_sendData(uint8_t);

/*Private variables*/
static uint8_t glcd_x = 0;
static uint8_t glcd_y = 0;
//this matrix is used to store the data of the screen
static uint8_t glcd_current_state[GLCD_HEIGHT][GLCD_WIDTH];

/* Code for init of the Graphic LCD N5110.
It depends on the SPI_drive.h files.
This is not tested for SPI2 but should work with some minor changes!*/
void GLCD_Init(){
	
	/* DISPLAY CODE */
	RCC->APB2ENR |= 0x4; //Activate GPIOA clock in case it is not activated
	spi_init();
	//MOSI PA7 and SCK as Alternate Function push-pull
	//CE, RESET, D/C as GPIO push-pull 50MHz
	
	//DISPLAY_PORT_CONFIG = (0x0000000B<<(4*GLCD_DIN) | 0x0000000B << (4*GLCD_SCK) | 0x00000003 << (4*GLCD_CS) | 0x00000003 << (4*GLCD_RST) | 0x00000003 << (4*GLCD_DC));
	DISPLAY_PORT_CONFIG = 0xB2B34433;


	//Set rst pin in case it was not already set
	GLCD_set_RST();
	delay_ms(10);
	//Reset display (maximum 100ms after power or else it may get damaged)
	GLCD_clear_RST();
	delay_ms(100); //100ns is enough acording to the datasheet
	GLCD_set_RST();
	
	GLCD_clear_DC();
	
	//Setup Screenlight Pin
	/*Proteus always shows the light on*/
	/* IDK
	init_GP(PA,2,OUT50,O_GP_PP);
	init_GP(PA,1,OUT50,O_GP_PP);
	W_GP(PA,2,HIGH);
	delay_ms(1000);								//1s Delay
	W_GP(PA,2,LOW);
	*/

	
	//Init the LCD ITS A HOLE SEQUENCE
	glcd_sendCommand(0x21); //Switch to extended mode
	glcd_sendCommand(0x84); //Set LCD Vop to 3.3V
	
	glcd_sendCommand(0x20); //Switch to basic instruction set
	glcd_sendCommand(0x0C); //Set normal display mode
	GLCD_clean();
}

/*
Send command function
*/
void glcd_sendCommand(uint8_t command){
	GLCD_clear_DC();
	spi_tx(command);
}

//Sends data (writes 8 pixels)
void glcd_sendData(uint8_t data){
	GLCD_set_DC();
	spi_tx(data);
}

//Sends Character (writes 8*5 pixels)
void GLCD_sendChar(char character){
	uint8_t i;
	if(glcd_x>GLCD_WIDTH-5) //will overflow, don't write
		return;
	GLCD_set_DC();
	spi_tx_msg(ASCII[character-32],5);
	for(i=0;i<5;i++){ //update the current state
		glcd_current_state[glcd_y][glcd_x+i] = ASCII[character-32][i];
	}
	glcd_x += 5; //update the x position
}

//Prints string finished with '\0' on the screen
void GLCD_sendString(char* string){
	int i = 0;
	while(string[i] != '\0'){
		GLCD_sendChar(string[i]);
		i++;
	}
}

/*
Sets X and Y coordinates
X is between 0 and 83
Y is between 0 and 5
*/
void GLCD_setXY(uint8_t x, uint8_t y){
	if(x>GLCD_WIDTH-1 || y>GLCD_HEIGHT-1){
		return;
	}
	glcd_sendCommand(0x40 | y); //Set Y address (1 in DB6)
	glcd_sendCommand(0x80 | x); //Set X address
	glcd_x = x;
	glcd_y = y;
}

//Cleans glcd then sets X and Y to 0
void GLCD_clean(void){
	int i,j;
	GLCD_setXY(0,0);
	for(i=0;i<GLCD_HEIGHT;i++){
		for(j=0;j<GLCD_WIDTH;j++){
			glcd_current_state[i][j] = 0;
			glcd_sendData(0x75);
			delay_us(1);
		}
	}
	GLCD_setXY(0,0);
}

/*
Draws an image at given coordinates
Image is an array of uint8_t of size width*height
You must specify the width and height of the image
*/
void GLCD_drawImage(uint8_t x, uint8_t y, uint8_t* image, uint8_t width, uint8_t height){
	int i,j;
	GLCD_setXY(x,y);
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			glcd_current_state[y+i][x+j] = image[i*width+j];
			glcd_sendData(image[i*width+j]);
		}
	}
	glcd_x=x+width;
	glcd_y=y+height;
}

/*
Draws an image at given coordinates
Image is an array of uint8_t of size width*height
You must specify the width and height of the image
*/
void GLCD_drawImageNonDestructive(uint8_t x, uint8_t y, uint8_t* image, uint8_t width, uint8_t height){
	int i,j;
	GLCD_setXY(x,y);
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			glcd_current_state[y+i][x+j] |= image[i*width+j];
			glcd_sendData(image[i*width+j]|glcd_current_state[y+i][x+j]);
		}
	}
	glcd_x=x+width;
	glcd_y=y+height;
}
