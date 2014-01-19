/**
 * SpeedManagerv3.h
 *
 *
 */

#ifndef _PMX_SPEEDMANAGER_H__
#define _PMX_SPEEDMANAGER_H__

#pragma systemFile

#ifndef _PMX_PID_H__
#include "Pidv3.h"
#endif

#ifndef __TMR_H__
#include "drivers/timer.h"
#endif


// Robot mechanical values
#define WHEEL_DIAMETER 80 //mm
#define DIST_PER_TICK (1.0*WHEEL_DIAMETER*PI/360.0) //mm
#define ENTRAX 137 //mm
// Asserv period
#define PERIOD_ASSERV 75 //ms
// Speed Motor configuration
#define MOTOR_LEFT motorA
#define MOTOR_RIGHT motorC
#define MAXSPEED 85
#define MINSPEED 8
#define MAX_ACC 3
// Nb ticks for stop robot
#define NB_TICK_TO_STOP_ASSERV 1


// Asserv working values
#define ACT_NONE 0
#define ACT_FORWARD 1
#define ACT_BACKWARD -1
#define ACT_TURN_RIGHT 2
#define ACT_TURN_LEFT -2
static int distanceTargetLeft = 0; // Tick
static int distanceTargetRight = 0; // Tick
static int currentSpeedLeft = 0;
static int currentSpeedRight = 0;
static int arrived = false;
static int action = ACT_NONE;
static bool asservKillMe = false; //TODO kill speedManager
static PIDParams pidPosition;

// Functions
int mmToTicks(int mm);
int degToTicks(int deg);
void executePID();
void timerAsservStd();
void moveForward(int distanceMm);
task timerAsservStdTask();
void asservReset();

void asservReset()
{
	currentSpeedLeft = 0;
	currentSpeedRight = 0;
	action = ACT_NONE;
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
  arrived = false;
  distanceTargetLeft = 0;
  distanceTargetRight = 0;
}

void moveForward(int distanceMm)
{
  if(distanceMm==0 || asservKillMe){return;}
  //ClearTimer(T2); // Used for logs only ????

  //reset PID Position
  pidReset(&pidPosition);
  //reset asserv
  asservReset();

  distanceTargetLeft = mmToTicks(distanceMm);
  distanceTargetRight = distanceTargetLeft;
  if(distanceMm < 0){
    action = ACT_BACKWARD;
    //DEBUG
    writeDebugStreamLine("Moving backward (%dmm = %dticks)", distanceMm, distanceTargetLeft);
  }else{
    action = ACT_FORWARD;
    //DEBUG
    writeDebugStreamLine("Moving forward (%dmm = %dticks)", distanceMm, distanceTargetLeft);
  }

  StartTask(timerAsservStdTask, 10);
  while(!arrived)
  {
    wait1Msec(PERIOD_ASSERV);
  }


  //TODO : tuer la task timerAsservStdTask !!

}

void timerAsservStd()
{
	writeDebugStreamLine("Starting asserv, CSV:");

	// Create Timer
  int timerAsserv = TMRnewTimer();
  // Configure timerAsserv for 100ms
  TMRsetup(timerAsserv, PERIOD_ASSERV);
  // Reset and start timer
  TMRreset(timerAsserv);

	while(!arrived)
	{
		// If timerAsserv expires, make a small noise and reset it.
    if (TMRisExpired(timerAsserv))
    {
    	//PlayTone(784, 20);
      //PlaySound(soundShortBlip);
      //while(bSoundActive) EndTimeSlice();
      executePID();

      TMRreset(timerAsserv);
    }
    EndTimeSlice();
	}
}



