/**
 * @file glcd_128x64.c
 * @author Embedded Laboratory
 * @date June 30, 2016
 * @brief This file contains functions related to Glcd.
 */

#include "glcd_128x64.h"
#include "glcd_font.h"

// Private Function Prototypes
static void _glcd_enable_pulse( void );
static void _glcd_start_line( u8_t line );

// Public Functions Definitions
/**
 * @brief Initialize Graphical LCD.
 *
 * This function will initialize the Graphical LCD, configure its data and 
 * control pins as output, turn-on the lcd and select the line to the starting 
 * point.
 */
void Glcd_Init( void )
{
  GLCD_DATA_DIR = 0;
  GLCD_CS1_DIR = 0;
  GLCD_CS2_DIR = 0;
  GLCD_RS_DIR = 0;
  GLCD_RW_DIR = 0;
  GLCD_EN_DIR = 0;
  GLCD_RST_DIR = 0;
  
  disable_chip1();
  disable_chip2();
  rst_high();
  
  // GLCD_PORT(0);
  // GLCD_DATA = GLCD_TURN_ON;
  enable_chip1();
  enable_chip2();
  rs_low();
  rw_low();
  GLCD_PORT(GLCD_TURN_ON);
  // GLCD_PORT(GLCD_TURN_OFF);
  _glcd_enable_pulse();
  _glcd_start_line(0);
}

/**
 * @brief Glcd Set Side.
 *
 * Selects Glcd side based on the x_pos. The parameter x_pos specifies the Glcd 
 * side: values from 0 to 63 specify the left side, values from 64 to 127 
 * specify the right side.
 * @param x_pos position on x-axis. Valid values: 0..127
 */
void Glcd_Set_Side( u8_t x_pos )
{
  if( x_pos < 64u )
  {
    enable_chip1();
    disable_chip2();
  }
  else
  {
    enable_chip2();
    disable_chip1();
  }
}

/**
 * @brief Glcd Set X Position.
 * Sets x-axis position to x_pos dots from the left border of Glcd within the 
 * selected side.
 * @param x_pos Position on x-axis. Valid values: 0..63
 */
void Glcd_Set_X( u8_t x_pos )
{
  // Boundary Checks
  if( x_pos >= GLCD_MAX_X_POS )
    x_pos = GLCD_MAX_X_POS-1;
  
  rs_low();     // Command
  rw_low();     // Writing
  x_pos = (x_pos | GLCD_X_ADD ) & GLCD_X_ADD_MSK;
  GLCD_PORT(x_pos);
  _glcd_enable_pulse ();
}

/**
 * @brief Glcd Set Page.
 * Selects the page on Glcd.
 * @param page Page Number. Valid values: 0..7
 */
void Glcd_Set_Page( u8_t page )
{
  // Boundary Checks
  if( page >= GLCD_MAX_PAGE )
    page = GLCD_MAX_PAGE-1;
  rs_low();     // Command
  rw_low();     // Writing
	page = (page | GLCD_PAGE_ADD ) & GLCD_PAGE_ADD_MSK;
  GLCD_PORT(page);
  _glcd_enable_pulse ();
}

/**
 * @brief Glcd Write Data.
 * Writes one byte to the current location in Glcd memory and moves to the next 
 * location.
 * @param data: data to be written.
 */
void Glcd_Write_Data( u8_t data )
{
  rs_high();    // Data
  rw_low();     // Writing
  GLCD_PORT(data);  
  _glcd_enable_pulse ();
}

/**
 * @brief Glcd Read Data.
 * Reads data from from the current location of Glcd memory and moves to the 
 * next location.
 * @return One byte from Glcd memory.
 * @note Glcd needs to be initialized, see #Glcd_Init routine. Glcd side, 
 * x-axis position and page should be set first. 
 * See functions #Glcd_Set_Side, #Glcd_Set_X, and #Glcd_Set_Page.
 */
u8_t Glcd_Read_Data( void )
{
  u8_t read_data = 0;
  GLCD_DATA_DIR = 0xFF;
  rs_high();    // Data
  rw_high();    // Read
  _glcd_enable_pulse();
  enable_high();
  __delay_us(5);
  read_data = GLCD_DATA_READ;
  enable_low();
  GLCD_DATA_DIR = 0x00;
  return read_data;
}

