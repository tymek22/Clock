/*******************************************************************************
* File Name: MinutePin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MinutePin_ALIASES_H) /* Pins MinutePin_ALIASES_H */
#define CY_PINS_MinutePin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MinutePin_0			(MinutePin__0__PC)
#define MinutePin_0_PS		(MinutePin__0__PS)
#define MinutePin_0_PC		(MinutePin__0__PC)
#define MinutePin_0_DR		(MinutePin__0__DR)
#define MinutePin_0_SHIFT	(MinutePin__0__SHIFT)
#define MinutePin_0_INTR	((uint16)((uint16)0x0003u << (MinutePin__0__SHIFT*2u)))

#define MinutePin_INTR_ALL	 ((uint16)(MinutePin_0_INTR))


#endif /* End Pins MinutePin_ALIASES_H */


/* [] END OF FILE */
