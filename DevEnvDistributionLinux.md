Retour sur DevEnvArmadeus

# Environnement actuel : Linux lUbuntu 14.04 LTS / Eclipse Luna for C++ #
http://www.lubuntu.net/

https://www.eclipse.org/downloads/

# La machine virtuelle de développement #

## 1. virtualBox + lubuntu 14.04 + eclipse ##

  * les chemins à connaitre sur la VM:
    * /install/armadeus-git/ : emplacement de compilation (attention 10Go d'espace libre sont nécessaires)
    * /home/pmx/tftpboot/ : emplacement des fichiers compilés pouvant être uploadé dans la carte Armadeus

  * les chemins à connaitre sur la carte linux Armadeus embarquée:
    * /pmx : emplacement SDcard où se situe le programme.

  * Installation de java (en installant Eclipse 3.8)
sudo apt-get install eclipse

  * Installer les packages **doxygen** et **graphviz** pour permettre la génération de la documentation.
  * Installer **Nautilus**

## Virtualbox tools ##
  * install g++
```
sudo apt-get install g++ automake 
```
  * mount the media
```
sudo ./VBoxLinuxAdditions.run
```

## 2. Montage additionel sur hôte ##

  * ajout d'un disque dur dans virtualbox
```
$ sudo fdisk /dev/sdb
```

> then type o press enter # creates a new table

> then type n press enter # creates a new partition

> then type p press enter # makes a primary partition.

> then type 1 press enter # creates it as the 1st partition

> finally type w #this will right any changes to disk.

```
$ sudo mkfs.ext4 /dev/sdb1
$ sudo mkdir /install
$ sudo chmod 777 /install
```


  * accès à la partition de compilation armadeus (ancienne VM):
```
$ sudo mount -t ext4 /dev/sdb1 /install
```
Then edit /etc/fstab
```
#device        mountpoint             fstype    options  dump   fsck
/dev/sdb1    /install    ext4    defaults    0    1
```







# Environnement 2014 : Linux lUbuntu 10.04 / Netbeans 7.4 #
http://www.lubuntu.net/

## Netbeans 7.4 avec Java jdk 7 ##
http://netbeans.org/downloads/index.html
  * Installation de la version C++ :
```
$ ./netbeans-7.4-cpp-linux.sh
```


# Ancien environnement : Linux Mint 8 / Netbeans 6.8 #
Based on Ubuntu 9.10 Karmic Koala, Linux 2.6.31, Gnome 2.28 and Xorg 7.4

http://www.linuxmint.com/index.php

## Netbeans 6.8 ##
http://netbeans.org/downloads/index.html
  * Installation de la version CPP :
```
$ ./netbeans-6.8-ml-cpp-linux.sh
```




# Ancien environnement : Fluxbuntu 7.10 et Netbeans 6.0.1 #

## Installation ##

Fluxbuntu : http://wiki.fluxbuntu.org/index.php?title=Get

JDK + Netbeans6.0.1: http://java.sun.com/javase/downloads/netbeans.html

Télécharger le fichier : jdk-6u4-nb-6\_0\_1-linux-ml.sh et exécuter le.

## Ajout du raccourci dans le menu de la Fluxbox ##

Editer le fichier ~.fluxbox/menu

Ajouter les lignes suivantes en dessous du "separator":

```
[exec] (vmware-toolbox) {vmware-toolbox}
[exec] (NetBeans6.0.1) {/usr/local/netbeans-6.0.1/bin/netbeans}
```


# Autres tests : distribution light toujours basées sur Ubuntu #
## crunchbang-lite-9.04.01 ##
a ”A Faster Ubuntu”

http://crunchbanglinux.org/