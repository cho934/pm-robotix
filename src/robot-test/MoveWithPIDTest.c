/**
 * MoveWithPIDTest.c
 *
 *
 */
#include "../common/SpeedManager.h"


task main()
{
	//Display
  nxtDisplayCenteredTextLine(0, "PMX robot-test");
  nxtDisplayCenteredBigTextLine(1, "MOTOR");
  nxtDisplayCenteredTextLine(3, "MotorWithPID");

	// Configuration Motor
	nPidUpdateInterval = 10;
	nPidUpdateInterval12V = 10;
	nPidUpdateIntervalNxt = 10;
	nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg; //RIGHT
	nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg; //LEFT
	nMaxRegulatedSpeed12V = 750;








	// Execution

	//decrBSpeedAtStart = 3;
	moveForward(-300);
	//turn(90);
	//decrBSpeedAtStart = 3;
	//moveForward(10);


	motor[motorA] = 0;//TODO Stop()
	motor[motorC] = 0;
	// End
}