/**
 * @brief Glcd Fill.
 * 
 * Fills Glcd memory with the byte pattern.
 * Call this function to clear the Display:
 * @code
 * Glcd_Fill(BLANK);
 * @endcode
 * Call this function to Fill the Display:
 * @code
 * Glcd_Fill(FILL);
 * @endcode
 * 
 * @param pattern byte to fill Glcd memory with.
 */
void Glcd_Fill( u8_t pattern )
{
  u8_t i,j;
  _glcd_start_line(0);
  enable_chip1();
  enable_chip2();
  for(j = 0; j < 8; j++)
  {
    Glcd_Set_Page(j);
    for(i=0 ; i<64; i++)
    {
      if( !pattern )
        Glcd_Write_Data(0x00);
      else
        Glcd_Write_Data(0xFF);
    }
  }
}

/**
 * @brief Glcd Dot.
 * 
 * Draws a dot on Glcd at coordinates (x_pos, y_pos).
 * 
 * @param x_pos: x position. Valid values: 0..127
 * @param y_pos: y position. Valid values: 0..63
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Dot( u8_t x_pos, u8_t y_pos, u8_t color )
{
	u8_t data;
  // Boundary Checks
  if( x_pos >= GLCD_PIXEL_X )
    x_pos = GLCD_PIXEL_X-1;
  if( y_pos >= GLCD_PIXEL_Y )
    y_pos = GLCD_PIXEL_Y-1;
  
  Glcd_Set_Side( x_pos );
  Glcd_Set_Page( y_pos/8 );
  if( x_pos >= GLCD_MAX_X_POS )
    Glcd_Set_X( x_pos-GLCD_MAX_X_POS );
  else
    Glcd_Set_X( x_pos );
  
  switch(color)
	{
    case 0: // Light
      data = ~(1<<(y_pos%8)) & Glcd_Read_Data();
      break;
    case 1: // Dark
      data = (1<<(y_pos%8)) | Glcd_Read_Data();
      break;
  }
  Glcd_Set_Page( y_pos/8 );
  if( x_pos >= GLCD_MAX_X_POS )
    Glcd_Set_X( x_pos-GLCD_MAX_X_POS );
  else
    Glcd_Set_X( x_pos );
  Glcd_Write_Data(data);
}

/**
 * @brief Glcd Vertical Line.
 * 
 * Draw vertical line between of length specified by y_start and y_end, and at
 * position specified by x_pos
 * 
 * @param y_start: y position to start vertical line. Valid values: 0..63
 * @param y_end: y position to end vertical line. Valid values: 0..63
 * @param x_pos: x position. Valid values: 0..127
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_V_Line ( u8_t y_start, u8_t y_end, u8_t x_pos, u8_t color)
{
  u8_t temp;
  if( y_start > y_end )
  {
    temp = y_start;
    y_start = y_end;
    y_end = temp;
  }
  
  while( y_start <= y_end )
  {
    Glcd_Dot(x_pos, y_start, color);
    y_start++;
  }
}

/**
 * @brief Glcd Horizontal Line.
 * 
 * Draw horizontal line between of length specified by x_start and x_end, and at
 * position specified by y_pos
 * 
 * @param x_start: y position to start horizontal line. Valid values: 0..127
 * @param x_end: y position to end horizontal line. Valid values: 0..127
 * @param y_pos: x position. Valid values: 0..63
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_H_Line( u8_t x_start, u8_t x_end, u8_t y_pos, u8_t color)
{
  u8_t temp;
  if( x_start > x_end )
  {
    temp = x_start;
    x_start = x_end;
    x_end = temp;
  }
  
  while( x_start <= x_end )
  {
    Glcd_Dot(x_start, y_pos, color);
    x_start++;
  }
}


/**
 * @brief Draws a rectangle on Glcd.
 * 
 * Draws a rectangle on Glcd by using the specified parameters.
 * 
 * @param x_upper_left: x coordinate of the upper left rectangle corner. 
 * Valid values: 0..127
 * @param y_upper_left: y coordinate of the upper left rectangle corner. 
 * Valid values: 0..63
 * @param x_bottom_right: x coordinate of the lower right rectangle corner. 
 * Valid values: 0..127
 * @param y_bottom_right: y coordinate of the lower right rectangle corner. 
 * Valid values: 0..63
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Rectangle( u8_t x_upper_left, u8_t y_upper_left, 
        u8_t x_bottom_right, u8_t y_bottom_right, 
        u8_t color)
{
  Glcd_V_Line( y_upper_left, y_bottom_right, x_upper_left, color);
  Glcd_H_Line( x_upper_left, x_bottom_right, y_bottom_right, color);
  Glcd_V_Line( y_upper_left, y_bottom_right, x_bottom_right, color);
  Glcd_H_Line( x_upper_left, x_bottom_right, y_upper_left, color);
}

/**
 * @brief Draws a line on Glcd.
 * 
 * Draws a line on Glcd by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">
 * Algorithm Used</a>
 * <a href="http://www.edaboard.com/thread68526.html#post302856"> Program Used
 * </a>
 * 
 * @param x_start: x coordinate of start point. Valid values: 0..127
 * @param y_start: x coordinate of start point. Valid values: 0..63
 * @param x_end: x coordinate of end point. Valid values: 0..127
 * @param y_end: y coordinate of end point. Valid values: 0..63
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Line( s16_t x_start, s16_t y_start,
               s16_t x_end, s16_t y_end, u8_t color)
{
  s16_t x, y, addx, addy, dx, dy;
  s32_t P;
  s16_t i;
  dx = abs((s16_t)(x_end - x_start));
  dy = abs((s16_t)(y_end - y_start));
  x = x_start;
  y = y_start;
  
  if(x_start > x_end)
    addx = -1;
  else
    addx = 1;
  
  if(y_start > y_end)
    addy = -1;
  else
    addy = 1;
  
  if(dx >= dy)
  {
    P = 2*dy - dx;
    
    for(i=0; i<=dx; ++i)
    {
      Glcd_Dot (x,y,color);
      if(P < 0)
      {
        P += 2*dy;
        x += addx;
      }
      else
      {
        P += 2*dy - 2*dx;
        x += addx;
        y += addy;
      }
    }
  }
  else
  {
    P = 2*dx - dy;
    for(i=0; i<=dy; ++i)
    {
      Glcd_Dot (x,y,color);
      
      if(P < 0)
      {
        P += 2*dx;
        y += addy;
      }
      else
      {
        P += 2*dx - 2*dy;
        x += addx;
        y += addy;
      }
    }
  }
}
//{
//  s16_t dx, dy, D;
//  s16_t x,y;
//  
//  // Boundary Checks
//  if( x_start >= GLCD_PIXEL_X )
//    x_start = GLCD_PIXEL_X-1;
//  if( y_start >= GLCD_PIXEL_Y )
//    y_start = GLCD_PIXEL_Y-1;
//  if( x_end >= GLCD_PIXEL_X )
//    x_end = GLCD_PIXEL_X-1;
//  if( y_end >= GLCD_PIXEL_Y )
//    y_end = GLCD_PIXEL_Y-1;
//  
//  dx = abs(x_end - x_start);
//  dy = abs(y_end - y_start);
//  D = abs(dy - dx);
//    
//  y = y_start;
//
//  for(x = x_start; x <= x_end; x++ )
//  {
//    Glcd_Dot((u8_t)x,(u8_t)y,color);
//    if (D  >= 0 )
//    {
//       y = y + 1;
//       D = D - dx;
//    }
//    D = D + dy;
//  }
//}

/**
 * @brief Glcd Image.
 * 
 * Displays bitmap image on Glcd.
 * 
 * @param *image: image to be displayed. Bitmap array must be located in code 
 * memory. Use the mikroC PRO for PIC integrated Glcd Bitmap Editor to convert
 * image to a constant array suitable for displaying on Glcd.
 */
