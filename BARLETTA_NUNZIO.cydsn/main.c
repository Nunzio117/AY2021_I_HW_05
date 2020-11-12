
//Include required header files
#include "define.h" //Vi sono presenti tutte le define 
#include "InterruptRoutines.h" //#include "project.h"  #include "stdio.h"
//#include "I2CFunctions.h" //#include "cytypes.h" 
#include "InitFunctions.h"  
#include "ExecutiveFunctions.h" //#include "cytypes.h" 

int main(void)
{   
    CyGlobalIntEnable; /*Enable global interrupts.*/
    lecture=0;
    
    //Inizializzazione componenti e settaggio variabili; 
    InitComponents();//Funzione definita in "InitFunctions.h" ed esplicitata in "InitFunctions.c"
    
    for(;;)
    {
        
        if(flag)
        {
            flag=0;
//            Timer_Stop();
            //Aggiornamento del frequency_rate salavto in EEPROM 
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(frequency_rate, EEPROM_CELL_ADDRESS);
            
            //Aggiornamento dl control register 1 del componente LIS3DH
            SetControlRegister1(); /*Funzione definita in "InitFunctions.h" ed esplicitata in
                                   "InitFunctions.c"*/
            CountTimer=0;
            flagStatusReg=0;
            lecture=0;
//            Timer_Start();
            
        }
        
        ReadAcceleration();//Lettura accelerazioni
        
    }
}

/* [] END OF FILE */
