
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    //Include required header files
    #include "project.h" 
    #include "stdio.h"
    
    CY_ISR_PROTO(Custom_Button_ISR);
    
    uint8_t LIS3DH_reg1_complete;
    int i_rate;
    volatile uint8 flag;
    
    
#endif
/* [] END OF FILE */
