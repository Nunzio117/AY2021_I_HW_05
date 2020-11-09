
#ifndef __I2C_FUNCTIONS_H
    #define __I2C_FUNCTIONS_H
    
    //Include required header files
    #include "cytypes.h"
   
    /*Enumerazione usata per indicare errori che potrebbero giungere nelle funzioni di scrittura
    e lettura del registri del dispositivo LIS3DH*/
    typedef enum {
        NO_ERROR,           ///< Nessun errore generato
        ERROR               ///< Errore generato
    } ErrorCode;
    
 
    /** \brief Start the I2C peripheral.
    *   
    *   This function starts the I2C peripheral so that it is ready to work.
    */
    ErrorCode I2C_Peripheral_Start(void);
    
    /** \brief Stop the I2C peripheral.
    *   
    *   This function stops the I2C peripheral from working.
    */
    ErrorCode I2C_Peripheral_Stop(void);
    
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address, uint8_t register_address,
                                            uint8_t data);
    
    ErrorCode I2C_Peripheral_WriteRegisterMulti(uint8_t device_address, uint8_t register_address,
                                            uint8_t register_count, uint8_t* data);
   
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    /** 
    *   \brief Read multiple bytes over I2C.
    *   
    *   This function performs a complete reading operation over I2C from multiple
    *   registers.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the first register to be read.
    *   \param register_count Number of registers we want to read.
    *   \param data Pointer to an array where data will be saved.
    */
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data);
    
    /**
    *   \brief Check if device is connected over I2C.
    *
    *   This function checks if a device is connected over the I2C lines.
    *   \param device_address I2C address of the device to be checked.
    *   \retval Returns true (>0) if device is connected.
    */
  
    
#endif 
/* [] END OF FILE */
