/* ========================================
 *
 * Copyright Tymek Feldman, 2019
 * All Rights Reserved
 *
 * ========================================
*/

#include "project.h"
#include <stdio.h>

#define DEBUG_MODE        1         // Comment to disable debug prints
#define TEMP_ENABLE       1         // Comment to disable temperature reading

#define I2C_ADDRESS 0b1101000       // I2C address of RTC IC DS3231

/* define the test register to switch the PA/LNA hardware control pins */
#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008

#define HOURS       0               // Array indices for readability
#define MINUTES     1               // ^
#define SECONDS     2               // ^
#define TRUE        1
#define FALSE       0
#define RED         0x0000FF00      // RGB Color definitions
#define GREEN       0x000000FF      // ^
#define BLUE        0x00FF0000      // ^

uint8 time[3];                      // Time array H:M:S
uint8 setColor[3];                  // Color array R:G:B
uint32 setColorFull = RED;          // Converted color variable from the above array
uint8 lampState = FALSE;            // Lamp mode On/Off
uint8 brightness = 0;               // Brightness (not used)
_Bool colorUpdated = FALSE;         // Changed color flag
_Bool itsDark = FALSE;              // Shows whether it's dark or not
volatile _Bool sqwFired = FALSE;    // SQW pin flag, set inside ISR
#ifdef TEMP_ENABLE
    uint8 states[5];                    // 5 bytes containing states which are sent over BLE:
//       Bytes   |    1st    |  2nd  |  3rd  |   4th  |   5th  |
//       Values  | lampState |  PIR  |  LDR  | TempHI | TempLO |
#else
    uint8 states[3];                    // 3 bytes containing states which are sent over BLE:
//       Bytes   |    1st    |  2nd  |  3rd  |
//       Values  | lampState |  PIR  |  LDR  |
#endif

CY_ISR(sqwPin_isr_Handler){
// ISR of SQW pin interrupt: set flag and clear interrupt
// runs every second from RTC
    sqwFired = TRUE;
    sqwPin_ClearInterrupt();
}

// Update Bluetooth data
void updateCharacteristics(uint8* passedData, uint8 len, uint16 attrHandle){
    CYBLE_GATT_HANDLE_VALUE_PAIR_T handleVar;
    handleVar.attrHandle = attrHandle;
    handleVar.value.val = passedData;
    handleVar.value.len = len;
    CyBle_GattsWriteAttributeValue(&handleVar, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
}

// Set RTC to time from Bluetooth data
void setTime(uint8* timeData){
    // Convert time to a format which the device uses, as described in the datasheet
    timeData[SECONDS] = (timeData[SECONDS] % 10) | ((timeData[SECONDS] / 10) << 4);
    timeData[MINUTES] = (timeData[MINUTES] % 10) | ((timeData[MINUTES] / 10) << 4);
    // Bit 6 of the hours register sets the 12h mode, instead of 24h
    timeData[HOURS]   = (timeData[HOURS] % 10)   | ((timeData[HOURS]   / 10) << 4) | (1 << 6);
    
    #ifdef DEBUG_MODE
        char buf[20];
        sprintf(buf, "h:%d m:%d s:%d\n\r", timeData[HOURS], timeData[MINUTES], timeData[SECONDS]);
        UART_UartPutString("After conv: ");
        UART_UartPutString(buf);
    #endif
    
    I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0);      // Start at register 0
    // Send time here
    I2C_I2CMasterWriteByte(timeData[SECONDS]);
    I2C_I2CMasterWriteByte(timeData[MINUTES]);
    I2C_I2CMasterWriteByte(timeData[HOURS]);
    I2C_I2CMasterSendStop();
}

void readTime(){
    // First tell to start at register 0
    I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0);
    I2C_I2CMasterSendRestart(I2C_ADDRESS, I2C_I2C_READ_XFER_MODE);
    // Now actually read, starting at register 0
    time[SECONDS]   = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
    time[MINUTES]   = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
    time[HOURS] = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    I2C_I2CMasterSendStop();
    
    // Convert read time to normal format
    time[SECONDS] = (time[SECONDS] & 0x0F) + (((time[SECONDS] & 0x70) >> 4) * 10);
    time[MINUTES] = (time[MINUTES] & 0x0F) + (((time[MINUTES] & 0x70) >> 4) * 10);
    time[HOURS]   = (time[HOURS]   & 0x0F) + (((time[HOURS]   & 0x10) >> 4) * 10);

    updateCharacteristics(time, sizeof(time), CYBLE_SET_TIME_TIME_CHAR_HANDLE);
}

