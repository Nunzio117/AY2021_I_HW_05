
//Include required header files
#include "InterruptRoutines.h"
#include "define.h" //Vi sono presenti tutte le define 


CY_ISR(Custom_Button_ISR)
{
    frequency_rate+=1; //Variabile descritta e definita in "InterruptRoutines.h"
    
    if(frequency_rate>MAX_FREQUENCY_RATE)
    {
        frequency_rate=MIN_FREQUENCY_RATE; 
    }
    
    flag=1; //Variabile definita in "InterruptRoutines.h"
}

CY_ISR(Custom_Timer_ISR)
{
    Timer_ReadStatusRegister();
    CountTimer+=1; //Variabile definita in "InterruptRoutines.h"
}

/* [] END OF FILE */
