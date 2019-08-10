/*******************************************************************************
* File Name: HourPin.h  
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

#if !defined(CY_PINS_HourPin_H) /* Pins HourPin_H */
#define CY_PINS_HourPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HourPin_aliases.h"


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
} HourPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HourPin_Read(void);
void    HourPin_Write(uint8 value);
uint8   HourPin_ReadDataReg(void);
#if defined(HourPin__PC) || (CY_PSOC4_4200L) 
    void    HourPin_SetDriveMode(uint8 mode);
#endif
void    HourPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   HourPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HourPin_Sleep(void); 
void HourPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HourPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HourPin_DRIVE_MODE_BITS        (3)
    #define HourPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HourPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HourPin_SetDriveMode() function.
         *  @{
         */
        #define HourPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HourPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HourPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HourPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HourPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HourPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HourPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HourPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HourPin_MASK               HourPin__MASK
#define HourPin_SHIFT              HourPin__SHIFT
#define HourPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HourPin_SetInterruptMode() function.
     *  @{
     */
        #define HourPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HourPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HourPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HourPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HourPin__SIO)
    #define HourPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HourPin__PC) && (CY_PSOC4_4200L)
    #define HourPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HourPin_USBIO_DISABLE              ((uint32)(~HourPin_USBIO_ENABLE))
    #define HourPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HourPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HourPin_USBIO_ENTER_SLEEP          ((uint32)((1u << HourPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HourPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define HourPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HourPin_USBIO_SUSPEND_SHIFT)))
    #define HourPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HourPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define HourPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HourPin__PC)
    /* Port Configuration */
    #define HourPin_PC                 (* (reg32 *) HourPin__PC)
#endif
/* Pin State */
#define HourPin_PS                     (* (reg32 *) HourPin__PS)
/* Data Register */
#define HourPin_DR                     (* (reg32 *) HourPin__DR)
/* Input Buffer Disable Override */
#define HourPin_INP_DIS                (* (reg32 *) HourPin__PC2)

/* Interrupt configuration Registers */
#define HourPin_INTCFG                 (* (reg32 *) HourPin__INTCFG)
#define HourPin_INTSTAT                (* (reg32 *) HourPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HourPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HourPin__SIO)
    #define HourPin_SIO_REG            (* (reg32 *) HourPin__SIO)
#endif /* (HourPin__SIO_CFG) */

/* USBIO registers */
#if !defined(HourPin__PC) && (CY_PSOC4_4200L)
    #define HourPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HourPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HourPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HourPin_DRIVE_MODE_SHIFT       (0x00u)
#define HourPin_DRIVE_MODE_MASK        (0x07u << HourPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HourPin_H */


/* [] END OF FILE */
