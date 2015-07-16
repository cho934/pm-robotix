Retour sur ElecStart

# Image de la carte APF9328 avec la carte devLight V2.1 #
https://sites.google.com/site/pmrobotix/home/wiki-img/ElecArmadeus_APF9328.jpg?attredirects=0

# 1. La carte APF9328 de chez [Armadeus Systems](http://www.armadeus.com) #

| **Processor** | **ADC** |
|:--------------|:--------|
|    MC9328L(i.MXL) ARM920T 200MHz (Freescale)| 8 channels 10bits 10MHz with internal fifo (can be removed on demand)|
| **RAM**       | **FPGA** |
|    8/16 Mo 32bits @ 100MHz|   Xilinx Spartan3 with 200k gates (50k FPGA or 400k FPGA optional)|
| **Flash**     | **Power supply** |
|    4/8/16 Mo 16bits @ 100MHz| +3.3V supply 5%. typical power consumption: 300mW (without the FPGA)|
| **Peripherals** |    Two power saving modes|
|    1 x RS232 (RX/TX)| **Environment** |
|    1 x RS232 TTL levels (RX, TX, CTS, RTS)| Cooling : None for temperature below 60°C**.**|
|    1 x I2C    | Operating temperature range: 0..60°C (without cooling)|
|    2 x SPI    | Storage temperature range: -10..70°C |
|    1 x SSI (High speed synchronous serial port)| Humidity 5-90%|
|    1 x USB 1.1 slave only with level converter| **Mechanical Overview** |
|    1 x Ethernet 10/100 Mbits (no RJ45 connector)| Dimensions: 71mm (2.8") x 39mm (1.55")|
|    1 x SD/MMC |
|    1 x RTC (no battery)|
|    1 x PWM 16bits resolution|
|    2 x Timer 32 bits with input capture/output compare|
|    1 x Watchdog. Adjustable timeout between 0.5s and 64s (0.5s step)|
|    LCD controller up to 640x512 (64K colors)|
|    CSI (CMOS sensor interface)|
|    97 total I/O pins multiplexed with most dedicated functions for pin efficiency (GPIO)|
|    JTAG (Debug (ICE) and test)|
| **Ethernet**  |
|    10/100Mbits (can be removed on demand)|
| **DAC**       |
|    2 channels 10bits 400kHz (can be removed on demand)|

L'association qui en découle [Armadeus Project Wiki](http://www.armadeus.org)

# 2. Les spécifications #

Le kernel actuel (uname -a) : Linux armadeus Linux-2.6.29.6

