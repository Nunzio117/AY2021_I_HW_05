
#ifndef __EXECUTIVE_FUNCTIONS_H
    #define __EXECUTIVE_FUNCTIONS_H
    
    //Include required header files
    #include "cytypes.h"
   
    void Execution(void); //Funzione per esecuzione codice nel loop
    void ReadAcceleration(void); //Funzione di lettura delle accelereazioni date dal LIS3DH
    uint8 ReadStatusRegister(void); //Funzione di lettura dello status register del LIS3DH
    
#endif

/* [] END OF FILE */
