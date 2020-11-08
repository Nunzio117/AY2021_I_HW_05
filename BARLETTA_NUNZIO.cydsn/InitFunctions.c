
//Include header
#include "InitFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h"

uint8_t LIS3DH_ctrl_reg1_complete; /*Variabile usata per indicare il control register 1 del
                                       LIS3DH al completo, dotato sia della define relativa ai
                                       4 bit meno significativi, sia dei bit del ODR[3:0]*/
void InitComponents(void)
  {
    EEPROM_Start();
    UART_Start();
    I2C_Peripheral_Start();
    isr_Button_StartEx(Custom_Button_ISR);
    
    SetControlRegister1();
    SetControlRegister4();
    
    flag=0;
  }  

void SetControlRegister1(void)
  {
//  char message[50];
//    EEPROM_UpdateTemperature();
//    EEPROM_WriteByte(0x01,EEPROM_CELL_ADDRESS);
    frequency_rate=EEPROM_ReadByte(EEPROM_CELL_ADDRESS);
    
//    sprintf(message, "I_rate:0x%02X\r\n", frequency_rate);
//    UART_PutString(message); 
    
    if( (frequency_rate>MAX_FREQUENCY_RATE)||(frequency_rate<MIN_FREQUENCY_RATE) ) { //per vedere se non c'è nulla di anomalo in EEprom
        frequency_rate=MIN_FREQUENCY_RATE;
    }
    
    LIS3DH_ctrl_reg1_complete= ((LIS3DH_CTRL_REG1_L) | (frequency_rate<<4));
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1_ADDRESS,
                                         LIS3DH_ctrl_reg1_complete);
    if (error == NO_ERROR)
    {
        UART_PutString("\nLIS3DH CONTROL REGISTER1 correct config\n"); 
    }
    else
    {
        UART_PutString("\nerror during LIS3DH CONTROL REGISTER1 config \n");    
    }    
  }

void SetControlRegister4(void)
  {
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4_ADDRESS,
                                         LIS3DH_CTRL_REG4_COMPLETE);
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
