
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

//typedef union FloatLongUnion{
//	float f;
//	uint32_t l;
//  }float_long;
//
//float_long OutAccFloat[3];
float32 OutAccFloat[3];

char message[50];

void ReadAccX(void)
  {
    error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_OUT_X_L_ADDRESS,
                                        6,
                                        accelleration);
    if (error == NO_ERROR)
        {   
            int k=0;
            for(int i=0;i<3;i++){
                OutAccInt[i] = (int16)((accelleration[i+k] | (accelleration[i+k+1]<<8)))>>4;
                OutAccFloat[i] = (CONVERSION*OutAccInt[i]);
                
//                k=0;
//                while( ((i*4)+k) < ((i+1)*4) ){
//                OutArrayf[(i*4)+(k+1)]= ((OutAccFloat[i].l & ((0x000000FF)<<(k*8)))>>(k*8));
//                k+=1;
//                }
                
                k=i+1;
//                sprintf(message, "float: %d\r\n",k);
//                UART_PutString(message);
            }
//            UART_PutString("azzo\n");
            
            
 //	buf[0]=((x.l&0xFF000000)>>24);
//	buf[1]=((x.l&0x00FF0000)>>16);
//	buf[2]=((x.l&0x0000FF00)>>8);
//	buf[3]=((x.l&0x000000FF)>>0);

//            OutArrayf[1]= (OutAccFloat[0].l & (0x000000FF)>>0);
//            OutArrayf[2]= (OutAccFloat[0].l & (0x0000FF00)>>8);
//            OutArrayf[3]= (OutAccFloat[0].l & (0x00FF0000)>>16);
//            OutArrayf[4]= (OutAccFloat[0].l & (0xFF000000)>>24);
//            
//            OutArrayf[5]= (OutAccFloat[1].l & (0x000000FF)>>0);
//            OutArrayf[6]= (OutAccFloat[1].l & (0x0000FF00)>>8);
//            OutArrayf[7]= (OutAccFloat[1].l & (0x00FF0000)>>16);
//            OutArrayf[8]= (OutAccFloat[1].l & (0xFF000000)>>24);
//            
//            OutArrayf[9]= (OutAccFloat[2].l & (0x000000FF)>>0);
//            OutArrayf[10]= (OutAccFloat[2].l & (0x0000FF00)>>8);
//            OutArrayf[11]= (OutAccFloat[2].l & (0x00FF0000)>>16);
//            OutArrayf[12]= (OutAccFloat[2].l & (0xFF000000)>>24);

//            sprintf(message, "float: %d\r\n",OutArrayf[10]);
//            UART_PutString(message);
            int16 ma[3];
            ma[0]= (int16) (OutAccFloat[0]*1000);
            ma[1]= (int16) (OutAccFloat[1]*1000);
            ma[2]= (int16) (OutAccFloat[2]*1000);
//           sprintf(message, "float: %ld\r\n",ma[2]);
//           UART_PutString(message);
        
            OutArrayf[1]= (uint8_t)(ma[0] & 0xFF);
            OutArrayf[2]= (uint8_t)((ma[0]>>8) & 0xFF);
            OutArrayf[3]= (uint8_t)(ma[1] & 0xFF);
            OutArrayf[4]= (uint8_t)((ma[1]>>8) & 0xFF);
            
            OutArrayf[5]= (uint8_t)(ma[2] & 0xFF);
            OutArrayf[6]= (uint8_t)((ma[2]>>8) & 0xFF);
        
            OutArrayf[0]=header;
            OutArrayf[7]=footer;
            UART_PutArray(OutArrayf,8);
           
		
//	buf[0]=((x.l&0xFF000000)>>24);
//	buf[1]=((x.l&0x00FF0000)>>16);
//	buf[2]=((x.l&0x0000FF00)>>8);
//	buf[3]=((x.l&0x000000FF)>>0);
            
            
        }
        else
        {
            UART_PutString("Error output registers\r\n");   
        }  
  }
/* [] END OF FILE */
