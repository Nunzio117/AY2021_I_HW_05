
//Include required header files
#include "ExecutiveFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h" //Vi sono presenti tutte le define

uint8_t OutAcc[COUNT_OUT_REG]; //Array contenente le uscite dei registri LIS3DH_OUT

int16_t OutAccDigit[N_ACC_AXIS];//Array contenente i valori in digit delle accelerazioni sui 3 assi

uint8_t OutArray[BUFFER_SIZE]; //Array contenente il buffer di trasmissione

uint8_t LIS3DH_Status_Reg; //Variabile contenente la configurazione dei pin dello status register

//union usata come trick per poter mandare l'intero valore float tramite buffer
typedef union FloatLongUnion{
	float f;
	uint32_t l;
  }float_long;

float_long OutAccFloat[N_ACC_AXIS];/*Array strutturato ad "union" contenente i valori delle 
                                     accelerazioni sui 3 assi*/

volatile uint8 lecture; /*variabile usata per indicare la disponiblità di nuovi dati da parte
del LIS3DH; disponiblità verificata tramite il controllo presente nella funzione sottostante
"uint8_t ReadStatusRegister(void)" */

int ArrayRate[7]={400,40,16,8,4,2,1};
uint8_t ReadStatusRegister(void) //Funzione definita in "ExecutiveFunctions.h"
  {
    
    //Funzione definita in "I2CFunctions.h" ed esplicitata in "I2CFunctions.c"
    I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG_ADDRESS,
                                &LIS3DH_Status_Reg);

    //Controllo disponibilità di nuovi dati
    if( LIS3DH_Status_Reg & LIS3DH_STATUS_REG_MASK )
    { 
        return 1;
    }
    
    return 0;
  }

void ReadAcceleration(void)
  {
    lecture=0;
    
//    if(ReadStatusRegister())
//    {
//        I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L_ADDRESS,
//                                       COUNT_OUT_REG,OutAcc);
//        lecture=1;
//    }
    
    if(flagTimer==ArrayRate[frequency_rate-1])
    {
        flagTimer=0;
        I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L_ADDRESS,
                                         COUNT_OUT_REG,OutAcc);
        lecture=1;
    }
    
    
    if(lecture)
    {   
        int k=0;
        for(int i=0;i<N_ACC_AXIS;i++){
            OutAccDigit[i] = (int16)((OutAcc[i+k] | (OutAcc[i+k+1]<<8)))>>4;
            OutAccFloat[i].f = (CONVERSION*OutAccDigit[i]);
            
            //completamento del buffer di trasmissione
            k=0;
            while( ((i*4)+k) < ((i+1)*4) ){
            OutArray[(i*4)+(k+1)]= (uint8_t)((OutAccFloat[i].l>>(k*8)) & 0xFF);
            k+=1;
            }
            
            k=i+1;

        }
            
//            OutArrayf[1]= (uint8_t)((OutAccFloat[0].l)>>0 & 0xFF);
//            OutArrayf[2]= (uint8_t)((OutAccFloat[0].l)>>8 & 0xFF);
//            OutArrayf[3]= (uint8_t)((OutAccFloat[0].l)>>16 & 0xFF);
//            OutArrayf[4]= (uint8_t)((OutAccFloat[0].l)>>24 & 0xFF);
//            
//            OutArrayf[5]= (uint8_t)((OutAccFloat[1].l)>>0 & 0xFF);
//            OutArrayf[6]= (uint8_t)((OutAccFloat[1].l)>>8 & 0xFF);
//            OutArrayf[7]= (uint8_t)((OutAccFloat[1].l)>>16 & 0xFF);
//            OutArrayf[8]= (uint8_t)((OutAccFloat[1].l)>>24 & 0xFF);
//            
//            OutArrayf[9]= (uint8_t)((OutAccFloat[2].l)>>0 & 0xFF);
//            OutArrayf[10]= (uint8_t)((OutAccFloat[2].l)>>8 & 0xFF);
//            OutArrayf[11]= (uint8_t)((OutAccFloat[2].l)>>16 & 0xFF);
//            OutArrayf[12]= (uint8_t)((OutAccFloat[2].l)>>24 & 0xFF);
            


//            int16 ma[3];
//            ma[0]= (int16) (OutAccFloat[0]*1000);
//            ma[1]= (int16) (OutAccFloat[1]*1000);
//            ma[2]= (int16) (OutAccFloat[2]*1000);
//        
//            OutArrayf[1]= (uint8_t)(ma[0] & 0xFF);
//            OutArrayf[2]= (uint8_t)((ma[0]>>8) & 0xFF);
//            OutArrayf[3]= (uint8_t)(ma[1] & 0xFF);
//            OutArrayf[4]= (uint8_t)((ma[1]>>8) & 0xFF);
//            
//            OutArrayf[5]= (uint8_t)(ma[2] & 0xFF);
//            OutArrayf[6]= (uint8_t)((ma[2]>>8) & 0xFF);
        
            OutArray[0]=HEADER;
            OutArray[BUFFER_SIZE-1]=TAIL;
                
            UART_PutArray(OutArray,BUFFER_SIZE);
               
    		
    //	buf[0]=((x.l&0xFF000000)>>24);
    //	buf[1]=((x.l&0x00FF0000)>>16);
    //	buf[2]=((x.l&0x0000FF00)>>8);
    //	buf[3]=((x.l&0x000000FF)>>0);
                     
    }
        
  }
/* [] END OF FILE */
