/*******************************************************************************
* File Name: stripMinutePin.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "stripMinutePin.h"

static stripMinutePin_BACKUP_STRUCT  stripMinutePin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: stripMinutePin_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet stripMinutePin_SUT.c usage_stripMinutePin_Sleep_Wakeup
*******************************************************************************/
void stripMinutePin_Sleep(void)
{
    #if defined(stripMinutePin__PC)
        stripMinutePin_backup.pcState = stripMinutePin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            stripMinutePin_backup.usbState = stripMinutePin_CR1_REG;
            stripMinutePin_USB_POWER_REG |= stripMinutePin_USBIO_ENTER_SLEEP;
            stripMinutePin_CR1_REG &= stripMinutePin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(stripMinutePin__SIO)
        stripMinutePin_backup.sioState = stripMinutePin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        stripMinutePin_SIO_REG &= (uint32)(~stripMinutePin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: stripMinutePin_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to stripMinutePin_Sleep() for an example usage.
*******************************************************************************/
void stripMinutePin_Wakeup(void)
{
    #if defined(stripMinutePin__PC)
        stripMinutePin_PC = stripMinutePin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            stripMinutePin_USB_POWER_REG &= stripMinutePin_USBIO_EXIT_SLEEP_PH1;
            stripMinutePin_CR1_REG = stripMinutePin_backup.usbState;
            stripMinutePin_USB_POWER_REG &= stripMinutePin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(stripMinutePin__SIO)
        stripMinutePin_SIO_REG = stripMinutePin_backup.sioState;
    #endif
}


/* [] END OF FILE */
