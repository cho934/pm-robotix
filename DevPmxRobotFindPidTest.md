Retour sur DevAsservissement

# 1. Objectif ''devPmxRobotFindPidTest'' #
Le but de ce programme est de faire avancer le robot et de déterminer déterminer les coefficients des PID (moteurs gauche et droit).

# 2. Usage #
```
USAGE: PMX_TEST  [NumProg] [tickG=1...5] [tickD=1...5] [Tps(sec)] [PID_G] [PID_D] [1=FORWARD 2=BACK]
```

Nombre de tick maximum avec les moteurs EMG30 : 155 ticks par période de 150ms.

# 3. Paramètres nécessaires pour ce programme #

  * positionManager.hpp  :
```
        static const double DISTANCE_ENTRAXE_MOTORWHEEL = 256.0; (en mm)

        static const double DISTANCE_ENTRAXE_FREEWHEEL = 327.5; (en mm)

        static const double DISTANCE_PER_MOTOR_PULSE = 0.8639; (en mm/pas)
        
        static const double DISTANCE_PER_FREE_PULSE = 1.2828; (en mm/pas)

        static const double ANGLE_PER_MOTOR_PULSE = 0.00373374757733; (en radiant)

        static const double ANGLE_PER_FREE_PULSE = 0.003916998474; (en radiant)
```

  * speedManagerFusion.hpp :
```
static const int PERIOD_PID = 150; 
```

# Les logs disponibles #
  * positionmanager.svg     - Affiche l'odométrie du robot.
  * positionmanager.log.csv - Log PID et correction en position (motor | orderSpeed théorique | vd | vx | vy | va | diffAngles | mode asserv | phase asserv | pourcent pos | speedByPos | speedCorrectionByPID | speed | correction | error | distance totale)


# 4. Fonctionnement #

## Rouler simplement ##
  * Appliquer les coefficients PID 1 0 0 sur chaque moteur. Le robot avancera sans correction pendant le temps indiqué.
  * Avec un [`./my recupcsvhost`] on recupère les fichier **.csv et**.svg. Le fichier ''positionmanager.svg'' montre le déplacement du robot.

## Déterminer les paramètres PID ##

### Approche de Ziegler-Nichols ###
  * '''Principe''' : Amener le système dans un état d'oscillations puis en déduire les valeurs des coefficients.
  * '''Protocole''' : Fixer Ki et Kd à 0 puis augmenter Kp jusqu'à obtenir des oscillations périodiques
stables, c'est à dire non amorties et non ampliées.

On note : '''Kp''' = Valeur de P lors des oscillations , '''Tc''' = Période des oscillations

Alors il faut choisir le mode P / PI / PID, les calculs sont alors les suivants :
  * P
    * P = 0.5 Kp

  * PI
    * P = 0.45 Kp
    * I = 1.2 / Tc

  * PID
    * P = 0.6 Kp
    * I = 2 / Tc
    * D = P **Tc / 8**

### Paramètres trouvés ###

LEFT :
  * Kp = 1.7
  * Tc = 0.45 (en s)

RIGHT:
  * Kp = 1.7
  * Tc = 0.45 (en s)

Après calcul :

  * P = 0.85

  * P = 0.765
  * I = 2.6666

  * P = 1.02
  * I = 4.4444
  * D = 1.7


Après différents essais, il s'avère que les paramètres théoriques ne donnent pas les meilleurs résultats. Nous les avons modifiés avec ce qui suit :


Retour sur DevAsservissement
