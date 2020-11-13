
//Include required header files
#include "ExecutiveFunctions.h"
#include "InterruptRoutines.h"
#include "InitFunctions.h"
#include "I2CFunctions.h"
#include "define.h" //Vi sono presenti tutte le define


uint8_t LIS3DH_Status_Reg; //Variabile per la configurazione dei pin dello status register

uint8_t OutAcc[COUNT_OUT_REG]; //Array per le uscite dei registri LIS3DH_OUT
int16_t OutAccDigit[N_ACC_AXIS];//Array per i valori in digit delle accelerazioni sui 3 assi
uint8_t OutArray[BUFFER_SIZE]; //Array per il buffer di trasmissione

//Union usata come trick per poter mandare l'intero valore float tramite buffer di trasmissione
typedef union FloatLongUnion
  {
	float f; //Parte per contenuto float
	uint32_t l;//Parte in uint32 usata nel casting per il completamento del buffer di trasmissione
  }float_long;
float_long OutAccFloat[N_ACC_AXIS];/*Array strutturato ad "union" per i valori delle 
                                     accelerazioni sui 3 assi*/


//Funzione per esecuzione loop e definita in "ExecutiveFunctions.h"
void Execution(void){
    
    if(flag)
    {
        flag=0; //Variabile definita in "InterruptRoutines.h"
        
        //Aggiornamento del frequency rate salvato in EEPROM 
        EEPROM_UpdateTemperature();
        EEPROM_WriteByte(frequency_rate, EEPROM_CELL_ADDRESS);
        
        /*Aggiornamento dl control register 1 del componente LIS3DH;
        Funzione definita in "InitFunctions.h" ed esplicitata in "InitFunctions.c"*/
        SetControlRegister1(); 
    }
        
    /*Lettura status register ed accelerazioni
    Funzione definita in "ExecutiveFunctions.h" ed esplicitata in qui di seguito*/
    ReadAcceleration();
}


//Funzione per lettura dello status register di LIS3DH e definita in "ExecutiveFunctions.h"
uint8 ReadStatusRegister(void)
  {
    
    /*Lettura dello status register;
    La funzione qui presente è definita in "I2CFunctions.h" ed esplicitata in "I2CFunctions.c"*/
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG_ADDRESS,
                                &LIS3DH_Status_Reg);
    
    //Controllo disponibilità di nuovi dati
    if(LIS3DH_Status_Reg & LIS3DH_STATUS_REG_MASK)
    { 
        return 1;
    }
    
    return 0;
        
  }

//Funzione per lettura accelerazioni e definita in "ExecutiveFunctions.h"
void ReadAcceleration(void) 
  {
  
    //Controllo disponibilità di nuovi dati tenendo conto dello status register del LIS3DH
    if( ReadStatusRegister() )
    {   
        //Lettura dei registri LIS3DH_OUT
        I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L_ADDRESS,
                                         COUNT_OUT_REG,OutAcc);
        
        //Assegnazione HEADER e TAIL al buffer di trasmissione
        OutArray[0]=HEADER;
        OutArray[BUFFER_SIZE-1]=TAIL;
        
        int k=0;
        for(int i=0;i<N_ACC_AXIS;i++)
        {
            //Composizione delle accelerazioni in digit e conversione a float
            OutAccDigit[i] = (int16)((OutAcc[i+k] | (OutAcc[i+k+1]<<8)))>>4;
            OutAccFloat[i].f = (CONVERSION*OutAccDigit[i]);
            
            //Completamento del buffer di trasmissione
            k=0;
            while( ((i*4)+k) < ((i+1)*4) )
            {
                OutArray[(i*4)+(k+1)]= (uint8_t)((OutAccFloat[i].l>>(k*8)) & 0xFF);
                k+=1;
            }
            
            k=i+1;
        }
        
        //Invio del buffer
        UART_PutArray(OutArray,BUFFER_SIZE);     
    }
    
  }


/* [] END OF FILE */
