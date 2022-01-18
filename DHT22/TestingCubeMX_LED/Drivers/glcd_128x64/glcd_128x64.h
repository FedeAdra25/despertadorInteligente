/**
 * @file glcd_128x64.h
 * @author Embedded Laboratory
 * @date June 30, 2016
 * @brief This file contains functions prototype definitions related to Glcd.
 */

#ifndef GLCD_128X64_H
#define	GLCD_128X64_H

#include "config.h"

/* Un-Comment the following Line if Using Active High CS Controller*/
#define CHIP_SELECT_ACTIVE_LOW                  /**< Glcd Chip Select Type.*/

#ifdef	__cplusplus
extern "C" {
#endif

#define GLCD_DATA           LATD                /**< Glcd Data Port.*/
#define GLCD_DATA_READ      PORTD               /**< Glcd Data Rear Port.*/
#define GLCD_CS1            LATBbits.LATB0      /**< Glcd Chip Select 1.*/
#define GLCD_CS2            LATBbits.LATB1      /**< Glcd Chip Select 2.*/
#define GLCD_RS             LATCbits.LATC1      /**< Glcd Register Pin.*/
#define GLCD_RW             LATCbits.LATC0      /**< Glcd Read/Write Pin.*/
#define GLCD_EN             LATCbits.LATC2      /**< Glcd Enable Pin.*/
#define GLCD_RST            LATBbits.LATB5      /**< Glcd Reset Pin.*/

#define GLCD_DATA_DIR       TRISD               /**< Glcd Data Direction.*/
#define GLCD_CS1_DIR        TRISBbits.TRISB0    /**< Glcd CS1 Direction.*/
#define GLCD_CS2_DIR        TRISBbits.TRISB1    /**< Glcd CS2 Direction.*/
#define GLCD_RS_DIR         TRISCbits.TRISC1    /**< Glcd RS Direction.*/
#define GLCD_RW_DIR         TRISCbits.TRISC0    /**< Glcd RW Direction.*/
#define GLCD_EN_DIR         TRISCbits.TRISC2    /**< Glcd EN Direction.*/
#define GLCD_RST_DIR        TRISBbits.TRISB5    /**< Glcd RST Direction.*/
    
#define GLCD_TURN_ON        0x3F                /**< Glcd Turn-On.*/
#define GLCD_TURN_OFF       0x3E                /**< Glcd Turn-Off.*/
#define GLCD_START_LINE     0xC0                /**< Glcd Start Line.*/
#define GLCD_PAGE_ADD       0xB8                /**< Glcd X(Page)Address.*/
#define GLCD_PAGE_ADD_MSK   0xBF                /**< Glcd X(Page)Address Mask.*/
#define GLCD_X_ADD          0x40                /**< Glcd Y Address (not X).*/
#define GLCD_X_ADD_MSK      0x7F                /**< Glcd Y Address Mask.*/

#define enable_high()       (GLCD_EN = 1)       /**< Glcd Enable High.*/
#define enable_low()        (GLCD_EN = 0)       /**< Glcd Enable Low.*/
#define rs_high()           (GLCD_RS = 1)       /**< Glcd RS High.*/
#define rs_low()            (GLCD_RS = 0)       /**< Glcd RS Low.*/
#define rw_high()           (GLCD_RW = 1)       /**< Glcd RW High.*/
#define rw_low()            (GLCD_RW = 0)       /**< Glcd RW Low.*/
#define rst_high()          (GLCD_RST = 1)      /**< Glcd RST High.*/
#define rst_low()           (GLCD_RST = 0)      /**< Glcd RST Low.*/

#define GLCD_PORT(value)    (GLCD_DATA = value) /**< Update Glcd Data port.*/
    
#ifdef CHIP_SELECT_ACTIVE_LOW
#define enable_chip1()      (GLCD_CS1 = 0)      /**< Glcd Enable CS1.*/
#define disable_chip1()     (GLCD_CS1 = 1)      /**< Glcd Disable CS1.*/
#define enable_chip2()      (GLCD_CS2 = 0)      /**< Glcd Enable CS2.*/
#define disable_chip2()     (GLCD_CS2 = 1)      /**< Glcd Disable CS2.*/
#else
#define enable_chip1()      (GLCD_CS1 = 1)      /**< Glcd Enable CS1.*/
#define disable_chip1()     (GLCD_CS1 = 0)      /**< Glcd Disable CS1.*/
#define enable_chip2()      (GLCD_CS2 = 1)      /**< Glcd Enable CS2.*/
#define disable_chip2()     (GLCD_CS2 = 0)      /**< Glcd Disable CS2.*/
#endif

#define BLANK               0u                  /**< Glcd Blank.*/
#define FILL                (!BLANK)            /**< Glcd Fill.*/

#define GLCD_PIXEL_X        128                 /**< Pixels in X-Direction.*/
#define GLCD_PIXEL_Y        64                  /**< Pixels in Y-Direction.*/
#define GLCD_MAX_PAGE       8                   /**< Maximum Page Size.*/
#define GLCD_MAX_X_POS      64                  /**< Maximum X Position.*/
    
// Basic Function Prototypes
void Glcd_Init( void );
void Glcd_Set_Side( u8_t x_pos);
void Glcd_Set_X( u8_t x_pos );
void Glcd_Set_Page( u8_t page );
void Glcd_Write_Data( u8_t data );
u8_t Glcd_Read_Data( void );

// Advanced Function Prototypes
void Glcd_Fill( u8_t pattern );
void Glcd_Dot( u8_t x_pos, u8_t y_pos, u8_t color );
void Glcd_V_Line ( u8_t y_start, u8_t y_end, u8_t x_pos, u8_t color);
void Glcd_H_Line( u8_t x_start, u8_t x_end, u8_t y_pos, u8_t color);
void Glcd_Image( const u8_t *image);
void Glcd_Circle( s8_t x_center, s8_t y_center, u8_t radius, u8_t color);
void Glcd_Line( s16_t x_start, s16_t y_start,
               s16_t x_end, s16_t y_end, u8_t color);
void Glcd_Rectangle( u8_t x_upper_left, u8_t y_upper_left, 
        u8_t x_bottom_right, u8_t y_bottom_right, 
        u8_t color);
void Glcd_Write_Char(u8_t chr, u8_t x_pos, u8_t page_num, u8_t color);
void Glcd_Write_Text(char *text, u8_t x_pos, u8_t page_num, u8_t color);
#ifdef	__cplusplus
}
#endif

#endif	/* GLCD_128X64_H */

