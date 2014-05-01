#!/usr/bin/expect
spawn scp /home/maillard/EV3/workspace/EV3/EV3/EV3 root@192.168.2.240:/media/card/program
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

