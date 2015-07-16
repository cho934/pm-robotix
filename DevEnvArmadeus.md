Retour sur DevStart


# L'environnement logiciel APF9328 #

## 1. La compilation et la configuration (réseau, logiciels, système d'exploitation) ##
  * [DevEnvDistributionLinux](DevEnvDistributionLinux.md)       : L'environnement Linux nécessaire
  * [DevArmadeusInstallToolchain60](DevArmadeusInstallToolchain60.md) : compilation Armadeus 6.0
  * DevArmadeusBiosUpdate              : Configuration du BIOS de la carte APF9328
  * DevArmadeusSystemConf              : Configuration du système APF9328

Ancienne version:
  * DevArmadeusInstallToolchain : compilation armadeus 3.4 ([Armadeus:Armadeus 3.4](http://www.armadeus.com/wiki/index.php?title=Armadeus_3))

## 2. Connexion par RS232 avec Kermit (voir [Armadeus:Kermit](http://www.armadeus.com/wiki/index.php?title=Kermit)) ##
  * Install
```
$ sudo apt-get install ckermit
```
  * Edit/Create .kermrc file in your $HOME/ directory (ex: /home/pmx/.kermrc) and fill it with:
```
#set line /dev/ttyS0 
set line /dev/ttyUSB0
set speed 115200
set carrier-watch off
set handshake none
set flow-control none
robust
set file type bin
set file name lit
set rec pack 1000
set send pack 1000
set window 5
set transmit linefeed on
```

use ttyUSB0 if you use USB2serial like TU-S9.

**USAGE :**
  * To launch it :
```
 $ sudo kermit -c
```
  * To login :
```
 root / pmx
```
  * To switch from terminal mode to command mode:
```
CTRL + \ then c (par défaut)
CTRL + h then c (configuration sur mint8-PMX)
```
  * To switch from command mode to terminal mode:
```
C-Kermit>c then ENTER
```

## 3. Connexion par RS232 avec Windows avec la machine Hote ##
  * Utilisation d'un Hyperterminal alternatif : [TerraTerm](http://ttssh2.sourceforge.jp/)
  * Configurer avec les paramètres suivants:
```
Configuration > Port série :
le port COM utilisé : COM5
Vitesse : 115200
Données : 8bit
Parité : none
Stop : 1bit
```

## 4. Configuration TFTP server configuration (hôte) (voir [Armadeus:Communicate](http://www.armadeus.com/wiki/index.php?title=Communicate)) ##
  * Install tftpd :
```
$ sudo apt-get install tftpd xinetd
```
  * Créer le répertoire /home/pmx/tftpboot
  * Créer et/ou modifier le fichier /etc/xinetd.d/tftp
```
# default: off
# description: The tftp server serves files using the trivial file transfer
#       protocol.  The tftp protocol is often used to boot diskless
#       workstations, download configuration files to network-aware printers,
#       and to start the installation process for some operating systems.
service tftp
{
       socket_type             = dgram
       protocol                = udp
       wait                    = yes
       user                    = root
       server                  = /usr/sbin/in.tftpd
       server_args             = -s /home/pmx/tftpboot
#       disable                 = yes
}
```
  * Errata (if you have troubles)

It looks like xinetd configuration is not sufficient in some recent versions of this tool. IPv6 is enabled by default and seems to be not compatible with the TFTP protocol. A simple inetd configuration should work for people who have this problem (connection refused in system logs with addresses like ::ffff:192.168.0.100).

Edit (as root user) - if necessary - the /etc/inetd.conf file and add this line:
```
tftp		dgram	udp	wait	nobody	/usr/sbin/tcpd	/usr/sbin/in.tftpd -s /home/pmx/tftpboot
```

  * Install inetd tools
On Ubuntu/Debian
```
$ sudo apt-get install inetutils-tools
```


  * Redémarrer xinetd service
```
$ sudo killall -HUP xinetd
```

  * Vérifier les droits
```
$ sudo chmod -R 777 /home/pmx/tftpboot
$ sudo chown -R nobody /home/pmx/tftpboot
```
  * Récupérer un fichier de l'hôte à partir de la carte APF9328
```
# tftp -g -r getfile.txt 192.168.7.14
```
  * Déposer un fichier sur l'hôte
```
# tftp -p -l putfile.txt 192.168.7.14
```

## 5. Connexion par SSH ##
  * prérequis : avoir flasher le rootfs avec l'option dropbear (voir configuration)
  * Pour tester : (il faut avoir mis auparavant un mot de passe avec la command "passwd")
```
$ ssh root@192.168.7.253
```




## 6. Les bases du développement Armadeus : Compilation C++ ##
  * Obtenir les variables d'environnement
```
$ make shell_env
$ . armadeus_env.sh
```
  * The C++ cross compiler is installed in $ARMADEUS\_TOOLCHAIN\_PATH and is named arm-linux-g++
```
$ echo $ARMADEUS_TOOLCHAIN_PATH
$ export PATH=$PATH:$ARMADEUS_TOOLCHAIN_PATH
```
  * Export to your PATH environment variable
```
$ export PATH=$PATH:$ARMADEUS_TOOLCHAIN_PATH
```
  * call directly $ARMADEUS\_TOOLCHAIN\_PATH/arm-linux-g++
```
$ $ARMADEUS_TOOLCHAIN_PATH/arm-linux-g++ -o hello hello.cpp
```

### Exemples ###
  * Exemple "Hello World" (voir [Armadeus:Developement](http://www.armadeus.com/wiki/index.php?title=Development))
  * Exemple "GPIO Driver " DevArmadeusGpio (voir [Armadeus:GPIO\_Driver](http://www.armadeus.com/wiki/index.php?title=GPIO_Driver#Examples))
  * Exemple d'utilisation des DAC [Armadeus:DAC](http://www.armadeus.com/wiki/index.php?title=DAC) : permet de gérer la motorisation sans passer par le multiplexage (pas de 1024 au lieu de 255).
  * Exemple d'utilisation Timer pwm0 natif (voir [Armadeus:PWM](http://www.armadeus.com/wiki/index.php?title=PWM)) (pas d'utilité pour le moment)

## La "TODO list" d'installation ##

[SVN:interrupt](http://armadeus.svn.sourceforge.net/viewvc/armadeus/trunk/target/demos/real_time/interrupt/linux/)
  * [FAIT](FAIT.md) intérêt de l'environnement temps réel [Armadeus:Xenomai ](http://www.armadeus.com/wiki/index.php?title=Xenomai) ? gestion des GPIO par interruption http://armadeus.git.sourceforge.net/git/gitweb.cgi?p=armadeus/armadeus;a=blob;f=target/demos/real_time/interrupt/xenomai/user_space/interrupt_xeno_userspace.c;h=670e328ac35775ca10ecb11c1cf3632adec67653;hb=HEAD
  * [FAIT](FAIT.md) le FPGA avec les servomoteurs [Armadeus:MotionSystem](http://www.armadeus.com/wiki/index.php?title=MotionSystem)
  * [FAIT](FAIT.md) Utiliser l'[ADC](http://www.armadeus.com/wiki/index.php?title=Adc) pour les détections par GP2 (en utilisant un multiplexeur devant ?) et pour surveiller les tensions des batteries (definir les alertes en conséquence) (a comparer avec ce [montage](http://www.astrochinon.fr/index.php?option=com_content&view=article&id=62:un-detecteur-de-seuil&catid=37:nos-dossiers&Itemid=56))

  * [TODO](TODO.md) l'exemple complet FPGA avec led et button [voir Armadeus:A\_simple\_design\_with\_Wishbone\_bus](http://www.armadeus.com/wiki/index.php?title=A_simple_design_with_Wishbone_bus) et [sur le svn armadeus](http://armadeus.svn.sourceforge.net/viewvc/armadeus/trunk/target/linux/modules/fpga/wishbone_example/)
  * [TODO](TODO.md) le vhdl [voir wiki autre équipe](http://code.google.com/p/robotter/wiki/CodingRulesVhdl)




Retour sur DevStart