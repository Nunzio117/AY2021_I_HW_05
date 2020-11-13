
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    //Include required header files
    #include "project.h" 
    #include "stdio.h"
    
    CY_ISR_PROTO(Custom_Button_ISR);
    
    volatile uint8 flag; //Variabile usata per indicare l'avvenuta premuta del pulsante
    
    int frequency_rate; /*Variabile usata per indicare la combinazione dei bit ODR[3:0] del
                         control register 1 del LIS3DH,i quali impostano la frequenza di 
                         campionamento del dispositivo. 
    TABELLA:
    Index ODR3 ODR2 ODR1 ODR0 Power mode selection 
      0    0    0    0    0   Power-down mode
      1    0    0    0    1   HR/Normal/Low-power mode (1 Hz)  
      2    0    0    1    0   HR/Normal/Low-power mode (10 Hz) 
      3    0    0    1    1   HR/Normal/Low-power mode (25 Hz)
      4    0    1    0    0   HR/Normal/Low-power mode (50 Hz)
      5    0    1    0    1   HR/Normal/Low-power mode (100 Hz)
      6    0    1    1    0   HR/Normal/Low-power mode (200 Hz)
      7    0    1    1    1   HR/Normal/Low-power mode (400 Hz)
      8    1    0    0    0   Low power mode (1.60 kHz)
      9    1    0    0    1   HR/normal (1.344 kHz)
                              Low-power mode (5.376 kHz)
    Per il progetto richiesto il LIS3DH lavorerà con frequenze che andranno da 1Hz a 200Hz */ 
    
#endif

/* [] END OF FILE */
