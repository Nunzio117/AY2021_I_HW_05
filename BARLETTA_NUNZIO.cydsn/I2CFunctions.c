
//Include required header files
#include "I2CFunctions.h"
#include "I2C_Master.h" 

// <<< NOTA SUI RETURN: sono stati lasciati per scopo di debugging >>>

//Funzione per startare la periferica I2C e definita in "I2CFunctions.h"
ErrorCode I2C_Peripheral_Start(void) 
  {
    I2C_Master_Start();  
    
    return NO_ERROR; 
  }

//Funzione per stoppare la periferica I2C e definita in "I2CFunctions.h"    
ErrorCode I2C_Peripheral_Stop(void)
  {
    I2C_Master_Stop();
  
    return NO_ERROR;
  }
    
/*Funzione per effettuare un'operazione di scrittura su un registro della perifierica I2C e 
definita in I2CFunctions.h" */
ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address, uint8_t register_address,
                                            uint8_t data)
  {
    //Invio della condizione di start
    uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        //Scrittura dell'indirizzo del registro
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            //Scrittura del byte di interesse
            error = I2C_Master_MasterWriteByte(data);
        }
    }
    //Invio della condizione di stop
    I2C_Master_MasterSendStop();
    //Return error code
    return error ? ERROR : NO_ERROR;
  }
 
/*Funzione per effettuare un'operazione di lettura su un registro della perifierica I2C e 
definita in I2CFunctions.h" */
ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, uint8_t register_address,
                                       uint8_t* data)
  {
    //Invio della condizione di start
    uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        //Scrittura dell'indirizzo del registro
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            //Invio della condizione di restart
            error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                //Lettura dato senza acknowledgement
                *data = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
            }
        }
    }
    //Invio della condizione di stop
    I2C_Master_MasterSendStop();
    //Return error code
    return error ? ERROR : NO_ERROR;
  }   

/*Funzione per effettuare un'operazione di lettura su più registri della perifierica I2C e 
definita in I2CFunctions.h" */
ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address, uint8_t register_address,
                                                uint8_t register_count, uint8_t* data)
  {
    //Invio della condizione di start
    uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        //Indirizzo di scrittura del registro da leggere con MSB uguale a 1
        register_address |= 0x80; // Datasheet indication for multi read -- autoincrement
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            //Invio della condizione di restart
            error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                //Continua lettura dei registri finchè vi sono registri da leggere
                uint8_t counter;
                for (counter=0;counter<register_count-1;counter++)
                {
                    data[counter] = I2C_Master_MasterReadByte(I2C_Master_ACK_DATA);
                }
                //Lettura del ultimo dato senza acknowledgement
                data[register_count-1]= I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
            }
        }
    }
    //Invio della condizione di stop
    I2C_Master_MasterSendStop();
    //Return error code
    return error ? ERROR : NO_ERROR;
  }
   
/* [] END OF FILE */
