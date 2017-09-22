/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "LCD.h"
#include "iprintf.h"

    #define W 320
#define H 240
    
uint16 lcdValue = 0xFF;

uint8 lcdPixels[9600];
uint8 temp;


int getPixel(unsigned int x, unsigned int y)
{
    int pixel = (lcdPixels[(y*W/8+x/8)]>>(x%8))&0x01;
    return(pixel);
}

#define TABLE_LENGTH 10   	 
#define DMA_BYTES_PER_BURST 1
#define DMA_REQUEST_PER_BURST 1
 
const uint8 sineTable[TABLE_LENGTH] = {0,0xFF,0,0xFF,0,0xFF,0,0xff};	

uint8 DMA_Chan;               /* The DMA Channel */
uint8 DMA_TD[3];	          /* The DMA Transaction Descriptor (TD) */  	
uint8 ShiftReg_DMA_Chan;
uint8 ShiftReg_DMA_TD[4];  


void pixelInt(void)
{
    Pixel_ShiftReg_GetIntStatus();
    
}

void vsyncISR(void)
{
    
      CyDmaChSetRequest(ShiftReg_DMA_Chan, CY_DMA_CPU_TERM_CHAIN);   // Terminate the entire chain of TD's
   
     while(CyDmaChGetRequest(ShiftReg_DMA_Chan));                                               // Wait for the request to be processed.
   
     CyDmaChEnable(ShiftReg_DMA_Chan, 1); 
    CyDmaChSetInitialTd(ShiftReg_DMA_Chan, ShiftReg_DMA_TD[3]);// Re-enable the DMA channel.   
}

int midX;
int midY;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    initLCD();
    
    
    /* Defines for LCD_DMA */
//#define LCD_DMA_BYTES_PER_BURST 1
//#define LCD_DMA_REQUEST_PER_BURST 1
//#define TABLE_LENGTH 9600
//#define LCD_DMA_SRC_BASE (CYDEV_SRAM_BASE)
//#define LCD_DMA_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for LCD_DMA */
/* Move these variable declarations to the top of the function */
//uint8 LCD_DMA_Chan;
//uint8 LCD_DMA_TD[1];

/* DMA Configuration for LCD_DMA */
//LCD_DMA_Chan = LCD_SHIFT_DMA_DmaInitialize(LCD_DMA_BYTES_PER_BURST, LCD_DMA_REQUEST_PER_BURST, HI16(&lcdValue), HI16(LCD_DMA_DST_BASE));
//LCD_DMA_TD[0] = CyDmaTdAllocate();
//TD1
//CY_DMA_TD_INC_SRC_ADR
//CyDmaTdSetConfiguration(LCD_DMA_TD[0], 1, LCD_DMA_TD[0], 0 | LCD_SHIFT_DMA__TD_TERMOUT_EN);
//CyDmaTdSetAddress(LCD_DMA_TD[0], LO16((uint32)&lcdValue), LO16((uint32)LCD_ShiftReg_IN_FIFO_VAL_LSB_PTR));


//CyDmaChSetInitialTd(LCD_DMA_Chan, LCD_DMA_TD[0]);

//CyDmaChEnable(LCD_DMA_Chan, 1);



LCD_CS_Write(0);
LCD_RS_Write(1);
LCD_WR_REG_Write(0);
CyDelay(100);
        //clearLCD(0xf800);
        //CyDelay(1000);
        //clearLCD(0x07E0);
        //CyDelay(1000);
        //clearLCD(0x001F);
        //CyDelay(1000);

        for(int i=0;i<9600;i++)
        {
            //int ind=(i-1);
            //if(ind<0)
            //    ind=9599;
            //if(i<(320/8))
            //    lcdPixels[ind]=0xFF;
            //else
            //    lcdPixels[ind]=0;
                
            //temp = lcdPixels[i];
        lcdPixels[i]=0xFF;
        }
        //lcdPixels[9599] = 0x00;
        //lcdPixels[0]=0xFF;
        //while(1);
LCD_CS_Write(0);
LCD_RS_Write(1);
LCD_WR_REG_Write(0);

//LCD_ShiftReg_Start();



    /* Defines for LCD_SHIFT_DMA */
//#define LCD_SHIFT_DMA_BYTES_PER_BURST 1
//#define LCD_SHIFT_DMA_REQUEST_PER_BURST 1
//#define LCD_SHIFT_DMA_SRC_BASE (CYDEV_SRAM_BASE)
//#define LCD_SHIFT_DMA_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for LCD_SHIFT_DMA */
/* Move these variable declarations to the top of the function */
//uint8 LCD_SHIFT_DMA_Chan;
//uint8 LCD_SHIFT_DMA_TD[1];

