/*******************************************************************************
* File Name: SW2_S.h  
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

#if !defined(CY_PINS_SW2_S_H) /* Pins SW2_S_H */
#define CY_PINS_SW2_S_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW2_S_aliases.h"


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
} SW2_S_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SW2_S_Read(void);
void    SW2_S_Write(uint8 value);
uint8   SW2_S_ReadDataReg(void);
#if defined(SW2_S__PC) || (CY_PSOC4_4200L) 
    void    SW2_S_SetDriveMode(uint8 mode);
#endif
void    SW2_S_SetInterruptMode(uint16 position, uint16 mode);
uint8   SW2_S_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SW2_S_Sleep(void); 
void SW2_S_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SW2_S__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SW2_S_DRIVE_MODE_BITS        (3)
    #define SW2_S_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW2_S_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SW2_S_SetDriveMode() function.
         *  @{
         */
        #define SW2_S_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SW2_S_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SW2_S_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SW2_S_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SW2_S_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SW2_S_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SW2_S_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SW2_S_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SW2_S_MASK               SW2_S__MASK
#define SW2_S_SHIFT              SW2_S__SHIFT
#define SW2_S_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SW2_S_SetInterruptMode() function.
     *  @{
     */
        #define SW2_S_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SW2_S_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SW2_S_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SW2_S_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SW2_S__SIO)
    #define SW2_S_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SW2_S__PC) && (CY_PSOC4_4200L)
    #define SW2_S_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SW2_S_USBIO_DISABLE              ((uint32)(~SW2_S_USBIO_ENABLE))
    #define SW2_S_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SW2_S_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SW2_S_USBIO_ENTER_SLEEP          ((uint32)((1u << SW2_S_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SW2_S_USBIO_SUSPEND_DEL_SHIFT)))
    #define SW2_S_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SW2_S_USBIO_SUSPEND_SHIFT)))
    #define SW2_S_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SW2_S_USBIO_SUSPEND_DEL_SHIFT)))
    #define SW2_S_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SW2_S__PC)
    /* Port Configuration */
    #define SW2_S_PC                 (* (reg32 *) SW2_S__PC)
#endif
/* Pin State */
#define SW2_S_PS                     (* (reg32 *) SW2_S__PS)
/* Data Register */
#define SW2_S_DR                     (* (reg32 *) SW2_S__DR)
/* Input Buffer Disable Override */
#define SW2_S_INP_DIS                (* (reg32 *) SW2_S__PC2)

/* Interrupt configuration Registers */
#define SW2_S_INTCFG                 (* (reg32 *) SW2_S__INTCFG)
#define SW2_S_INTSTAT                (* (reg32 *) SW2_S__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SW2_S_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SW2_S__SIO)
    #define SW2_S_SIO_REG            (* (reg32 *) SW2_S__SIO)
#endif /* (SW2_S__SIO_CFG) */

/* USBIO registers */
#if !defined(SW2_S__PC) && (CY_PSOC4_4200L)
    #define SW2_S_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SW2_S_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SW2_S_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SW2_S_DRIVE_MODE_SHIFT       (0x00u)
#define SW2_S_DRIVE_MODE_MASK        (0x07u << SW2_S_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SW2_S_H */


/* [] END OF FILE */
