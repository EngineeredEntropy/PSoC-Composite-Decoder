/*******************************************************************************
* File Name: Trigger_Reference_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Trigger_Reference.h"

static Trigger_Reference_backupStruct Trigger_Reference_backup;


/*******************************************************************************
* Function Name: Trigger_Reference_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Trigger_Reference_SaveConfig(void) 
{
    if (!((Trigger_Reference_CR1 & Trigger_Reference_SRC_MASK) == Trigger_Reference_SRC_UDB))
    {
        Trigger_Reference_backup.data_value = Trigger_Reference_Data;
    }
}


/*******************************************************************************
* Function Name: Trigger_Reference_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Trigger_Reference_RestoreConfig(void) 
{
    if (!((Trigger_Reference_CR1 & Trigger_Reference_SRC_MASK) == Trigger_Reference_SRC_UDB))
    {
        if((Trigger_Reference_Strobe & Trigger_Reference_STRB_MASK) == Trigger_Reference_STRB_EN)
        {
            Trigger_Reference_Strobe &= (uint8)(~Trigger_Reference_STRB_MASK);
            Trigger_Reference_Data = Trigger_Reference_backup.data_value;
            Trigger_Reference_Strobe |= Trigger_Reference_STRB_EN;
        }
        else
        {
            Trigger_Reference_Data = Trigger_Reference_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Trigger_Reference_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Trigger_Reference_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Trigger_Reference_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Trigger_Reference_ACT_PWR_EN == (Trigger_Reference_PWRMGR & Trigger_Reference_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Trigger_Reference_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Trigger_Reference_backup.enableState = 0u;
    }
    
    Trigger_Reference_Stop();
    Trigger_Reference_SaveConfig();
}


/*******************************************************************************
* Function Name: Trigger_Reference_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Trigger_Reference_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Trigger_Reference_Wakeup(void) 
{
    Trigger_Reference_RestoreConfig();
    
    if(Trigger_Reference_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Trigger_Reference_Enable();

        /* Restore the data register */
        Trigger_Reference_SetValue(Trigger_Reference_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
