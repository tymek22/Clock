/*******************************************************************************
* File Name: pirPin.h  
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

#if !defined(CY_PINS_pirPin_ALIASES_H) /* Pins pirPin_ALIASES_H */
#define CY_PINS_pirPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pirPin_0			(pirPin__0__PC)
#define pirPin_0_PS		(pirPin__0__PS)
#define pirPin_0_PC		(pirPin__0__PC)
#define pirPin_0_DR		(pirPin__0__DR)
#define pirPin_0_SHIFT	(pirPin__0__SHIFT)
#define pirPin_0_INTR	((uint16)((uint16)0x0003u << (pirPin__0__SHIFT*2u)))

#define pirPin_INTR_ALL	 ((uint16)(pirPin_0_INTR))


#endif /* End Pins pirPin_ALIASES_H */


/* [] END OF FILE */