void bleEventHandler(uint32 event, void * eventParam){
    // Main Bluetooth event handler: handles connections and reads data
    
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    switch(event){
        case CYBLE_EVT_STACK_ON:
        // BLE stack is on
        
        // From page 16 of the CYBLE-224110-00 datasheet:
        // Enable the Skyworks SE2438T PA/LNA
        CSD_Write(1); // PA/LNA Mode 3, both CSD and CPS have to be 1 for BLE to work correctly
        CPS_Write(1); // ^
        // Configure the Link Layer to automatically switch PA control pin P3[2] and LNA control pin P3[3]
        CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
        CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
        
        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
        break;
        
        case CYBLE_EVT_GATT_CONNECT_IND:
        // BLE connection
        #ifdef DEBUG_MODE
            UART_UartPutString("BT is connected\n\r");
        #endif
        break;
        
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
        // BLE disconnection
        #ifdef DEBUG_MODE
            UART_UartPutString("BT is disconnected\n\r");
        #endif
        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
        break;
        
        case CYBLE_EVT_GATTS_WRITE_REQ:
        // Receiving data: parameter ‘eventParam’ contains the data written
        wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
        
        if(wrReqParam->handleValPair.attrHandle == CYBLE_SET_TIME_TIME_CHAR_HANDLE){
            // Receive time from Bluetooth in normal format
            uint8 tempTime[3];
            tempTime[HOURS]   = wrReqParam->handleValPair.value.val[0];
            tempTime[MINUTES] = wrReqParam->handleValPair.value.val[1];
            tempTime[SECONDS] = wrReqParam->handleValPair.value.val[2];
            
            updateCharacteristics(tempTime, sizeof(tempTime), CYBLE_SET_TIME_TIME_CHAR_HANDLE);
            
            #ifdef DEBUG_MODE
                char buf[20];
                sprintf(buf, "h:%d m:%d s:%d\n\r", tempTime[HOURS], tempTime[MINUTES], tempTime[SECONDS]);
                UART_UartPutString("Setting time to ");
                UART_UartPutString(buf);
            #endif
            
            setTime(tempTime); // Send that time to RTC
        }
        
        else if(wrReqParam->handleValPair.attrHandle == CYBLE_SET_COLOR_COLOR_CHAR_HANDLE){
            // Receive lamp data: color + ON/OFF + brightness
            setColor[0]     = wrReqParam->handleValPair.value.val[0]; //R
            setColor[1]     = wrReqParam->handleValPair.value.val[1]; //G
            setColor[2]     = wrReqParam->handleValPair.value.val[2]; //B
            lampState       = wrReqParam->handleValPair.value.val[3]; //Lamp On/Off
            brightness  = wrReqParam->handleValPair.value.val[4]; //Brightness (not used)
            
            if(lampState == 22){ // 0x16=d22 this is the bootloader start command
                #ifdef DEBUG_MODE
                    UART_UartPutString("Entering OTA update mode\n\r");
                #endif
                // Enter bootloader mode
                Bootloadable_SetActiveApplication(0);
                Bootloadable_Load();
                CySoftwareReset();
            }
            
            // Convert to correct 32 bit format (0x00BBRRGG)
            setColorFull = (setColor[1] | (setColor[0] << 8) | (setColor[2] << 16));
            colorUpdated = TRUE;
            
            states[0] = lampState;
            updateCharacteristics(states, sizeof(states), CYBLE_SET_COLOR_COLOR_CHAR_HANDLE);
            
            #ifdef DEBUG_MODE
                char buf[21];
                sprintf(buf, "%d:%d:%d:%d:%d\n\r",
                        setColor[0], setColor[1], setColor[2], lampState, brightness);
                UART_UartPutString("Color+state+brig: ");
                UART_UartPutString(buf);
            #endif
        }
        // Send response
        CyBle_GattsWriteRsp(cyBle_connHandle);
        break;
        
        default:
        break;
    }
}

void initRTC(){
    // SQW output at 1Hz + one time read
    I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0x0E);
    I2C_I2CMasterWriteByte(0);
    I2C_I2CMasterSendStop();
    readTime();
}

void startTemp(){
    // Initiate a temperature reading on the DS3231
    // First make sure that both bits CONV and BSY are 0,
    // only then start a new reading

    // First read the status from registers 0x0E and 0x0F
    I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0x0E);
    I2C_I2CMasterSendRestart(I2C_ADDRESS, I2C_I2C_READ_XFER_MODE);
    uint8 temp0E = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
    uint8 temp0F = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    I2C_I2CMasterSendStop();
    if(!(temp0E & 0x20) && !(temp0F & 4)){
        // If no conversion is busy, start a fresh conversion
        I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
        I2C_I2CMasterWriteByte(0x0E);
        I2C_I2CMasterWriteByte(0x20); // 1 << 5 = 0x20, this is the CONV bit
        I2C_I2CMasterSendStop();
    }
}

