#init root password 
passwd

#create /pmx for sdcard
mkdir /pmx

#mount sdcard
mount -t vfat /dev/mmcblk0p1 /pmx

#/etc/fstab :
#/dev/mmcblk0p1  /pmx       vfat     defaults          0      0

# date -s MMDDhhmm[[YY]YY][.ss] 
# date -s 011723542014 (Sun Jan 17 23:54:00 CET 2014)
# date -s 040822352014 (Sun Avr 08 22:35:00 CET 2014)

cd /pmx

xeno-test

