
//Include required header files
#include "InitFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h" //Vi sono presenti tutte le define

uint8_t LIS3DH_ctrl_reg1_complete; /*Variabile usata per indicare il control register 1 del
                                   LIS3DH al completo, dotato sia della define relativa ai
                                   4 bit meno significativi, sia dei bit del ODR[3:0]*/

/*Funzione per inizializzione componenti e variabili, settaggio dei control register 1 e 4 di 
LIS3DH e definita in "InitFunctions.h"*/
void InitComponents(void) 
  {
    EEPROM_Start();
    UART_Start();
    Timer_Start();
    I2C_Peripheral_Start();
    
    isr_Button_StartEx(Custom_Button_ISR);
    isr_Timer_StartEx(Custom_Timer_ISR);
    
    SetControlRegister1(); //Funzione definita in "InitFunctions.h" ed esplicitata di seguito
    SetControlRegister4(); //funzione definita in "InitFunctions.h" ed esplicitata di seguito
    
    flag=0; //Variabile definita in "InterruptRoutines.h"
    flagStatusReg=0;
    CountTimer=0; //Variabile definita in "InterruptRoutines.h"
  }  

//Funzione per il settaggio del control register 1 di LIS3DH e definita in "InitFunctions.h"
void SetControlRegister1(void) 
  {
    //Recupero del frequency_rate dalla cella di memoria del EEPROM scelta
    frequency_rate=EEPROM_ReadByte(EEPROM_CELL_ADDRESS);
    
    //Controllo per assicurasi di essere in un range di valori previsto
    if( (frequency_rate>MAX_FREQUENCY_RATE)||(frequency_rate<MIN_FREQUENCY_RATE) ) 
    { 
        frequency_rate=MIN_FREQUENCY_RATE;
    }
    
    //Completamento del control register 1 dati i 4 bit meno significativi ed i 4 bit ODR
    LIS3DH_ctrl_reg1_complete= (LIS3DH_CTRL_REG1_L | frequency_rate<<4);
    
    //La funzione qui presente, è definita in "I2CFunctions.h" ed esplicitata in "I2CFunctions.c"
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1_ADDRESS,
                                         LIS3DH_ctrl_reg1_complete); 
  }

//Funzione per il settaggio del control register 4 di LIS3DH e definita in "InitFunctions.h"
void SetControlRegister4(void)
  {
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4_ADDRESS,
                                         LIS3DH_CTRL_REG4_COMPLETE);
  }

/* [] END OF FILE */
