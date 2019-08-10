/*******************************************************************************
* File Name: stripMinutePin.h  
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

#if !defined(CY_PINS_stripMinutePin_ALIASES_H) /* Pins stripMinutePin_ALIASES_H */
#define CY_PINS_stripMinutePin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define stripMinutePin_0			(stripMinutePin__0__PC)
#define stripMinutePin_0_PS		(stripMinutePin__0__PS)
#define stripMinutePin_0_PC		(stripMinutePin__0__PC)
#define stripMinutePin_0_DR		(stripMinutePin__0__DR)
#define stripMinutePin_0_SHIFT	(stripMinutePin__0__SHIFT)
#define stripMinutePin_0_INTR	((uint16)((uint16)0x0003u << (stripMinutePin__0__SHIFT*2u)))

#define stripMinutePin_INTR_ALL	 ((uint16)(stripMinutePin_0_INTR))


#endif /* End Pins stripMinutePin_ALIASES_H */


/* [] END OF FILE */
