/*******************************************************************************
* File Name: LCD_ShiftReg_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_ShiftReg.h"

static LCD_ShiftReg_BACKUP_STRUCT LCD_ShiftReg_backup =
{
    LCD_ShiftReg_DISABLED,

    ((uint8) LCD_ShiftReg_DEFAULT_A0),
    ((uint8) LCD_ShiftReg_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) LCD_ShiftReg_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: LCD_ShiftReg_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_ShiftReg_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    LCD_ShiftReg_backup.saveSrA0Reg   = CY_GET_REG8(LCD_ShiftReg_SHIFT_REG_LSB_PTR);
    LCD_ShiftReg_backup.saveSrA1Reg   = CY_GET_REG8(LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        LCD_ShiftReg_backup.saveSrIntMask = LCD_ShiftReg_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(LCD_ShiftReg_SHIFT_REG_LSB_PTR, LCD_ShiftReg_backup.saveSrA0Reg);
    CY_SET_REG8(LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR, LCD_ShiftReg_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        LCD_ShiftReg_SR_STATUS_MASK = ((uint8) LCD_ShiftReg_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_ShiftReg_Sleep(void) 
{
    LCD_ShiftReg_backup.enableState = ((uint8) LCD_ShiftReg_IS_ENABLED);

    LCD_ShiftReg_Stop();
    LCD_ShiftReg_SaveConfig();
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_Wakeup(void) 
{
    LCD_ShiftReg_RestoreConfig();

    if(0u != LCD_ShiftReg_backup.enableState)
    {
        LCD_ShiftReg_Enable();
    }
}


/* [] END OF FILE */
