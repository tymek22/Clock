/*******************************************************************************
* File Name: ledStrip_StringSel_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ledStrip_StringSel.h"

/* Check for removal by optimization */
#if !defined(ledStrip_StringSel_Sync_ctrl_reg__REMOVED)

static ledStrip_StringSel_BACKUP_STRUCT  ledStrip_StringSel_backup = {0u};

    
/*******************************************************************************
* Function Name: ledStrip_StringSel_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ledStrip_StringSel_SaveConfig(void) 
{
    ledStrip_StringSel_backup.controlState = ledStrip_StringSel_Control;
}


/*******************************************************************************
* Function Name: ledStrip_StringSel_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void ledStrip_StringSel_RestoreConfig(void) 
{
     ledStrip_StringSel_Control = ledStrip_StringSel_backup.controlState;
}


/*******************************************************************************
* Function Name: ledStrip_StringSel_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ledStrip_StringSel_Sleep(void) 
{
    ledStrip_StringSel_SaveConfig();
}


/*******************************************************************************
* Function Name: ledStrip_StringSel_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ledStrip_StringSel_Wakeup(void)  
{
    ledStrip_StringSel_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
