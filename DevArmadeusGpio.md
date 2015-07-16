Retour sur DevStart

# Mise en place des GPIO #

## Les bases ##

Voir le [GPIO Driver](http://www.armadeus.com/wiki/index.php?title=Gpio) et son utilisation sur Armadeus.

**Le shell :**

Voir le programme sur le svn Armadeus :
[GIT:Les tests sh](http://armadeus.git.sourceforge.net/git/gitweb.cgi?p=armadeus/armadeus;a=tree;f=target/test;h=2da529e161605dece6cb5728c867e3e04485eda6;hb=HEAD)

Liste des fichiers nécessaires pour le test de "blink\_led" sur PD31 :
  * test\_env.sh
  * test\_helpers.sh
  * test\_gpio.sh

**Le programme en C correspondant :**

Voir le programme [GIT:blink\_led.c](http://armadeus.git.sourceforge.net/git/gitweb.cgi?p=armadeus/armadeus;a=tree;f=target/demos/gpio;h=00f7dab496c87dc72fba7d7bec8a04ddafb0b0da;hb=HEAD) et la gestion des interruptions en "lecture bloquante"[GIT:interrupt\_linux\_us.c](http://armadeus.git.sourceforge.net/git/gitweb.cgi?p=armadeus/armadeus;a=tree;f=target/demos/real_time/interrupt/linux;h=b6e23565ef120804ca46dca3852acd5f666f453e;hb=HEAD)

**Le C++ :**

Les programmes de tests mis en place :
  * /robot-test/ApfOutTest.cpp//Test de clignotement d'un pad GPIO sur DevLightV2.
  * /robot-test/ApfOutTest.hpp
  * /robot-test/ApfInTest.cpp//Test d'interruption en lecture bloquante d'un pad GPIO sur DevLightV2.
  * /robot-test/ApfInTest.hpp

## La config PMX ##

**Les pads à utiliser sur la devLightV2**
Nous utilisons dans un premier temps les pads utilisés pour le LCD pour la connexion aux cartes de multiplexage :
|**DevlightV2**|**Primary Signal**|**GPIO Port**|**GPIO**|
|:-------------|:-----------------|:------------|:-------|
|REV/SPI2/SCLK |REV               |D            |PD7     |
|CLS/SPI2\_SSn |CLS               |D            |PD8     |
|PS/SPI2\_MISO |PS                |D            |PD9     |
|SPL\_SPR/SPI2\_MOSI|SPL\_SPR          |D            |PD10    |
|CONTRAST      |CONTRAST          |D            |PD11    |
|OE\_ACD       |ACD/OE            |D            |PD12    |
|HSYNC         |LP/HSYNC          |D            |PD13    |
|VSYNC         |FLM/VSYNC         |D            |PD14    |

|LD0\_B0|LD0|D|PD15|
|:------|:--|:|:---|
|LD1\_B1|LD1|D|PD16|
|LD2\_B2|LD2|D|PD17|
|LD3\_B3|LD3|D|PD18|
|LD4\_B4|LD4|D|PD19|
|LD5\_G0|LD5|D|PD20|
|LD6\_G1|LD6|D|PD21|
|LD7\_G2|LD7|D|PD22|
|LD8\_G3|LD8|D|PD23|
|LD9\_G4|LD9|D|PD24|
|LD10\_G5|LD10|D|PD25|
|LD11\_R0|LD11|D|PD26|
|LD12\_R1|LD12|D|PD27|
|LD13\_R2|LD13|D|PD28|

Autres pads à utiliser :
|**DevlightV2**|**Primary Signal**|**GPIO Port**|**GPIO**|
|:-------------|:-----------------|:------------|:-------|
|LD14\_R3      |LD14              |D            |PD29    |
|LD15\_R4      |LD15              |D            |PD30    |
|TOUT2         |TMR2OUT           |D            |PD31    |
|CSI\_D0       |CSI\_D0           |A            |PA4     |
|CSI\_D1       |CSI\_D1           |A            |PA5     |
|CSI\_D2       |CSI\_D2           |A            |PA6     |
|CSI\_D3       |CSI\_D3           |A            |PA7     |
|CSI\_D4       |CSI\_D4           |A            |PA8     |
|CSI\_D5       |CSI\_D5           |A            |PA9     |

**La configuration GPIO nécessaire**

Connexion carte de multiplexage (sur le port D, pin 28...15):
|**GPIO**|PD28|PD27|PD26|PD25|PD24|PD23|PD22|PD21|PD20|PD19|PD18|PD17|PD16|PD15|
|:-------|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|:---|
|**Réf** |E2  |E1  |IMPDD|IMPGD|IMPG|AD  |@C  |@B  |@A  |IMPD|DE  |MC  |MB  |MA  |
|**MODE**|O   |O   |I   |I   |I   |O   |O   |O   |O   |I   |I   |O   |O   |O   |
Connexion aux leds d'information (sur le port D, pin 14...7):
|**GPIO**|PD14|PD13|PD12|PD11|PD10|PD9 |PD8 |PD7 |
|**Réf** |LED8|LED7|LED6|LED5|LED4|LED3|LED2|LED1|
|**MODE**|O   |O   |O   |O   |O   |O   |O   |O   |

  * GPIORDMODE (1 = GPIO)
0x3FFF << 15 //3FFF ==> 0011 1111 1111 1111 ---- ---- ---- ----

  * GPIORDDIRECTION (1 = output, 0 = input)
0x31E7 << 15 //31E7 ==> 0011 0001 1110 0111 ---- ---- ---- ----

**Configuration au démarrage : /etc/init.d/S60loadgpio
voir le fichier ici : DevArmadeusInstallToolchain**


Retour sur DevStart