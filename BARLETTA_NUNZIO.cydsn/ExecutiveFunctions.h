
#ifndef __EXECUTIVE_FUNCTIONS_H
    #define __EXECUTIVE_FUNCTIONS_H
    
    //Include required header files
    #include "cytypes.h"
    
    void ReadAcceleration(void); //Funzione di lettura delle accelereazioni date dal LIS3DH
    void ReadStatusRegister(uint8* da); //Funzione di lettura dello status register del LIS3DH
    
    uint8 lecture; /*variabile usata per indicare la disponiblità di nuovi dati da parte
del LIS3DH; disponiblità verificata tramite il controllo presente nella funzione sottostante
"uint8_t ReadStatusRegister(void)" */
    
#endif

/* [] END OF FILE */
