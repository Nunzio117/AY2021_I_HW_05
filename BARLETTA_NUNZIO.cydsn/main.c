
#include "define.h"
#include "InterruptRoutines.h" //#include "project.h"  #include "stdio.h"
//#include "I2CFunctions.h" //#include "cytypes.h" 
#include "InitFunctions.h"  
#include "ExecutiveFunctions.h"

char message[50];

int main(void)
{   
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    InitComponents();
//    EEPROM_Start();
//    UART_Start();
//    isr_Button_StartEx(Custom_Button_ISR);
//    I2C_Peripheral_Start();
//    
//    EEPROM_UpdateTemperature();
//    EEPROM_WriteByte(0xA0,EEPROM_CELL_ADDRESS);
//    i_rate=EEPROM_ReadByte(EEPROM_CELL_ADDRESS);
//    InitRegisters();
  
    for(;;)
    {
        if(flag)
        {
            flag=0;
            //aggiornamento EEPROM ed aggiornamento registro 1
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(i_rate, EEPROM_CELL_ADDRESS);
            
        //        LIS3DH_reg1_complete= ((LIS3DH_REG1_L) | (i_rate<<4));
        //        sprintf(message, "LIS3DH CONFIG REGISTER1: 0x%02X\r\n",LIS3DH_reg1_complete);
        //        UART_PutString(message);
            SetRegister1();
            
        }
        
        ReadAccX();
    }
}

/* [] END OF FILE */
