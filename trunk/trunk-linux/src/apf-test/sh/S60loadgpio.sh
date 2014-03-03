
/usr/bin/loadgpio.sh
#initialisation GPIO ; pins order: [31...0]                 //dir :  outputs ('1'), all others as inputs ('0'):
#echo -n 11111111111111111111111110000000 > /proc/driver/gpio/portDmode
#echo -n 10011000111100111111111110000000 > /proc/driver/gpio/portDdir
#echo -n 02200111000010000000000000000000 > /proc/driver/gpio/portDirq

#initialisation ADC pour GP2D12
modprobe max1027
export ADC_SPI="spi1.0"
#use "Fast" interface > 10kHz (using blocking read)
#loadmax.sh

#initialisation DAC pour controle motorisation
#/usr/bin/setDAC AB

#initialisation FPGA motionSystem
modprobe servo
#echo '1' > /sys/class/servo/servo0/enable
#echo '1' > /sys/class/servo/servo1/enable

#initialisation de la frequence de bus I2C à 100kHz
imxregs IFDR 0x17

modprobe spidev

#sleep 3
cd /pmx
#prog d'homologation
#./pmx 1
#prog matches
#./pmx 0
