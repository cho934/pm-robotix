# Architecture Entrée/Sortie (draft) #

https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchInOut_general.png?attredirects=0
(depracated)
[[BR](BR.md)][schéma général de la communication entre les composants principaux du robot]

## Infos sur la communication des entrées/sorties ##

Le programme doit communiquer avec soit:
  * le port parallèle (utilisation du pc portable IBM)
  * la carte APF9328 (utilisation des GPIOs configurées sur la carte devLightV2)
  * un système de simulation (affichage écran seulement)

**Comment communiquer ?**

## Représentation informatique ##

https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchInOut_RobotInOut-details.png?attredirects=0
[[BR](BR.md)][Détails de la classe `RobotInOut` et de ses méthodes]

## Environnement de test du robot ##

Séparation des flux d'entrée et de sortie grâce a deux interfaces : `RobotIn` (les accesseurs) et `RobotOut` (les modificateurs).

## La hiérarchie des classes ##

La classe **robotInOutFactory** implémente, suivant les cas d'utilisation, les classes suivantes :

> --> **robotInApf / robotOutApf** : Si carte APF9328 : test sur access("/etc/machine")

> --> **robotInOutParallelPort** : Si port // disponible : test sur ioperm(pmx::RobotInOutParallelPort::DATA\_ADDR, 3, 1)

> --> **robotInSimulate / robotOutSimulate** : Sinon


### Si le robot est présent ###

https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchInOut_ArchInOutProd.png?attredirects=0
[[BR](BR.md)][Schéma de classes pour la gestion des entrées/sorties "en production"]

Classe unique et instance unique : facilite l'implémentation "thread-safe" en particulier pour les lectures qui nécessitent une écriture préalable.

### Si le robot n'est pas présent ###

https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchInOut_ArchInOutTest.png?attredirects=0
[[BR](BR.md)][Schéma de classes pour la gestion des entrées/sorties "en test"]

Deux classes pour permettre la création d'une interface de simulation des données en entrée (`TestRobotIn`) via un thread spécifique (et une interface ?).

## Questions / Réponses ##

**Pourquoi avoir séparer les entrées des sorties ?**

Car si certaines des instances de la classe Action auront certainement besoin des deux (je vérifie une info, puis j'en écris une nouvelle), il est évident que la classe Listener ne sera pas dans ce cas : seules les entrées seront nécessaires.