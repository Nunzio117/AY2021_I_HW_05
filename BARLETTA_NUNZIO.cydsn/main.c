
//Include required header files
#include "define.h" //Vi sono presenti tutte le define 
#include "InterruptRoutines.h" //#include "project.h"  #include "stdio.h"
//#include "I2CFunctions.h" //#include "cytypes.h" 
#include "InitFunctions.h"  
#include "ExecutiveFunctions.h" //#include "cytypes.h" 

int main(void)
{   
    CyGlobalIntEnable; /*Enable global interrupts.*/
   
    //Inizializzazione componenti e settaggio flag=0; 
    InitComponents();//Funzione definita in "InitFunctions.h" ed esplicitata in "InitFunctions.c"
   
    for(;;)
    {
        if(flag)
        {
            flag=0;
            
            //Aggiornamento del frequency_rate salavto in EEPROM 
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(frequency_rate, EEPROM_CELL_ADDRESS);
            
            //Aggiornamento dl control register 1 del componente LIS3DH
            SetControlRegister1(); /*Funzione definita in "InitFunctions.h" ed esplicitata in
                                    "InitFunctions.c"*/
        }
        ReadAcceleration();
    }
}

//char message[50];
//        sprintf(message, "LIS3DH CONFIG REGISTER1: 0x%02X\r\n",LIS3DH_reg1_complete);
//        UART_PutString(message);
/* [] END OF FILE */
