Retour sur DevEnvArmadeus

# Compilation Armadeus version 6.0 (version Git) #

## Installation des packages nécessaires (sur l'hôte machine virtuelle) ##
```
$ sudo apt-get install build-essential gcc  g++ autoconf  automake libtool bison flex gettext 
$ sudo apt-get install patch subversion texinfo wget git-core
$ sudo apt-get install libncurses5 libncurses5-dev
$ sudo apt-get install zlib1g-dev liblzo2-2 liblzo2-dev
$ sudo apt-get install libacl1 libacl1-dev
$ sudo apt-get install uuid-dev

$ sudo apt-get install ckermit
$ sudo apt-get install tftpd xinetd
$ sudo apt-get install lrzsz

$ sudo apt-get install expect

$ sudo apt-get install default-jre
```

## Virtualbox shared folder ##
  * add user permission
```
$ sudo adduser pmx vboxsf
```
  * reconfigure dash
```
$ sudo dpkg-reconfigure -plow dash
```

## Dernier Snapshot GIT ##
```
$ cd /install
$ git clone git://git.code.sf.net/p/armadeus/code armadeus-git
```

## Download Armadeus 6.0 ##
https://sourceforge.net/projects/armadeus/files/armadeus/


## Configuration du noyau ##
```
$ cd /install/armadeus-git/
$ make apf9328_defconfig
```

## Ajout des configurations nécessaires pour PMX ##
```
$ make menuconfig
```

**Configuration du paramètre de download local :
```
 Build options  --->
    ($(BASE_DIR)/../downloads) => /armadeus/local/downloads/
```
  * Transfert SSH [Armadeus:SSH](http://www.armadeus.com/wiki/index.php?title=SSH):
  * Transfert série [Armadeus:serial\_transfer](http://www.armadeus.com/wiki/index.php?title=Serial_Transfer) (non utilisé pour le moment):
```
 Package Selection for the target  --->
    [*] Networking  --->
        [*]   dropbear
        [*]   lrzsz
```
  * As\_device [Armadeus:AsDevices](http://www.armadeus.com/wiki/index.php?title=AsDevices): permet d'utiliser le MAX5821 (DAC) en code C. Le makefile a dû être modifié pour prendre en compte cette bibliothèque.
```
 Package Selection for the target  --->
  *** Armadeus specific packages ***
  Armadeus specific tools/utilities  --->   
    [*] as_devices 
    [*] imxregs (pour configurer la fréquence du bus I2C)
    [*] max5821ctrl   
```**

  * Tools
```
 [*] Hardware handling / blockdevices and filesystem maintenance  ---> 
    [*]   i2c-tools  
```

  * GDB [Armadeus:GDB](http://www.armadeus.com/wiki/index.php?title=GDB) (Attention peut génèrer un fichier trop volumineux pour la carte APF9328)
```
 Toolchain  --->
        *** Gdb Options ***
    [*] Build gdb debugger for the Target
```

  * pthread debugging [Armadeus:Troubleshots](http://www.armadeus.com/wiki/index.php?title=GDB#pthread_debugging)
```
$ make uclibc-menuconfig
```
```
General Library Settings  --->
    ...
    [*] POSIX Threading Support
    [*]   Build pthreads debugging support
    ...
```
```
$ cp buildroot/output/toolchain/uClibc-0.9.30.3/.config buildroot/target/device/armadeus/apfXX/uClibc.config.arm
```
```
$ rm -rf buildroot/output
$ make
```


  * Désactivation de programmes non nécessaires:
```
 Package Selection for the target  ---> 
    [ ] Audio libraries and applications  ---> 
    [ ] Text editors  ---> 
         (nano)
    [*] Graphic libraries and applications (graphic/text)  --->
       [ ]   libts - The Touchscreen tslib Library 

    Toolchain  --->
       [ ] Enable IPv6 
```

  * Compilation sur l'hôte :
```
$ make
```


## Xenomai ##
Suivre le tuto [Armadeus:Xenomai (version for apf9328)](http://www.armadeus.com/wiki/index.php?title=Xenomai&oldid=9846)
  * Selecting Xenomai package
```
$ make menuconfig
```
Puis
```
 [*] Hardware handling / blockdevices and filesystem maintenance  --->  
    [*]   Xenomai  
```

  * Configuration if you use xeno-test
```
$ make busybox-menuconfig
```
```
Shells  --->
        Choose your default shell (ash)  --->
    --- ash
    ---   Ash Shell Options
          ...
          [*]   Builtin getopt to parse positional parameters 
```
```
 $ make busybox-clean && make
```

  * Ajout de l'option suivante '''High resolution Timer Support''' permettant des timing (usleep) plus précis :
```
$ make linux26-menuconfig
```
Puis cocher :
```
 Kernel features --> 
  [*] High resolution Timer Support
```
```
$ make linux26 && make
```

## motionSystem (utilisation des servomoteur via FPGA) ##
  * voir [Armadeus:MotionSystem](http://www.armadeus.com/wiki/index.php?title=MotionSystem#How_to_build_and_install_the_Linux_Kernel_Servo_Driver)
```
$ make linux26-menuconfig
```
```
In Device Drivers ---> 
   Armadeus specific drivers ---> 
      FPGA Drivers, 
        [M] Armadeus Servo driver (NEW) (as module)
```
```
$ make clean
$ make
```
**Il faudra installé le nouveau "Linux Kernel" et le nouveau "root filesystem"**

## Activer le [Armadeus:DebugFS](http://www.armadeus.com/wiki/index.php?title=Linux_Debug#Using_DebugFS) (voir  [linuxtopia](http://www.linuxtopia.org/online_books/linux_kernel/kernel_configuration/ch09s07.html)) ##
```
   ---> Kernel hacking
    [*] Debug filesystem
```


## A supprimer en plus ##
```
 Device Drivers  ---> 
   [ ] USB support  --->
   [ ] Sound card support
   Armadeus specific drivers  --->  
      [ ] Armadeus Parallel Port emulation driver (with LCD port) 
      [ ] Armadeus keypad driver  
```


## (Deprecated) Désactivation du framebuffer (LCD) pour utiliser les pads associés en GPIO ##
(voir [Armadeus:FrameBuffer](http://www.armadeus.com/wiki/index.php?title=FrameBuffer))

**Pour supprimer l'apparition des messages d'erreur incessant dans la console série RS232 : DevArmadeusSystemConf**

  * Configuration
```
$ make linux26-menuconfig
```

  * options à désactiver
```
 Device Drivers  
    ---> Character devices  ---> 
        [ ] Virtual terminal
```
```
 Device Drivers  
    ---> Graphics support  
        < > Lowlevel video output switch controls 
        < > Support for frame buffer devices  
        [ ] Backlight &LCD device support
```

  * Recompilation du kernel:
```
 $ make linux26
```




Retour sur DevEnvArmadeus