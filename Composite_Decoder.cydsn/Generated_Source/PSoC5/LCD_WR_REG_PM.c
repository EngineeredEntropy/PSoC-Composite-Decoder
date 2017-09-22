/*******************************************************************************
* File Name: LCD_WR_REG_PM.c
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

#include "LCD_WR_REG.h"

/* Check for removal by optimization */
#if !defined(LCD_WR_REG_Sync_ctrl_reg__REMOVED)

static LCD_WR_REG_BACKUP_STRUCT  LCD_WR_REG_backup = {0u};

    
/*******************************************************************************
* Function Name: LCD_WR_REG_SaveConfig
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
void LCD_WR_REG_SaveConfig(void) 
{
    LCD_WR_REG_backup.controlState = LCD_WR_REG_Control;
}


/*******************************************************************************
* Function Name: LCD_WR_REG_RestoreConfig
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
void LCD_WR_REG_RestoreConfig(void) 
{
     LCD_WR_REG_Control = LCD_WR_REG_backup.controlState;
}


/*******************************************************************************
* Function Name: LCD_WR_REG_Sleep
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
void LCD_WR_REG_Sleep(void) 
{
    LCD_WR_REG_SaveConfig();
}


/*******************************************************************************
* Function Name: LCD_WR_REG_Wakeup
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
void LCD_WR_REG_Wakeup(void)  
{
    LCD_WR_REG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
