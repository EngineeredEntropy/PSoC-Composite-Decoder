/*******************************************************************************
* File Name: Trigger_Reference.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Trigger_Reference.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Trigger_Reference_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Trigger_Reference_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Trigger_Reference_backupStruct Trigger_Reference_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Trigger_Reference_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_Init(void) 
{
    Trigger_Reference_CR0 = (Trigger_Reference_MODE_V );

    /* Set default data source */
    #if(Trigger_Reference_DEFAULT_DATA_SRC != 0 )
        Trigger_Reference_CR1 = (Trigger_Reference_DEFAULT_CNTL | Trigger_Reference_DACBUS_ENABLE) ;
    #else
        Trigger_Reference_CR1 = (Trigger_Reference_DEFAULT_CNTL | Trigger_Reference_DACBUS_DISABLE) ;
    #endif /* (Trigger_Reference_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Trigger_Reference_DEFAULT_STRB != 0)
        Trigger_Reference_Strobe |= Trigger_Reference_STRB_EN ;
    #endif/* (Trigger_Reference_DEFAULT_STRB != 0) */

    /* Set default range */
    Trigger_Reference_SetRange(Trigger_Reference_DEFAULT_RANGE); 

    /* Set default speed */
    Trigger_Reference_SetSpeed(Trigger_Reference_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Trigger_Reference_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_Enable(void) 
{
    Trigger_Reference_PWRMGR |= Trigger_Reference_ACT_PWR_EN;
    Trigger_Reference_STBY_PWRMGR |= Trigger_Reference_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Trigger_Reference_restoreVal == 1u) 
        {
             Trigger_Reference_CR0 = Trigger_Reference_backup.data_value;
             Trigger_Reference_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Trigger_Reference_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  Trigger_Reference_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Trigger_Reference_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Trigger_Reference_initVar == 0u)
    { 
        Trigger_Reference_Init();
        Trigger_Reference_initVar = 1u;
    }

    /* Enable power to DAC */
    Trigger_Reference_Enable();

    /* Set default value */
    Trigger_Reference_SetValue(Trigger_Reference_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Trigger_Reference_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_Stop(void) 
{
    /* Disble power to DAC */
    Trigger_Reference_PWRMGR &= (uint8)(~Trigger_Reference_ACT_PWR_EN);
    Trigger_Reference_STBY_PWRMGR &= (uint8)(~Trigger_Reference_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Trigger_Reference_backup.data_value = Trigger_Reference_CR0;
        Trigger_Reference_CR0 = Trigger_Reference_CUR_MODE_OUT_OFF;
        Trigger_Reference_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Trigger_Reference_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Trigger_Reference_CR0 &= (uint8)(~Trigger_Reference_HS_MASK);
    Trigger_Reference_CR0 |=  (speed & Trigger_Reference_HS_MASK);
}


/*******************************************************************************
* Function Name: Trigger_Reference_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_SetRange(uint8 range) 
{
    Trigger_Reference_CR0 &= (uint8)(~Trigger_Reference_RANGE_MASK);      /* Clear existing mode */
    Trigger_Reference_CR0 |= (range & Trigger_Reference_RANGE_MASK);      /*  Set Range  */
    Trigger_Reference_DacTrim();
}


/*******************************************************************************
* Function Name: Trigger_Reference_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Trigger_Reference_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Trigger_Reference_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Trigger_Reference_Data = value;
        CyExitCriticalSection(Trigger_Reference_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Trigger_Reference_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Trigger_Reference_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Trigger_Reference_CR0 & Trigger_Reference_RANGE_MASK) >> 2) + Trigger_Reference_TRIM_M7_1V_RNG_OFFSET;
    Trigger_Reference_TR = CY_GET_XTND_REG8((uint8 *)(Trigger_Reference_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
