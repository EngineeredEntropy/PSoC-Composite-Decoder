/*******************************************************************************
* File Name: Pixel_ShiftReg.h
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


#if !defined(CY_SHIFTREG_Pixel_ShiftReg_H)
#define CY_SHIFTREG_Pixel_ShiftReg_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Pixel_ShiftReg_FIFO_SIZE          (4u)
#define Pixel_ShiftReg_USE_INPUT_FIFO     (0u)
#define Pixel_ShiftReg_USE_OUTPUT_FIFO    (1u)
#define Pixel_ShiftReg_SR_SIZE            (8u)


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

} Pixel_ShiftReg_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Pixel_ShiftReg_Start(void)                              ;
void  Pixel_ShiftReg_Stop(void)                               ;
void  Pixel_ShiftReg_Init(void)                               ;
void  Pixel_ShiftReg_Enable(void)                             ;
void  Pixel_ShiftReg_RestoreConfig(void)                      ;
void  Pixel_ShiftReg_SaveConfig(void)                         ;
void  Pixel_ShiftReg_Sleep(void)                              ;
void  Pixel_ShiftReg_Wakeup(void)                             ;
void  Pixel_ShiftReg_EnableInt(void)                          ;
void  Pixel_ShiftReg_DisableInt(void)                         ;
void  Pixel_ShiftReg_SetIntMode(uint8 interruptSource)        ;
uint8 Pixel_ShiftReg_GetIntStatus(void)                       ;
void  Pixel_ShiftReg_WriteRegValue(uint8 shiftData) \
                                                                ;
uint8 Pixel_ShiftReg_ReadRegValue(void) ;
uint8    Pixel_ShiftReg_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != Pixel_ShiftReg_USE_INPUT_FIFO)
    cystatus Pixel_ShiftReg_WriteData(uint8 shiftData) \
                                                                ;
#endif /* (0u != Pixel_ShiftReg_USE_INPUT_FIFO) */

#if(0u != Pixel_ShiftReg_USE_OUTPUT_FIFO)
    uint8 Pixel_ShiftReg_ReadData(void) ;
#endif /* (0u != Pixel_ShiftReg_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 Pixel_ShiftReg_initVar;


/***************************************
*           API Constants
***************************************/

#define Pixel_ShiftReg_LOAD                   (0x01u)
#define Pixel_ShiftReg_STORE                  (0x02u)
#define Pixel_ShiftReg_RESET                  (0x04u)

#define Pixel_ShiftReg_IN_FIFO                (0x01u)
#define Pixel_ShiftReg_OUT_FIFO               (0x02u)

#define Pixel_ShiftReg_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define Pixel_ShiftReg_RET_FIFO_NOT_EMPTY     (0x01u)

