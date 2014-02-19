#init root password 
passwd

#create /pmx for sdcard
mkdir /pmx

#mount sdcard
mount -t vfat /dev/mmcblk0p1 /pmx

