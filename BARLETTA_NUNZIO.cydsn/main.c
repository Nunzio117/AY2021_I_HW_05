
#include "define.h"
#include "InterruptRoutines.h" //#include "project.h"  #include "stdio.h"
//#include "I2CFunctions.h" //#include "cytypes.h" 
#include "InitFunctions.h"  
#include "ExecutiveFunctions.h"

//char message[50];

int main(void)
{   
    CyGlobalIntEnable; /*Enable global interrupts.*/
    
    /*Inizializzazione componenti e settaggio flag=0; funzione definita in "InitFunctions.h"
    ed esplicitata in "InitFunctions.c"*/
    InitComponents();

    for(;;)
    {
        if(flag)
        {
            flag=0;
            
            //Aggiornamento EEPROM 
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(frequency_rate, EEPROM_CELL_ADDRESS);
            
            //Aggiornamento registro 1 del componente LIS3DH
            SetControlRegister1();  
        }
        ReadAccX();
    }
}
        //        sprintf(message, "LIS3DH CONFIG REGISTER1: 0x%02X\r\n",LIS3DH_reg1_complete);
        //        UART_PutString(message);
/* [] END OF FILE */