void executePID()
{

	// ===========
	// = MOTOR LEFT =
	// ===========

	// Remaining distance for motor LEFT (ticks)
	int remainingDistLeft = distanceTargetLeft-nMotorEncoder[MOTOR_LEFT];
	// Get the order for motor LEFT from the PID
	float orderLeft = pidComputeOptimized(&pidPosition, nMotorEncoder[MOTOR_LEFT], remainingDistLeft);
	// Limit acceleration
	if(action!=ACT_BACKWARD && orderLeft - currentSpeedLeft > MAX_ACC) { orderLeft = 0.0+currentSpeedLeft+MAX_ACC; }
	if(action==ACT_BACKWARD && orderLeft - currentSpeedLeft < -MAX_ACC) { orderLeft = 0.0+currentSpeedLeft-MAX_ACC; }
	// Limit Speed
	if(orderLeft > MAXSPEED) { orderLeft = MAXSPEED; }
	if(orderLeft < -MAXSPEED) { orderLeft = -MAXSPEED; }
	// Avoid null speed
	if((action==ACT_FORWARD || action==ACT_TURN_LEFT) && orderLeft < MINSPEED)
	{
		orderLeft = MINSPEED;
	}
	if(action==ACT_BACKWARD && orderLeft > -MINSPEED)
	{
		orderLeft = -MINSPEED;
	}
	// Prepare order
	currentSpeedLeft = orderLeft;

	// ===========
	// = MOTOR RIGHT =
	// ===========

	// Remaining distance for motor RIGHT (ticks)
	int remainingDistRight = distanceTargetRight-nMotorEncoder[MOTOR_RIGHT];
	// Get the order for motor B from the PID
	float orderRight = pidComputeOptimized(&pidPosition, nMotorEncoder[MOTOR_RIGHT], remainingDistRight);
	// Limit acceleration
	if(action!=ACT_BACKWARD && orderRight - currentSpeedRight > MAX_ACC) { orderRight = 0.0+currentSpeedRight+MAX_ACC; }
	if(action==ACT_BACKWARD && orderRight - currentSpeedRight < -MAX_ACC) { orderRight = 0.0+currentSpeedRight-MAX_ACC; }
	// Limit Speed
	if(orderRight > MAXSPEED) { orderRight = MAXSPEED; }
	if(orderRight < -MAXSPEED) { orderRight = -MAXSPEED; }
	// Avoid null speed
	if((action==ACT_FORWARD || action==ACT_TURN_RIGHT) && orderRight < MINSPEED)
	{
		orderRight = MINSPEED;
	}
	if(action==ACT_BACKWARD && orderRight > -MINSPEED)
	{
		orderRight = -MINSPEED;
	}
	// Prepare order
	currentSpeedRight = orderRight;

	// =======
	// = LOG =
	// =======
	//writeDebugStreamLine("execTime, motorB_real, MOTOR_RIGHT_real, motorB_order, MOTOR_RIGHT_order");
	//string toDisplay =
	writeDebugStreamLine("%d, %d, %d, %d, %d, %d", action, nMotorEncoder[MOTOR_LEFT], nMotorEncoder[MOTOR_RIGHT], currentSpeedLeft, currentSpeedRight);
  writeDebugStreamLine("L: %d, %f  R: %d, %f", remainingDistLeft, orderLeft, remainingDistRight, orderRight );

	// ==================
	// = EXECUTE ORDERS =
	// ==================
	motor[MOTOR_LEFT] = currentSpeedLeft;
	motor[MOTOR_RIGHT] = currentSpeedRight;

	// ========================
	// = Order stop of motors =
	// ========================
	if(action == ACT_FORWARD && (remainingDistLeft < NB_TICK_TO_STOP_ASSERV || remainingDistRight < NB_TICK_TO_STOP_ASSERV)){arrived = true;}
	if(action == ACT_BACKWARD && (remainingDistLeft > -NB_TICK_TO_STOP_ASSERV || remainingDistRight > -NB_TICK_TO_STOP_ASSERV)){arrived = true;}
	if(action == ACT_TURN_RIGHT && remainingDistRight < NB_TICK_TO_STOP_ASSERV){arrived = true;}
	if(action == ACT_TURN_LEFT && remainingDistLeft < NB_TICK_TO_STOP_ASSERV){arrived = true;}

}

int mmToTicks(int mm)
{
  return (int)(1.0*mm/(DIST_PER_TICK));
}

int degToTicks(int deg)
{
  return mmToTicks((1.0*deg/360.0)*(2.0*PI*ENTRAX));
}

task timerAsservStdTask()
{
	timerAsservStd();
}

#endif
