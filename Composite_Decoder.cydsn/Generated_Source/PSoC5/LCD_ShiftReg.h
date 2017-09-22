/*******************************************************************************
* File Name: LCD_ShiftReg.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_LCD_ShiftReg_H)
#define CY_SHIFTREG_LCD_ShiftReg_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_ShiftReg_FIFO_SIZE          (4u)
#define LCD_ShiftReg_USE_INPUT_FIFO     (1u)
#define LCD_ShiftReg_USE_OUTPUT_FIFO    (0u)
#define LCD_ShiftReg_SR_SIZE            (8u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint8 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} LCD_ShiftReg_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  LCD_ShiftReg_Start(void)                              ;
void  LCD_ShiftReg_Stop(void)                               ;
void  LCD_ShiftReg_Init(void)                               ;
void  LCD_ShiftReg_Enable(void)                             ;
void  LCD_ShiftReg_RestoreConfig(void)                      ;
void  LCD_ShiftReg_SaveConfig(void)                         ;
void  LCD_ShiftReg_Sleep(void)                              ;
void  LCD_ShiftReg_Wakeup(void)                             ;
void  LCD_ShiftReg_EnableInt(void)                          ;
void  LCD_ShiftReg_DisableInt(void)                         ;
void  LCD_ShiftReg_SetIntMode(uint8 interruptSource)        ;
uint8 LCD_ShiftReg_GetIntStatus(void)                       ;
void  LCD_ShiftReg_WriteRegValue(uint8 shiftData) \
                                                                ;
uint8 LCD_ShiftReg_ReadRegValue(void) ;
uint8    LCD_ShiftReg_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != LCD_ShiftReg_USE_INPUT_FIFO)
    cystatus LCD_ShiftReg_WriteData(uint8 shiftData) \
                                                                ;
#endif /* (0u != LCD_ShiftReg_USE_INPUT_FIFO) */

#if(0u != LCD_ShiftReg_USE_OUTPUT_FIFO)
    uint8 LCD_ShiftReg_ReadData(void) ;
#endif /* (0u != LCD_ShiftReg_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 LCD_ShiftReg_initVar;


/***************************************
*           API Constants
***************************************/

#define LCD_ShiftReg_LOAD                   (0x01u)
#define LCD_ShiftReg_STORE                  (0x02u)
#define LCD_ShiftReg_RESET                  (0x04u)

#define LCD_ShiftReg_IN_FIFO                (0x01u)
#define LCD_ShiftReg_OUT_FIFO               (0x02u)

#define LCD_ShiftReg_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define LCD_ShiftReg_RET_FIFO_NOT_EMPTY     (0x01u)

