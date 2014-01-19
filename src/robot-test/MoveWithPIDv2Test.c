
#include "../common/PidBrett2.h"
#include "drivers/timer.h"

// Action
#define ACT_NONE 0
#define ACT_FORWARD 1
#define ACT_BACKWARD -1
#define ACT_TURN_RIGHT 2
#define ACT_TURN_LEFT -2

// Config
#define MOTOR_LEFT motorA
#define MOTOR_RIGHT motorC
int maxSpeed = 85;
int minSpeed = 5;
float maxAcceleration = 2.0;

// Working values
bool arrived;
int distTickTargetLeft = 0;
int oldSpeedLeft = 0;
int action = ACT_NONE;

// Functions
void PIDExecute();


task main()
{

  // Setup PID speed
  nPidUpdateInterval = 10; //Interval (in milliseconds) to use for motor PID updates.(Default is 25)
  //nPidUpdateInterval12V = 10;
  nPidUpdateIntervalNxt = 10;
  nMotorPIDSpeedCtrl[MOTOR_LEFT] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[MOTOR_RIGHT] = mtrSpeedReg;
  nMaxRegulatedSpeedNxt = 500; //Specifies the maximum speed, in encoder counts per second, that should be used for speed regulation on the NXT.  (Default is 1000)

	// Setup PID position
	PIDSetSampleTime(100); //ms
	PIDSetOutputLimits(minSpeed, maxSpeed);
	PIDSetMode(AUTOMATIC);

  //PIDSetTunings(0.2, 0.0, 0.0);
	PIDSetTunings(20.0, 100.0, 100.0);

  // Create Timer
  int timer1 = TMRnewTimer();
  // Configure timer1 for 2000ms
  TMRsetup(timer1, 100);
  // Reset and start both timers
  TMRreset(timer1);

  nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
	arrived = false;

  distTickTargetLeft = 100;

  if(distTickTargetLeft < 0){
    action = ACT_BACKWARD;
    PIDSetControllerDirection(REVERSE);
    writeDebugStreamLine("Moving backward (%dmm = %dticks)", 0, distTickTargetLeft);
  }else{
    action = ACT_FORWARD;
    PIDSetControllerDirection(DIRECT);
    writeDebugStreamLine("Moving forward (%dmm = %dticks)", 0, distTickTargetLeft);
  }


  while(!arrived)
	{
    // If timer1 expires, make a small noise and reset it.
    if (TMRisExpired(timer1))
    {
      PlaySound(soundShortBlip);
      PIDExecute();
      //while(bSoundActive) EndTimeSlice();
      TMRreset(timer1);
    }

    EndTimeSlice();
  }

  //Stop motors
  motor[MOTOR_LEFT] = 0;
	motor[MOTOR_RIGHT] = 0;



}


void PIDExecute()
{

	// ====================
	// = MOTOR MOTOR_LEFT =
	// ====================
/*
	// Remaining distance for motor B
	int distanceLeft = distanceTargetLeft-nMotorEncoder[MOTOR_LEFT];
	// DEBUG
	debug_ErrorLeft = distanceLeft;
	// Get the order for motor B from the PID
	float orderB = PidCompute(distanceB);
*/


	//===PID en position
	int distLeft = distTickTargetLeft - nMotorEncoder[MOTOR_LEFT];
	PIDSetInputs(nMotorEncoder[MOTOR_LEFT], distTickTargetLeft);
	PIDCompute();

	// Limit Speed
	//if(Output > maxSpeed) { Output = maxSpeed; }
	//if(Output < -maxSpeed) { Output = -maxSpeed; }

	// Limit acceleration
	if(action!=ACT_BACKWARD ) { Output = 0.0+oldSpeedLeft+maxAcceleration; }
	if(action==ACT_BACKWARD ) { Output = 0.0+oldSpeedLeft-maxAcceleration; }


	motor[MOTOR_LEFT] = Output;
	oldSpeedLeft = Output;

	//writeDebugStreamLine("%d, %d, %d, %d, %d", action, nMotorEncoder[MOTOR_LEFT], Output, nMotorEncoder[MOTOR_RIGHT], 0);
	writeDebugStreamLine("%d, %d",distTickTargetLeft ,nMotorEncoder[MOTOR_LEFT]);

/*
	// Limit Speed
	if(orderB > maxSpeed) { orderB = maxSpeed; }
	if(orderB < -maxSpeed) { orderB = -maxSpeed; }
	// Limit acceleration
	if(action!=ACT_BACKWARD && orderB - currentSpeedB > maxAcceleration) { orderB = 0.0+currentSpeedB+maxAcceleration; }
	if(action==ACT_BACKWARD && orderB - currentSpeedB < -maxAcceleration) { orderB = 0.0+currentSpeedB-maxAcceleration; }
	// Avoid null speed
	if((action==ACT_FORWARD || action==ACT_TURN_LEFT) && orderB < minSpeed)
	{
		orderB = minSpeed;
	}
	if(action==ACT_BACKWARD && orderB > -minSpeed)
	{
		orderB = -minSpeed;
	}
	// Prepare order
	currentSpeedB = orderB;

	// ===========
	// = MOTOR C =
	// ===========

	// Remaining distance for motor C
	int distanceC = distanceTargetC-nMotorEncoder[motorC];
	// DEBUG
	debug_ErrorC = distanceC;
	// Get the order for motor B from the PID
	float orderC = PidCompute(distanceC);

	// Limit acceleration
	if(action!=ACT_BACKWARD && orderC - currentSpeedC > maxAcceleration) { orderC = 0.0+currentSpeedC+maxAcceleration; }
	if(action==ACT_BACKWARD && orderC - currentSpeedC < -maxAcceleration) { orderC = 0.0+currentSpeedC-maxAcceleration; }
	// Limit Speed
	if(orderC > maxSpeed) { orderC = maxSpeed; }
	if(orderC < -maxSpeed) { orderC = -maxSpeed; }
	// Avoid null speed

	//if(orderC>0 && orderC < minSpeed) { orderC = minSpeed; }
	//if(orderC<0 && orderC > -minSpeed) { orderC = -minSpeed; }

	if((action==ACT_FORWARD || action==ACT_TURN_RIGHT) && orderC < minSpeed)
	{
		orderC = minSpeed;
	}
	if(action==ACT_BACKWARD && orderC > -minSpeed)
	{
		orderC = -minSpeed;
	}

	// Prepare order
	currentSpeedC = orderC;


	// =======
	// = LOG =
	// =======
	// writeDebugStreamLine("execTime, motorB_real, motorC_real, motorB_order, motorC_order");
	//string toDisplay =
	//writeDebugStreamLine("%d, %d, %d, %d, %d, %d", action, time1[T2], nMotorEncoder[motorB], nMotorEncoder[motorC], currentSpeedB, currentSpeedC);

	// ==================
	// = EXECUTE ORDERS =
	// ==================
	motor[motorA] = currentSpeedB;
	motor[motorC] = currentSpeedC;

	// ========================
	// = Order stop of motors =
	// ========================
	if(action == ACT_FORWARD && distanceB < nbTicksToStopAsserv && distanceC < nbTicksToStopAsserv){arrived = true;}
	if(action == ACT_BACKWARD && distanceB > -nbTicksToStopAsserv && distanceC > -nbTicksToStopAsserv){arrived = true;}
	if(action == ACT_TURN_RIGHT && distanceC < nbTicksToStopAsserv){arrived = true;}
	if(action == ACT_TURN_LEFT && distanceB < nbTicksToStopAsserv){arrived = true;}*/

	// ========================
	// = Order stop of motors =
	// ========================

}
