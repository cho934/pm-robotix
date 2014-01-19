/**
* FindPowerToSpeedTest.c
*
*
*/

#define PERIOD_ASSERV 100 //ms
#define MOTOR_LEFT motorA
#define MOTOR_RIGHT motorC
// Robot mechanical values
#define WHEEL_DIAMETER 80 //mm
#define DIST_PER_TICK 1.0*WHEEL_DIAMETER*PI/360.0 //mm
#define ENTRAX 137 //mm

static int lastEncoderLeft = 0;
static int lastEncoderRight = 0;


task main()
{
	//Display
	nxtDisplayCenteredTextLine(0, "PMX robot-test");
	nxtDisplayCenteredBigTextLine(1, "MOTOR");
	nxtDisplayCenteredTextLine(3, "FindPowerToSpeed");
	writeDebugStreamLine("PMX robot-test | MOTOR | FindPowerToSpeed");


	//Motor
	nMotorPIDSpeedCtrl[MOTOR_LEFT] = mtrNoReg;
	nMotorPIDSpeedCtrl[MOTOR_RIGHT] = mtrNoReg;
	//reset encoder
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
	writeDebugStreamLine("incrementation 0->100 every %d ms",PERIOD_ASSERV);
	writeDebugStreamLine("MotorCode,vitesseTickLeft,vitesseMsLeft,vitesseTickRight,vitesseMsRight");


	for(int i = 1; i < 100; i++)
	{

		motor[MOTOR_LEFT] = i;
		motor[MOTOR_RIGHT] = i;

		wait1Msec(PERIOD_ASSERV);

		//log
		int encoderLeft = nMotorEncoder[MOTOR_LEFT];
		int encoderRight = nMotorEncoder[MOTOR_RIGHT];

		int vitesseTickLeft = encoderLeft - lastEncoderLeft;
		int vitesseTickRight = encoderRight - lastEncoderRight;

		float vitesseMsLeft = (vitesseTickLeft * DIST_PER_TICK * 1000.0) / (PERIOD_ASSERV * 1.0); //en mm/s
		float vitesseMsRight = (vitesseTickRight * DIST_PER_TICK * 1000.0) / (PERIOD_ASSERV * 1.0); //en mm/s


		writeDebugStreamLine("%d,%d,%.2f,%d,%.2f,", i, vitesseTickLeft, vitesseMsLeft, vitesseTickRight, vitesseMsRight);


		lastEncoderLeft = encoderLeft;
		lastEncoderRight = encoderRight;


	}
}
