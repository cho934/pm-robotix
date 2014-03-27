#include <stdio.h>
#include <stdlib.h>
#ifdef SIMULATED

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "../robot.h"

/**
 * SIMULATION
 **/
long long timeOffset;
int lPower;
int rPower;

long tLeft;

long tRight;

long rightCounter;
long leftCounter;

void robot_init() {
	tLeft=0;
	tRight=0;
	lPower=0;
	rPower=0;

	rightCounter=0;
	leftCounter=0;
	//
	struct timeval te;
	gettimeofday(&te, NULL);// get current time
	timeOffset =( te.tv_sec*1000LL + te.tv_usec/1000);

	printf("Init time %ld\n",currentTimeInMillis());
}
void robot_dispose() {
}
void robot_startMotorLeft() {
}
void robot_startMotors() {
}

void robot_stopMotorRight() {
}
void robot_stopMotorLeft() {
}
void computeCounterL() {
	long deltaT= currentTimeInMillis()- tLeft;
	leftCounter+= (deltaT*lPower )/25;

}
void computeCounter() {
	long deltaT= currentTimeInMillis()- tRight;
	rightCounter+= (deltaT*rPower )/25;
}

void robot_setMotorRightSpeed(int speed) {
	computeCounter();
	rPower=speed;
	tRight=currentTimeInMillis();
}

void robot_setMotorLeftSpeed(int speed) {
	computeCounterL();
	lPower=speed;
	tLeft=currentTimeInMillis();
}

long robot_getLeftExternalCounter() {
	computeCounterL();
	return leftCounter;
}
long robot_getRightExternalCounter() {
	computeCounter();
	return rightCounter;
}
long robot_getLeftInternalCounter() {
	return robot_getLeftExternalCounter();
}
long robot_getRightInternalCounter() {
	return robot_getRightExternalCounter();
}
int robot_isButton1Pressed() {
	return 0;
}

#endif
