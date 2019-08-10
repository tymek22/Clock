/* =========================================================
 *
 * Strip Light Controller
 * By Mark Hastings
 *
 * 05/27/2013  v1.0  Mark Hastings   Initial working version
 * 09/04/2013  v1.3  Mark Hastings   Add more features and color lookup.
 * 12/02/2013  v1.6  Mark Hastings   Added a couple more functions.
 *
 * This file contains the functions required to control each
 * lighting control channel.
 *
 * =========================================================
*/

#include <project.h>
#include "cytypes.h"
#include "stdlib.h"
#include "cyfitter.h"
#include "ledStrip.h"
#include "ledStrip_fonts.h"

uint8  ledStrip_initvar = 0;

#if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
uint32  ledStrip_ledArray[ledStrip_ARRAY_ROWS][ledStrip_ARRAY_COLS];
#else
uint8   ledStrip_ledArray[ledStrip_ARRAY_ROWS][ledStrip_ARRAY_COLS];
#endif

uint32  ledStrip_ledIndex = 0;  
uint32  ledStrip_row = 0;
uint32  ledStrip_refreshComplete;

uint32  ledStrip_DimMask;
uint32  ledStrip_DimShift;


#if(ledStrip_CHIP == ledStrip_CHIP_WS2812)
const uint32 ledStrip_CLUT[ ] = {
//xxBBRRGG (WS2812)
//     (24)   [ Index = 0 ]
0x0000FFFF,  // 0 Yellow
0x0000CCFF,
0x000099FF,
0x000033FF,
0x000000FF,  // 5  Green
0x006600B3,
0x00990099, 
0x00B30066, 
0x00CC0033,  // 9 Blue
0x00B31919, 
0x00993300, 
0x00994000, 
0x00996600, 
0x00999900, 
0x0099CC00, 
0x0066E600, 
0x0000FF00, 
0x0000FF33, 
0x0000FF66, 
0x0000FF80, 
0x0000FF99,  // 20 Orange
0x0000FFB2, 
0x0000FFCC, 
0x0000FFE5,
// #24

//xxBBRRGG  (64)  [ Index = 24 ]
0x00000000, 0x00550000, 0x00AA0000, 0x00FF0000,  // 0, Black,  LtBlue, MBlue, Blue
0x00000055, 0x00550055, 0x00AA0055, 0x00FF0055,  // 4, LtGreen
0x000000AA, 0x005500AA, 0x00AA00AA, 0x00FF00AA,  // 8, MGreen
0x000000FF, 0x005500FF, 0x00AA00FF, 0x00FF00FF,  // 12 Green

0x00005500, 0x00555500, 0x00AA5500, 0x00FF5500,  // 16, LtRed
0x00005555, 0x00555555, 0x00AA5555, 0x00FF5555,  // 20, LtYellow
0x000055AA, 0x005555AA, 0x00AA55AA, 0x00FF55AA,  // 24, 
0x000055FF, 0x005555FF, 0x00AA55FF, 0x00FF55FF,  // 28,

0x0000AA00, 0x0055AA00, 0x00AAAA00, 0x00FFAA00,  // 32, MRed
0x0000AA55, 0x0055AA55, 0x00AAAA55, 0x00FFAA55,  // 36, 
0x0000AAAA, 0x0055AAAA, 0x00AAAAAA, 0x00FFAAAA,  // 55, 
0x0000AAFF, 0x0055AAFF, 0x00AAAAFF, 0x00FFAAFF,  // 44, 

0x0000FF00, 0x0055FF00, 0x00AAFF00, 0x00FFFF00,  // 48, Red, ??, ??, Magenta
0x0000FF55, 0x0055FF55, 0x00AAFF55, 0x00FFFF55,  // 52,
0x0000FFAA, 0x0055FFAA, 0x00AAFFAA, 0x00FFFFAA,  // 56,
0x0000FFFF, 0x0055FFFF, 0x00AAFFFF, 0x00FFFFFF,  // 60, Yellow,??, ??, White

// Misc ( 16 )  [ Index = 88 ]
0x000080FF,  // SPRING_GREEN
0x008000FF,  // TURQUOSE
0x00FF00FF,  // CYAN
0x00FF0080,  // OCEAN
0x00FF8000,  // VIOLET
0x0080FF00,  // RASPBERRY
0x000000FF,  // GREEN
0x00202020,  // DIM WHITE
0x00200000,  // DIM BLUE
0x10000000,  // INVISIBLE
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare

// Temperture Color Blue to Red (16) [ Index = 104 ]
0x00FF0000, 0x00F01000, 0x00E02000, 0x00D03000,
0x00C04000, 0x00B05000, 0x00A06000, 0x00907000,
0x00808000, 0x00709000, 0x0060A000, 0x0050B000,
0x0040C000, 0x0030D000, 0x0020E000, 0x0000FF00
};
#else  //xxBBGGRR (WS2811)
const uint32 ledStrip_CLUT[ ] = {
//     (24)   [ Index = 0 ]
0x0000FFFF,  // 0 Yellow
0x0000FFCC,
0x0000FF99,
0x0000FF33,
0x0000FF00,  // 5  Green
0x0066B300,
0x00999900, 
0x00B36600, 
0x00CC3300,  // 9 Blue
0x00B31919, 
0x00990033, 
0x00990040, 
0x00990066, 
0x00990099, 
0x009900CC, 
0x006600E6, 
0x000000FF, 
0x000033FF, 
0x000066FF, 
0x000080FF, 
0x000099FF,  // 20 Orange
0x0000B2FF, 
0x0000CCFF, 
0x0000E5FF,
// #24

//xxBBRRGG  (64)  [ Index = 24 ]
0x00000000, 0x00550000, 0x00AA0000, 0x00FF0000,  // 0, Black,  LtBlue, MBlue, Blue
0x00005500, 0x00555500, 0x00AA5500, 0x00FF5500,  // 4, LtGreen
0x0000AA00, 0x0055AA00, 0x00AAAA00, 0x00FFAA00,  // 8, MGreen
0x0000FF00, 0x0055FF00, 0x00AAFF00, 0x00FFFF00,  // 12 Green

0x00000055, 0x00550055, 0x00AA0055, 0x00FF0055,  // 16, LtRed
0x00005555, 0x00555555, 0x00AA5555, 0x00FF5555,  // 20, LtYellow
0x0000AA55, 0x0055AA55, 0x00AAAA55, 0x00FFAA55,  // 24, 
0x0000FF55, 0x0055FF55, 0x00AAFF55, 0x00FFFF55,  // 28,

0x000000AA, 0x005500AA, 0x00AA00AA, 0x00FF00AA,  // 32, MRed
0x000055AA, 0x005555AA, 0x00AA55AA, 0x00FF55AA,  // 36, 
0x0000AAAA, 0x0055AAAA, 0x00AAAAAA, 0x00FFAAAA,  // 55, 
0x0000FFAA, 0x0055FFAA, 0x00AAFFAA, 0x00FFFFAA,  // 44, 

0x000000FF, 0x005500FF, 0x00AA00FF, 0x00F00FFF,  // 48, Red, ??, ??, Magenta
0x000055FF, 0x005555FF, 0x00AA55FF, 0x00FF55FF,  // 52,
0x0000AAFF, 0x0055AAFF, 0x00AAAAFF, 0x00FFAAFF,  // 56,
0x0000FFFF, 0x0055FFFF, 0x00AAFFFF, 0x00FFFFFF,  // 60, Yellow,??, ??, White

// Misc ( 16 )  [ Index = 88 ]
0x0000FF80,  // SPRING_GREEN
0x0080FF00,  // TURQUOSE
0x00FFFF00,  // CYAN
0x00FF8000,  // OCEAN
0x00FF0080,  // VIOLET
0x008000FF,  // RASPBERRY
0x0000FF00,  // GREEN
0x00202020,  // DIM WHITE
0x00200000,  // DIM BLUE
0x10000000,  // INVISIBLE
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare
0x00000000,  // Spare

// Temperture Color Blue to Red (16) [ Index = 104 ]
0x00FF0000, 0x00F00010, 0x00E00020, 0x00D00030,
0x00C00040, 0x00B00050, 0x00A00060, 0x00900070,
0x00800080, 0x00700090, 0x006000A0, 0x005000B0,
0x004000C0, 0x003000D0, 0x002000E0, 0x000000FF
};
#endif



