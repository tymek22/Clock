/*******************************************************************************
* File Name: sqwPin_isr.h
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
#if !defined(CY_ISR_sqwPin_isr_H)
#define CY_ISR_sqwPin_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void sqwPin_isr_Start(void);
void sqwPin_isr_StartEx(cyisraddress address);
void sqwPin_isr_Stop(void);

CY_ISR_PROTO(sqwPin_isr_Interrupt);

void sqwPin_isr_SetVector(cyisraddress address);
cyisraddress sqwPin_isr_GetVector(void);

void sqwPin_isr_SetPriority(uint8 priority);
uint8 sqwPin_isr_GetPriority(void);

void sqwPin_isr_Enable(void);
uint8 sqwPin_isr_GetState(void);
void sqwPin_isr_Disable(void);

void sqwPin_isr_SetPending(void);
void sqwPin_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the sqwPin_isr ISR. */
#define sqwPin_isr_INTC_VECTOR            ((reg32 *) sqwPin_isr__INTC_VECT)

/* Address of the sqwPin_isr ISR priority. */
#define sqwPin_isr_INTC_PRIOR             ((reg32 *) sqwPin_isr__INTC_PRIOR_REG)

/* Priority of the sqwPin_isr interrupt. */
#define sqwPin_isr_INTC_PRIOR_NUMBER      sqwPin_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable sqwPin_isr interrupt. */
#define sqwPin_isr_INTC_SET_EN            ((reg32 *) sqwPin_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the sqwPin_isr interrupt. */
#define sqwPin_isr_INTC_CLR_EN            ((reg32 *) sqwPin_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the sqwPin_isr interrupt state to pending. */
#define sqwPin_isr_INTC_SET_PD            ((reg32 *) sqwPin_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the sqwPin_isr interrupt. */
#define sqwPin_isr_INTC_CLR_PD            ((reg32 *) sqwPin_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_sqwPin_isr_H */


/* [] END OF FILE */
