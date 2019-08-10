/*******************************************************************************
* File Name: ldrPin.h  
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

#if !defined(CY_PINS_ldrPin_H) /* Pins ldrPin_H */
#define CY_PINS_ldrPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ldrPin_aliases.h"


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
} ldrPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ldrPin_Read(void);
void    ldrPin_Write(uint8 value);
uint8   ldrPin_ReadDataReg(void);
#if defined(ldrPin__PC) || (CY_PSOC4_4200L) 
    void    ldrPin_SetDriveMode(uint8 mode);
#endif
void    ldrPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   ldrPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ldrPin_Sleep(void); 
void ldrPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ldrPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ldrPin_DRIVE_MODE_BITS        (3)
    #define ldrPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ldrPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ldrPin_SetDriveMode() function.
         *  @{
         */
        #define ldrPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ldrPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ldrPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ldrPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ldrPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ldrPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ldrPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ldrPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ldrPin_MASK               ldrPin__MASK
#define ldrPin_SHIFT              ldrPin__SHIFT
#define ldrPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ldrPin_SetInterruptMode() function.
     *  @{
     */
        #define ldrPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ldrPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ldrPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ldrPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ldrPin__SIO)
    #define ldrPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ldrPin__PC) && (CY_PSOC4_4200L)
    #define ldrPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ldrPin_USBIO_DISABLE              ((uint32)(~ldrPin_USBIO_ENABLE))
    #define ldrPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ldrPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ldrPin_USBIO_ENTER_SLEEP          ((uint32)((1u << ldrPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ldrPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define ldrPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ldrPin_USBIO_SUSPEND_SHIFT)))
    #define ldrPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ldrPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define ldrPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ldrPin__PC)
    /* Port Configuration */
    #define ldrPin_PC                 (* (reg32 *) ldrPin__PC)
#endif
/* Pin State */
#define ldrPin_PS                     (* (reg32 *) ldrPin__PS)
/* Data Register */
#define ldrPin_DR                     (* (reg32 *) ldrPin__DR)
/* Input Buffer Disable Override */
#define ldrPin_INP_DIS                (* (reg32 *) ldrPin__PC2)

/* Interrupt configuration Registers */
#define ldrPin_INTCFG                 (* (reg32 *) ldrPin__INTCFG)
#define ldrPin_INTSTAT                (* (reg32 *) ldrPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ldrPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ldrPin__SIO)
    #define ldrPin_SIO_REG            (* (reg32 *) ldrPin__SIO)
#endif /* (ldrPin__SIO_CFG) */

/* USBIO registers */
#if !defined(ldrPin__PC) && (CY_PSOC4_4200L)
    #define ldrPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ldrPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ldrPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ldrPin_DRIVE_MODE_SHIFT       (0x00u)
#define ldrPin_DRIVE_MODE_MASK        (0x07u << ldrPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ldrPin_H */


/* [] END OF FILE */