/*******************************************************************************
* Function Name: ledStrip_Start
********************************************************************************
* Summary:
*  Initialize the hardware. 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_Start()
{
    extern uint8 ledStrip_initvar;
    extern uint32 ledStrip_refreshComplete;

    ledStrip_ACTL0_REG = ledStrip_DISABLE_FIFO;
    
    ledStrip_Period   = ledStrip_PERIOD-1;
    ledStrip_Compare0 = ledStrip_DATA_ZERO;
    ledStrip_Compare1 = ledStrip_DATA_ONE;
    
    ledStrip_CONTROL = ledStrip_ENABLE;
    ledStrip_MemClear(ledStrip_OFF);
    ledStrip_CONTROL = ledStrip_DISABLE;
    
    ledStrip_SetFont( ledStrip_FONT_5X7);
    
    /* Set no dimming, full brightness */
    ledStrip_Dim(0); 

    
    if(ledStrip_initvar == 0)
    {

        ledStrip_initvar = 1;
 
         /* Start and set interrupt vector */

#if(ledStrip_TRANSFER == ledStrip_TRANSFER_ISR)
       {
           ledStrip_cisr_StartEx(ledStrip_CISR);
		   ledStrip_fisr_StartEx(ledStrip_FISR);
       }
#endif       
       if(ledStrip_TRANSFER == ledStrip_TRANSFER_FIRMWARE)
       {
           ledStrip_CONTROL = ledStrip_ENABLE;    
       }
    }
    ledStrip_refreshComplete = 1;
}


