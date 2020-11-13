
//Include required header files 
#include "InitFunctions.h"
#include "ExecutiveFunctions.h" 

int main(void)
{   
    /*Inizializzazione componenti e settaggio variabili;
    Funzione definita in "InitFunctions.h" ed esplicitata in "InitFunctions.c"*/
    InitComponents();
    
    for(;;)
    {
        /*Esecuzione loop;
        Funzione definita in "InitFunctions.h" ed esplicitata in "InitFunctions.c"*/
        Execution();
    }
}

/* [] END OF FILE */
