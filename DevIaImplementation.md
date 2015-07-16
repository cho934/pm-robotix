Retour sur DevStart


# Implémentation de l'IA dans le robot #

## Les informations nécessaires ##
Informations du robot :
  * Temps restant / écoulé
  * Position du robot (X, Y, têta)
  * Remplissage du robot
Informations de l'adversaire (par robot) :
  * Position (X, Y)
  * Temps écoulé depuis la dernière détection
Informations sur les actions :
  * Liste des **''Strategy''**

## Les définitions des objets ##
### Une stratégie ###
Une stratégie décrit de manière générique un objectif pour le robot. Par exemple:
  * Récolter des éléments de jeu à un emplacement de la table
  * Déposer les éléments en stock dans la zone de dépose
  * ...

Lorsqu'une stratégie a été choisie et que l'état **''Strategy''** est activé, celui-ci va mettre en place une succession d'actions simples a effectuer pour atteindre l'objectif. Une fois cette liste mise en place, les actions sont envoyées une à une aux actionneurs.

Si un adversaire est détecté, une interruption arrive. L'état **''Strategy''** détermine alors si l'adversaire se trouve sur la trajectoire du robot. Dans ce cas, la stratégie est compromise, donc le robot s'arrête et l'état se termine prématurément. Une fois cet état terminé, l'état **''DecisionMaker''** est appelé pour prendre une nouvelle décision.

### Une action simple ###
Une action simple est une action compréhensible par les actionneurs.

Actions génériques :
  * Rotation du robot (angle)
  * Déplacement (distance)

Actions spécifiques :

Dépendantes du règlement et des actions définies pour le robot. Par exemple :
  * Prendre un élément de jeu
  * Poser un élément de jeu
  * ...




Retour sur DevStart