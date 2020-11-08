
//Include required header files
#include "ExecutiveFunctions.h"
#include "InterruptRoutines.h"
#include "I2CFunctions.h"
#include "define.h"

uint8_t accelleration[6];
int16_t OutAccInt[3];
//float32 OutAccFloat[3];
uint8_t header = 0xA0; 
uint8_t footer = 0xC0;
//uint8_t OutArray[8];
uint8_t OutArrayf[14];

uint8_t LIS3DH_Status_Reg;

typedef union FloatLongUnion{
	float f;
	uint32_t l;
  }float_long;

float_long OutAccFloat[3];
volatile uint8 lecture;
//char message[50];
uint8_t ReadStatusRegister(void)
  {
    error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG_ADDRESS,
                                        1,
                                        &LIS3DH_Status_Reg);
    if(error==NO_ERROR){
        if( LIS3DH_Status_Reg & 0b00001000 ){ //ZYXDA
            return 1;
        }else{
            return 0;
        }
    }
    else
    {
       UART_PutString("Error output status register\r\n");
       return 0;
    }  
  }

void ReadAccX(void)
  {
    lecture=0;
    
    if(ReadStatusRegister())
    {
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_OUT_X_L_ADDRESS,
                                        6,
                                        accelleration);
        if (error == NO_ERROR){
           lecture=1;
        }else{
           UART_PutString("Error output registers\r\n");   
        }
    }
    
    if(lecture)
    {   
        int k=0;
        for(int i=0;i<3;i++){
            OutAccInt[i] = (int16)((accelleration[i+k] | (accelleration[i+k+1]<<8)))>>4;
            OutAccFloat[i].f = (CONVERSION*OutAccInt[i]);
      
            //completamento del buffer di trasmissione
            k=0;
            while( ((i*4)+k) < ((i+1)*4) ){
            OutArrayf[(i*4)+(k+1)]= (uint8_t)((OutAccFloat[i].l>>(k*8)) & 0xFF);
            k+=1;
            }
            
            k=i+1;
//                sprintf(message, "float: %d\r\n",k);
//                UART_PutString(message);
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
        
            OutArrayf[0]=header;
            OutArrayf[13]=footer;
                
                UART_PutArray(OutArrayf,14);
               
    		
    //	buf[0]=((x.l&0xFF000000)>>24);
    //	buf[1]=((x.l&0x00FF0000)>>16);
    //	buf[2]=((x.l&0x0000FF00)>>8);
    //	buf[3]=((x.l&0x000000FF)>>0);
                     
    }
        
  }
/* [] END OF FILE */
