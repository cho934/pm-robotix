Retour sur DevEnvArmadeus


# Update U-Boot APF9328 (Configuration des paramètres du BIOS) #
(version actuelle : U-Boot 1.3.4-00201-gda54480 (Jan  3 2011 - 12:37:40) apf9328 patch 3.9)

  * Configuration :
```
BIOS> 
setenv ipaddr 192.168.7.253
setenv netmask 255.255.255.0
setenv serverip 192.168.7.16
setenv gatewayip 192.168.7.254
setenv bootdelay 5
setenv "bootcmd run unlock_regs; run jffsboot"
saveenv 
```
ce qui donne:
```
BIOS> printenv

ipaddr=192.168.7.253
netmask=255.255.255.0
serverip=192.168.7.16            (the IP address of your tftp server/PC hosting the files to download)
rootpath=/tftpboot/apf9328-root  (to boot Linux over NFS)
ntpserverip=217.147.208.1
board_name=apf9328
hostname="apf9328"
gatewayip=192.168.7.254
bootcmd=run unlock_regs; run jffsboot
...
bootdelay=5 (au lieu de 20 secondes par défaut)
...

BIOS>
```
  * Pour modifier les paramètres du bios : [Armadeus:Configure\_U-Boot](http://www.armadeus.com/wiki/index.php?title=Target_Software_Installation#Configure_U-Boot)

  * Update APF9328 u-boot : Installation du fichier '''apf9328-u-boot.bin''' [Armadeus:U-Boot\_installation](http://www.armadeus.com/wiki/index.php?title=Target_Software_Installation#Update_U-Boot)

# Update Kernel linux APF9328 (booting information) #

  * Kernel actuellement utilisé:
```

## Booting kernel from Legacy Image at 100a0000 ...
   Image Name:   Linux-2.6.29.6
   Created:      2012-03-29  22:30:23 UTC
   Image Type:   ARM Linux Kernel Image (uncompressed)
   Data Size:    1627732 Bytes =  1.6 MB
   Load Address: 08008000
   Entry Point:  08008000
   Verifying Checksum ... OK
   Loading Kernel Image ... OK
Linux version 2.6.29.6 (root@pmx-mint8) (gcc version 4.2.1) #13 PREEMPT Fri Mar 30 00:30:21 CEST 2012

```


  * Update APF9328 kernel : Installation du fichier '''apf9328-linux.bin''', voir [Armadeus:Target\_Software\_Installation](http://www.armadeus.com/wiki/index.php?title=Target_Software_Installation)


# Update rootfs APF9328 #
  * Installation du fichier '''apf9328-rootfs.jffs2''' compilé avec le kernel [Armadeus:rootfs\_installation](http://www.armadeus.com/wiki/index.php?title=Target_Software_Installation#rootfs_installation)


# Update FPGA firmware APF9328 for servomotors #
  * voir [Armadeus:FPGA\_Firmware](http://www.armadeus.com/wiki/index.php?title=MotionSystem#FPGA_Firmware)

  * follow
```
BIOS> tftpboot ${loadaddr} servo_top.bit
BIOS> fpga loadb 0 ${loadaddr} ${filesize} 
BIOS> run flash_firmware
BIOS> setenv firmware_autoload 1
BIOS> saveenv
```

  * Show the FPGA Memory Register:
```
BIOS> md.w 12000000
```

Result:
```
12000000: 7207 0003 0020 0000 0000 0000 0000 0000    .r.. ...........
12000010: 0800 0800 0800 0800 0800 0800 0800 0800    ................
12000020: 0800 0800 0800 0800 0800 0800 0800 0800    ................
12000030: 0800 0800 0800 0800 0800 0800 0800 0800    ................
12000040: 0800 0800 0800 0800 0800 0800 0800 0800    ................
12000050: 0000 0000 0000 0000 0000 0000 0000 0000    ................
12000060: 0000 0000 0000 0000 0000 0000 0000 0000    ................
12000070: 0000 0000 0000 0000 0000 0000 0000 0000    ................
```

  * Si le run flash\_firmware donne le message d'erreur suivant :
```
Erasing FLASH
- Warning: 1 protected sectors will not be erased!
. done
Erased 2 sectors
Copy to Flash... Can't write to protected Flash sectors
Flashing of Firmware failed
```
Enlever la protection comme suit :
```
BIOS> protect off ${firmware_addr} +${firmware_len}
```

# Update i2c bus frequency on APF9328 #

Par défaut, la fréquence est de 250kHz (IFDR clk divider = 0x10).
Il faut effectuer la commande "unlock registers access" pour changer le I2C IFDR register [Changing processor registers from Linux user space with imxregs](http://www.armadeus.com/wiki/index.php?title=Imxregs#Changing_processor_registers_from_Linux_user_space_with_imxregs)

Pour cela, dans le BIOS, taper :
```
BIOS> run unlock_regs
BIOS> boot
```
Ensuite il sera possible d'utiliser imxregs.

La commande unlock\_regs effectue en fait les commandes suivantes (voir printenv unlock\_regs dans le BIOS):
```
BIOS> mw.l 0x00200008 0
BIOS> mw.l 0x00210008 0
```

Définition "IFDR clk divider":
```
+       { 22,   0x20 }, { 24,   0x21 }, { 26,   0x22 }, { 28,   0x23 },
+       { 30,   0x00 }, { 32,   0x24 }, { 36,   0x25 }, { 40,   0x26 },
+       { 42,   0x03 }, { 44,   0x27 }, { 48,   0x28 }, { 52,   0x05 },
+       { 56,   0x29 }, { 60,   0x06 }, { 64,   0x2A }, { 72,   0x2B },
+       { 80,   0x2C }, { 88,   0x09 }, { 96,   0x2D }, { 104,  0x0A },
+       { 112,  0x2E }, { 128,  0x2F }, { 144,  0x0C }, { 160,  0x30 },
+       { 192,  0x31 }, { 224,  0x32 }, { 240,  0x0F }, { 256,  0x33 },
+       { 288,  0x10 }, { 320,  0x34 }, { 384,  0x35 }, { 448,  0x36 },
+       { 480,  0x13 }, { 512,  0x37 }, { 576,  0x14 }, { 640,  0x38 },
+       { 768,  0x39 }, { 896,  0x3A }, { 960,  0x17 }, { 1024, 0x3B },
+       { 1152, 0x18 }, { 1280, 0x3C }, { 1536, 0x3D }, { 1792, 0x3E },
+       { 1920, 0x1B }, { 2048, 0x3F }, { 2304, 0x1C }, { 2560, 0x1D },
+       { 3072, 0x1E }, { 3840, 0x1F }
```

Changement de la fréquence du bus i2c dans le système :
USAGE:
```
 # imxregs REGISTER_NAME  
```
//=> avec 0x17 la fréquence du bus i2c sera donc de 96000000 / 960 = '''100000kHz'''
```
 # imxregs IFDR 0x17 
```

Pour automatiser le changement dans le BIOS:
```
BIOS> setenv bootcmd run unlock_regs\; run jffsboot
BIOS> saveenv
```


'''TODO''' : then if you want something "clean" look at:
buildroot/output/build/linux-2.6.29.6/drivers/i2c/busses/i2c-imx.c
and try to use its custom IOCTL to setup bus frequency








Retour sur DevEnvArmadeus