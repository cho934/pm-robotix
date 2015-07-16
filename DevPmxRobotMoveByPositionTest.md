Retour sur DevAsservissement

# 1. Objectif ''devPmxRobotMoveByPositionTest'' #
Le but de ce programme est de faire avancer le robot sur une position X,Y donnée(avec PID configuré).

# 2. Usage #
```
USAGE: PMX_TEST [NumProg] [targetX] [targetY]
```

# 3. Paramètres nécessaires pour ce programme #
  * Fichier de configuration (valeurs PID)
TODO
  * base.hpp :
```
static const double EPSILON = 6.0; //Distance du point d'arret à partir duquel on peut s'arrêter en mm.
```
```
static const double GRADIENT = 0.4; //Multiplicateur de la courbe de vitesse.
```
```
static const double GRADIENT_ACC = -1.0; //Multiplicateur de la courbe de vitesse.
```
```
static const double SPEED_MIN = 45.0; //Vitesse minimum appliquée au robot.
```
```
static const double SPEED_MAX = 250.0; //Vitesse maximum appliquée au robot.
```

# 4. Les logs disponibles #
  * positionmanager.svg     - Affiche l'odométrie du robot.
  * positionmanager.log.csv - Affiche les informations de correction de position (du speedManager) : ''motor	orderSpeed théorique | vd | vx | vy | va | diffAngles | mode asserv | phase asserv | pourcent pos | speedByPos | speedByPID''

# 5. Fonctionnement #

La fonction `movexy` active automatiquement la correction de position [`positionCorrectionEnabled(true);`]. Cette correction permet de calculer le vecteur jusqu'au point destination, et de corriger en conséquence la vitesse sur chaque moteur.

Celle-ci s'effectue juste avant le calcul du PID dans le `speedManager.cpp`.




Retour sur DevAsservissement