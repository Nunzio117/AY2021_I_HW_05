
//Include required header files
#include "InterruptRoutines.h"
#include "define.h"

CY_ISR(Custom_Button_ISR)
{
    frequency_rate+=1; //Variabile descritta e definita in "InterruptRoutines.h"
    if(frequency_rate>MAX_FREQUENCY_RATE){
        frequency_rate=MIN_FREQUENCY_RATE; 
    }
    
    flag=1; //Variabile definita in "InterruptRoutines.h"
}


/* [] END OF FILE */
