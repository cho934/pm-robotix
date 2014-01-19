/**
* MoveWithPIDPolarTest.c
*
*
*/
#pragma platform(NXT)
#include "../common/SpeedManagerPolar.h"


task main()
{
	//Display
	nxtDisplayCenteredTextLine(0, "PMX robot-test");
	nxtDisplayCenteredBigTextLine(1, "MOTOR");
	nxtDisplayCenteredTextLine(3, "MotorWithPIDPolar");
	writeDebugStreamLine("PMX robot-test | MOTOR | MotorWithPIDPolar");

	//// Configuration Speed PID on each motor
	//nPidUpdateInterval = 10; // A good interval is 20.
	//nPidUpdateInterval12V = 10;
	//nPidUpdateIntervalNxt = 10;
	//nMotorPIDSpeedCtrl[MOTOR_LEFT] = mtrSpeedReg; //RIGHT
	//nMotorPIDSpeedCtrl[MOTOR_RIGHT] = mtrSpeedReg; //LEFT
	//nMaxRegulatedSpeed12V = 750;

	// Configuration PID
	setPidValues(&pidRotation, 0.4, 0.005, 0.0);//1.5 0.2
	setPidValues(&pidDistance, 0.4, 0.005, 0.0);

	// GO
	moveNxtWithBrake(1200.0, 0.0, 7.0 / (100.0 / PERIOD_ASSERV));


}
