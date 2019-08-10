/*******************************************************************************
* File Name: MinutePin.h  
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

#if !defined(CY_PINS_MinutePin_H) /* Pins MinutePin_H */
#define CY_PINS_MinutePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MinutePin_aliases.h"


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
} MinutePin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MinutePin_Read(void);
void    MinutePin_Write(uint8 value);
uint8   MinutePin_ReadDataReg(void);
#if defined(MinutePin__PC) || (CY_PSOC4_4200L) 
    void    MinutePin_SetDriveMode(uint8 mode);
#endif
void    MinutePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   MinutePin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MinutePin_Sleep(void); 
void MinutePin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MinutePin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MinutePin_DRIVE_MODE_BITS        (3)
    #define MinutePin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MinutePin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MinutePin_SetDriveMode() function.
         *  @{
         */
        #define MinutePin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MinutePin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MinutePin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MinutePin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MinutePin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MinutePin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MinutePin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MinutePin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MinutePin_MASK               MinutePin__MASK
#define MinutePin_SHIFT              MinutePin__SHIFT
#define MinutePin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MinutePin_SetInterruptMode() function.
     *  @{
     */
        #define MinutePin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MinutePin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MinutePin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MinutePin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MinutePin__SIO)
    #define MinutePin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MinutePin__PC) && (CY_PSOC4_4200L)
    #define MinutePin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MinutePin_USBIO_DISABLE              ((uint32)(~MinutePin_USBIO_ENABLE))
    #define MinutePin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MinutePin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MinutePin_USBIO_ENTER_SLEEP          ((uint32)((1u << MinutePin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MinutePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define MinutePin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MinutePin_USBIO_SUSPEND_SHIFT)))
    #define MinutePin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MinutePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define MinutePin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MinutePin__PC)
    /* Port Configuration */
    #define MinutePin_PC                 (* (reg32 *) MinutePin__PC)
#endif
/* Pin State */
#define MinutePin_PS                     (* (reg32 *) MinutePin__PS)
/* Data Register */
#define MinutePin_DR                     (* (reg32 *) MinutePin__DR)
/* Input Buffer Disable Override */
#define MinutePin_INP_DIS                (* (reg32 *) MinutePin__PC2)

/* Interrupt configuration Registers */
#define MinutePin_INTCFG                 (* (reg32 *) MinutePin__INTCFG)
#define MinutePin_INTSTAT                (* (reg32 *) MinutePin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MinutePin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MinutePin__SIO)
    #define MinutePin_SIO_REG            (* (reg32 *) MinutePin__SIO)
#endif /* (MinutePin__SIO_CFG) */

/* USBIO registers */
#if !defined(MinutePin__PC) && (CY_PSOC4_4200L)
    #define MinutePin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MinutePin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MinutePin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MinutePin_DRIVE_MODE_SHIFT       (0x00u)
#define MinutePin_DRIVE_MODE_MASK        (0x07u << MinutePin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MinutePin_H */


/* [] END OF FILE */