/*******************************************************************************
* Function Name: ledStrip_Trigger
********************************************************************************
* Summary:
*   Update the LEDs with graphics memory.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_Trigger(uint32 rst)
{
    uint32 color;
    
    if(rst) 
    {
        ledStrip_row = 0;  /* Reset the row */
        ledStrip_Channel = 0;
    }
    
    #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
       color = ledStrip_ledArray[ledStrip_row][0];
    #else  /* Else use lookup table */
       color = ledStrip_CLUT[ (ledStrip_ledArray[ledStrip_row][0]) ];
    #endif
    
     color = (color >> ledStrip_DimShift) & ledStrip_DimMask;
     
    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Red
    color = color >> 8;
    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write green
    color = color >> 8;
    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write green
    
    ledStrip_ledIndex = 1;
 //   ledStrip_CONTROL = ledStrip_ENABLE | ledStrip_FIFO_IRQ_EN; 
	
	ledStrip_CONTROL = ledStrip_ENABLE | ledStrip_XFRCMPT_IRQ_EN | ledStrip_FIFO_IRQ_EN; 
    ledStrip_refreshComplete = 0;
}

/*******************************************************************************
* Function Name: ledStrip_Ready
********************************************************************************
* Summary:
*  Checks to see if transfer is complete.
*
* Parameters:  
*  none  
*
* Return: 
*  Zero if not complete, non-zero if transfer complete.
*
*******************************************************************************/
uint32 ledStrip_Ready(void)
{
    if(ledStrip_refreshComplete )
    {
        ledStrip_CONTROL = ledStrip_DISABLE;
        return((uint32)1);
    }
    else
    {
         return((uint32)0);
    }
}


