/*******************************************************************************
* File Name: stripHourPin.h  
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

#if !defined(CY_PINS_stripHourPin_H) /* Pins stripHourPin_H */
#define CY_PINS_stripHourPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "stripHourPin_aliases.h"


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
} stripHourPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   stripHourPin_Read(void);
void    stripHourPin_Write(uint8 value);
uint8   stripHourPin_ReadDataReg(void);
#if defined(stripHourPin__PC) || (CY_PSOC4_4200L) 
    void    stripHourPin_SetDriveMode(uint8 mode);
#endif
void    stripHourPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   stripHourPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void stripHourPin_Sleep(void); 
void stripHourPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(stripHourPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define stripHourPin_DRIVE_MODE_BITS        (3)
    #define stripHourPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - stripHourPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the stripHourPin_SetDriveMode() function.
         *  @{
         */
        #define stripHourPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define stripHourPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define stripHourPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define stripHourPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define stripHourPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define stripHourPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define stripHourPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define stripHourPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define stripHourPin_MASK               stripHourPin__MASK
#define stripHourPin_SHIFT              stripHourPin__SHIFT
#define stripHourPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in stripHourPin_SetInterruptMode() function.
     *  @{
     */
        #define stripHourPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define stripHourPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define stripHourPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define stripHourPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(stripHourPin__SIO)
    #define stripHourPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(stripHourPin__PC) && (CY_PSOC4_4200L)
    #define stripHourPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define stripHourPin_USBIO_DISABLE              ((uint32)(~stripHourPin_USBIO_ENABLE))
    #define stripHourPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define stripHourPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define stripHourPin_USBIO_ENTER_SLEEP          ((uint32)((1u << stripHourPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << stripHourPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define stripHourPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << stripHourPin_USBIO_SUSPEND_SHIFT)))
    #define stripHourPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << stripHourPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define stripHourPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(stripHourPin__PC)
    /* Port Configuration */
    #define stripHourPin_PC                 (* (reg32 *) stripHourPin__PC)
#endif
/* Pin State */
#define stripHourPin_PS                     (* (reg32 *) stripHourPin__PS)
/* Data Register */
#define stripHourPin_DR                     (* (reg32 *) stripHourPin__DR)
/* Input Buffer Disable Override */
#define stripHourPin_INP_DIS                (* (reg32 *) stripHourPin__PC2)

/* Interrupt configuration Registers */
#define stripHourPin_INTCFG                 (* (reg32 *) stripHourPin__INTCFG)
#define stripHourPin_INTSTAT                (* (reg32 *) stripHourPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define stripHourPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(stripHourPin__SIO)
    #define stripHourPin_SIO_REG            (* (reg32 *) stripHourPin__SIO)
#endif /* (stripHourPin__SIO_CFG) */

/* USBIO registers */
#if !defined(stripHourPin__PC) && (CY_PSOC4_4200L)
    #define stripHourPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define stripHourPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define stripHourPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define stripHourPin_DRIVE_MODE_SHIFT       (0x00u)
#define stripHourPin_DRIVE_MODE_MASK        (0x07u << stripHourPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins stripHourPin_H */


/* [] END OF FILE */
