/*******************************************************************************
* File Name: Pixel_ShiftReg_PM.c
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

#include "Pixel_ShiftReg.h"

static Pixel_ShiftReg_BACKUP_STRUCT Pixel_ShiftReg_backup =
{
    Pixel_ShiftReg_DISABLED,

    ((uint8) Pixel_ShiftReg_DEFAULT_A0),
    ((uint8) Pixel_ShiftReg_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) Pixel_ShiftReg_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: Pixel_ShiftReg_SaveConfig
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
void Pixel_ShiftReg_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    Pixel_ShiftReg_backup.saveSrA0Reg   = CY_GET_REG8(Pixel_ShiftReg_SHIFT_REG_LSB_PTR);
    Pixel_ShiftReg_backup.saveSrA1Reg   = CY_GET_REG8(Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        Pixel_ShiftReg_backup.saveSrIntMask = Pixel_ShiftReg_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Pixel_ShiftReg_RestoreConfig
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
void Pixel_ShiftReg_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(Pixel_ShiftReg_SHIFT_REG_LSB_PTR, Pixel_ShiftReg_backup.saveSrA0Reg);
    CY_SET_REG8(Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR, Pixel_ShiftReg_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        Pixel_ShiftReg_SR_STATUS_MASK = ((uint8) Pixel_ShiftReg_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Pixel_ShiftReg_Sleep
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
void Pixel_ShiftReg_Sleep(void) 
{
    Pixel_ShiftReg_backup.enableState = ((uint8) Pixel_ShiftReg_IS_ENABLED);

    Pixel_ShiftReg_Stop();
    Pixel_ShiftReg_SaveConfig();
}


/*******************************************************************************
* Function Name: Pixel_ShiftReg_Wakeup
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
void Pixel_ShiftReg_Wakeup(void) 
{
    Pixel_ShiftReg_RestoreConfig();

    if(0u != Pixel_ShiftReg_backup.enableState)
    {
        Pixel_ShiftReg_Enable();
    }
}


/* [] END OF FILE */
