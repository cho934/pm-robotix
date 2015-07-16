# 1. EV3DEV Installation #

  * Download latest ev3dev image file : **ev3dev-jessie-2015-02-24**
https://github.com/ev3dev/ev3dev/releases

  * Copy ev3dev image on the SDcard
For linux: http://www.ev3dev.org/docs/tutorials/writing-sd-card-image-ubuntu-disk-image-writer
For Windows : http://www.ev3dev.org/docs/tutorials/writing-sd-card-image-win32diskimager

  * Then Boot ev3dev

# 2. USB Connection #
  * For Windows : http://www.ev3dev.org/docs/tutorials/setting-up-ethernet-over-usb-on-windows

  * For linux : http://www.ev3dev.org/docs/tutorials/setting-up-ethernet-over-usb-on-linux-networkmanager

## for image ev3dev-jessie-2015-02-24 ##
  * In brickman, enable CDC driver
  * (In brickman, DON'T activate Tethering > Gadget)
  * In linux host, System Settings > Network > change the Method to **Shared to other computers**
  * In brickman, on the IPv4 tab, choose **Load Linux Defaults**
  * In brickman, tick the checkbox **Connect automatically**

## for old image ev3dev-jessie-2014-12-01 ##
  * In brickman, enable CDC driver
  * In brickman, enable Networking > Gadget
  * In linux host, System Settings > Network > change the Method to **Shared to other computers**
  * In brickman, on the IPv4 tab, choose **Load Linux Defaults**
  * In brickman, tick the checkbox **Connect automatically**

## Connection ##
**Connect to the EV3 using ssh
```
user@host:~$ ssh root@10.42.0.3
```
  * Default password : r00tme**

# 3. Grow your root file system #
```
root@ev3dev:~# lvextend --extents +100%FREE --resizefs /dev/ev3devVG/root /dev/mmcblk0p3
```
then reboot ev3.

# 4. Set up a new user #
```
root@ev3dev:~# adduser user
root@ev3dev:~# usermod -a -G sudo,ev3dev,plugdev,audio,video,input,bluetooth user
```

# 5. Update system and last kernel #
```
root@ev3dev:~$ apt-get update
root@ev3dev:~$ apt-get upgrade
root@ev3dev:~$ apt-get dist-upgrade
```


# 6. Wifi using connman #
_Reference_ : https://wiki.archlinux.org/index.php/Connman
  * enable Wifi
```
root@ev3dev:~$ connmanctl enable wifi
```
  * list the available networks found after a scan run
```
root@ev3dev:~$ connmanctl 
```
```
connmanctl> scan wifi
Scan completed for wifi
connmanctl> services
*AO Wired                gadget_..._usb
    SSID       wifi_..._managed_psk

connmanctl> agent on
Agent registered
connmanctl>  connect wifi_...
(and enter your passphrase)
connmanctl> quit
```


  * list connman settings
```
root@ev3dev:~$ cat /var/lib/connman/*/settings
```
verify settings for each connection (AutoConnect and Favorite):
```
root@ev3dev:~# cat /var/lib/connman/*/settings
[gadget_..._usb]
Name=Wired
Favorite=true
AutoConnect=true
Modified=2015-03-02T00:02:45.046284Z
IPv4.method=manual
IPv4.netmask_prefixlen=24
IPv4.local_address=10.42.0.3
IPv4.gateway=10.42.0.1
IPv6.method=off
IPv6.privacy=disabled
Nameservers=10.42.0.1;
[wifi_..._managed_psk]
Name=[SSID_NAME]
SSID=[SSID_NUMBER]
Frequency=2457
Favorite=true
AutoConnect=true
Modified=2015-03-02T00:02:12.644730Z
Passphrase=[passphrase]
IPv4.method=dhcp
IPv4.DHCP.LastAddress=192.168.7.44
IPv6.method=off
IPv6.privacy=disabled
[wifi_..._managed_psk]
Name=[SSID_NAME]
SSID=[SSID_NUMBER]
Frequency=2457
Favorite=true
AutoConnect=true
Modified=2015-03-01T23:59:35.241565Z
Passphrase=[passphrase]
IPv4.method=dhcp
IPv4.DHCP.LastAddress=192.168.7.252
IPv6.method=off
IPv6.privacy=disabled
```

# 7. Stop brickman on EV3 LCD #

  * Stop brickman
```
root@ev3dev:~$ systemctl stop brickman.service
```
  * Disable brickman on startup
```
root@ev3dev:~$ systemctl disable brickman.service
```
  * Autologin and clear display after boot
(from https://wiki.archlinux.org/index.php/automatic_login_to_virtual_console)
```
root@ev3dev:~$ mkdir /etc/systemd/system/getty@tty1.service.d/
root@ev3dev:~$ nano /etc/systemd/system/getty@tty1.service.d/autologin.conf
```
and copy/paste the following in autologin.conf
```
[Service]
ExecStart=
ExecStart=-/usr/bin/agetty --autologin root --noclear %I 38400 linux
```

# 8. Launch your program / To get a program to run at boot #

## 8.1 Using Brickman and his **file browser** ##
Put the program into /home

## 8.2 Create a **systemd service** ##
https://github.com/ev3dev/ev3dev/issues/238

  * Save the following as /etc/systemd/system/myprogram.service
```
[Unit]
Description=My Program
After=multi-user.target

[Install]
WantedBy=multi-user.target

[Service]
Type=simple
ExecStart=/home/user/bin/myprogram
```
myprogram of course can be replace by the name of your program. Also, ExecStart is not run in a shell and there is no PATH environment variable, so you can't take any shortcuts. For example, if you program is a python script, you would have to write ExecStart=/usr/bin/python /home/user/myprogram.py
  * Enable the custom service
```
systemctl daemon-reload
systemctl enable myprogram.service
```

# 10. Power Off and exit ssh #
```
user@ev3dev:~$ poweroff & exit
```