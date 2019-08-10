/*******************************************************************************
* File Name: stripHourPin.c  
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
#include "stripHourPin.h"

static stripHourPin_BACKUP_STRUCT  stripHourPin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: stripHourPin_Sleep
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
*  \snippet stripHourPin_SUT.c usage_stripHourPin_Sleep_Wakeup
*******************************************************************************/
void stripHourPin_Sleep(void)
{
    #if defined(stripHourPin__PC)
        stripHourPin_backup.pcState = stripHourPin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            stripHourPin_backup.usbState = stripHourPin_CR1_REG;
            stripHourPin_USB_POWER_REG |= stripHourPin_USBIO_ENTER_SLEEP;
            stripHourPin_CR1_REG &= stripHourPin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(stripHourPin__SIO)
        stripHourPin_backup.sioState = stripHourPin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        stripHourPin_SIO_REG &= (uint32)(~stripHourPin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: stripHourPin_Wakeup
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
*  Refer to stripHourPin_Sleep() for an example usage.
*******************************************************************************/
void stripHourPin_Wakeup(void)
{
    #if defined(stripHourPin__PC)
        stripHourPin_PC = stripHourPin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            stripHourPin_USB_POWER_REG &= stripHourPin_USBIO_EXIT_SLEEP_PH1;
            stripHourPin_CR1_REG = stripHourPin_backup.usbState;
            stripHourPin_USB_POWER_REG &= stripHourPin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(stripHourPin__SIO)
        stripHourPin_SIO_REG = stripHourPin_backup.sioState;
    #endif
}


/* [] END OF FILE */
