/**
 * MoveWithPIDv3Test.c
 *
 *
 */
#include "../common/SpeedManagerv3.h"


task main()
{
	//Display
  nxtDisplayCenteredTextLine(0, "PMX robot-test");
  nxtDisplayCenteredBigTextLine(1, "MOTOR");
  nxtDisplayCenteredTextLine(3, "MotorWithPID");

	// Configuration Speed PID
	nPidUpdateInterval = 10; // A good interval is 20.
	nPidUpdateInterval12V = 10;
	nPidUpdateIntervalNxt = 10;
	nMotorPIDSpeedCtrl[MOTOR_LEFT] = mtrSpeedReg; //RIGHT
	nMotorPIDSpeedCtrl[MOTOR_RIGHT] = mtrSpeedReg; //LEFT
	nMaxRegulatedSpeed12V = 750;

  // Configuration Position PID
	setPidValues(&pidPosition, 0.4, 0.0003, 0.01);
	//setPidOutputLimits(&pidPosition, MAXSPEED, MINSPEED);

	// Execution
	moveForward(-200);

	//moveForward(10);


	motor[MOTOR_LEFT] = 0;//TODO Stop()
	motor[MOTOR_RIGHT] = 0;
	// End
}
