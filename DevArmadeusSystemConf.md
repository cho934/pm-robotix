Retour sur DevEnvArmadeus


# Configuration system APF9328 #


## a.Désactivation du framebuffer (LCD) ##

Pour supprimer l'apparition des messages d'erreur incessant dans la console série RS232 :
  * modifier le fichier **/etc/inittab** du rootfs (par connexion ssh, et pour initialiser le password de root, se connecter via la console série et utiliser la cmd passwd sans tenir compte des messages qui défilent) et commenter les 2 lignes ci-dessous :
Dans la partie :# Set up a couple of getty's
```
#tty1::respawn:/sbin/getty 38400 tty1
```
Dans la partie :# Logging junk
```
#tty3::respawn:/usr/bin/tail -f /var/log/messages
```


## b.Configuration de la microSD (APF9328) ##

  * Accès à la microSD (voir [Armadeus:MultiMediaCard](http://www.armadeus.com/wiki/index.php?title=MultiMediaCard))
```
# mkdir /pmx
# mount -t vfat /dev/mmcblk0p1 /pmx
```

  * montage automatique de la microSD, ajout dans le /etc/fstab :
```
/dev/mmcblk0p1  /pmx       vfat     defaults          0      0
```

  * se connecter directement au login dans /pmx
Editer le fichier '''/etc/passwd'''
pour root, modifier le path avec /pmx

## c.Chargement automatique des GPIO (APF9328) ##
Chargement manuel des GPIO, lancer la commande :
```
/usr/bin/loadgpio.sh 
```
Pour le chargement de l'initialisation du programme PMX :

Créer un lien symbolique
```
$ ln -s /pmx/S60loadgpio.sh  /etc/init.d/S60loadgpio
```
ou copier le fichier S60loadgpio dans /etc/init.d/
```
$ cp /pmx/S60loadgpio /etc/init.d/.
```

/pmx/S60loadgpio :
```
/usr/bin/loadgpio.sh

echo -n 10011111111111111111111110000000 > /proc/driver/gpio/portDmode
echo -n 10011000111100111111111110000000 > /proc/driver/gpio/portDdir
echo -n 02200111000001000000000000000000 > /proc/driver/gpio/portDirq
```

Puis faire un chmod :
```
$ chmod 755 /etc/init.d/S60loadgpio
```

## d.Mise à jour de la date et heure (APF9328) ##
```
# date -s MMDDhhmm[[YY]YY][.ss] 
# date -s 011723542010(Sun Jan 17 23:54:00 CET 2010)
```


Retour sur DevEnvArmadeus