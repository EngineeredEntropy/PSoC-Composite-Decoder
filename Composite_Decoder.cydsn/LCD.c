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

/* [] END OF FILE */

#include "LCD.h"
#include "project.h"

void writeBusLCD(uint8 value)
{
    LCD_Data_Reg_Write(value);
    LCD_WR_REG_Write(5);
    LCD_WR_REG_Write(7);
}

void writeComLCD(uint8 value)
{
    LCD_RS_Write(0);
    writeBusLCD(value);
    
}
void writeDataLCD(uint8 value)
{
    LCD_RS_Write(1);
    writeBusLCD(value);
    
}

void Address_set(uint16 y1,uint16 x1,uint16 y2,uint16 x2)
{
    writeComLCD(0x2a);
    writeDataLCD((x1>>8)&0xFF);
    writeDataLCD(x1&0xFF);
    writeDataLCD((x2>>8)&0xFF);
    writeDataLCD(x2&0xFF);
    writeComLCD(0x2b);
    writeDataLCD((y1>>8)&0xFF);
    writeDataLCD(y1&0xFF);
    writeDataLCD((y2>>8)&0xFF);
    writeDataLCD(y2&0xFF);
    writeComLCD(0x2c);     
}
void clearLCD(uint16 value)
{
    
 uint16 i,m;
    
 
  //writeComLCD(0x02c); //write_memory_start
  //digitalWrite(LCD_RS,HIGH);
    LCD_CS_Write(0);
    
  for(i=0;i<240;i++)
    for(m=0;m<320;m++)
    {
      writeDataLCD((value>>8&0xFF));
      writeDataLCD(value&0xFF);

    }
    LCD_CS_Write(1);
  //digitalWrite(LCD_CS,HIGH);  
    
}
void initLCD(void)
{
    LCD_RST_Write(1);
    LCD_CS_Write(1);
    LCD_RS_Write(1);
    LCD_WR_REG_Write(7);
    LCD_RD_Write(1);
    CyDelay(100);
    
    LCD_RST_Write(1);
    CyDelay(5);
    LCD_RST_Write(0);
    CyDelay(15);
    LCD_RST_Write(1);
    CyDelay(15);
    LCD_CS_Write(1);
    LCD_WR_REG_Write(7);
    LCD_CS_Write(0);
    
    writeComLCD(0xCB);  
    writeDataLCD(0x39); 
    writeDataLCD(0x2C); 
    writeDataLCD(0x00); 
    writeDataLCD(0x34); 
    writeDataLCD(0x02); 

    writeComLCD(0xCF);  
    writeDataLCD(0x00); 
    writeDataLCD(0XC1); 
    writeDataLCD(0X30); 

    writeComLCD(0xE8);  
    writeDataLCD(0x85); 
    writeDataLCD(0x00); 
    writeDataLCD(0x78); 

    writeComLCD(0xEA);  
    writeDataLCD(0x00); 
    writeDataLCD(0x00); 
 
    writeComLCD(0xED);  
    writeDataLCD(0x64); 
    writeDataLCD(0x03); 
    writeDataLCD(0X12); 
    writeDataLCD(0X81); 

    writeComLCD(0xF7);  
    writeDataLCD(0x20); 
  
    writeComLCD(0xC0);    //Power control 
    writeDataLCD(0x23);   //VRH[5:0] 
 
    writeComLCD(0xC1);    //Power control 
    writeDataLCD(0x10);   //SAP[2:0];BT[3:0] 

    writeComLCD(0xC5);    //VCM control 
    writeDataLCD(0x3e);   //Contrast
    writeDataLCD(0x28); 
 
    writeComLCD(0xC7);    //VCM control2 
    writeDataLCD(0x86);   //--
 
    writeComLCD(0x36);    // Memory Access Control 
    //writeDataLCD(0x48);  
    writeDataLCD(0xE8);  

    writeComLCD(0x3A);    
    writeDataLCD(0x55); 

    writeComLCD(0xB1);    
    writeDataLCD(0x00);  
    writeDataLCD(0x18); 
 
    writeComLCD(0xB6);    // Display Function Control 
    writeDataLCD(0x08); 
    writeDataLCD(0x82);
    writeDataLCD(0x27);  

    writeComLCD(0x11);    //Exit Sleep 
    CyDelay(120); 
				
    writeComLCD(0x29);    //Display on 
    writeComLCD(0x2c);    
    
    Address_set(0,0,240,320);
}