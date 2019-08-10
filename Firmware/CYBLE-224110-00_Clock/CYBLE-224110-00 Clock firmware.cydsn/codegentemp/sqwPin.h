/*******************************************************************************
* File Name: sqwPin.h  
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

#if !defined(CY_PINS_sqwPin_H) /* Pins sqwPin_H */
#define CY_PINS_sqwPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "sqwPin_aliases.h"


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
} sqwPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   sqwPin_Read(void);
void    sqwPin_Write(uint8 value);
uint8   sqwPin_ReadDataReg(void);
#if defined(sqwPin__PC) || (CY_PSOC4_4200L) 
    void    sqwPin_SetDriveMode(uint8 mode);
#endif
void    sqwPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   sqwPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void sqwPin_Sleep(void); 
void sqwPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(sqwPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define sqwPin_DRIVE_MODE_BITS        (3)
    #define sqwPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - sqwPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the sqwPin_SetDriveMode() function.
         *  @{
         */
        #define sqwPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define sqwPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define sqwPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define sqwPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define sqwPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define sqwPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define sqwPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define sqwPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define sqwPin_MASK               sqwPin__MASK
#define sqwPin_SHIFT              sqwPin__SHIFT
#define sqwPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sqwPin_SetInterruptMode() function.
     *  @{
     */
        #define sqwPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define sqwPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define sqwPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define sqwPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(sqwPin__SIO)
    #define sqwPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(sqwPin__PC) && (CY_PSOC4_4200L)
    #define sqwPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define sqwPin_USBIO_DISABLE              ((uint32)(~sqwPin_USBIO_ENABLE))
    #define sqwPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define sqwPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define sqwPin_USBIO_ENTER_SLEEP          ((uint32)((1u << sqwPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << sqwPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define sqwPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << sqwPin_USBIO_SUSPEND_SHIFT)))
    #define sqwPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << sqwPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define sqwPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(sqwPin__PC)
    /* Port Configuration */
    #define sqwPin_PC                 (* (reg32 *) sqwPin__PC)
#endif
/* Pin State */
#define sqwPin_PS                     (* (reg32 *) sqwPin__PS)
/* Data Register */
#define sqwPin_DR                     (* (reg32 *) sqwPin__DR)
/* Input Buffer Disable Override */
#define sqwPin_INP_DIS                (* (reg32 *) sqwPin__PC2)

/* Interrupt configuration Registers */
#define sqwPin_INTCFG                 (* (reg32 *) sqwPin__INTCFG)
#define sqwPin_INTSTAT                (* (reg32 *) sqwPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define sqwPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(sqwPin__SIO)
    #define sqwPin_SIO_REG            (* (reg32 *) sqwPin__SIO)
#endif /* (sqwPin__SIO_CFG) */

/* USBIO registers */
#if !defined(sqwPin__PC) && (CY_PSOC4_4200L)
    #define sqwPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define sqwPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define sqwPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define sqwPin_DRIVE_MODE_SHIFT       (0x00u)
#define sqwPin_DRIVE_MODE_MASK        (0x07u << sqwPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins sqwPin_H */


/* [] END OF FILE */