void readTemp(){
    // Read the temperature from registers 0x11 and 0x11
    I2C_I2CMasterSendStart(I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0x11);
    I2C_I2CMasterSendRestart(I2C_ADDRESS, I2C_I2C_READ_XFER_MODE);
    int8 tempMSB = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
    uint8 tempLSB = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
    I2C_I2CMasterSendStop();
    #ifdef DEBUG_MODE
        char buf[20];
        float temp = (float)tempMSB + (float)tempLSB/256;
        sprintf(buf, "Temp=%.2f*C\n\r", temp);
        UART_UartPutString(buf);
    #endif
    states[3] = tempMSB;
    states[4] = tempLSB;
}

void setDimLevel(_Bool dim){
    /******************************************
    0: No dimming
    1: Dim to 50%
    2: Dim to 25%
    3: Dim to 12.5%
    4: Dim to 6.3%
    ******************************************/
    
    if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
    /*no warnings pls*/;
    
    int16 adcResult = ADC_GetResult16(0); // Read adc data in 16 bit value
    
    #ifdef DEBUG_MODE
        char buf[16];
        sprintf(buf, "ADC=%d\n\r", adcResult);
        UART_UartPutString(buf);
    #endif
    
    states[2] = adcResult & 0xFF;
    
    if(dim){
        itsDark = FALSE;
        // Range: 0->127 (dark->light)
        if(adcResult > 70)        ledStrip_Dim(0);
        else if(adcResult > 60)   ledStrip_Dim(1);
        else if(adcResult > 40)   ledStrip_Dim(2);
        else if(adcResult > 20)   ledStrip_Dim(3);
        else{                     
            ledStrip_Dim(4);
            itsDark = TRUE;
        }
    }
}

void updateClockFull(){
    // Update clock LEDs for full clock when somebody is in the room
    
    ledStrip_MemClear(0);
    uint32 hrColor  = BLUE;
    uint32 minColor = RED;
    uint32 secColor = GREEN;
    
    // Hours
    uint8 hourIndex = 44;
    if(time[HOURS] != 0 && time[HOURS] != 12)       // Can be either 0 or 12, depending on AM/PM
        hourIndex = 44 - time[HOURS]*4;             // Count down starting at 44, total LEDs 48
    for(int i = 44; i >= hourIndex; i--){
        ledStrip_Pixel(i, 0, hrColor);              // Color all up to the correct hour-hand
    }
    
    // Minutes
    uint8 minIndex = (60 - time[MINUTES] + 2) % 60; // Count down starting at 2, total LEDs 60
    switch(minIndex){
        case 0:                                     // Minute nr. 2
            ledStrip_Pixel(0, 1, minColor);
        //break;                                    // No break, if 2, should color the rest too
        case 1:                                     // Minute nr. 1
            ledStrip_Pixel(1, 1, minColor);
        //break;                                    // Again no break, if 1, should color the rest too
        case 2:                                     // Minute nr. 0/60
            ledStrip_Pixel(2, 1, minColor);
        break;                                      // Break here, the rest is for minutes>2
        default:
            ledStrip_Pixel(0, 1, minColor);
            ledStrip_Pixel(1, 1, minColor);
            ledStrip_Pixel(2, 1, minColor);
            for(int i = 59; i >= minIndex; i--){
                ledStrip_Pixel(i, 1, minColor);     // Color all up to the correct minute-hand
            }
        break;
    }
    
    // Seconds
    uint8 secIndex = (60 - time[SECONDS] + 2) % 60; // Count down starting at 2, total LEDs 60
    if(time[SECONDS] <= time[MINUTES]) ledStrip_Pixel(secIndex, 1, (minColor | secColor));
    else ledStrip_Pixel(secIndex, 1, secColor);

    ledStrip_Trigger(1);
}

