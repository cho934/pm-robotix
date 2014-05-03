#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <sys/time.h>
#include "robot.h"
#include "mcontrol/motion.h"

int running = 1;

int robot_getLeftPower() {
	return lPower;
}
int robot_getRightPower() {
	return rPower;
}

long currentTimeInMillis() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = (te.tv_sec * 1000LL + te.tv_usec / 1000); // caculate milliseconds
	return (long) (milliseconds - timeOffset);
}

int robot_isRunning() {
	if (running > 0) {
		if (robot_isEmergencyPressed()) {
			running = 0;
		}
	}
	return running;
}

