/* ========================================
 *
 * Strip Light Controller
 * By Mark Hastings
 *
 * 05/27/2013  v1.0  Mark Hastings   Initial working version
 *
 * ========================================
*/

#if (!defined(CY_SLIGHTS_ledStrip_H))
#define CY_SLIGHTS_ledStrip_H

#include "cytypes.h"
#include "cyfitter.h"

/* Function Prototypes */
void   ledStrip_Start(void);
void   ledStrip_Stop(void);
void   ledStrip_WriteColor(uint32 color);
void   ledStrip_DisplayClear(uint32 color);
void   ledStrip_MemClear(uint32 color);
void   ledStrip_Trigger(uint32 rst);
uint32 ledStrip_Ready(void);

void   ledStrip_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, uint32 color);
void   ledStrip_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, uint32 color);
void   ledStrip_DrawCircle (int32 x0, int32 y0, int32 radius, uint32 color);
void   ledStrip_Pixel(int32 x, int32 y, uint32 color);
uint32 ledStrip_GetPixel(int32 x, int32 y);
uint32 ledStrip_ColorInc(uint32 incValue);
void   ledStrip_Dim(uint32 dimLevel); 

#define ledStrip_DimLevel_0   0
#define ledStrip_DimLevel_1   1
#define ledStrip_DimLevel_2   2
#define ledStrip_DimLevel_3   3
#define ledStrip_DimLevel_4   4




#define ledStrip_CIRQ_Enable() CyIntEnable(ledStrip_CIRQ__INTC_NUMBER ); 
#define ledStrip_CIRQ_Disable() CyIntDisable(ledStrip_CIRQ__INTC_NUMBER );
CY_ISR_PROTO(ledStrip_CISR);

#define ledStrip_FIRQ_Enable() CyIntEnable(ledStrip_FIRQ__INTC_NUMBER ); 
#define ledStrip_FIRQ_Disable() CyIntDisable(ledStrip_FIRQ__INTC_NUMBER );
CY_ISR_PROTO(ledStrip_FISR);

/* Register Definitions */
#define ledStrip_DATA         (*(reg8 *) ledStrip_B_WS2811_dshifter_u0__F0_REG)
#define ledStrip_DATA_PTR     ((reg8 *)  ledStrip_B_WS2811_dshifter_u0__F0_REG)

#define ledStrip_CONTROL      (*(reg8 *) ledStrip_B_WS2811_ctrl__CONTROL_REG)
#define ledStrip_STATUS       (*(reg8 *) ledStrip_B_WS2811_StatusReg__STATUS_REG)

#define ledStrip_Period       (*(reg8 *) ledStrip_B_WS2811_pwm8_u0__F0_REG)
#define ledStrip_Period_PTR   ((reg8 *)  ledStrip_B_WS2811_pwm8_u0__F0_REG)

#define ledStrip_Compare0     (*(reg8 *) ledStrip_B_WS2811_pwm8_u0__D0_REG)
#define ledStrip_Compare1     (*(reg8 *) ledStrip_B_WS2811_pwm8_u0__D1_REG)

#define ledStrip_Period2      (*(reg8 *) ledStrip_B_WS2811_pwm8_u0__F1_REG)
#define ledStrip_Period2_PTR  ((reg8 *)  ledStrip_B_WS2811_pwm8_u0__F1_REG)

#define ledStrip_ACTL0_REG    (*(reg8 *) ledStrip_B_WS2811_pwm8_u0__DP_AUX_CTL_REG)
#define ledStrip_DISABLE_FIFO  0x03


#define ledStrip_Channel      (*(reg8 *) ledStrip_StringSel_Sync_ctrl_reg__CONTROL_REG)
#define ledStrip_Channel_PTR  ((reg8 *)  ledStrip_StringSel_Sync_ctrl_reg__CONTROL_REG)



/* Status Register Constants  */
#define ledStrip_FIFO_EMPTY       0x01
#define ledStrip_FIFO_NOT_FULL    0x02
#define ledStrip_STATUS_ENABLE    0x80
#define ledStrip_STATUS_XFER_CMPT 0x40

/* Control Register Constants */
#define ledStrip_ENABLE         0x01
#define ledStrip_DISABLE        0x00
#define ledStrip_RESTART        0x02
#define ledStrip_CNTL           0x04
#define ledStrip_FIFO_IRQ_EN    0x08
#define ledStrip_XFRCMPT_IRQ_EN 0x10
#define ledStrip_ALL_IRQ_EN     0x18
#define ledStrip_NEXT_ROW       0x20

#define ledStrip_TRANSFER           1
#define ledStrip_TRANSFER_FIRMWARE  0
#define ledStrip_TRANSFER_ISR       1
#define ledStrip_TRANSFER_DMA       2

#define ledStrip_SPEED        
#define ledStrip_SPEED_400KHZ 0
#define ledStrip_SPEED_800KHZ 1

#define ledStrip_MEMORY_TYPE  0
#define ledStrip_MEMORY_RGB   0
#define ledStrip_MEMORY_LUT   1

