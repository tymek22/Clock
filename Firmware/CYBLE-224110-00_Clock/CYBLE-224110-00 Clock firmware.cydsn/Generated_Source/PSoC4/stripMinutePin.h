/*******************************************************************************
* File Name: stripMinutePin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_stripMinutePin_H) /* Pins stripMinutePin_H */
#define CY_PINS_stripMinutePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "stripMinutePin_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} stripMinutePin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   stripMinutePin_Read(void);
void    stripMinutePin_Write(uint8 value);
uint8   stripMinutePin_ReadDataReg(void);
#if defined(stripMinutePin__PC) || (CY_PSOC4_4200L) 
    void    stripMinutePin_SetDriveMode(uint8 mode);
#endif
void    stripMinutePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   stripMinutePin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void stripMinutePin_Sleep(void); 
void stripMinutePin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(stripMinutePin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define stripMinutePin_DRIVE_MODE_BITS        (3)
    #define stripMinutePin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - stripMinutePin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the stripMinutePin_SetDriveMode() function.
         *  @{
         */
        #define stripMinutePin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define stripMinutePin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define stripMinutePin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define stripMinutePin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define stripMinutePin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define stripMinutePin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define stripMinutePin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define stripMinutePin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define stripMinutePin_MASK               stripMinutePin__MASK
#define stripMinutePin_SHIFT              stripMinutePin__SHIFT
#define stripMinutePin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in stripMinutePin_SetInterruptMode() function.
     *  @{
     */
        #define stripMinutePin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define stripMinutePin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define stripMinutePin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define stripMinutePin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(stripMinutePin__SIO)
    #define stripMinutePin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(stripMinutePin__PC) && (CY_PSOC4_4200L)
    #define stripMinutePin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define stripMinutePin_USBIO_DISABLE              ((uint32)(~stripMinutePin_USBIO_ENABLE))
    #define stripMinutePin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define stripMinutePin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define stripMinutePin_USBIO_ENTER_SLEEP          ((uint32)((1u << stripMinutePin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << stripMinutePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define stripMinutePin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << stripMinutePin_USBIO_SUSPEND_SHIFT)))
    #define stripMinutePin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << stripMinutePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define stripMinutePin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(stripMinutePin__PC)
    /* Port Configuration */
    #define stripMinutePin_PC                 (* (reg32 *) stripMinutePin__PC)
#endif
/* Pin State */
#define stripMinutePin_PS                     (* (reg32 *) stripMinutePin__PS)
/* Data Register */
#define stripMinutePin_DR                     (* (reg32 *) stripMinutePin__DR)
/* Input Buffer Disable Override */
#define stripMinutePin_INP_DIS                (* (reg32 *) stripMinutePin__PC2)

/* Interrupt configuration Registers */
#define stripMinutePin_INTCFG                 (* (reg32 *) stripMinutePin__INTCFG)
#define stripMinutePin_INTSTAT                (* (reg32 *) stripMinutePin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define stripMinutePin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(stripMinutePin__SIO)
    #define stripMinutePin_SIO_REG            (* (reg32 *) stripMinutePin__SIO)
#endif /* (stripMinutePin__SIO_CFG) */

/* USBIO registers */
#if !defined(stripMinutePin__PC) && (CY_PSOC4_4200L)
    #define stripMinutePin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define stripMinutePin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define stripMinutePin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define stripMinutePin_DRIVE_MODE_SHIFT       (0x00u)
#define stripMinutePin_DRIVE_MODE_MASK        (0x07u << stripMinutePin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins stripMinutePin_H */


/* [] END OF FILE */
