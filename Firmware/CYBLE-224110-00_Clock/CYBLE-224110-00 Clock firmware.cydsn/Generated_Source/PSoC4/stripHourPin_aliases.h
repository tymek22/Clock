/*******************************************************************************
* File Name: stripHourPin.h  
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

#if !defined(CY_PINS_stripHourPin_ALIASES_H) /* Pins stripHourPin_ALIASES_H */
#define CY_PINS_stripHourPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define stripHourPin_0			(stripHourPin__0__PC)
#define stripHourPin_0_PS		(stripHourPin__0__PS)
#define stripHourPin_0_PC		(stripHourPin__0__PC)
#define stripHourPin_0_DR		(stripHourPin__0__DR)
#define stripHourPin_0_SHIFT	(stripHourPin__0__SHIFT)
#define stripHourPin_0_INTR	((uint16)((uint16)0x0003u << (stripHourPin__0__SHIFT*2u)))

#define stripHourPin_INTR_ALL	 ((uint16)(stripHourPin_0_INTR))


#endif /* End Pins stripHourPin_ALIASES_H */


/* [] END OF FILE */
