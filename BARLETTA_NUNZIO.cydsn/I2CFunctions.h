
#ifndef __I2C_FUNCTIONS_H
    #define __I2C_FUNCTIONS_H
    
    //Include required header files
    #include "cytypes.h"
   
    /*Enumerazione usata per indicare errori che potrebbero giungere nelle funzioni di scrittura
    e lettura dei registri del dispositivo LIS3DH; uso per scopi di debugging*/
    typedef enum {
        NO_ERROR,           ///< Nessun errore generato
        ERROR               ///< Errore generato
    } ErrorCode;
    
    
    ErrorCode I2C_Peripheral_Start(void); //Funzione per startare la periferica I2C
    
    ErrorCode I2C_Peripheral_Stop(void); //Funzione per stoppare la periferica I2C
    
    /*Funzione per effettuare un'operazione di scrittura su un registro della perifierica I2C;
    i parametri richiesti sono:
    - indirizzo del device collegato tramite counicazione I2C --> "device_address";
    - indirizzo del registro in cui scrivere il mio dato --> "register_address";
    - dato da inserire nel registro designato --> "data". */
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address, uint8_t register_address,
                                            uint8_t data);
   
     /*Funzione per effettuare un'operazione di lettura su un registro della perifierica I2C;
    i parametri richiesti sono:
    - indirizzo del device collegato tramite counicazione I2C --> "device_address";
    - indirizzo del registro da cui leggere il byte --> "register_address";
    - puntatore a una variabile in cui verrà salvato il byte --> "data". */
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, uint8_t register_address,
                                            uint8_t* data);
 
    /*Funzione per effettuare un'operazione di lettura su più registri della perifierica I2C;
    i parametri richiesti sono:
    - indirizzo del device collegato tramite counicazione I2C --> "device_address";
    - indirizzo del registro da cui leggere il byte --> "register_address";
    - puntatore a un'array in cui verranno salvati i byte --> "data". */
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address, uint8_t register_address,
                                               uint8_t register_count, uint8_t* data);
 
#endif 
/* [] END OF FILE */