#if (CY_PSOC3 || CY_PSOC5LP)
    #define  ledStrip_PERIOD     ((BCLK__BUS_CLK__KHZ)/800)
#elif (CY_PSOC4)
    #define  ledStrip_PERIOD     ((CYDEV_BCLK__HFCLK__KHZ)/800)
#endif /* CY_PSOC5A */
        

#define  ledStrip_DATA_ZERO  ((ledStrip_PERIOD * 20)/25) 
#define  ledStrip_DATA_ONE   ((ledStrip_PERIOD * 12)/25) 


#if (ledStrip_SPEED_800KHZ)
    #define ledStrip_BYTE_TIME_US 10u
    #define ledStrip_WORD_TIME_US 30u
#else
    #define ledStrip_BYTE_TIME_US 20u
    #define ledStrip_WORD_TIME_US 60u
#endif

#define ledStrip_COLUMNS     60
#define ledStrip_ROWS        2
#define ledStrip_TOTAL_LEDS   (ledStrip_COLUMNS*ledStrip_ROWS)

#define ledStrip_ARRAY_COLS  (int32)(60)
#define ledStrip_ARRAY_ROWS  (int32)(2)
#define ledStrip_CHIP        (2)
#define ledStrip_CHIP_WS2811 1
#define ledStrip_CHIP_WS2812 2

#define ledStrip_MIN_X        (int32)0u
#define ledStrip_MAX_X        (int32)(ledStrip_COLUMNS - 1)
#define ledStrip_MIN_Y        (int32)0u
#define ledStrip_MAX_Y        (int32)(ledStrip_ROWS - 1)

//#define ledStrip_RBCOLORS     48
#define ledStrip_COLOR_WHEEL_SIZE  24

#if(ledStrip_CHIP == ledStrip_CHIP_WS2812)
#define ledStrip_RED_MASK   0x0000FF00
#define ledStrip_GREEN_MASK 0x000000FF
#define ledStrip_BLUE_MASK  0x00FF0000
#else
#define ledStrip_RED_MASK   0x000000FF
#define ledStrip_GREEN_MASK 0x0000FF00
#define ledStrip_BLUE_MASK  0x00FF0000	
#endif

#if(ledStrip_MEMORY_TYPE == ledStrip_MEMORY_RGB)
   #define ledStrip_getColor( a ) ledStrip_CLUT[a]
#else  /* Else use lookup table */
   #define ledStrip_getColor( a ) a
#endif


#define ledStrip_CWHEEL_SIZE 24
#define ledStrip_YELLOW      ledStrip_getColor(1)
#define ledStrip_GREEN       ledStrip_getColor((70 + ledStrip_CWHEEL_SIZE))
#define ledStrip_ORANGE      ledStrip_getColor(20)
#define ledStrip_BLACK       ledStrip_getColor((0 + ledStrip_CWHEEL_SIZE))
#define ledStrip_OFF         ledStrip_getColor((0 + ledStrip_CWHEEL_SIZE))
#define ledStrip_LTBLUE      ledStrip_getColor((1 + ledStrip_CWHEEL_SIZE))
#define ledStrip_MBLUE       ledStrip_getColor((2 + ledStrip_CWHEEL_SIZE))
#define ledStrip_BLUE        ledStrip_getColor((3 + ledStrip_CWHEEL_SIZE))
#define ledStrip_LTGREEN     ledStrip_getColor((4 + ledStrip_CWHEEL_SIZE))
#define ledStrip_MGREEN      ledStrip_getColor((8 + ledStrip_CWHEEL_SIZE))
//#define ledStrip_GREEN       (12 + ledStrip_CWHEEL_SIZE) 
#define ledStrip_LTRED       ledStrip_getColor((16 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_LTYELLOW    ledStrip_getColor((20 + ledStrip_CWHEEL_SIZE))
#define ledStrip_MGRED       ledStrip_getColor((32 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_RED         ledStrip_getColor((48 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_MAGENTA     ledStrip_getColor((51 + ledStrip_CWHEEL_SIZE))
#define ledStrip_WHITE       ledStrip_getColor((63 + ledStrip_CWHEEL_SIZE)) 

#define ledStrip_SPRING_GREEN ledStrip_getColor((64 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_TURQUOSE    ledStrip_getColor((65 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_CYAN        ledStrip_getColor((66 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_OCEAN       ledStrip_getColor((67 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_VIOLET      ledStrip_getColor((68 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_RASPBERRY   ledStrip_getColor((69 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_DIM_WHITE   ledStrip_getColor((71 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_DIM_BLUE    ledStrip_getColor((72 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_INVISIBLE   ledStrip_getColor((73 + ledStrip_CWHEEL_SIZE))

#define ledStrip_COLD_TEMP   ledStrip_getColor((80 + ledStrip_CWHEEL_SIZE)) 
#define ledStrip_HOT_TEMP    ledStrip_getColor((95 + ledStrip_CWHEEL_SIZE)) 

#define ledStrip_CLUT_SIZE  (96 + ledStrip_CWHEEL_SIZE)

#define ledStrip_RESET_DELAY_US  55

#endif  /* CY_SLIGHTS_ledStrip_H */

//[] END OF FILE
