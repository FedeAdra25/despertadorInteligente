#ifndef N5510_DRIVE_H
#define N5510_DRIVE_H



/*MACROS (change for port)*/
#define DISPLAY_PORT GPIOA
#define DISPLAY_PORT_DR GPIOA->ODR
#define DISPLAY_PORT_CONFIG GPIOA->CRL




/* Function Headers */

void n5110_init(unsigned short spi);
void n5110_print(short x, short y, char str[],unsigned short spi);
void n5110_pos(short x, short y);


/* Estructura para las imagenes */
typedef struct State {
	
	/* Height and Weight*/
	unsigned short h;
	unsigned short w;
	
	/* Coordenadas X e Y */
	unsigned short x;	
	unsigned short y;
	
	//Pueden ser los que quieras, puse 20 por poner
	const unsigned char *image[20];	
	
} ImgType;

void n5110_print_buffer(unsigned char screen_buffer[][84]);
void n5110_clear_buffer(unsigned char screen_buffer[][84]);
void n5110_clear(void);

void n5110_update_buffer(ImgType img, unsigned short img_number, unsigned char screen_buffer[][84]);
void n5110_update_str_buffer(short y, short x,char str[], unsigned char screen_buffer[][84]);

/* https://playground.arduino.cc/Code/PCD8544/ 
Changed byte to Char for C code.
*/
static const char ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c �
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};

/* IMAGE TYPE DECLARATIONS.
THIS DATA IS PROVIDED BY A PYTHON SCRYPT*/


/* IMAGE DATA provided by a python Script*/

/* WELCOME SCREEN UNLP */
static unsigned short welcome_screen_rows = 6;
static unsigned short welcome_screen_cols = 84;
static unsigned char welcome_screen[] = 
{
0xff,0x1,0xfd,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0xd5,0xd5,0xd5,0xd5,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0x7d,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xf5,0xd5,0xd5,0xd5,0xd5,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0xfd,0x1,0xff,
0xff,0x0,0xff,0x55,0x55,0xd5,0xd5,0xf5,0xf5,0xfd,0xfd,0xfd,0x7f,0x7f,0x3f,0x1f,0x1f,0xf,0xf,0x7,0x7,0x3,0x3,0x3,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,0x3,0x3,0x3,0x7,0x7,0xf,0xf,0x1f,0x1f,0x3f,0x3f,0x7f,0xfd,0xfd,0xfd,0xf5,0xf5,0xd5,0xd5,0x55,0x55,0xff,0x0,0xff,
0xff,0x0,0xff,0xfd,0xff,0xff,0xff,0x1f,0xf,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0xfc,0x0,0x0,0xfc,0xfc,0xc,0x78,0xe0,0x80,0x0,0x0,0xfc,0xfc,0x0,0x0,0xfc,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0xfc,0x4,0x4,0x4,0x8c,0xf8,0x70,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0xf,0x1f,0xff,0xff,0xff,0xfd,0xff,0x0,0xff,
0xff,0x0,0xff,0xbf,0xff,0xff,0xff,0xf8,0xf0,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x1f,0x30,0x20,0x20,0x20,0x20,0x30,0x1f,0xf,0x0,0x0,0x3f,0x3f,0x0,0x0,0x1,0x7,0x1e,0x30,0x3f,0x3f,0x0,0x0,0x3f,0x3f,0x20,0x20,0x20,0x20,0x20,0x0,0x3f,0x3f,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xe0,0xf8,0xff,0xff,0xff,0xbf,0xff,0x0,0xff,
0xff,0x0,0xff,0xaa,0xaa,0xab,0xab,0xaf,0xaf,0xbf,0xbf,0xbf,0xfe,0xfc,0xfc,0xf8,0xf0,0xf0,0xf0,0xe0,0xe0,0xc0,0xc2,0xc2,0x82,0x82,0x82,0x82,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x82,0x82,0x82,0x82,0xc2,0xc2,0xc0,0xe0,0xe0,0xf0,0xf0,0xf0,0xf8,0xfc,0xfc,0xfe,0xbf,0xbf,0xbf,0xaf,0xaf,0xab,0xab,0xaa,0xaa,0xff,0x0,0xff,
0xff,0x80,0xbf,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xab,0xab,0xab,0xab,0xab,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xbf,0xbf,0xbf,0xbf,0xbf,0xbf,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbe,0xbf,0xbf,0xbf,0xbf,0xbf,0xbf,0xbf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xab,0xab,0xab,0xab,0xab,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xbf,0x80,0xff
};

/* Default NO-DAY-SELECTED Display */
static unsigned short display_rows = 6;
static unsigned short display_cols = 84;
static unsigned char display[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* LUNES */
static unsigned short display_lunes_rows = 6;
static unsigned short display_lunes_cols = 84;
static unsigned char display_lunes[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xab,0xaa,0xaa,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* MARTES */
static unsigned short display_martes_rows = 6;
static unsigned short display_martes_cols = 84;
static unsigned char display_martes[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xab,0xa8,0xa8,0xa8,0xab,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* MIERCOLES */
static unsigned short display_miercoles_rows = 6;
static unsigned short display_miercoles_cols = 84;
static unsigned char display_miercoles[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xab,0xa8,0xa8,0xa8,0xab,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* JUEVES */
static unsigned short display_jueves_rows = 6;
static unsigned short display_jueves_cols = 84;
static unsigned char display_jueves[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xab,0xaa,0xaa,0xab,0xa8,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* VIERNES */
static unsigned short display_viernes_rows = 6;
static unsigned short display_viernes_cols = 84;
static unsigned char display_viernes[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa8,0xa9,0xab,0xa9,0xa8,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* SABADO */
static unsigned short display_sabado_rows = 6;
static unsigned short display_sabado_cols = 84;
static unsigned char display_sabado[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xaa,0xaa,0xaa,0xab,0xa0,0xa3,0xa2,0xa3,0xa1,0xa0,0xbf,0x80,0xff
};

/* DOMINGO */
static unsigned short display_domingo_rows = 6;
static unsigned short display_domingo_cols = 84;
static unsigned char display_domingo[] = 
{
0xff,0x1,0xfd,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0x5,0xfd,0x1,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,
0xff,0x0,0xff,0x0,0xe0,0x0,0x0,0xe0,0x0,0xe0,0xe0,0x80,0x0,0xe0,0x0,0xe0,0x0,0x0,0x0,0xe0,0xa0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xe0,0x60,0xc0,0x60,0xe0,0x0,0xa0,0x20,0x20,0xe0,0x20,0x0,0xe0,0x80,0x0,0x80,0xe0,0x0,0xe0,0xa0,0xa0,0xa0,0x0,0xe0,0x60,0xc0,0x80,0x0,0xff,0x0,0xff,
0xff,0x80,0xbf,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa3,0xa0,0xa1,0xa3,0xa3,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa3,0xa2,0xa2,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa0,0xa0,0xa0,0xa3,0xa0,0xa3,0xa2,0xa2,0xa3,0xa0,0xa0,0xa0,0xa1,0xa3,0xa1,0xa0,0xa0,0xa2,0xa2,0xa2,0xa3,0xa0,0xab,0xaa,0xab,0xa9,0xa0,0xbf,0x80,0xff
};

#endif
