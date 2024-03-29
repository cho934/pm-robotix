#include "../cpp/Md25.hpp"
#include "encoder.h"

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
#include "robot_trajectory.h"
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

	//printf("Init time %ld\n", currentTimeInMillis());
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
	pmx
	::Robot &robot = pmx::Robot::instance();
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
	/*
	 pmx
	 ::Robot &robot = pmx::Robot::instance();
	 long leftCounter = -1 * robot.encoderLeft().readCounter();

	 return leftCounter;*/
	return 0;
}
long robot_getRightExternalCounter()
{
	/*
	 pmx
	 ::Robot &robot = pmx::Robot::instance();
	 long rightCounter = robot.encoderRight().readCounter();

	 return rightCounter;
	 */
	return 0;
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
	if (!useExternalEncoders) //INTERNAL ENCODERS
	{
printf("\n!!!! robot_initPID\n");
		//Pid RCVA
		//motion_configureAlphaPID(760.0f, 0.0f, 0.002f);
		motion_configureAlphaPID(130.0f, 0.0f, 0.0002f);

		motion_configureDeltaPID(160.0f, 0.0f, 0.03f);

		motion_configureLeftPID(0.0006f, 0.0f, 0.0f);
		motion_configureRightPID(0.0006f, 0.0f, 0.0f);

		/*//pid standardf
		 motion_configureAlphaPID(0.0009f, 0.00003f, 0.0f);
		 motion_configureDeltaPID(0.0005f, 0.0002f, 0.00000004f);
		 //motion_configureAlphaPID(0.0009f, 0.00003f, 0.0f); //0.0015f, 0.0002f, 0.000002f
		 //motion_configureDeltaPID(0.0006f, 0.0002f, 0.0f); //0.0003f, 0.0009f, 0.0f

		 motion_configureLeftPID(0.0006, 0.0, 0.0);
		 motion_configureRightPID(0.0006, 0.0, 0.0);
		 */
	}
	else //EXTERNAL ENCODERS
	{
		exit(0);
		/*
		 motion_configureAlphaPID(0.000065f, 0.00001f, 0.00000002f); //(0.000065f, 0.000001f, 0.00000001f);
		 motion_configureDeltaPID(0.00006f, 0.00002f, 0.0000002f);

		 //motion_configureLeftPID(0.0004, 0.0004, 0.0000002);
		 //motion_configureRightPID(0.0004, 0.0004, 0.0000002);

		 motion_configureLeftPID(0.00003, 0.00004, 0.0000002);
		 motion_configureRightPID(0.00003, 0.00004, 0.0000002);*/
	}

	//printf("\n debug pid values %f %f %f", motion_GetDefaultSpeed(), motion_GetDefaultAccel(), motion_GetDefaultDecel());

}
void robot_initPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd)
{
	printf("\n!!!! robot_initPID_AD\n");
	motion_configureAlphaPID(Ap, Ai, Ad);
	motion_configureDeltaPID(Dp, Di, Dd);
}

void robot_initPID_LR(float Lp, float Li, float Ld, float Rp, float Ri, float Rd)
{
	motion_configureLeftPID(Lp, Li, Ld);
	motion_configureRightPID(Rp, Ri, Rd);
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