/* DMA Configuration for LCD_SHIFT_DMA */
//LCD_SHIFT_DMA_Chan = LCD_SHIFT_DMA_DmaInitialize(LCD_SHIFT_DMA_BYTES_PER_BURST, LCD_SHIFT_DMA_REQUEST_PER_BURST, 
//    HI16(LCD_SHIFT_DMA_SRC_BASE), HI16(LCD_SHIFT_DMA_DST_BASE));
//LCD_SHIFT_DMA_TD[0] = CyDmaTdAllocate();
//CyDmaTdSetConfiguration(LCD_SHIFT_DMA_TD[0], 1, LCD_SHIFT_DMA_TD[0], LCD_SHIFT_DMA__TD_TERMOUT_EN | CY_DMA_TD_INC_SRC_ADR);
//CyDmaTdSetAddress(LCD_SHIFT_DMA_TD[0], LO16((uint32)&lcdPixels[0]), LO16((uint32)LCD_Data_Reg_Control_PTR));
//CyDmaChSetInitialTd(LCD_SHIFT_DMA_Chan, LCD_SHIFT_DMA_TD[0]);
//CyDmaChEnable(LCD_SHIFT_DMA_Chan, 1);



ShiftReg_1_Start();
    PWM_1_Start();

    DMA_Chan = DMA_DmaInitialize( 1, 1, HI16(  lcdPixels ), HI16(CYDEV_PERIPH_BASE) );
    DMA_TD[0] = CyDmaTdAllocate(); 
    DMA_TD[1] = CyDmaTdAllocate(); 
    DMA_TD[2] = CyDmaTdAllocate(); 
    
 	CyDmaTdSetConfiguration(DMA_TD[0], (4095   ), DMA_TD[1], TD_INC_SRC_ADR  ); 	 
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)lcdPixels), LO16((uint32)ShiftReg_1_IN_FIFO_VAL_LSB_PTR)); 

    CyDmaTdSetConfiguration(DMA_TD[1], (4095   ), DMA_TD[2], TD_INC_SRC_ADR  ); 	 
    CyDmaTdSetAddress(DMA_TD[1], LO16((uint32)lcdPixels+4095), LO16((uint32)ShiftReg_1_IN_FIFO_VAL_LSB_PTR)); 

    CyDmaTdSetConfiguration(DMA_TD[2], (1410   ), DMA_TD[0], TD_INC_SRC_ADR |DMA__TD_TERMOUT_EN ); 	 
    CyDmaTdSetAddress(DMA_TD[2], LO16((uint32)lcdPixels+8190), LO16((uint32)ShiftReg_1_IN_FIFO_VAL_LSB_PTR)); 

                                                                    // ShiftReg_1_IN_FIFO_VAL_LSB_PTR  
															        // ShiftReg_1_SHIFT_REG_LSB_PTR   
																	// ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR
																	// ShiftReg_1_OUT_FIFO_VAL_LSB_PTR
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]); 	
    CyDmaChEnable(DMA_Chan, 1); 
    
  CyDelay(100);
LCD_Data_Reg_Write(0);
LCD_WR_REG_Write(8);
LCD_WR_REG_Write(0);
LCD_WR_REG_Write(8);
//lcdPixels[9599]=0xFF;
    
Trigger_Reference_Start();
Trigger_Comp_Start();

