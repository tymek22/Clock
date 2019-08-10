/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/*  FONTS  */

#define ledStrip_FONT_5X7  0

/* 5x7 Font */
//#define ledStrip_Font5x7_COLS  5
//#define ledStrip_Font5x7_ROWS  7
#define ledStrip_Font5x7_XSIZE  5
#define ledStrip_Font5x7_YSIZE  7
#define ledStrip_Font5x7_OFFSET 32u
#define ledStrip_COLORWHEEL_FONT  0x80000000
#define ledStrip_TRANS_BG         0xFF000000


void ledStrip_SetFont( uint32 font);
void ledStrip_PutChar(int32 row, int32 col, uint8 theChar, uint32 fg, uint32 bg);
void ledStrip_PrintString(int32 row, int32 col, char * theString, uint32 fg, uint32 bg);

//[] END OF FILE
