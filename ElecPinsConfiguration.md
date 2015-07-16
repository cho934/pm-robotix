Retour sur ElecStart

# Données de compréhension #

Robot face à vous :

  * 1GR : moteur 1 = moteurG gauche = moteur fil rouge
  * 2DJ : moteur 2 = moteurD droit  = moteur fil jaune

## Brochage de la carte de démultiplexage (nouvelle version) ##

TODO

## Brochage de la carte de multiplexage (nouvelle version) ##

TODO

## Brochage de la carte APF9328 ##

TODO





# **Ancienne configuration (version 2009)** #

## **Brochage de la carte de démultiplexage (version 2009)** ##

Sorties : démultiplexage (DM0 à DM7)

| DM7 pin 0 à 7 | mot 8bits de force sur moteurG |
|:--------------|:-------------------------------|
| DM6 pin0      | marche avant/arrière moteurG   |
| DM6 pin1      | WR| moteurG                    |
| DM6 pin2      | CS| moteurG                    |
| DM5 pin0      | marche avant/arrière moteurD   |
| DM5 pin1      | WR| moteurD                    |
| DM5 pin 2     | CS| moteurD                    |
| DM4 pin 0 à 7 | mot 8bits de force sur moteurD |
| DM0 pin0      | WR| GP2D12\_n°1                |
| DM0 pin1      | WR| GP2D12\_n°2                |
| DM0 pin2      | WR| GP2D12\_n°3                |

## **Brochage de la carte de multiplexage (version 2009)** ##

Entrées : multiplexage (M0 à M5)

| M0 pin0 à 7| GP2D12\_n°1 - adversaire devant|
|:-----------|:-------------------------------|
| M1 pin0 à 7| GP2D12\_n°2 - bordure ou adversaire devant|
| M2 pin0 à 7| GP2D12\_n°3 - '''''? à déterminer''''' |
| M3 pin0    | contact avant droit            |
| M3 pin1    | contact avant gauche           |
| M3 pin2    | contact arrière droit          |
| M3 pin3    | contact arrière gauche         |
| M3 pin4    | contact présence balle n°1     |
| M3 pin5    | contact présence balle n°2     |
| M3 pin6    | couleur bleu/rouge n°1         |
| M3 pin7    | couleur bleu/rouge n°2         |

## **Brochage direct des entrées sur le port parallèle (version 2009)** ##

| (Port //) pin10 | S3 STATUS | IMP2 = IMPD |
|:----------------|:----------|:------------|
| (Port //) pin11 | S4 STATUS | IMP1 = IMPG |

## **Brochage du port parallèle pour le démultiplexage/multiplexage (version 2009)** ##

voir la première section du document suivant (version 2009):
http://www.assembla.com/spaces/pmx/documents/awbFTisWir3OBleJe5afGb/download/PMX_ST_v03_090510.doc

Retour sur ElecStart