/*******************************************************************************
* File Name: ledStrip_cisr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ledStrip_cisr_H)
#define CY_ISR_ledStrip_cisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ledStrip_cisr_Start(void);
void ledStrip_cisr_StartEx(cyisraddress address);
void ledStrip_cisr_Stop(void);

CY_ISR_PROTO(ledStrip_cisr_Interrupt);

void ledStrip_cisr_SetVector(cyisraddress address);
cyisraddress ledStrip_cisr_GetVector(void);

void ledStrip_cisr_SetPriority(uint8 priority);
uint8 ledStrip_cisr_GetPriority(void);

void ledStrip_cisr_Enable(void);
uint8 ledStrip_cisr_GetState(void);
void ledStrip_cisr_Disable(void);

void ledStrip_cisr_SetPending(void);
void ledStrip_cisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ledStrip_cisr ISR. */
#define ledStrip_cisr_INTC_VECTOR            ((reg32 *) ledStrip_cisr__INTC_VECT)

/* Address of the ledStrip_cisr ISR priority. */
#define ledStrip_cisr_INTC_PRIOR             ((reg32 *) ledStrip_cisr__INTC_PRIOR_REG)

/* Priority of the ledStrip_cisr interrupt. */
#define ledStrip_cisr_INTC_PRIOR_NUMBER      ledStrip_cisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ledStrip_cisr interrupt. */
#define ledStrip_cisr_INTC_SET_EN            ((reg32 *) ledStrip_cisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ledStrip_cisr interrupt. */
#define ledStrip_cisr_INTC_CLR_EN            ((reg32 *) ledStrip_cisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ledStrip_cisr interrupt state to pending. */
#define ledStrip_cisr_INTC_SET_PD            ((reg32 *) ledStrip_cisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ledStrip_cisr interrupt. */
#define ledStrip_cisr_INTC_CLR_PD            ((reg32 *) ledStrip_cisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_ledStrip_cisr_H */


/* [] END OF FILE */
