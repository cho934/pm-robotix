#ifndef SIMULATED

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "robot.h"
#include "motion.h"
#include "../cpp/Robot.hpp"

/**
 * APF
 **/
long long timeOffset;

long tLeft;
long tRight;

int lPower;
int rPower;

long rightCounter;
long leftCounter;

//asserv setup
void robot_init()
{
	tLeft = 0;
	tRight = 0;

	rightCounter = 0;
	leftCounter = 0;
	/*
	 //reset external encoder
	 pmx::Robot &robot = pmx::Robot::instance();
	 robot.encoderLeft().clearCounter();
	 robot.encoderRight().clearCounter();

	 //reset internal encoder
	 robot.md25().setCommand(MD25_RESET_ENCODERS);
	 */
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	timeOffset = (te.tv_sec * 1000LL + te.tv_usec / 1000);

	printf("Init time %ld\n", currentTimeInMillis());
}

/*
 void computeCounterL() {
 long deltaT= currentTimeInMillis()- tLeft;
 leftCounter+= (deltaT*lPower )/25;

 }
 void computeCounter() {
 long deltaT= currentTimeInMillis()- tRight;
 rightCounter+= (deltaT*rPower )/25;
 }

 */
void robot_stopMotorRight()
{

	pmx
	::Robot &robot = pmx::Robot::instance();
	robot.md25().stopMotor(MD25_SPEED1_REG);

}
void robot_stopMotorLeft()
{

	pmx
	::Robot &robot = pmx::Robot::instance();
	robot.md25().stopMotor(MD25_SPEED2_REG);

}

void robot_setMotorRightSpeed(int power) //-100 à 100
{

	pmx
	::Robot &robot = pmx::Robot::instance();
	/*
	int powerR = (int) (((-power + 100) * 256.0 / 200.0));*/
	int powerR = (int) (-power + 128);
	if (powerR >= 256)
		powerR = 255;
	//printf("robot_setMotorRightSpeed.c %d\n", powerR);
	robot.md25().ensureSetSpeed(powerR, MD25_SPEED1_REG); //0=>255
	rPower = power;
	tRight = currentTimeInMillis();
}

void robot_setMotorLeftSpeed(int power)
{
	pmx::Robot &robot = pmx::Robot::instance();
	/*
	int powerL = (int) (((-power + 100) * 256.0 / 200.0));
	if (powerL == 256)
		powerL = 255;
		*/
	int powerL = (int) (-power + 128);
	if (powerL >= 256)
			powerL = 255;
	//printf("robot_setMotorLeftSpeed.c %d\n", powerL);
	robot.md25().ensureSetSpeed(powerL, MD25_SPEED2_REG); //0=>255
	lPower = power;
	tLeft = currentTimeInMillis();
}

long robot_getLeftExternalCounter() //en tick
{

	pmx
	::Robot &robot = pmx::Robot::instance();
	int leftCounter = -robot.encoderLeft().readCounter();

	return leftCounter;
}
long robot_getRightExternalCounter()
{

	pmx
	::Robot &robot = pmx::Robot::instance();
	int rightCounter = robot.encoderRight().readCounter();

	return rightCounter;
}

long robot_getLeftInternalCounter()
{
	long encoder = 0;

	pmx
	::Robot &robot = pmx::Robot::instance();
	encoder = (-1 * robot.md25().ensureGetEncoder(0, MD25_ENCODER2_REG));

	return encoder;
}
long robot_getRightInternalCounter()
{
	long encoder = 0;

	pmx
	::Robot &robot = pmx::Robot::instance();
	encoder = (-1 * robot.md25().ensureGetEncoder(0, MD25_ENCODER1_REG));

	return encoder;
}

void robot_initPID()
{
	motion_configureAlphaPID(0.0015f, 0.0008f, 0.000002f); //0.0008 0.00002 0.00003
	motion_configureDeltaPID(0.0010f, 0.0008f, 0.000002f); //0.0005 0.000008 0.000009 //0.0015 0.0008 0.000002
}
void robot_initPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd)
{
	motion_configureAlphaPID(Ap, Ai, Ad);
	motion_configureDeltaPID(Dp, Di, Dd);
}

int robot_isDetectingObstacle()
{
	return 0;
}

void robot_dispose()
{
}
void robot_startMotorLeft()
{
}
void robot_startMotors()
{
}

void robot_waitStart()
{
	// nothing to do here :)
}
int robot_isButton1Pressed()
{
	return 0;
}
int robot_isEmergencyPressed()
{
	return 0;
}
void robot_displayText(int line, char* text)
{
	printf("%d : %s\n", line, text);
}
int robot_isButtonPressed(int)
{
	return 0;
}
void robot_setLedStatus(int status)
{
	printf("LED STATUS : %d\n", status);
}

#endif