/*******************************************************************************
* Function Name: ledStrip_Stop
********************************************************************************
* Summary:
*  Stop all transfers.
*
* Parameters:  
*  None 
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_Stop()
{

    ledStrip_CONTROL = ledStrip_DISABLE;
}


/*******************************************************************************
* Function Name: ledStrip_ColorInc
********************************************************************************
* Summary:
*  Increment color throught the color lookup table.
*
* Parameters:  
*  uint32 incValue: Increment through color table by incValue. 
*
* Return: Color at next location.
*  
*
*******************************************************************************/
uint32 ledStrip_ColorInc(uint32 incValue)
{
    uint32 color;
    extern const uint32 ledStrip_CLUT[];
    static uint32 colorIndex = 0;
    
    colorIndex += incValue;
    colorIndex = colorIndex % ledStrip_COLOR_WHEEL_SIZE;

    #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
       color = ledStrip_CLUT[ colorIndex ];
    #else
        color = colorIndex;
    #endif


    return(color);
}
/*****************************************************************************
* Function Name: ledStrip_FISR
******************************************************************************
*
* Summary:
*  Interrupt service handler for data transfer for each LED 
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ledStrip_FISR)
{
    extern uint32  ledStrip_DimMask;
    extern uint32  ledStrip_DimShift;
    uint32 static color;

    if(ledStrip_ledIndex < ledStrip_ARRAY_COLS)
    {
        #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
            color = ledStrip_ledArray[ledStrip_row][ledStrip_ledIndex++];
        #else  /* Else use lookup table */
            color = ledStrip_CLUT[ (ledStrip_ledArray[ledStrip_row][ledStrip_ledIndex++]) ];
        #endif

        color = (color >> ledStrip_DimShift) & ledStrip_DimMask;  

        ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Green
        color = color >> 8;
        ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Red
        color = color >> 8;
        ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Blue
    }
    else 
    {
         ledStrip_CONTROL = ledStrip_ENABLE | ledStrip_XFRCMPT_IRQ_EN; 
    }

}

/*****************************************************************************
* Function Name: ledStrip_CISR
******************************************************************************
*
* Summary:
*  Interrupt service handler after each row is complete.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ledStrip_CISR)
{
    extern uint32  ledStrip_DimMask;
    extern uint32  ledStrip_DimShift;
    uint32 static color;
    extern uint32 ledStrip_refreshComplete;

	ledStrip_CONTROL = ledStrip_ENABLE |ledStrip_NEXT_ROW;
    ledStrip_row++;
    if( ledStrip_row < ledStrip_ARRAY_ROWS)  /* More Rows to do  */
    {
        ledStrip_Channel = ledStrip_row;  

		#if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
             color = ledStrip_ledArray[ledStrip_row][0];
        #else  /* Else use lookup table */
             color = ledStrip_CLUT[ (ledStrip_ledArray[ledStrip_row][0]) ];
        #endif

        color = (color >> ledStrip_DimShift) & ledStrip_DimMask;
 
        ledStrip_DATA = (uint8)(color & 0x000000FF);  /* Write Red   */
        color = color >> 8;
        ledStrip_DATA = (uint8)(color & 0x000000FF);  /* Write green */
        color = color >> 8;
        ledStrip_DATA = (uint8)(color & 0x000000FF);  /* Write green */

        ledStrip_ledIndex = 1;
		ledStrip_CONTROL = ledStrip_ENABLE | ledStrip_FIFO_IRQ_EN; 
		
    }
    else
    {
        ledStrip_refreshComplete = 1u;
    }
  
}


/*******************************************************************************
* Function Name: ledStrip_DisplayClear
********************************************************************************
* Summary:
*   Clear memory with a given value and update the display.
*
* Parameters:  
*  uint32 color: Color to clear display. 
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_DisplayClear(uint32 color)
{   
    ledStrip_MemClear(color);
    ledStrip_Trigger(1);
}

/*******************************************************************************
* Function Name: ledStrip_MemClear
********************************************************************************
* Summary:
*   Clear LED memory with given color, but do not update display.
*
* Parameters:  
*  uint32 color: Color to clear display.  
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_MemClear(uint32 color)
{
    uint32  row, col;
    
    for(row=0; row < ledStrip_ARRAY_ROWS; row++)
    {
        for(col=0; col < ledStrip_ARRAY_COLS; col++)
        {
            ledStrip_ledArray[row][col] = color;
            #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
                ledStrip_ledArray[row][col] = color;
            #else  /* Else use lookup table */
                 ledStrip_ledArray[row][col] = (uint8)color;
            #endif
        }
    }
}



