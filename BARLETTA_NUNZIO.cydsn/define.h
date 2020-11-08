
#ifndef __DEFINE_H
  #define __DEFINE_H
    
  //define relative agli indirrizzi 
  #define LIS3DH_DEVICE_ADDRESS 0x18 //001100xb x è arbitrario noi abbiamo messso 0

  #define LIS3DH_CTRL_REG1_ADDRESS  0x20 
  #define LIS3DH_CTRL_REG4_ADDRESS  0x23
  #define LIS3DH_STATUS_REG_ADDRESS 0x27
  #define LIS3DH_OUT_X_L_ADDRESS    0x28
//  #define LIS3DH_OUT_X_H_ADDRESS 0x29 per debugging
//  #define LIS3DH_OUT_Y_L_ADDRESS 0x2A
//  #define LIS3DH_OUT_Y_H_ADDRESS 0x2B
//  #define LIS3DH_OUT_Z_L_ADDRESS 0x2C
//  #define LIS3DH_OUT_Z_H_ADDRESS 0x2D

  #define LIS3DH_CTRL_REG1_L 0b0111 // ora metti solo i bit meno significativi 0x07 settare gli ODR nel MSB 
  #define LIS3DH_CTRL_REG4_L 0b1000 // ora metti solo i bit meno significativi 0x18, cambiare le fsh e le sensitivuta di conseguenza

  #define LIS3DH_CTRL_REG4_FS 0b01 //in relazione alla sentività ed alla resolution mode
  #define LIS3DH_SENSITIVITY  2.0 //mg/digit FS: 01 per high resolution mode
  #define LIS3DH_CTRL_REG4_BLE_BDU 0b00
  #define LIS3DH_CTRL_REG4_COMPLETE LIS3DH_CTRL_REG4_L | ((LIS3DH_CTRL_REG4_FS) | (LIS3DH_CTRL_REG4_BLE_BDU<<2))<<4

  #define ACC_GRAVITY 9.81
  #define CONVERSION LIS3DH_SENSITIVITY*0.001*ACC_GRAVITY

  #define EEPROM_CELL_ADDRESS 0x0000
  
  // Define usate per settare il range delle frequenze di campionamento del LIS3DH da usare
  // NOTA: i valori fanno riferimento alla colonna Index della TABELLA in "InterruptRoutines.h"
  #define MAX_FREQUENCY_RATE 6
  #define MIN_FREQUENCY_RATE 1
      
#endif
    
/* [] END OF FILE */
