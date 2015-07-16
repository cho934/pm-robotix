# Automate #

Le schéma suivant décrit l'automate mis en place pour la gestion du robot.

https://sites.google.com/site/pmrobotix/home/wiki-img/DevAutomate_automate.png?attredirects=0

## Détail des états ##

### WaitForReboot ###
Le robot attend un appui sur le bouton de reboot.

**ok** : le bouton reboot est appuié et relaché.

### Initialize ###
Le robot s'initialise et vérifie son fonctionnement.

**ok** : Le robot est correctement initialisé.
**error** : Une erreur s'est produite ou a été détectée lors de l'initialisation.

### WaitForStart ###
Le robot attend l'activation du controle de start (goupille).

**ok** : le bouton start est actif (passage à 1).

**reboot** : le bouton reboot est appuié et relaché.

### DecisionMaker ###
Le robot se déplace vers le distributeur.

**s1** : La stratégie 1 est utilisée.

**s2** : La stratégie 1 est utilisée.

**s3** : La stratégie 1 est utilisée.

### Strategie1 ###
Exemple de stratégie simple.

**ok** : La stratégie est terminée, une nouvelle décision doit être prise.

### Strategie2 ###
Exemple de stratégie complexe.

**ok** : La stratégie est terminée, une nouvelle décision doit être prise.

**opponent** : Le robot adverse se trouve sur le chemin du robot.

### Wait ###
Le robot attend que le robot adverse ne soit plus devant lui.

**ok** : Le robot adverse n'est plus détecté devant le robot.

### Strategie3 ###
Exemple de stratégie finale.

**ok** : Le robot a fini ces taches.

## Détail de l'implémentation ##

Tous les états de l'automate doivent implémenter l'interface `IAutomateState` et fournir une implémentation de la méthode `execute` qui renvoie l'état suivant ou `NULL` si l'état final de l'automate est atteint.

Pour simplifier ce travail, la classe abstraite `AAutomateState` fournit une première implémentation permettant de gérer les transitions.

Enfin les stratégies manipulées par la classe `StateDecisionMaker` doivent dériver de `AStrategy` et implémenter la méthode `computeInterest` qui permet de choisir une stratégie.

https://sites.google.com/site/pmrobotix/home/wiki-img/DevAutomate_automate-impl.png?attredirects=0