Dernière version du kernel installé et configuration : voir DevArmadeusInstallToolchain

  * [DataSheet DevLightv2](http://www.armadeus.com/_downloads/apf9328DevLight/)
  * [DataSheet APF9328](http://www.armadeus.com/_downloads/apf9328/documentation/dataSheet_APF9328.pdf)
  * [System Processor MC9328MX1 DataSheet: Technical Data](http://www.freescale.com/files/32bit/doc/data_sheet/MC9328MX1.pdf)
  * [System Processor MC9328MX1 DataSheet: Reference Manual](http://www.freescale.com/files/32bit/doc/ref_manual/MC9328MX1RM.pdf?fpsp=1&WT_TYPE=Reference%20Manuals&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation)

## 2.1. L'alimentation dans le bons sens ##

  * For devLight V2 : Use +5Vdc to +7Vdc input voltage, [Pour ne pas se tromper...](http://www.armadeus.com/wiki/index.php?title=Development_boards_power_supply)
  * For all development boards: **+ is in the middle of the connector, - on the side**

## 2.2. GPIO Pin configuration ##

  * Résumé de la configuration devLightV2 / cartes de multiplexage/démultiplexage :
|Pin (devlightv2)|Port (GPIO)|N°GPIO|I/O|Réf carte|Description|
|:---------------|:----------|:-----|:--|:--------|:----------|
|LD0\_B0         |D          |PD15  |O  |MA       |Adresse du DM/M visé.|
|LD1\_B1         |D          |PD16  |O  |MB       |Adresse du DM/M visé.|
|LD2\_B2         |D          |PD17  |O  |MC       |Adresse du DM/M visé.|
|LD3\_B3         |D          |PD18  |I  |DE       |Donnée d’entrée à lire.|
|LD4\_B4         |D          |PD19  |I  |IMPD     |Impulsion du moteur droit.|
|LD5\_G0         |D          |PD20  |O  |@A       |Adresse du pin du DM/M sélectionné.|
|LD6\_G1         |D          |PD21  |O  |@B       |Adresse du pin du DM/M sélectionné.|
|LD7\_G2         |D          |PD22  |O  |@C       |Adresse du pin du DM/M sélectionné.|
|LD8\_G3         |D          |PD23  |O  |AD       |Donnée à appliquer sur le pin sélectionné.|
|LD9\_G4         |D          |PD24  |I  |IMPG     |Impulsion du moteur gauche.|
|LD10\_G5        |D          |PD25  |I  |IMPGD    |Impulsion déphasée associée au pin IMPG permettant de connaitre le sens du moteur.|
|LD11\_R0        |D          |PD26  |I  |IMPDD    |Impulsion déphasée associée au pin IMPD permettant de connaitre le sens du moteur.|
|LD12\_R1        |D          |PD27  |O  |E1       |Activation de la carte rouge des DM (démultiplexors) => sorties.|
|LD13\_R2        |D          |PD28  |O  |E2       |Activation de la carte blanche des M (Multiplexors) => entrées.|
|LD14\_R3        |D          |PD29  |I  |IMPGD    | = IMPGD   |
|LD15\_R4        |D          |PD30  |I  |IMPDD    | = IMPDD   |

  * Connecteur associé sur devLightV2 :

[**Numéro\_schematic**] (code\_armadeus) (code\_multiplexage)  [Entrée/Sortie]

| |**30** REV/SPI2/SCLK O|
|:|:---------------------|
|**27** CONTRAST O   |**28** SPL\_SPR/SPI2\_MOSI O|
|**25** OE\_ACD O      |**26** PS/SPI2\_MISO O|
|**23** HSYNC O       |**24** CLS\_SPI2\_SSN O|
|**21** VSYNC O        |**22** **GND**        |
|**19** **GND**          |**20** LD0\_B0 MA O   |
|**17** LD1\_B1 MB O  |**18** LD2\_B2 MC O   |
|**15** LD3\_B3 DE I  |**16** LD4\_B4 IMPD I |
|**13** LD5\_G0 @A O  |**14** LD6\_G1 @B O   |
|**11** LD7\_G2 @C O  |**12** LD8\_G3 AD O   |
|**9**  LD9\_G4 IMPG I|**10** LD10\_G5 IMPGD I|
|**7**  LD11\_R0 IMPDD I|**8** LD12\_R1 E1 O   |
|**5**  LD13\_R2 E2 O |**6** LD14\_R3 Not connected|
|**3**  **GND**          |**4** LD15\_R4 Not connected|
|**1**  **VCC(3,3V)**    |**2** ''VCC(3,3V)''   |

[<< sens / vue de dessus carte de connexion / vue de dessous devLightV2]

  * Connecteur vers la carte de multiplexage

[**Numéro\_schematic**] (code\_multiplexage)  [Entrée/Sortie]
|**1**|Not connected|**2**| |MC|O|
|:----|:------------|:----|:|:-|:|
|**3**|IMPG         |I    |**4**|MB|O|
|**5**|IMPD         |I    |**6**|MA|O|
|**7**|GND          |**8**| |AD|O |
|**9**|IMPDD        |I    |**10**|@C|O|
|**11**|IMPGD        |I    |**12**|@B|O|
|**13**|DE           |I    |**14**|@A|O|
|**15**|E2           |O    |**16**|E1|O|
[>> sens / vue de dessus carte de connexion]

# La communication 5V <=> 3,3V #

  * Pour les entrées **sens 5v => 3,3v**
Utilisation du composant [TPS7333QP : Régulateur 3,3v, 0,5A](http://www.datasheetcatalog.org/datasheet2/1/03pe5pihyt1rj55dhsuxk1et037y.pdf).

  * Pour les sorties **sens 3,3v => 5v**
Utilisation du composant [SN74AHC244N](http://www.datasheetcatalog.org/datasheet2/e/0lzrsr4j7opqkakja3teqcgjyhwy.pdf): Octal Buffer Driver

= Config Elec de la DevLightV2
  * Pour les DAC : DAC\_REF: corresponds to REF (pin 6) on Max5821. It's the reference voltage (max value that will be achieved by outputs). This input should be connected to a voltage reference between 0 and 3,3V.
    * Connect DAC\_REF to 3,3V

  * Pour les ADC : Connect #EOC pin (End Of Conversion) and #CNVST pin (conversion start) to two i.MXL GPIOs. By default the driver is using:
    * PA13 (CSI\_HSYNC) for #EOC
    * and PA14 (CSI\_PIXCLK) for #CNVST

# La "TODO list" électronique #

  * (Fait) Utiliser les ADC pour les GP2 => a documenter
  * (Fait) Utiliser l'i2c pour commander les nouveaux moteurs => a documenter
  * (Fait) Utiliser le FPGA pour utiliser les servos moteurs => a documenter
  * (TODO) Programmer 2 compteurs dans le FPGA pour les codeurs indépendant




Retour sur ElecStart