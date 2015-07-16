Retour sur ElecStart

# Le démultiplexage/multiplexage fait maison #

## 1. Objectif ##

L'objectif était d'utiliser uniquement le port parallèle d'un PC. Par conséquent, peu d'entrées, sorties sont disponibles, d'où l'idée de mettre en place un '''double multiplexage en place simplement'''.
Seules les impulsions des moteurs droit et gauche (ainsi que les quadratures de phase) ne passe pas par le multiplexage, et sont directement affectées à des pins d'entrées du port parallèle.

## 2. Principe ##

Le principe du démultiplexage(DM)/multiplexage(M) est de multiplier les entrées/sorties, celles-ci étant très limitées par le seul port parallèle.
Les 2 cartes (une pour les sorties, une pour les entrées) permettent d’obtenir :
  * 8 DM x 8 pins = 64 sorties
  * 6 M x 8 pins = 48 entrées

Liste des multiplexeurs/démultiplexeurs identifiés sur les cartes :
- DM0, DM1, DM2, DM3, DM4, DM5, DM6, DM7
- M0, M1, M2, M3, M4, M5
Les pins vont de 0 à 7 pour chaque composant.

Deux bus d’adresse sont disponibles :
  * le premier pour choisir le multiplexeur/démultiplexeur (MA, MB, MC),
  * le deuxième pour choisir le pin d’entrée/sortie (@A, @B, @C).

Le choix du mode entrée/sortie se fait via 2 pins du port parallèle (E1 et E2). Suivant la carte choisie, soit on utilise la données d’entrée à lire (DE), soit on utilise la donnée à appliquer (AD).

## 3. Composants utilisés ##

Les composants sont bons marchés et ne sont pas très nombreux :

| **Composant** | **Description** |
|:--------------|:----------------|
|74HC04N        |Hex Inverter     |
|74HCT259E      |High Speed CMOS Logic 8-Bit Addressable Latch|
|74HC151N       |8-input multiplexer|
|MC14070BCP     |Quad Exclusive « OR »|

## 4. Utilisation et brochage du port parallèle ##

|Pin (port //)|Port (port //)|Réf carte|Description|
|:------------|:-------------|:--------|:----------|
|6            |D4 DATA       |MA       |Adresse du DM/M visé.|
|7            |D5 DATA       |MB       |Adresse du DM/M visé.|
|8            |D6 DATA       |MC       |Adresse du DM/M visé.|
|12           |S2 STATUS     |DE       |Donnée d’entrée à lire.|
|10           |S3 STATUS     |IMPD     |Impulsion du moteur droit.|
|11           |S4 STATUS     |IMPG     |Impulsion du moteur gauche.|
|13           |S1 STATUS     |IMPG Déphasage|Impulsion déphasée associée au pin IMPG permettant de connaitre le sens du moteur.|
|15           |S0 STATUS     |IMPD Déphasage|pin FOUTU sur le PC IBM voir C3 du port CONTROL|
|2            |D0 DATA       |@A       |Adresse du pin du DM/M sélectionné.|
|3            |D1 DATA       |@B       |Adresse du pin du DM/M sélectionné.|
|4            |D2 DATA       |@C       |Adresse du pin du DM/M sélectionné.|
|5            |D3 DATA       |AD       |Donnée à appliquer sur le pin sélectionné.|
|1            |C0 CONTROL    |E1       |Activation de la carte rouge des DM (démultiplexors) => sorties.|
|14           |C1 CONTROL    |E2       |Activation de la carte blanche des M (Multiplexors) => entrées.|
|17           |C3 CONTROL    |IMPD Déphasage|Impulsion déphasée associée au pin IMPD permettant de connaitre le sens du moteur.|

## 5. Câbles de connexion ##

### Connecteur côté port parallèle : ###

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecMultiDemultiplexage_brochage_port_parallele.JPG?attredirects=0

### Connecteur côté carte de multiplage : ###

|E1|E2|
|:-|:-|
|@A|DE|
|@B|DéphasageG|
|@C|DéphasageD|
|AD|GND|
|MA|IMPD|
|MB|IMPG|
|MC|Not connected|
|>>|sens / vue de dessus|

### Nappe entre les 2 cartes DM et M : ###

|@A|@B|@C|AD|5V|MA|MB|MC|GND|MD|E1|
|:-|:-|:-|:-|:-|:-|:-|:-|:--|:-|:-|

## 6. Les modifications "a posteriori" ##

Le typon modifié :

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecMultiDemultiplexage_multi10_modifications2009.jpg?attredirects=0

Schéma des modifiations :

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecMultiDemultiplexage_multi10_ajout_schema2009.jpg?attredirects=0

  * Protection de la pin DE, via un optocoupleur 4N28.
  * Utilisation de la pin CONTROL C3 (du port //) en mode input (entrée):

**PRINCIPE de l'utilisation du port CONTROL en INPUT :**
Le port CONTROL possède des sorties en "open collector", c'est-à-dire que 2 états sont possibles, haute impédance et GND. Si vous connectez votre entrée directement (par exemple la pin de déphasageD directement sur la pin C17 du port parallèle), un conflit va en résulter lorsque l'entrée est à 1 et que le port parallèle essaye de mettre à 0 la pin. C'est pourquoi il faut utiliser une inversion en "open collector" (via un 74LS04 par exemple).

## 7. Les cartes en photo ##

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecMultiDemultiplexage_multiplexage_29042008275.jpg?attredirects=0


## 8. Schéma électronique et typon ##

[1\_annexe\_schema\_multi10.zip](https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnxwbXJvYm90aXh8Z3g6NmVlNzkxNmU3OWU3YTMxYw)


## 9. Document de spécifications des composants utilisés (datasheets) ##

[1\_annexe\_schema\_multi10\_datasheets.zip](https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnxwbXJvYm90aXh8Z3g6NTQ0MzVhNWJlMzQwODkwYQ)

Ces documents donnent les caractéristiques techniques des composants, leurs utilisations, et la signification des états possibles des différents pins.

;o)

Retour sur ElecStart