Pixel_ISR_StartEx(pixelInt);
Pixel_ShiftReg_Start();
Pixel_ShiftReg_1_Start();
Pixel_ShiftReg_GetIntStatus();
//CyDelay(1000);


 #define A_DMA_SRC_BASE (CYDEV_PERIPH_BASE) 
    #define A_DMA_DST_BASE (&pixelValues)
    #define A_DMA_BYTES_PER_BURST 1
    #define A_DMA_REQUEST_PER_BURST 1
    #define A_TABLE_LENGTH 1



    /* Step1 : DmaInitialize - Initialize the DMA channel
	 * Bytes per burst = 1, (8 bit data transferred to VDAC one at a time)
	 * Request per burst = 1 (this will cause transfer of the bytes only with every new request)
	 * High byte of source address = Upper 16 bits of Flash Base address for PSoC 3,
	                               = HI16(&sineTable) for PSoC 5
     * High byte of destination address =  Upper 16 bits of peripheral base address */
    ShiftReg_DMA_Chan = ShiftReg_DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST, HI16(A_DMA_SRC_BASE), HI16(lcdPixels) );
	
    /* Step2 :CyDmaTdAllocate - Allocate TD */
    ShiftReg_DMA_TD[0] = CyDmaTdAllocate();  								 
    
    ShiftReg_DMA_TD[1] = CyDmaTdAllocate();  								 
    
    ShiftReg_DMA_TD[2] = CyDmaTdAllocate();  								 
    
        ShiftReg_DMA_TD[3] = CyDmaTdAllocate();  								 
    
    
    /* Step3 :CyDmaTdSetConfiguration - Configures the TD:
	 * tdHandle = DMA_TD[0] - TD handle previously returned by CyDmaTdAlloc()
	 * Transfer count = table_length (number of bytes to transfer for a sine wave)
	 * Next Td = DMA_TD[0] ; loop back to the same TD to generate a continous sien wave 
	 * Configuration = The source address is incremented after every burst transfer
	 */
        
        int offset = 5;
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[0], 4095, ShiftReg_DMA_TD[1], CY_DMA_TD_INC_DST_ADR); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[0], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels));
        
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[1], 4095, ShiftReg_DMA_TD[2], CY_DMA_TD_INC_DST_ADR ); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[1], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels+4095));
        
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[2], 1410-offset, ShiftReg_DMA_TD[3], CY_DMA_TD_INC_DST_ADR); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[2], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels+8190));
        
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[3], offset, ShiftReg_DMA_TD[0], CY_DMA_TD_INC_DST_ADR); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[3], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels+(9600-offset)));
        
    
	/*CyDmaTdSetConfiguration(ShiftReg_DMA_TD[0], 4095, ShiftReg_DMA_TD[1], CY_DMA_TD_INC_DST_ADR); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[0], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels));
        
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[1], 4095, ShiftReg_DMA_TD[2], CY_DMA_TD_INC_DST_ADR ); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[1], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels+4095));
        
    CyDmaTdSetConfiguration(ShiftReg_DMA_TD[2], 1410, ShiftReg_DMA_TD[0], CY_DMA_TD_INC_DST_ADR | ShiftReg_DMA__TD_TERMOUT_EN); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[2], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels+8190));
        
        CyDmaTdSetConfiguration(ShiftReg_DMA_TD[3], 100, ShiftReg_DMA_TD[0], CY_DMA_TD_INC_DST_ADR | ShiftReg_DMA__TD_TERMOUT_EN); 	 
    CyDmaTdSetAddress(ShiftReg_DMA_TD[3], LO16((uint32)Pixel_ShiftReg_OUT_FIFO_VAL_LSB_PTR), LO16((uint32)lcdPixels));
        */
    /* Step 4 : CyDmaTdSetAddress - Configure the lower 16 bit source and destination addresses 
	 * Source address = Lower 16 bits of sineTable array
	 * Destination address = Lower 16 bits of VDAC8_Data_PTR register */

    /* Step 5: Map the TD to the DMA Channel */
    CyDmaChSetInitialTd(ShiftReg_DMA_Chan, ShiftReg_DMA_TD[3]); 	
	
    
    /* Step 6: Enable the DMA channel */
    while(Pin_8_Read()==0);
    while(Pin_8_Read()==1);
    while(Pin_8_Read()==0);
    while(Pin_8_Read()==1);
    
    CyDmaChEnable(ShiftReg_DMA_Chan, 1); 
    
    VDAC8_1_Start();
    VDAC8_1_SetValue(200);
    Comp_1_Start();
    
    VSync_ISR_StartEx(vsyncISR);
    


UART_1_Start();
while(1)
{
    unsigned int xPix,yPix;
unsigned int c;
unsigned int minX,minY,maxX,maxY;  
   // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  int found = 0;
  for(yPix=0;yPix<H;yPix++) {
    for(xPix=0;xPix<W;xPix++) {
      c = getPixel(xPix,yPix);
      if (c == 1) {
        found = 1;
        if (xPix < minX) {
          minX = xPix;
        }
        if (xPix > maxX) {
          maxX = xPix;
        }
        if (yPix < minY) {
          minY = yPix;
        }
        if (yPix > maxY) {
          maxY = yPix;
        }
      }
    }
  }
CyDelay(100);
if(found)
{
    midX = (minX+maxX)/2;
    midY = (minY+maxY)/2;

    if(midX<140)
    {
        iprintf("Move Left.");
    }
    else if(midX>180)
    {
        iprintf("Move Right.");
    }
    else
    {
        iprintf("Centered X.");
    }
    
    if(midY<100)
    {
        iprintf("\tMove Up.\r\n");
    }
    else if(midY>140)
    {
        iprintf("\tMove Down.\r\n");
    }
    else
    {
        iprintf("\tCentered Y.\r\n");
    }
}
else
{
    iprintf("Nothing Found.\r\n");
    
    
}
  
}
    for(;;)
    {
        /* Place your application code here. */

        
        lcdValue = (0xf800);
        CyDelay(1000);
        lcdValue = (0x07E0);
        CyDelay(1000);
        lcdValue = (0x001F);
        CyDelay(1000);
        
    }
}

/* [] END OF FILE */
