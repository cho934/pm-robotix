
task main()
{
	// Preparation
	nPidUpdateInterval = 10;
	nPidUpdateInterval12V = 10;
	nPidUpdateIntervalNxt = 10;
	nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
	nMaxRegulatedSpeed12V = 750;
	nVolume = 4;

	StartTask(endTimer,9); //reset


	// Execution
	moveForward(50);
	turn(90);





}
