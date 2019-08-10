/*******************************************************************************
* File Name: ledStrip_fisr.h
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
#if !defined(CY_ISR_ledStrip_fisr_H)
#define CY_ISR_ledStrip_fisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ledStrip_fisr_Start(void);
void ledStrip_fisr_StartEx(cyisraddress address);
void ledStrip_fisr_Stop(void);

CY_ISR_PROTO(ledStrip_fisr_Interrupt);

void ledStrip_fisr_SetVector(cyisraddress address);
cyisraddress ledStrip_fisr_GetVector(void);

void ledStrip_fisr_SetPriority(uint8 priority);
uint8 ledStrip_fisr_GetPriority(void);

void ledStrip_fisr_Enable(void);
uint8 ledStrip_fisr_GetState(void);
void ledStrip_fisr_Disable(void);

void ledStrip_fisr_SetPending(void);
void ledStrip_fisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ledStrip_fisr ISR. */
#define ledStrip_fisr_INTC_VECTOR            ((reg32 *) ledStrip_fisr__INTC_VECT)

/* Address of the ledStrip_fisr ISR priority. */
#define ledStrip_fisr_INTC_PRIOR             ((reg32 *) ledStrip_fisr__INTC_PRIOR_REG)

/* Priority of the ledStrip_fisr interrupt. */
#define ledStrip_fisr_INTC_PRIOR_NUMBER      ledStrip_fisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ledStrip_fisr interrupt. */
#define ledStrip_fisr_INTC_SET_EN            ((reg32 *) ledStrip_fisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ledStrip_fisr interrupt. */
#define ledStrip_fisr_INTC_CLR_EN            ((reg32 *) ledStrip_fisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ledStrip_fisr interrupt state to pending. */
#define ledStrip_fisr_INTC_SET_PD            ((reg32 *) ledStrip_fisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ledStrip_fisr interrupt. */
#define ledStrip_fisr_INTC_CLR_PD            ((reg32 *) ledStrip_fisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_ledStrip_fisr_H */


/* [] END OF FILE */
