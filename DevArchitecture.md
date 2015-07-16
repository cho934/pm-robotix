# Architecture #

Le schéma suivant décrit les classes principales mises en oeuvre pour la gestion du Robot.
https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchitecture_ClassesPrincipales.png?attredirects=0

Les classes `ActionManager` et `SensorManager` correspondent à des threads.

## SensorManager ##

La classe `SensorManager` assure la récupération des 'fronts' sur les capteurs associés aux moteurs.
A chaque fois qu'un front est détecté, la méthode `onXXXPulse()` de tous les listeners associés est appelée.

Dans la pratique, la classe `SpeedManager` implementera l'interface `SensorListener` pour être informé des déplacements du robot et en ajuster la vitesse.

De plus, comme la classe `SpeedManager` assure le suivi de la vitesse, il sera possible de repérer les arrêts imprévus du robot et de faire remonter cette information via un évenement `OnBlockedMovement` par exemple.

Note : l'ajout de nouveaux 'sensors' (détection de collision par exemple) pourra être réalisé de deux façons :
  * soit en intégrant celui-ci à la classe `SensorManager`, on limite le nombre de threads
  * soit en créant un nouveau Manager qui reprendrait les mêmes principes de fonctionnement, ce qui simplifie les classes.

## ActionManager ##

Afin de simplifier la gestion des threads et éviter d'avoir des threads concurrents dans l'exécution des actions du robot (se déplacer, se tourner, ...), une liste des actions à réaliser est exploitée par un thread unique dans la classe `ActionManager`.
Les actions sont alors traitées dans leur ordre d'apparition.

Note : Il manque deux éléments au système de gestion des actions :
  * La possibilité de gérer une priorité dans les actions, pour pouvoir arreter le robot par exemple.
  * La 'réflexion'. Les actions doivent être placés dans la liste en fonction des choix de l'[wiki:DevIntelligenceArtificielle Intelligence Artificielle].