#define Pixel_ShiftReg_RET_FIFO_PARTIAL       (0x01u)
#define Pixel_ShiftReg_RET_FIFO_EMPTY         (0x02u)
#define Pixel_ShiftReg_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Pixel_ShiftReg__LEFT 0
#define Pixel_ShiftReg__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define Pixel_ShiftReg_SR_MASK    (0xFFu) /* Unsigned is added to parameter */
#define Pixel_ShiftReg_INT_SRC    (2u)
#define Pixel_ShiftReg_DIRECTION  (0u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define Pixel_ShiftReg_SR_CONTROL_REG (* (reg8 *) \
                                           Pixel_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define Pixel_ShiftReg_SR_CONTROL_PTR (  (reg8 *) \
                                           Pixel_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define Pixel_ShiftReg_SR_STATUS_REG      (* (reg8 *) Pixel_ShiftReg_bSR_StsReg__STATUS_REG)
#define Pixel_ShiftReg_SR_STATUS_PTR      (  (reg8 *) Pixel_ShiftReg_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define Pixel_ShiftReg_SR_STATUS_MASK_REG (* (reg8 *) Pixel_ShiftReg_bSR_StsReg__MASK_REG)
#define Pixel_ShiftReg_SR_STATUS_MASK_PTR (  (reg8 *) Pixel_ShiftReg_bSR_StsReg__MASK_REG)

/* Aux control register */
#define Pixel_ShiftReg_SR_AUX_CONTROL_REG (* (reg8 *) Pixel_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)
#define Pixel_ShiftReg_SR_AUX_CONTROL_PTR (  (reg8 *) Pixel_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define Pixel_ShiftReg_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define Pixel_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

    #define Pixel_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

    #define Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

    #define Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

#else
    #if(Pixel_ShiftReg_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define Pixel_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #elif(Pixel_ShiftReg_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define Pixel_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_F0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_A0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_A1_REG )

        #define Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(Pixel_ShiftReg_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define Pixel_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define Pixel_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_F0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_A0_REG )

        #define Pixel_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_A1_REG )

        #define Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  Pixel_ShiftReg_bSR_sC8_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (Pixel_ShiftReg_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define Pixel_ShiftReg_INTERRUPTS_ENABLE      (0x10u)
#define Pixel_ShiftReg_LOAD_INT_EN            (0x01u)
#define Pixel_ShiftReg_STORE_INT_EN           (0x02u)
#define Pixel_ShiftReg_RESET_INT_EN           (0x04u)
#define Pixel_ShiftReg_CLK_EN                 (0x01u)

#define Pixel_ShiftReg_RESET_INT_EN_MASK      (0xFBu)
#define Pixel_ShiftReg_LOAD_INT_EN_MASK       (0xFEu)
#define Pixel_ShiftReg_STORE_INT_EN_MASK      (0xFDu)
#define Pixel_ShiftReg_INTS_EN_MASK           (0x07u)

#define Pixel_ShiftReg_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != Pixel_ShiftReg_USE_INPUT_FIFO)

    #define Pixel_ShiftReg_IN_FIFO_MASK       (0x18u)

    #define Pixel_ShiftReg_IN_FIFO_FULL       (0x00u)
    #define Pixel_ShiftReg_IN_FIFO_EMPTY      (0x01u)
    #define Pixel_ShiftReg_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define Pixel_ShiftReg_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != Pixel_ShiftReg_USE_INPUT_FIFO) */

#define Pixel_ShiftReg_OUT_FIFO_MASK          (0x60u)

#define Pixel_ShiftReg_OUT_FIFO_EMPTY         (0x00u)
#define Pixel_ShiftReg_OUT_FIFO_FULL          (0x01u)
#define Pixel_ShiftReg_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define Pixel_ShiftReg_OUT_FIFO_NOT_EMPTY     (0x02u)

#define Pixel_ShiftReg_IN_FIFO_SHIFT_MASK     (0x03u)
#define Pixel_ShiftReg_OUT_FIFO_SHIFT_MASK    (0x05u)

#define Pixel_ShiftReg_DISABLED               (0u)
#define Pixel_ShiftReg_DEFAULT_A0             (0u)
#define Pixel_ShiftReg_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define Pixel_ShiftReg_IS_ENABLED         (0u != (Pixel_ShiftReg_SR_CONTROL & Pixel_ShiftReg_CLK_EN))

#define Pixel_ShiftReg_GET_OUT_FIFO_STS   ((Pixel_ShiftReg_SR_STATUS & Pixel_ShiftReg_OUT_FIFO_MASK) >> \
                                              Pixel_ShiftReg_OUT_FIFO_SHIFT_MASK)

#define Pixel_ShiftReg_GET_IN_FIFO_STS    ((Pixel_ShiftReg_SR_STATUS & Pixel_ShiftReg_IN_FIFO_MASK)  >> \
                                              Pixel_ShiftReg_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define Pixel_ShiftReg_SR_CONTROL     (Pixel_ShiftReg_SR_CONTROL_REG)
#define Pixel_ShiftReg_SR_STATUS      (Pixel_ShiftReg_SR_STATUS_REG)
#define Pixel_ShiftReg_SR_STATUS_MASK (Pixel_ShiftReg_SR_STATUS_MASK_REG)
#define Pixel_ShiftReg_SR_AUX_CONTROL (Pixel_ShiftReg_SR_AUX_CONTROL_REG)

#define Pixel_ShiftReg_IN_FIFO_SHFT_MASK  (Pixel_ShiftReg_IN_FIFO_SHIFT_MASK)
#define Pixel_ShiftReg_OUT_FIFO_SHFT_MASK (Pixel_ShiftReg_OUT_FIFO_SHFIT_MASK)

#define Pixel_ShiftReg_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_Pixel_ShiftReg_H) */


/* [] END OF FILE */
