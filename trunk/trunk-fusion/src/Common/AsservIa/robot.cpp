#include "robot.hpp"

#include <stdio.h>
#include <sys/time.h>

#include "../../Bot-SmallPMX/SAsservExtended.hpp"
#include "../../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Asserv/EncoderControl.hpp"
#include "encoder.h"
#include "global.h"
#include "motion.h"

int running = 1;

long long timeOffset;

long tLeft;
long tRight;

int lPower;
int rPower;

long rightCounter;
long leftCounter;

//#include "../Asserv/EncoderControl.hpp"

/*

 //long c_getL(struct EncoderControl* p);
 long c_getL(struct EncoderControl * p)
 {
 return call_EncoderControl_getLeftEncoder(p);
 }

 */

int robot_getLeftPower()
{
	return lPower;
}
int robot_getRightPower()
{
	return rPower;
}

long currentTimeInMillis()
{
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = (te.tv_sec * 1000LL + te.tv_usec / 1000); // calculate milliseconds
	return (long) (milliseconds - timeOffset);
}

int robot_isRunning()
{
	if (running > 0)
	{
		if (robot_isEmergencyPressed())
		{
			running = 0;
		}
	}
	return running;
}

//asserv setup
void robot_init()
{
	tLeft = 0;
	tRight = 0;

	rightCounter = 0;
	leftCounter = 0;

	/*
	 //TODO reset external encoder
	 pmx::Robot &robot = pmx::Robot::instance();
	 robot.encoderLeft().clearCounter();
	 robot.encoderRight().clearCounter();

	 //reset internal encoder
	 robot.md25().setCommand(MD25_RESET_ENCODERS);
	 */

	robot_resetEncoders();

	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	timeOffset = (te.tv_sec * 1000LL + te.tv_usec / 1000);

	//TODO config à déporter
	defaultSamplingFreq = 100; // en Hz (cad combien de fois par seconde)
	valueSample = 0.01f; //(1f/DEFAULT_SAMPLING_FREQ)
	vtopsPerTicks = 2048;
	maxPwmValue = 900; //128 default
	defaultVmax = 0.9f; // 0.9
	defaultAcc = 0.3f; //0.3
	defaultDec = 0.3f; //0.05

	//printf("Init time %ld\n", currentTimeInMillis());
}

void robot_setMotorRightSpeed(int power) //-900 à 900
{
	SRobotExtended &robot = SRobotExtended::instance();
	robot.asserv().motors().runMotorRight(power, 0);
}

void robot_setMotorLeftSpeed(int power)
{
	SRobotExtended &robot = SRobotExtended::instance();
	robot.asserv().motors().runMotorLeft(power, 0);

}

long robot_getLeftExternalCounter() //en tick
{

	return 0;
}
long robot_getRightExternalCounter()
{

	return 0;
}

long robot_getLeftInternalCounter()
{
	long encoder = 0;

	SRobotExtended &robot = SRobotExtended::instance();
	encoder = robot.asserv().encoders().getLeftEncoder();

	return encoder;
}
long robot_getRightInternalCounter()
{
	long encoder = 0;

	SRobotExtended &robot = SRobotExtended::instance();
	encoder = robot.asserv().encoders().getRightEncoder();

	return encoder;
}

void robot_resetEncoders()
{
	SRobotExtended &robot = SRobotExtended::instance();
	robot.asserv().encoders().reset();

}

void robot_initPID()
{
	//internal encoder
	//motion_configureAlphaPID(0.0015f, 0.0008f, 0.000002f); //0.0008 0.00002 0.00003
	//motion_configureDeltaPID(0.0015f, 0.0008f, 0.000002f); //0.0005 0.000008 0.000009 //0.0015 0.0008 0.000002
	motion_configureAlphaPID(0.010, 0.0005, 0.000005); //0.0008 0.00002 0.00003
	motion_configureDeltaPID(0.006, 0.0, 0.0); //0.0005 0.000008 0.000009 //0.0015 0.0008 0.000002

	motion_configureLeftPID(0.0006, 0.0, 0.0);
	motion_configureRightPID(0.0006, 0.0, 0.0);

}
void robot_initPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd)
{
	motion_configureAlphaPID(Ap, Ai, Ad);
	motion_configureDeltaPID(Dp, Di, Dd);
}

void robot_initPID_LR(float Lp, float Li, float Ld, float Rp, float Ri, float Rd)
{
	motion_configureLeftPID(Lp, Li, Ld);
	motion_configureRightPID(Rp, Ri, Rd);
}

int robot_isEmergencyPressed()
{
	return 0;
}

void robot_displayText(int line, char* text)
{
	printf("%d : %s\n", line, text);
}

void robot_setLedStatus(int status)
{
	printf("LED STATUS : %d\n", status);
}