void Glcd_Image( const u8_t *image)
{
  u8_t i,j;
  _glcd_start_line(0);
  
  for( i = 0 ; i < 8 ; i++ )
  {
    Glcd_Set_Page(i);
    Glcd_Set_X(0);
    /*Select First Controller*/
    enable_chip1();
    disable_chip2();
    for(j=0;j<64;j++)
    {
      Glcd_Write_Data(*(image+128*i+j));
    }
    
    Glcd_Set_Page(i);
    Glcd_Set_X(0);
    /*Select Second Controller*/
    enable_chip2();
    disable_chip1();
    for(j=0;j<64;j++)
    {
      Glcd_Write_Data(*(image+128*i+j+64));
    }
  }
}

/**
 * @brief Draws a Circle on Glcd.
 * 
 * Draws a Circle on Glcd by using the specified parameters.
 * <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm">
 * Mid Point Circle Algorithm Weblink</a>
 * 
 * @param x_center: x coordinate of the circle center. Valid values: 0..127
 * @param y_center: y coordinate of the circle center. Valid values: 0..63
 * @param radius: radius of the circle.
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Circle( s8_t x_center, s8_t y_center, u8_t radius, u8_t color)
{
  s8_t x = radius;
  s8_t y = 0;
  s8_t err = 0;
  s16_t temp1,temp2;
  // Boundary Checks
  if( (u8_t)x_center >= GLCD_PIXEL_X )
    x_center = GLCD_MAX_X_POS-1;
  if( (u8_t)y_center >= GLCD_PIXEL_Y )
    y_center = GLCD_PIXEL_Y-1;
  
  while (x >= y)
  {
    temp1 = x_center + x;
    temp2 = y_center + y;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center + y;
    temp2 = y_center + x;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center - y;
    temp2 = y_center + x;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center - x;
    temp2 = y_center + y;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center - x;
    temp2 = y_center - y;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center - y;
    temp2 = y_center - x;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center + y;
    temp2 = y_center - x;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    temp1 = x_center + x;
    temp2 = y_center - y;
    if( temp1 >=0 && temp1 < GLCD_PIXEL_X 
       && temp2 >= 0 && temp2 < GLCD_PIXEL_Y )
      Glcd_Dot(temp1, temp2, color);
    
    y += 1;
    err += 1 + 2*y;
    if (2*(err-x) + 1 > 0)
    {
      x -= 1;
      err += 1 - 2*x;
    }
  }
}

/**
 * @brief Write character on Glcd.
 * 
 * Prints character on the Glcd.
 * 
 * @param chr: Character to be written.
 * @param x_pos: character starting position on x-axis. Valid values: 0..127
 * @param page_num: the number of the page on which character will be written. 
 * Valid values: 0..7
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Write_Char(u8_t chr, u8_t x_pos, u8_t page_num, u8_t color)
{
  Glcd_Set_Side (x_pos);
  Glcd_Set_Page (page_num);
  if( x_pos >= GLCD_MAX_X_POS )
    Glcd_Set_X( x_pos-GLCD_MAX_X_POS );
  else
    Glcd_Set_X( x_pos );
  for(u8_t i=0; i<8; i++)
  {
    u16_t temp = 0;
    temp = 8*(chr - 32) + i;
    temp = Terminal8x8[temp];
    if( !color )
      temp = ~temp;
    Glcd_Write_Data ((u8_t)temp);
  }
}

/**
 * @brief Write Text on Glcd.
 * 
 * Prints text on the Glcd.
 * 
 * @param *text: Pointer to the array of the text to be written.
 * @param x_pos: character starting position on x-axis. Valid values: 0..127
 * @param page_num: the number of the page on which character will be written. 
 * Valid values: 0..7
 * @param color: color parameter. Valid values: 0 and 1
 */