#define LCD_ShiftReg_RET_FIFO_PARTIAL       (0x01u)
#define LCD_ShiftReg_RET_FIFO_EMPTY         (0x02u)
#define LCD_ShiftReg_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define LCD_ShiftReg__LEFT 0
#define LCD_ShiftReg__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define LCD_ShiftReg_SR_MASK    (0xFFu) /* Unsigned is added to parameter */
#define LCD_ShiftReg_INT_SRC    (0u)
#define LCD_ShiftReg_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define LCD_ShiftReg_SR_CONTROL_REG (* (reg8 *) \
                                           LCD_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define LCD_ShiftReg_SR_CONTROL_PTR (  (reg8 *) \
                                           LCD_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define LCD_ShiftReg_SR_STATUS_REG      (* (reg8 *) LCD_ShiftReg_bSR_StsReg__STATUS_REG)
#define LCD_ShiftReg_SR_STATUS_PTR      (  (reg8 *) LCD_ShiftReg_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define LCD_ShiftReg_SR_STATUS_MASK_REG (* (reg8 *) LCD_ShiftReg_bSR_StsReg__MASK_REG)
#define LCD_ShiftReg_SR_STATUS_MASK_PTR (  (reg8 *) LCD_ShiftReg_bSR_StsReg__MASK_REG)

/* Aux control register */
#define LCD_ShiftReg_SR_AUX_CONTROL_REG (* (reg8 *) LCD_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)
#define LCD_ShiftReg_SR_AUX_CONTROL_PTR (  (reg8 *) LCD_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define LCD_ShiftReg_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

    #define LCD_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

    #define LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

    #define LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

#else
    #if(LCD_ShiftReg_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define LCD_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #elif(LCD_ShiftReg_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_F0_REG )

        #define LCD_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_A0_REG )

        #define LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_A1_REG )

        #define LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(LCD_ShiftReg_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define LCD_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_F0_REG )

        #define LCD_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_A0_REG )

        #define LCD_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_A1_REG )

        #define LCD_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  LCD_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (LCD_ShiftReg_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define LCD_ShiftReg_INTERRUPTS_ENABLE      (0x10u)
#define LCD_ShiftReg_LOAD_INT_EN            (0x01u)
#define LCD_ShiftReg_STORE_INT_EN           (0x02u)
#define LCD_ShiftReg_RESET_INT_EN           (0x04u)
#define LCD_ShiftReg_CLK_EN                 (0x01u)

#define LCD_ShiftReg_RESET_INT_EN_MASK      (0xFBu)
#define LCD_ShiftReg_LOAD_INT_EN_MASK       (0xFEu)
#define LCD_ShiftReg_STORE_INT_EN_MASK      (0xFDu)
#define LCD_ShiftReg_INTS_EN_MASK           (0x07u)

#define LCD_ShiftReg_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != LCD_ShiftReg_USE_INPUT_FIFO)

    #define LCD_ShiftReg_IN_FIFO_MASK       (0x18u)

    #define LCD_ShiftReg_IN_FIFO_FULL       (0x00u)
    #define LCD_ShiftReg_IN_FIFO_EMPTY      (0x01u)
    #define LCD_ShiftReg_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define LCD_ShiftReg_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != LCD_ShiftReg_USE_INPUT_FIFO) */

#define LCD_ShiftReg_OUT_FIFO_MASK          (0x60u)

#define LCD_ShiftReg_OUT_FIFO_EMPTY         (0x00u)
#define LCD_ShiftReg_OUT_FIFO_FULL          (0x01u)
#define LCD_ShiftReg_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define LCD_ShiftReg_OUT_FIFO_NOT_EMPTY     (0x02u)

#define LCD_ShiftReg_IN_FIFO_SHIFT_MASK     (0x03u)
#define LCD_ShiftReg_OUT_FIFO_SHIFT_MASK    (0x05u)

#define LCD_ShiftReg_DISABLED               (0u)
#define LCD_ShiftReg_DEFAULT_A0             (0u)
#define LCD_ShiftReg_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define LCD_ShiftReg_IS_ENABLED         (0u != (LCD_ShiftReg_SR_CONTROL & LCD_ShiftReg_CLK_EN))

#define LCD_ShiftReg_GET_OUT_FIFO_STS   ((LCD_ShiftReg_SR_STATUS & LCD_ShiftReg_OUT_FIFO_MASK) >> \
                                              LCD_ShiftReg_OUT_FIFO_SHIFT_MASK)

#define LCD_ShiftReg_GET_IN_FIFO_STS    ((LCD_ShiftReg_SR_STATUS & LCD_ShiftReg_IN_FIFO_MASK)  >> \
                                              LCD_ShiftReg_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define LCD_ShiftReg_SR_CONTROL     (LCD_ShiftReg_SR_CONTROL_REG)
#define LCD_ShiftReg_SR_STATUS      (LCD_ShiftReg_SR_STATUS_REG)
#define LCD_ShiftReg_SR_STATUS_MASK (LCD_ShiftReg_SR_STATUS_MASK_REG)
#define LCD_ShiftReg_SR_AUX_CONTROL (LCD_ShiftReg_SR_AUX_CONTROL_REG)

#define LCD_ShiftReg_IN_FIFO_SHFT_MASK  (LCD_ShiftReg_IN_FIFO_SHIFT_MASK)
#define LCD_ShiftReg_OUT_FIFO_SHFT_MASK (LCD_ShiftReg_OUT_FIFO_SHFIT_MASK)

#define LCD_ShiftReg_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_LCD_ShiftReg_H) */


/* [] END OF FILE */
