Retour sur MecaStart

# Descriptif #
Utilisation d'une roue de roller, d'un cylindre en bois concentrique sur lequel repose par pression un moteur pas à pas utilisé en codeur.


# VERSION 2012 #
  * Il y a maintenant 4 encodeurs.

## Spécifications MD25 / EMG30 ##
Moteurs :
  * 170 tours/min (après réducteur)
  * réducteur de  30:1

Encodeurs :
  * 360 pas / tour

## Dimensions ##

  * L'entraxe des roues de motorisation est de '''256 mm'''.
  * L'entraxe des roues libres est de '''327.5 mm'''.

|Libellé|coté GAUCHE('''1GR''') en mm|coté DROIT('''2DJ''') en mm|
|:------|:---------------------------|:--------------------------|
|Diam. roue de trotinette|99                          |99                         |
|Diam. roue PaP|19,6                        |19,6                       |
|Diam. roue codeuse libre (en cdrom)|122                         |122                        |

## Calculs ##

Périmètre de la roue motrice : 99 **PI = '''311.01 mm'''**

Périmètre de la roue PaP : 19.6 **PI = '''61.575 mm'''**

Vitesse max :

  * 170 / 60 = '''2.8 tr/s'''
  * 2.8 **311.01 = '''870.85 mm/s'''**

Précision (distance par pas) sur roue motrice :

  * 311.01 / 360 = '''0.8639 mm/pas'''

Précision (distance par pas) sur roue libre :

  * 61.575 / 48 = '''1.2828 mm/pas'''

'''=> TODO : A confirmer avec des tests réels !!'''


# VERSION 2011 #
## Dimensions ##

|Libellé|coté GAUCHE('''1GR''') en mm|coté DROIT('''2DJ''') en mm|
|:------|:---------------------------|:--------------------------|
|Diam. roue de roller|78                          |78                         |
|Diam. roue concentrique en bois|74,4                        |74,4                       |
|Diam. roue codeuse|19,6                        |19,6                       |

L'entraxe des roues au sol est de 320mm.
Les moteurs pas à pas ont 48 pas (en utilisant un seul front).

## Les calculs ##

Distance parcourue entre 2 fronts montants (une impulsion) = 19.6 / 74.4 **78** PI / 48 = '''1.3448888 mm/pulse'''



# VERSION 2009 et 2010 #
## Dimensions ##

|Libellé|coté GAUCHE('''1GR''') en mm|coté DROIT('''2DJ''') en mm|
|:------|:---------------------------|:--------------------------|
|Diam. roue de roller|78,1                        |78,1                       |
|Diam. roue concentrique en bois|72                          |72,1                       |
|Diam. roue codeuse|19,6                        |19,6                       |

L'entraxe des roues au sol est de 313,5mm.
Les moteurs pas à pas ont 48 pas (en utilisant un seul front).

## Les calculs ##

Distance parcourue entre 2 fronts montants (une impulsion) = 19,6 / 72 **78,1** PI / 48 = '''1,39150 mm/pulse'''




Retour sur MecaStart