/*******************************************************************************
* Function Name: ledStrip_WriteColor
********************************************************************************
* Summary:
*   Write given color directly to output register.
*
* Parameters:  
*  uint32 color: Color to write to display. 
*
* Return: 
*  void
*
*******************************************************************************/
void ledStrip_WriteColor(uint32 color)
{
    while( (ledStrip_STATUS & ledStrip_FIFO_EMPTY) == 0); 

    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Green
    color = color >> 8;
    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Red
    color = color >> 8;
    ledStrip_DATA = (uint8)(color & 0x000000FF);  // Write Blue
}


/*******************************************************************************
* Function Name: ledStrip_Pixel
********************************************************************************
*
* Summary:
*  Draw Pixel  
*
* Parameters:  
*  x,y:    Location to draw the pixel
*  color:  Color of the pixel
*
* Return: 
*  None 
*******************************************************************************/
void ledStrip_Pixel(int32 x, int32 y, uint32 color)
{

	if((x >= ledStrip_MIN_X) && (y >= ledStrip_MIN_Y) && (x <= ledStrip_MAX_X) && (y <= ledStrip_MAX_Y))
    {

    #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
       ledStrip_ledArray[y][x] = color;
    #else  /* Else use lookup table */
       ledStrip_ledArray[y][x] = (uint8)color;
    #endif
    }
  
}

/*******************************************************************************
* Function Name: ledStrip_GetPixel
********************************************************************************
*
* Summary:
*  Get Pixel Color  
*
* Parameters:  
*  x,y:    Location to get pixel color
*
* Return: 
*  None 
*******************************************************************************/
uint32 ledStrip_GetPixel(int32 x, int32 y)
{
    uint32 color = 0;
    if((x>=0) && (y>=0) && (x < ledStrip_ARRAY_COLS) && (y < ledStrip_ARRAY_ROWS))
    {
    #if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
       color = ledStrip_ledArray[y][x];
    #else  /* Else use lookup table */
       color = (uint32)ledStrip_ledArray[y][x];
    #endif
    }
    return(color);
}

/*******************************************************************************
* Function Name: ledStrip_DrawCircle
********************************************************************************
*
* Summary:
*  Draw a circle on the display given a start point and radius.  
*
*  This code uses Bresenham's Circle Algorithm. 
*
* Parameters:  
*  x0, y0: Center of circle
*  radius: Radius of circle
*  color:  Color of circle
*
* Return: 
*  None 
*  
*******************************************************************************/
void ledStrip_DrawCircle (int32 x0, int32 y0, int32 radius, uint32 color)
{
	int32 f = 1 - radius;
	int32 ddF_x = 0;
	int32 ddF_y = -2 * radius;
	int32 x = 0;
	int32 y = radius;

	ledStrip_Pixel(x0, y0 + radius, color);
	ledStrip_Pixel(x0, y0 - radius, color);
	ledStrip_Pixel( x0 + radius, y0, color);
	ledStrip_Pixel( x0 - radius, y0, color);

	while(x < y)
	{
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;

		ledStrip_Pixel(x0 + x, y0 + y, color);
		ledStrip_Pixel(x0 - x, y0 + y, color);
		ledStrip_Pixel( x0 + x, y0 - y, color);
		ledStrip_Pixel( x0 - x, y0 - y, color);
		ledStrip_Pixel( x0 + y, y0 + x, color);
		ledStrip_Pixel( x0 - y, y0 + x, color);
		ledStrip_Pixel( x0 + y, y0 - x, color);
		ledStrip_Pixel( x0 - y, y0 - x, color);
	}
}


