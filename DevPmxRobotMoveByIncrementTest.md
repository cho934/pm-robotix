Retour sur DevAsservissement

# Objectif ''robotMoveByIncrementTest'' #
Le but de ce programme est de déterminer la relation entre l'application de la force moteur (Motorcode) et de la vitesse réel.
Les moteurs utilisés sont des Gearbox 919D, et donc très bon marché, mais pas forcément linéaire. C'est ce que l'on va vérifier.

# Paramètres nécessaires (verssion 2012) #
  * robotMoveByIncrementTest.cpp : Temporisation dans la boucle d'incrémentation
```
usleep(150000);
```
  * speedTracer.hpp  : (En milliseconde)
```
PERIOD_TIMER = 150;
```
  * speedTracer::computeApproximation() : Les 2 ordonnées de la droite moyenne (en mm/s) : speed1 et speed2
```
double speed1 = 50; //en mm/s
double speed2 = 100; //en mm/s
```
  * positionManager.hpp : (voir MecaDimGear)
```
static const double DISTANCE_ENTRAXE_MOTORWHEEL = 256.0; (en mm)

static const double DISTANCE_ENTRAXE_FREEWHEEL = 327.5; (en mm)

static const double DISTANCE_PER_MOTOR_PULSE = 0.8639; (en mm/pas)
        
static const double DISTANCE_PER_FREE_PULSE = 1.2828; (en mm/pas)

static const double ANGLE_PER_MOTOR_PULSE = 0.00373374757733; (en radiant)

static const double ANGLE_PER_FREE_PULSE = 0.003916998474; (en radiant)
```

# Les logs disponibles #
  * '''speed-tracer-file.csv''' - Log CSV des informations ''nbpulses | distance sur la periode(mm) | vitesse mesurée (mm/s) | code moteur demandée | consigne de vitesse (mm/s) | timeSpan | time Elapsed''
  * '''positionmanager.svg''' - Affiche l'odométrie du robot.

# Configuration de l'électronique #
Les cartes électroniques de motorisation demandent chacune une configuration du potentiomètre permettant de régler la vitesse maximum.

# Fonctionnement #
Pour cela on incrémente le code moteur sur chacun, et on logue les données dans un fichier csv : speed-tracer-file.csv
On détermine la droite y=Ax+B la plus proche pour chaque moteur.

Manipulation sur le fichier Excel :
  * Supprimer une des lignes de titre
  * Faire un tri sur la colonne B pour séparer les 2 moteurs
  * Remplacer les "." par des "," (conversion de langue FR/EN sous Excel) (CTRL F, puis onglet remplacer)
  * Sélectionner la colonne "Vitesse" puis insérer un graphique. On visualise la courbe des 2 moteurs.

Et voici le résultat avec les coefficients 2012 :
```
test::RobotMoveByIncrementTest INFO LEFT :  a:8.33333 b:0
test::RobotMoveByIncrementTest INFO RIGHT:  a:8.33333 b:0
```
Exemple de graphique
  * Avec les moteurs EMG30 (version 2012):
https://sites.google.com/site/pmrobotix/home/wiki-img/DevPmxRobotMoveByIncrementTest_graph_ax%2Bb%282012%29.png?attredirects=0

  * Avec les moteurs Gearbox (version 2011):
https://sites.google.com/site/pmrobotix/home/wiki-img/DevPmxRobotMoveByIncrementTest_graphe_ax%2Bb.png?attredirects=0



Retour sur DevAsservissement