Cette page est le point d'entrée pour le développement du programme.

Voici toutes les explications sur le "déjà fait". Tout ce qui a été créé doit être utile.

Reprenons la maxime de Lavoisier « **Rien ne se perd, rien ne se crée, tout se transforme** ».

# 1. Environnements de développement #
## 1.1 Généralités ##
  * DevConfig - L'environnement de développement
  * DevStandards - Les standards de codage
  * DevHelp - L'aide sur les développements
  * DevEnvDebug - Comment déboguer

## 1.2 Environnement C++ ##
  * DevEnvDistributionLinux] - Liste des distributions et des environnements de développements utilisés
  * DevEnvEclipse - Environnement de développement Eclipse / C++ / SVN
  * DevEnvNetbeans - (Deprecated) Environnement de développement Netbeans / C++ / SVN
  * DevEnvDocumentation - Documentation du code, How To...
  * DevEnvFormatting - Formatage du code

### 1.2.1 C++ pour Armadeus APF9328 ###
  * DevEnvArmadeus - Liste des installations et de configurations à mettre en place pour utiliser la carte Armadeus APF9328
**Les 4 binaries générés à la compilation sont :**
  * DEV\_TEST : tests unitaires software non liés aux éléments du robot
  * UNIT\_TEST : tests unitaires des éléments du robot (utilise les fichiers de configuration **unit-test.conf.txt** et loggerInitialize.cpp)
  * ROBOT\_TEST : tests unitaires des éléments du robot via les objets Robot.cpp (utilise les fichiers de configuration **robot-test.conf.txt** et loggerInitialize.cpp)
  * PMX : Programme principal pour l'homologation et les matches(utilise les fichiers de configuration **pmx.conf.txt** et loggerInitialize.cpp)

### 1.2.2 C++ pour Mindstorm EV3dev ###

  * DevEv3devInstall - Install ev3dev image file : ev3dev-jessie

## 1.3 Environnement C pour Arduino ##
  * ArduinoEnv

## 1.4 Environnement C pour CMUCAM3 ##
  * DevEnvEeepc - Environnement natif avec MINT8 utilisé pour la CMUCAM3


# 2. Développement C++ pour nos robots #
## Section principale ##
  * DevArchitecture - La description générale de l'architecture
  * DevArchLogger - La description de l'architecture du système de trace
  * DevAutomate - Automate mis en place pour la gestion du robot (première intelligence du robot)
  * DevArchInOut - Réflexion sur la communication entre les éléments du robot
  * DevAsservissement - Asservissement en vitesse / PID / trajectoire en position
  * DevChronometer - La description de l'utilisation d'un Timer et d'un Chronometer
  * DevCppThread - Designing a Thread Class in C++

## Section communication ##
  * DevArmadeusGpio - Tests et bases de développement sur les GPIO de la carte APF9328
  * DevArmadeusI2C - Bases sur la communication I2C de la carte AFF9328

## Section détection ##
  * DevCmucam
  * DevIrRangeSensors - Bases de développement du capteur de distance GP2D12

## Section motorisation ##
  * DevServoMotor - Bases de développement d'un servomoteur
  * DevStepperMotor - Bases de développement des moteurs pas à pas

# 3. Développement Arduino #
  * ArduinoRotaryEncoderWithLs7366
  * ArduinoColorSensor
  * ArduinoDynamixelAx12
  * ArduinoRotaryEncoderRe16
  * ArduinoUltrasonSfr05
  * ArduinoStepperEasyDriver
  * ArduinoStepperEasyStep1000
  * SeeedstudioRainbowduinoLedmatrix

# 4. Section IA #
## IA ##
  * DevArchIntelligence - Réflexion sur l'intelligence artificielle du robot
  * DevEnvSimuJava - Environnement nécessaire pour la simulation du comportement du robot
  * DevSimuIaConcept - Concept utilisé pour l'intelligence artificielle
  * DevIaImplementation - Description de l'implémentation de l'IA dans le robot
  * [2012 - Scénario sur Treasure Island](2012.md) - Scénario et configuration IA pour la coupe 2012
  * [2011 - Scénario sur Chess'Up](2011.md) - Scénario et liste des états pour la coupe 2011
  * [2009 - Scénario sur les temples d'Atlantis](2009.md) - Scénario principal pour l'année 2009