void updateClockEco(){
    // Update clock LEDs for eco mode when there is nobody in the room
    
    ledStrip_MemClear(0);
    uint32 hrColor  = GREEN;
    uint32 minColor = BLUE;
    uint32 secColor = RED;
    
    // Hours
    uint8 hourIndex = 44;
    if(time[HOURS] != 0 && time[HOURS] != 12)       // Can be either 0 or 12, depending on AM/PM
        hourIndex = 44 - time[HOURS]*4;             // Count down starting at 44, total LEDs 48
    ledStrip_Pixel(hourIndex, 0, hrColor);
    // Minutes, shift by 2 because of the physical alignment of LEDs
    uint8 minIndex = (60 - time[MINUTES] + 2) % 60;
    // Seconds, shift by 2 because of the physical alignment of LEDs
    uint8 secIndex = (60 - time[SECONDS] + 2) % 60;
    if(time[SECONDS] == time[MINUTES]) ledStrip_Pixel(secIndex, 1, (minColor | secColor));
    else{
        ledStrip_Pixel(minIndex, 1, minColor);
        ledStrip_Pixel(secIndex, 1, secColor);
    }
    ledStrip_Trigger(1);
}

void updateClock(){
    
    if(pirPin_Read()){
        #ifdef DEBUG_MODE
            UART_UartPutString("PIR On\n\r");
        #endif
        states[1] = 1;
        if(itsDark) updateClockEco();
        else updateClockFull();
    }
    else{
        #ifdef DEBUG_MODE
            UART_UartPutString("PIR Off\n\r");
        #endif
        states[1] = 0;
        updateClockEco();
    }
}

void initialization(){
    sqwPin_isr_StartEx(sqwPin_isr_Handler);
    #ifdef DEBUG_MODE
        UART_Start();
        UART_UartPutString("Start\n\r");
    #endif
    // Internal pullup resistors for I2C pins
    I2C_scl_SetDriveMode(I2C_scl_DM_RES_UP);
    I2C_sda_SetDriveMode(I2C_sda_DM_RES_UP);
    I2C_Start();
    CyBle_Start(bleEventHandler);
    ledStrip_Start();
    initRTC();
    states[0] = lampState;
    updateCharacteristics(states, sizeof(states), CYBLE_SET_COLOR_COLOR_CHAR_HANDLE);
    ADC_Start();
    ADC_StartConvert();
    if(ADC_IsEndConversion(ADC_WAIT_FOR_RESULT)) ADC_GetResult16(0); // First dummy read
    ledStrip_Dim(0);
}

int main(void){
    
    // Needed for OTA update
    #if !defined(__ARMCC_VERSION)
        InitializeBootloaderSRAM();
    #endif
    AfterImageUpdate();
    
    // Enable global interrupts
    CyGlobalIntEnable;
    initialization();
    
    while(1){

        if(!lampState){ // Normal clock mode
            
            if(sqwFired){ // Flag from RTC interrupt
                #ifdef TEMP_ENABLE
                    startTemp();        // Start a temperature reading
                #endif
                ADC_StartConvert();     // Start reading of light from LDR
                readTime();             // Read current time
                #ifdef DEBUG_MODE
                    char buf[20];
                    sprintf(buf, "h:%d m:%d s:%d\n\r", time[HOURS], time[MINUTES], time[SECONDS]);
                    UART_UartPutString(buf);
                #endif
                setDimLevel(1);         // Set LED brightness from LDR
                #ifdef TEMP_ENABLE
                    readTemp();         // Read the temperature from DS3231
                #endif
                updateClock();          // Refresh LEDs with new time
                updateCharacteristics(states, sizeof(states), CYBLE_SET_COLOR_COLOR_CHAR_HANDLE);
                sqwFired = FALSE;
            }
        }
        else{ // Lamp mode

            if(colorUpdated){
                // If the color has been changed (via app), refresh the LEDs
                ledStrip_Dim(0);        // Brightness is included in the colors
                
                for(int i = 0; i < 60; i++){
                    ledStrip_Pixel(i, 0, setColorFull);
                    ledStrip_Pixel(i, 1, setColorFull);
                }
                
                ledStrip_Trigger(1);
                colorUpdated = FALSE;
            }
            if(sqwFired){               // Still run every second to update data
                #ifdef TEMP_ENABLE
                    startTemp();        // Start a temperature reading
                #endif
                ADC_StartConvert();     // Start reading of light from LDR
                setDimLevel(0);         // Set LED brightness from LDR
                #ifdef TEMP_ENABLE
                    readTemp();         // Read the temperature from DS3231
                #endif
                if(pirPin_Read()) states[1] = 1;
                else states[1] = 0;
                updateCharacteristics(states, sizeof(states), CYBLE_SET_COLOR_COLOR_CHAR_HANDLE);
                sqwFired = FALSE;
            }
        }
        CyBle_ProcessEvents(); // Process BT
    }
}

/* [] END OF FILE */