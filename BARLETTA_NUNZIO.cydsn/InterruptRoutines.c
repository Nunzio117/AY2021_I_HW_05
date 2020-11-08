
// Include header
#include "InterruptRoutines.h"
#include "define.h"
//char message[50];

CY_ISR(Custom_Button_ISR)
{
    i_rate+=1;
    if(i_rate==0x07){
        i_rate=0x01;
    }
//    sprintf(message, "i_rate: 0x%02X\n",i_rate);
//    UART_PutString(message);
    
    
   
    flag=1;
}


/* [] END OF FILE */
