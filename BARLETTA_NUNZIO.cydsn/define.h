
#ifndef __DEFINE_H
  #define __DEFINE_H
    
  //Define relativa all'indirizzo del dispositivo LIS3DH
  #define LIS3DH_DEVICE_ADDRESS 0x18 /*0b001100x; x è un bit arbitrario che dipende dal pin SDO 
                                      e nel progetto in questione tale pin è connesso a GND e 
                                      quindi x=0 --> 0b00011000 --> 0x18*/
    
  //Define relative agli indirizzi dei registri di LIS3DH usati per tale applicazione
  #define LIS3DH_CTRL_REG1_ADDRESS  0x20 
  #define LIS3DH_CTRL_REG4_ADDRESS  0x23
  #define LIS3DH_STATUS_REG_ADDRESS 0x27
  #define LIS3DH_OUT_X_L_ADDRESS    0x28 
  /*NOTA:dato il fatto che i registri relativi alla lettura dei valori delle accelerazioni lungo
    gli assi x, y e z, sono uno di seguito all'altro (come elencato sotto), è possibile definire
    ed usare la seguente funzione "ErrorCode I2C_Peripheral_ReadRegisterMulti(...)" (definita in 
    "I2CFunctions.h" ed esplicitata in "I2CFunctions.c") per leggere quelli desiderati, settando 
    correttamente la define "N_ACC_AXIS" --> "COUNT_OUT_REG".
    Per applicazioni differenti da quella richiesta sono stati lasciati gli address dei registri:
    #define LIS3DH_OUT_X_H_ADDRESS 0x29
    #define LIS3DH_OUT_Y_L_ADDRESS 0x2A
    #define LIS3DH_OUT_Y_H_ADDRESS 0x2B
    #define LIS3DH_OUT_Z_L_ADDRESS 0x2C
    #define LIS3DH_OUT_Z_H_ADDRESS 0x2D*/
  
  //Define per definire il numero di assi su cui leggere i valori di accelerazione
  #define N_ACC_AXIS 3
  
  /*Define per settare il numero di registri LIS3DH_OUT da leggere sequenzialmente con la funzione 
  sopra citata*/
  #define COUNT_OUT_REG 2*N_ACC_AXIS 
  
  //Define per settare i 4 bit meno significativi del control register 1
  #define LIS3DH_CTRL_REG1_L 0x07 /*0x07 --> 0b0111; i bit settati a 1 sono quelli relativi alla
                                attivazione degli assi x,y e z per la lettura delle accelerazioni,
                                mentre il bit lasciato a zero è il bit LPen, settato in tale modo
                                per avere la modalità ad alta o normale risoluzione*/
    
  //Define per settare i 4 bit meno significativi del control register 4 
  #define LIS3DH_CTRL_REG4_L 0x08 /*0x08 --> 0b1000; l'unico bit settato ad 1 è quello relativo
                                   alla impostazione della risoluzione del LIS3DH ad HIGH*/
    
  //Define per settare il full scale e la sensitività dei dati in uscita dal LIS3DH
  #define LIS3DH_CTRL_REG4_FS 0b00 //FS[1:0] = 0b00 --> full scale range: ±2.0g
  /*NOTA:
    FS bit set to 00 --> ±2.0  g
    FS bit set to 01 --> ±4.0  g
    FS bit set to 10 --> ±8.0  g
    FS bit set to 11 --> ±16.0 g */
  #define LIS3DH_SENSITIVITY  1.0 //sensitività [mg/digit]
  /*NOTA: la sensitività è in relazione al full scale range ed alla risoluzione adottata, pertanto
    il valore è stato preso dalla tabella presente nel datasheet a pag.10:
    "Table 4. Mechanical characteristics"; nella stessa tabella è indicata anche la NOTA sul FS*/
  
  //Define relative al completamento del control register 4
  #define LIS3DH_CTRL_REG4_BLE_BDU 0b00 //[BDU:BLE]
  #define LIS3DH_CTRL_REG4_H (LIS3DH_CTRL_REG4_FS) | (LIS3DH_CTRL_REG4_BLE_BDU<<2)
  #define LIS3DH_CTRL_REG4_COMPLETE LIS3DH_CTRL_REG4_L | (LIS3DH_CTRL_REG4_H<<4)
    
  /*Define della maschera usata per il controllo dello status register sulla disponibilità di 
  nuovi dati, relativi alle accelerazioni, da parte del LIS3DH*/
  #define LIS3DH_STATUS_REG_MASK 0x08 //0x08 --> 0b00001000; l'1 è in corrispondenza di ZYXDA
  
  //Define per la conversione da digit ad accelerazione
  #define ACC_GRAVITY 9.81
  #define CONVERSION LIS3DH_SENSITIVITY*0.001*ACC_GRAVITY

  /*Define dell'indirizzo cella di memoria EEPROM in cui viene salvata la variabile 
  "frequency_rate" definita in "InterruptRoutines.h" */
  #define EEPROM_CELL_ADDRESS 0x0000
 
  //Define per settare il range delle frequenze di campionamento del LIS3DH da impiegare
  #define MAX_FREQUENCY_RATE 6
  #define MIN_FREQUENCY_RATE 1
  //NOTA: i valori fanno riferimento alla colonna Index della TABELLA in "InterruptRoutines.h"
  
  //Define del header, del tail e della dimensione del buffer di trasmissione
  #define HEADER 0xA0
  #define TAIL   0xC0
  #define BUFFER_SIZE 14
    
#endif
    
/* [] END OF FILE */
