
//Include required header files
#include "ExecutiveFunctions.h"
#include "InterruptRoutines.h"
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

int ArrayRate[MAX_FREQUENCY_RATE]={ COUNT_FS_1H, COUNT_FS_10H, COUNT_FS_25H, 
                                    COUNT_FS_50H, COUNT_FS_100H, COUNT_FS_200H};
/*Array contenente il numero di conteggi che la variabile "CountTimer" deve eseguire per compiere
il corretto periodo di campionamento alle diverse frequenze di campionamento del LIS3DH, nella
modalità high resolution; vedere la NOTA relativa ai "COUNT_FS" in "define.h". 
"CountTimer è definita in "InterruptRoutines.h"*/           



void ReadStatusRegister(uint8* da) //Funzione definita in "ExecutiveFunctions.h"
  {
    *da=0;
    //Funzione definita in "I2CFunctions.h" ed esplicitata in "I2CFunctions.c"
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG_ADDRESS,
                                &LIS3DH_Status_Reg);
    
    //Controllo disponibilità di nuovi dati
    if(LIS3DH_Status_Reg & LIS3DH_STATUS_REG_MASK)
    { 
        *da=1;
    }  
        
  }

void ReadAcceleration(void) //Funzione definita in "ExecutiveFunctions.h"
  {
 
//    if( flagStatusReg )
//    {
//       flagStatusReg=0;
       ReadStatusRegister(&lecture);
//    }
    
    //Controllo disponibilità dati tenendo conto del periodo di campionamento del LIS3DH;
    if( lecture )
    {   

        lecture=0;
//        CountTimer=0;
//        CountTimer==ArrayRate[frequency_rate-1])
        
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
        
        UART_PutArray(OutArray,BUFFER_SIZE);

        
    }
    
  }

/* [] END OF FILE */