/*******************************************************************************
* Function Name: ledStrip_DrawLine
********************************************************************************
*
* Summary:
*  Draw a line on the display.  
*
* Parameters:  
*  x0, y0:  The beginning endpoint
*  x1, y1:  The end endpoint.
*  color:   Color of the line.
*
* Return: 
*  None 
*  
*******************************************************************************/
void ledStrip_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, uint32 color)
{
	int32 dy = y1 - y0; /* Difference between y0 and y1 */
	int32 dx = x1 - x0; /* Difference between x0 and x1 */
	int32 stepx, stepy;

	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	else
	{
		stepy = 1;
	}

	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	else
	{
		stepx = 1;
	}

	dy <<= 1; /* dy is now 2*dy  */
	dx <<= 1; /* dx is now 2*dx  */
	ledStrip_Pixel(x0, y0, color);

	if (dx > dy) 
	{
		int fraction = dy - (dx >> 1);
		while (x0 != x1)
		{
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			x0 += stepx;
			fraction += dy;
			ledStrip_Pixel(x0, y0, color);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			ledStrip_Pixel( x0, y0, color);
		}
	}
}

/*******************************************************************************
* Function Name: ledStrip_DrawRect
********************************************************************************
*
* Summary:
*  Draw a rectangle, filled or not.  
*
* Parameters:  
*  x0, y0:  The upper lefthand corner.
*  x1, y1:  The lower right corner.
*  fill:    Non-Zero if retangle is to be filled.
*  color:   Color for rectangle, border and fill.
*
* Return: 
*  None 
*  
*******************************************************************************/
void ledStrip_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, uint32 color)
{	
     int xDiff;
	/* Check if the rectangle is to be filled    */
	if (fill != 0)
	{	
        /* Find the difference between the x vars */
		if(x0 > x1)
		{
			xDiff = x0 - x1; 
		}
		else
		{
			xDiff = x1 - x0;
		}
	
	    /* Fill it with lines  */
		while(xDiff >= 0)
		{
			ledStrip_DrawLine(x0, y0, x0, y1, color);
		
			if(x0 > x1)
				x0--;
			else
				x0++;
		
			xDiff--;
		}

	}
	else 
	{
		/* Draw the four sides of the rectangle */
		ledStrip_DrawLine(x0, y0, x1, y0, color);
		ledStrip_DrawLine(x0, y1, x1, y1, color);
		ledStrip_DrawLine(x0, y0, x0, y1, color);
		ledStrip_DrawLine(x1, y0, x1, y1, color);
	}
}

/*******************************************************************************
* Function Name: ledStrip_Dim
********************************************************************************
*
* Summary:
*  Dim all output by a specific level (0,1,2,3,4)  
*
* Parameters:  
*  dimLevel:  Dim level 1 to 4, 0 => No dimming.
*
* Return: 
*  None 
*  
*******************************************************************************/
void ledStrip_Dim(uint32 dimLevel) 
{
extern uint32  ledStrip_DimMask;
extern uint32  ledStrip_DimShift;

    switch(dimLevel)
    {
       case 1:  // 1/2 bright
           ledStrip_DimMask = 0x007F7F7F;
           ledStrip_DimShift = 1;
           break;
           
       case 2:
           ledStrip_DimMask = 0x003F3F3F;
           ledStrip_DimShift = 2;
           break;
           
       case 3:
           ledStrip_DimMask = 0x001F1F1F;
           ledStrip_DimShift = 3;
           break;
           
       case 4:
           ledStrip_DimMask = 0x000F0F0F;
           ledStrip_DimShift = 4;
           break;
           
       default:
           ledStrip_DimMask = 0x00FFFFFF;
           ledStrip_DimShift = 0;
           break;
        
    }
}

void ledStrip_bplot( int32 x, int32 y, uint8 * bitMap, int32 update)
{
    int32 dx, dy;
    int32 aindex = 0;
    int32 maxX, maxY;

    maxX = x + (int32)bitMap[aindex++];
    maxY = y  + (int32)bitMap[aindex++];

	for(dy = y; dy < maxY; dy++)
    {
		for(dx = x; dx < maxX; dx++)
        {
            ledStrip_Pixel(dx, dy, bitMap[aindex++]);
        }
    }
	if(update) ledStrip_Trigger(1);
}

/* [] END OF FILE */
