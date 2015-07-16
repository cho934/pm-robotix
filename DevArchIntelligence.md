# Intelligence Artificielle #

## Premières réflexions ##

Je saute l'étape mathématique et si ça vous interesse vraiment, voici deux liens :
> - niveau 0 'logique des propositions' ... http://fr.wikipedia.org/wiki/Calcul_des_propositions.
> - niveau 1 'logique de premier ordre' et donc à une vraie intelligence artificielle.

### Comment réfléchi-t-on ? ###

Si je sais les points suivants :
> - ma voiture est une Golf ;
> - toutes les golf sont noires.
Et si je pose la question suivante :
> - de quelle couleur est ma voiture ?

Je peux déduire que si 'ma voiture est une golf' et que 'toutes les golfs sont noires', 'ma voiture est noire'.

On a donc besoin de trois éléments pour réfléchir :
> - une base de connaissance qui regroupe toutes les 'vérités' connues ;
> - un moteur de réflexion qui définit la méthode utilisé pour réfléchir ;
> - une question qui initialise le moteur.

On y reviendra.

Dans notre cas : nous n'avons pas une question mais un ordre 'Gagne !' ;) [[BR](BR.md)]
De façon plus général, il s'agit là de la plus grande difficulté : **trouvé le déclencheur pour notre réflexion**.

### Forte ou faible ###

Il existe deux types d'Intelligence Artificielle : les fortes et les faibles.

Les fortes sont capables d'apprendre. C'est à dire qu'elles peuvent faire évoluer leur base de connaissance pour étendre l'étendue de leur connaissance.
Les faibles ne sont pas capables d'apprendre. Leur réflexion restent dans le cadre du moteur de réflexion et des vérités connues initialement.

Dans notre cas : on va aller vers du 'faible' ;)

## La base de connaissance ##

une base de connaissance qui regroupe toutes les 'vérités' connues du système. Qu'est-ce qu'une 'vérité' :
> - une vérité scientique,
> - un fait empiriquement vérifiable,
> - une formule mathématique.

Par exemple, en français dans le texte (je vais éviter au maximum les formules mathématiques) :
> - "la voiture est bleue",
> - "si il y a une balle devant moi, je l'attrape".

on a donc :
> - des variables ('la voiture', la couleur 'bleue', 'moi') ;
> - des opérations ('est', 'si', ',') ;
> - des conséquences ('je l'attrape').

Dans notre cas, il faut pouvoir définir les phrases suivantes en terme de code : 'si une balle est devant moi' ou 'je me dirige vers la balle la plus proche'. Attention à ne pas tomber dans l'exces : la phrase '~~aller au point (10, 10)~~' n'a pas lieu d'être : ce n'est pas à l'IA de calculer les coordonnées de la balle la plus proche ou d'effectuer les opérations complexes, l'IA est là pour faire des choix.

## Le moteur de réflexion ##

Dans notre cas, le moteur de réflexion se basera certainement sur une logique de type : perception -> réflexion -> action.
> - la perception consiste à initialiser les variables en fonction de l'environnement du robot ;
> - la réflexion sera de mixer ces variables pour définir les actions que le robot doit entreprendre ;
> - l'action sera le résultat directe de la réflexion.

### Quelques réflexions pour le robot ###

| **perception** | **action** |
|:---------------|:-----------|
| temps >= 150   | arret      |
| adversaire en face | contourner |
| stock = 3 balles | rapporter  |
| stock = 3 balles et devant conteneur | décharger  |
| chargeur de balles en face et vide | changer de chargeur |
| chargeur de balles en face | prendre balle |

## La Question ##
(avec un grand Q, sans jeu de mot)