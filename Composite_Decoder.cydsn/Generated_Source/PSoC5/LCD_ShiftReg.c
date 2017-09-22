/*******************************************************************************
* File Name: LCD_ShiftReg.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LCD_ShiftReg.h"

uint8 LCD_ShiftReg_initVar = 0u;


/*******************************************************************************
* Function Name: LCD_ShiftReg_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_ShiftReg_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_ShiftReg_Start(void) 
{
    if(0u == LCD_ShiftReg_initVar)
    {
        LCD_ShiftReg_Init();
        LCD_ShiftReg_initVar = 1u; /* Component initialized */
    }

    LCD_ShiftReg_Enable();
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void LCD_ShiftReg_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    LCD_ShiftReg_SR_CONTROL |= LCD_ShiftReg_CLK_EN;

    LCD_ShiftReg_EnableInt();
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void LCD_ShiftReg_Init(void) 
{
    LCD_ShiftReg_SetIntMode(LCD_ShiftReg_INT_SRC);
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    LCD_ShiftReg_SR_CONTROL &= ((uint8) ~LCD_ShiftReg_CLK_EN);
    LCD_ShiftReg_DisableInt();
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    LCD_ShiftReg_SR_AUX_CONTROL |= LCD_ShiftReg_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    LCD_ShiftReg_SR_AUX_CONTROL &= ((uint8) ~LCD_ShiftReg_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 LCD_ShiftReg_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = LCD_ShiftReg_RET_FIFO_NOT_DEFINED;

    #if(0u != LCD_ShiftReg_USE_INPUT_FIFO)
        if(LCD_ShiftReg_IN_FIFO == fifoId)
        {
            switch(LCD_ShiftReg_GET_IN_FIFO_STS)
            {
                case LCD_ShiftReg_IN_FIFO_FULL :
                    result = LCD_ShiftReg_RET_FIFO_FULL;
                    break;

                case LCD_ShiftReg_IN_FIFO_EMPTY :
                    result = LCD_ShiftReg_RET_FIFO_EMPTY;
                    break;

                case LCD_ShiftReg_IN_FIFO_PARTIAL:
                    result = LCD_ShiftReg_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = LCD_ShiftReg_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != LCD_ShiftReg_USE_INPUT_FIFO) */

    if(LCD_ShiftReg_OUT_FIFO == fifoId)
    {
        switch(LCD_ShiftReg_GET_OUT_FIFO_STS)
        {
            case LCD_ShiftReg_OUT_FIFO_FULL :
                result = LCD_ShiftReg_RET_FIFO_FULL;
                break;

            case LCD_ShiftReg_OUT_FIFO_EMPTY :
                result = LCD_ShiftReg_RET_FIFO_EMPTY;
                break;

            case LCD_ShiftReg_OUT_FIFO_PARTIAL :
                result = LCD_ShiftReg_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = LCD_ShiftReg_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_SetIntMode(uint8 interruptSource) 
{
    LCD_ShiftReg_SR_STATUS_MASK &= ((uint8) ~LCD_ShiftReg_INTS_EN_MASK);          /* Clear existing int */
    LCD_ShiftReg_SR_STATUS_MASK |= (interruptSource & LCD_ShiftReg_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 LCD_ShiftReg_GetIntStatus(void) 
{
    return(LCD_ShiftReg_SR_STATUS & LCD_ShiftReg_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: LCD_ShiftReg_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_ShiftReg_WriteRegValue(uint8 shiftData)
                                                                     
{
    CY_SET_REG8(LCD_ShiftReg_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != LCD_ShiftReg_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: LCD_ShiftReg_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus LCD_ShiftReg_WriteData(uint8 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(LCD_ShiftReg_RET_FIFO_FULL != (LCD_ShiftReg_GetFIFOStatus(LCD_ShiftReg_IN_FIFO)))
        {
            CY_SET_REG8(LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != LCD_ShiftReg_USE_INPUT_FIFO) */


#if(0u != LCD_ShiftReg_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: LCD_ShiftReg_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 LCD_ShiftReg_ReadData(void) 
    {
        return(CY_GET_REG8(LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != LCD_ShiftReg_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: LCD_ShiftReg_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 LCD_ShiftReg_ReadRegValue(void) 
{
    uint8 result;

    /* Clear FIFO before software capture */
    while(LCD_ShiftReg_RET_FIFO_EMPTY != LCD_ShiftReg_GetFIFOStatus(LCD_ShiftReg_OUT_FIFO))
    {
        (void) CY_GET_REG8(LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(LCD_ShiftReg_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG8(LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (LCD_ShiftReg_SR_SIZE % 8u))
        result &= ((uint8) LCD_ShiftReg_SR_MASK);
    #endif /* (0u != (LCD_ShiftReg_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
