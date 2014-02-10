#!/usr/bin/expect
spawn scp /home/maillard/EV3/workspace/EV3/Debug/EV3 root@192.168.2.240:/mnt/ramdisk
expect {
password: {
send "\r";
exp_continue
}
}

#spawn ssh root@192.168.2.240 "LD_LIBRARY_PATH=/mnt/card /mnt/card/RobotEV3"
#expect {
#password: {
#send "\r";
#exp_continue
#}
#}

