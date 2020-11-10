
//Include required header files
#include "ExecutiveFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h" //Vi sono presenti tutte le define

uint8_t OutAcc[COUNT_OUT_REG]; //Array contenente le uscite dei registri LIS3DH_OUT

int16_t OutAccDigit[N_ACC_AXIS];//Array contenente i valori in digit delle accelerazioni sui 3 assi

uint8_t OutArray[BUFFER_SIZE]; //Array contenente il buffer di trasmissione

//Union usata come trick per poter mandare l'intero valore float tramite buffer
typedef union FloatLongUnion
  {
	float f;
	uint32_t l;
  }float_long;

float_long OutAccFloat[N_ACC_AXIS];/*Array strutturato ad "union" contenente i valori delle 
                                     accelerazioni sui 3 assi*/

int ArrayRate[MAX_FREQUENCY_RATE]={ COUNT_FS_1H, COUNT_FS_10H, COUNT_FS_25H, 
                                    COUNT_FS_50H, COUNT_FS_100H, COUNT_FS_200H};
/*Array contenente il numero di conteggi che la variabile "CountTimer" deve eseguire per compiere
il corretto periodo di campionamento alle diverse frequenze di campionamento del LIS3DH, nella
modalità high resolution; vedere la NOTA relativa in "define.h". 
"CountTimer è definita in "InterruptRoutines.h"*/           
                 
//Funzione di lettura accelerazioni e definita in "ExecutiveFunctions.h"
void ReadAcceleration(void) 
  {
    
    //Controllo disponibilità dati tenendo conto del periodo di campionamento del LIS3DH;
    if(CountTimer==ArrayRate[frequency_rate-1])
    {   
        CountTimer=0;
        
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
