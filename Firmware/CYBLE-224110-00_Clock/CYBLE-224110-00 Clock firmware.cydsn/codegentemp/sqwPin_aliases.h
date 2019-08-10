/*******************************************************************************
* File Name: sqwPin.h  
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

#if !defined(CY_PINS_sqwPin_ALIASES_H) /* Pins sqwPin_ALIASES_H */
#define CY_PINS_sqwPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define sqwPin_0			(sqwPin__0__PC)
#define sqwPin_0_PS		(sqwPin__0__PS)
#define sqwPin_0_PC		(sqwPin__0__PC)
#define sqwPin_0_DR		(sqwPin__0__DR)
#define sqwPin_0_SHIFT	(sqwPin__0__SHIFT)
#define sqwPin_0_INTR	((uint16)((uint16)0x0003u << (sqwPin__0__SHIFT*2u)))

#define sqwPin_INTR_ALL	 ((uint16)(sqwPin_0_INTR))


#endif /* End Pins sqwPin_ALIASES_H */


/* [] END OF FILE */