void Glcd_Write_Text(char *text, u8_t x_pos, u8_t page_num, u8_t color)
{
  u8_t i = x_pos;
  while(*text)
  {
    u8_t temp = *text;
    Glcd_Write_Char(temp,i,page_num,color);
    text++;
    i = i+8;
    if(i >= GLCD_PIXEL_X )
      break;
  }
}

// Private Function Definition
/**
 * @brief Glcd Enable Pulse.
 * 
 * Enable Pulse to send data at pins of Glcd to the Glcd Controller.
 */
static void _glcd_enable_pulse( void )
{
  enable_high();
  __delay_us(5);
  enable_low();
  __delay_us(5);
}

/**
 * @brief Glcd Start Line.
 * 
 * Display Start Line (Z Address). Indicates the Display Data RAM displayed 
 * at the top of the screen. Valid values: 0 and 63
 * 
 * @param line: 
 */
static void _glcd_start_line( u8_t line )
{
	/*
	Display Start Line (Z Address)
	Indicates the Display Data RAM displayed at the top of the screen.
	Values(0-64)
	*/
  rs_low();     // Command
  rw_low();     // Writing
  
  // Activate Both Chips
  enable_chip1();
  enable_chip2();
  
  GLCD_PORT(GLCD_START_LINE | line);
  
  _glcd_enable_pulse ();
  disable_chip1();
  disable_chip2();
}
