Retour sur DevStart

# seeedStudio Rainbowduino #
## Présentation ##


## Matériel ##

**Rainbowduino LED driver platform - Atmega 328 (Rainbowduino V3.0)**

http://www.seeedstudio.com/depot/rainbowduino-led-driver-platform-atmega-328-p-371.html

**8x8 RGB LED Dot Matrix - Compatible with Rainbowduino**

http://www.seeedstudio.com/depot/60mm-square-88-led-matrix-super-bright-rgb-p-113.html?cPath=163_165


## Doc Rainbowduino V3.0 ##
http://www.seeedstudio.com/wiki/Rainbowduino_v3.0

doc d'une version précédante (plus détaillée): http://www.seeedstudio.com/wiki/Rainbowduino_LED_driver_platform_-_ATmega328


## Firmware ##
(code arduino à transférer sur le Rainbowduino)

http://www.seeedstudio.com/wiki/images/4/43/Rainbowduino_for_Arduino1.0.zip
voir README.txt:
```
Change the 33th line in Rainbowduino.h "#include <WProgram.h>" to "#include <Arduino.h>"
```

## IDE Arduino ##
Le rainbowduino est un arduino modifié, utiliser Arduino IDE pour transférer les programmes.

cf http://arduino.cc/en/Main/Software

Version utilisée: dernière version stable: 1.0.5 sous Win7 64bits

pour Rainbowduino V3, utiliser "Auduino DuoMilanove with Atmaga 328"

installer le driver Arduino (pont USB vers UART): http://arduino.cc/en/Guide/Windows#toc4


## Code ##
http://pm-robotix.googlecode.com/svn/trunk/trunk-arduino/src/RainbowduinoV3/

**Affichage de texte de façon autonome**

Le texte peut être mis à jour par I2C

http://pm-robotix.googlecode.com/svn/trunk/trunk-arduino/src/RainbowduinoV3/drawCharPmRobotix/drawCharPmRobotix.ino

**Exemple de master I2C (arduino)**

http://pm-robotix.googlecode.com/svn/trunk/trunk-arduino/src/RainbowduinoV3/i2cMaster/i2cMaster.ino

Retour sur DevStart