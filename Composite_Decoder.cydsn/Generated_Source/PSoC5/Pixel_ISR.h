/*******************************************************************************
* File Name: Pixel_ISR.h
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
#if !defined(CY_ISR_Pixel_ISR_H)
#define CY_ISR_Pixel_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Pixel_ISR_Start(void);
void Pixel_ISR_StartEx(cyisraddress address);
void Pixel_ISR_Stop(void);

CY_ISR_PROTO(Pixel_ISR_Interrupt);

void Pixel_ISR_SetVector(cyisraddress address);
cyisraddress Pixel_ISR_GetVector(void);

void Pixel_ISR_SetPriority(uint8 priority);
uint8 Pixel_ISR_GetPriority(void);

void Pixel_ISR_Enable(void);
uint8 Pixel_ISR_GetState(void);
void Pixel_ISR_Disable(void);

void Pixel_ISR_SetPending(void);
void Pixel_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Pixel_ISR ISR. */
#define Pixel_ISR_INTC_VECTOR            ((reg32 *) Pixel_ISR__INTC_VECT)

/* Address of the Pixel_ISR ISR priority. */
#define Pixel_ISR_INTC_PRIOR             ((reg8 *) Pixel_ISR__INTC_PRIOR_REG)

/* Priority of the Pixel_ISR interrupt. */
#define Pixel_ISR_INTC_PRIOR_NUMBER      Pixel_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Pixel_ISR interrupt. */
#define Pixel_ISR_INTC_SET_EN            ((reg32 *) Pixel_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Pixel_ISR interrupt. */
#define Pixel_ISR_INTC_CLR_EN            ((reg32 *) Pixel_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Pixel_ISR interrupt state to pending. */
#define Pixel_ISR_INTC_SET_PD            ((reg32 *) Pixel_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Pixel_ISR interrupt. */
#define Pixel_ISR_INTC_CLR_PD            ((reg32 *) Pixel_ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_Pixel_ISR_H */


/* [] END OF FILE */
