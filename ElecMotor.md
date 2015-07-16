Retour sur ElecStart

# Motorisation de la base roulante #

Nous avons choisi de développer des cartes électroniques simples à l'aide de composants bon marché. Chaque carte permet de transcrire une commande numérique en analogique mettant en œuvre un PWM (Pulse Width modulator ou modulation de largeur d'impulsion) "fait maison".

## 1. Les moteurs ##

Nous avons utilisés des moteurs courant continu GEARBOX 919D541/1 avec un rapport de réduction de 150:1

## 2. Principe par PWM ##

A partir d’un mot binaire de 8 bits, le convertisseur Numérique-Analogique (CNA ou DAC) transforme la valeur du mot binaire en tension. Cette tension est ensuite injectée dans le système d’amplification opérationnel (AOP).
Un comparateur à Hystérésis (signal carré) est intégré avec un autre AOP (LM324) pour obtenir un signal triangulaire constant. Ce dernier est ensuite comparé avec la tension variable de CNA (ou DAC) (c'est un AD7302BN qui est utilisé) pour obtenir un carré où la largeur d’impulsion varie. Ce signal est ensuite envoyé comme commande à un étage de puissance, constitué de transistors sur le principe de montage Darlington. Ce montage se compose d'un transistor 2N3904 puis d'un 2N3055E permettant un courant fort. Bien penser aux diodes de roues libres. Le signal de puissance est transmis au moteur à courant continu. Le changement de sens est opéré par 2 relais NO/NC qui permettent d'inverser le sens du courant dans le moteur via une commande TTL (via une commande par un ULN2003 intégrant des diodes de roues libres).

CONCLUSION : **la puissance du moteur varie donc par rapport au mot binaire appliqué.**

## 3. Suppression des parasites ##

En effectuant les tests, il s'avère que beaucoup de parasites interviennent sur les cartes, les servomoteurs se mettent à bouger lorsque les moteurs sont en route, bref que des ennuis.
Pour les supprimer, voici ce que l'on peut faire :
  * Utiliser une fréquence de PWM > 20kHz si possible.
  * Isoler les câbles moteurs par un blindage à la masse.
  * Les câbles moteurs doivent être seuls dans le passage de câble, aucun autre fil ne doit les longer (sinon les parasites seront transmis).
  * Mettre des **ferrites** avec au moins une boucle sur chaque câble moteur.

## 4. Composants utilisés pour une carte moteur ##

Les composants sont bons marchés et ne sont pas très nombreux :

|**Composant**|**Description**|
|:------------|:--------------|
|LM324N       |Quad low power operational amplifiers|
|AD7302BN     |Parallel Input Dual Voltage Output 8-bits DAC|
|ULN2003      |High current Darlington transistor array|
|2N3904       |NPN switching transistor|
|2N3055E      |Complementary silicon Power Transitors|
|REL FRS1B    |Relais 5V 1NO 1NC|

## 5. Contrôle de la carte ##

|**Contrôle**|**Description**|
|:-----------|:--------------|
|1 mot de 8bits D7-D0|AD7302 Parallel Data Inputs. Définit la force à appliquer sur le moteur.|
|WR|         |AD7302 Write Input. WR| est une entrée s’activant par niveau bas. Elle s’utilise en conjonction avec CS|. Elle permet d’écrire sur la sortie analogique choisie (sortie A ou B).|
|CS|         |AD7302 Chip Select. CS| est une entrée s’activant par niveau bas. |
|AV/AR       |Marche Avant/Arrière. Permet de configurer les relais en conséquence.|

## 6. Schéma électronique et typon ##

http://www.assembla.com/spaces/pmx/documents/aMz364OqWr3lKUabIlDkbG/download?filename=1_annexe_schema_motor3.1.zip

## 7. Document de spécifications des composants utilisés (datasheets) ##

http://www.assembla.com/spaces/pmx/documents/bsIEMAOqWr3kctabIlDkbG/download?filename=1_annexe_schema_motor3.1_datasheets.zip

Ces documents donne les caractéristiques techniques des composants, leurs utilisations, et la signification des états possibles des différents pins.

;o)

  * (TODO) Dimensionnement roues-motoreducteur-codeur
  * (TODO) Suppression de l'AD7302 pour utiliser l'ADC de la carte AFF9328

Retour sur ElecStart