Retour sur DevStart

# Couche supérieure : Machine d'état #
Le principe global de l'intelligence du robot est une machine d'état.

http://fr.wikipedia.org/wiki/Machine_d%27%C3%A9tat

Le principe est le même que celui mit en place initialement (voir DevAutomate).

La principale modification se trouve après le lancement du robot, en parallèle de l'état 90 secondes.
<

&lt;TODO&gt;

> Faire schéma

Le nouveau principe de prise de décision est une machine d'états composée en étoile.

L'état central est appelé **''DecisionMaker''**. Il est rattaché à plusieurs états **''Strategy''**, qui décrivent tous une stratégie à adopter.
Par exemple:
  * Déposer le contenu du robot dans la zone de dépôt 1
  * Aller collecter des éléments de jeu au centre de la table
  * ...

Le **''DecisionMaker''** est le premier état appelé. Il va parcourir tous les états **''Strategy''** disponibles, et leur demander leur intérêt. C'est celui ayant le plus gros intérêt qui sera appelé. Une fois son travail terminé, le **''DecisionMaker''** sera à nouveau appelé, etc...

# Calcul d'intérêt #

Chaque état **''Strategy ''**, lorsque son intérêt lui sera demandé, va parcourir les paramètres du robot, et renvoyer un intérêt calculé sur 100 points.
La méthode de calcul de l'intérêt va varier selon les états, mais le principe reste le même:
  * L'intérêt doit varier entre 0 et 100, 0 correspondant à un intérêt nul, 100 à un intérêt maximal.
  * Le calcul doit se baser sur un fichier de configuration externe, afin de pouvoir modifier la stratégie sans avoir à recompiler le programme.

## Simulateur ##

L'objectif du simulateur est de voir si l'étoile de prise de décision est correctement configurée.

L'idée, sur les années à venir, est de mettre en place un système de calcul amélioré des paramètres des calcul d'intérêt. Ça évitera d'avoir a tâtonner pour estimer les paramètres, mais aussi de tester des configurations auxquelles nous ne penserions pas spontanément.

# Construction de la séquence l'actions #

A partir de la décision D choisie, l'IA doit déterminer la séquence d'actions

Retour sur DevStart