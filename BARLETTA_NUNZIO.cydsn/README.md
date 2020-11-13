# ASSIGNMENT 5

## Richieste
Le richieste per tale assignment sono esplicitate nel README generale.


## Schematico
Vi sono presenti i seguenti componenti:
- Pagina 1:
	- I2C_Master: componente del PSoC che nella comunicazione I2C è il master rispetto alla periferica LIS3DH;
	- EEPROM: componente del PSoC relativo alla memoria dati non volatile;
	- Debouncer: componente del PSoC per gestire l'antirimbalzo dello switch/pulsante.
- Pagina 2:
	- UART: componente interno al PSoC per comunicazione con terminale.
Tutti i dettagli per i componenti sono presenti nel Top Design
	

## Port/Pin
Si hanno le seguenti porte con i corrispettivi pin:
- P2[2]: porta relativa allo switch/pulsante interno al PSoC e corrispondente al pin 64;
- P12[0]: porta relativa al serial clock e corrispondente al pin 38;
- P12[1]: porta relativa al serial data e corrispondente al pin 39;
- P12[6]: port relativa al Rx del PSoC e corrispondente al pin 20;
- P12[7]: port relativa al Rx del PSoC e corrispondente al pin 21.


## Firmware
Nei file di "Header" e di "Source" vi sono esplicitati già i dettagli reativi alle righe di codice presenti.


## Bridge control panel confing
Nei file di "Config.iic" e "Confing.ini" vi sono esplicitati già i dettagli reativi ai comandi presenti.
