Retour sur DevStart

# Infos eeepc #

T91MT ASUS

# Installation des drivers sur LINUX MINT8 #

Référence [voir ici](http://jeffhoogland.blogspot.com/2010/05/howto-linux-mint-8-on-t91mt.html)

## Carte graphique ##

```
$ wget http://gma500re.altervista.org/scripts/poulsbo.sh && sh ./poulsbo.sh
```


# L'installation software nécessaire #

[voir le Linux Quick Start](http://www.cmucam.org/wiki/Linux-Quick-Start)


# Utilisation de la CMUCAM #

## Connexion à l'eeePC ##
Connecteur utilisé : TRENDnet TU-S9
Pour détecter le port concerné :
```
$ tail -f /var/log/messages
```
On déconnecte et reconnecte le connecteur pour détecter le port utilisé

## Environnement de développement ##
mise a jour du PATH :
```
$ export PATH=$PATH:/home/trip/CodeSourcery/Sourcery_G++_Lite/bin/
```

## Project ##
Une grosse partie de la génération des programmes se fait en chemin relatif.
Pour éviter de fouiller les utilitaires, on place les projets dans le dossier projects de cc3
Après édition du Makefile pour avoir des noms corrects, on make
```
$ Make
```

## Envoi sur la cmucam ##
On lance la cam en dev mode (appui sur le bouton pendant l'allumage)
Envoi du projet dans la cam :
```
$ sudo /home/trip/Téléchargements/lpc21isp_unix/lpc21isp project.hex /dev/ttyUSB0 115200 14746
```


Retour sur DevStart