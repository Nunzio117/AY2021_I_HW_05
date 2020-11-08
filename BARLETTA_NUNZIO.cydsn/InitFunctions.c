
#include "InitFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h"

void InitComponents(void)
  {
    EEPROM_Start();
    UART_Start();
    I2C_Peripheral_Start();
    isr_Button_StartEx(Custom_Button_ISR);
    
    SetRegister1();
    SetRegister4();
    
    flag=0;
  }  

void SetRegister1(void)
  {
//  char message[50];
//    EEPROM_UpdateTemperature();
//    EEPROM_WriteByte(0x01,EEPROM_CELL_ADDRESS);
    i_rate=EEPROM_ReadByte(EEPROM_CELL_ADDRESS);
    
//    sprintf(message, "I_rate:0x%02X\r\n", i_rate);
//    UART_PutString(message); 
    
    if( (i_rate>0x06)||(i_rate<0x01) ) { //per vedere se non c'è nulla di anomalo in EEprom
        i_rate=0x01;
    }
//    sprintf(message, "I_rate33:0x%02X\r\n", i_rate);
//    UART_PutString(message);
    
    LIS3DH_reg1_complete= ((LIS3DH_REG1_L) | (i_rate<<4));
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG1_ADDRESS,
                                         LIS3DH_reg1_complete);
    if (error == NO_ERROR)
    {
        UART_PutString("\nLIS3DH CONTROL REGISTER1 correct config\n"); 
    }
    else
    {
        UART_PutString("\nerror during LIS3DH CONTROL REGISTER1 config \n");    
    } 
    
//    i_register=1;
//    uint8_t LIS3DH_reg4_complete=LIS3DH_REG4_COMPLETE;
//    error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4_ADDRESS,
//                                              i_register , &LIS3DH_reg4_complete);
//    if (error == NO_ERROR)
//    {
//        sprintf(message, "LIS3DH CONFIG REGISTER4 after being updated: 0x%02X\r\n", LIS3DH_reg4_complete);
//        UART_PutString(message); 
//    }
//    else
//    {
//        UART_PutString("Error occurred during I2C comm to read config register\r\n");   
//    }
     
  }
void SetRegister4(void)
  {
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG4_ADDRESS,
                                         LIS3DH_REG4_COMPLETE);
    if (error == NO_ERROR)
    {
        UART_PutString("LIS3DH CONTROL REGISTER4 correct config\n"); 
    }
    else
    {
        UART_PutString("error during LIS3DH CONTROL REGISTER4 config\n");    
    }
  }
/* [] END OF FILE */
