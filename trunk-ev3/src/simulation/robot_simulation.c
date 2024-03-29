#include <stdio.h>
#include <stdlib.h>
#ifdef SIMULATED

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "../robot.h"
#include "../motion.h"
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
int robot_isEmergencyPressed() {
	return 0;
}
void robot_waitStart() {
	// nothing to do here :)
}
void robot_startMenu() {
	// nothing to do here :)
}
int robot_isDetectingObstacle() {
	return 0;
}
void robot_displayText(int line, char* text) {
	printf("%d : %s\n",line,text);
}
int robot_isButtonPressed(int button) {
	return 0;
}
void robot_setLedStatus(int status) {
	printf("LED STATUS : %d\n",status);
}
void robot_initPID() {
	motion_configureAlphaPID(0.0002400f, 0.001f, 0.000000f);
	//motion_configureDeltaPID(0.0002950f, 0.0f, 0.000001f);
	motion_configureDeltaPID(0.0003000f, 0.0001f, 0.000000f);
}
void robot_setMotorASpeed(int speed) {

}
void robot_setMotorDSpeed(int speed) {

}
#endif
