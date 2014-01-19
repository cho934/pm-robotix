/**
 * SpeedManager.h
 *
 *
 */

#ifndef _PMX_SPEEDMANAGER_H__
#define _PMX_SPEEDMANAGER_H__

#pragma systemFile

#ifndef _PMX_PID_H__
#include "Pid.h"
#endif


// Robot mechanical values
const float wheelDiameter = 82; //mm
const float distancePerTick = 1.0*wheelDiameter*PI/360;
const float entrax = 137; //mm
// Asserv values
float asservPeriod = 100.0; //ms
// Distance to move on
int distanceTargetB = 0; // Tick
int distanceTargetC = 0; // Tick
// Movement working values
int currentSpeedB = 0;
int currentSpeedC = 0;
int arrived = false;
// Action
int ACT_NONE = 0;
int ACT_FORWARD = 1;
const int ACT_BACKWARD = -1;
const int ACT_TURN_RIGHT = 2;
const int ACT_TURN_LEFT = -2;
int action = ACT_NONE;
// Main program structure
bool killMe = false; //TODO kill speedManager
// Debug values
int debugger = 0;
int debug_ErrorB = 0;
int debug_ErrorC = 0;
int nbCorrect = 0;
// Motor configuration
int maxSpeed = 85;
int minSpeed = 5;
//int maxAccelerationInPercPerSecond = 20; // (percent of max speed per seconds)
//float maxAcceleration = 1.0*maxAccelerationInPercPerSecond*asservPeriod/1000.0;
float maxAcceleration = 5.0;

// Nb ticks for stop position
int nbTicksToStopAsserv = 0;


// Functions
int mmToTicks(int mm);
int degToTicks(int deg);
void executePID();
void timerAsservStd();
void moveForward(int distanceMm);
task timerAsservStdTask();

void moveForward(int distanceMm)
{
  if(distanceMm==0 || killMe){return;}
  ClearTimer(T2); // Used for logs only
  PidReset();
  distanceTargetB = 0;
	distanceTargetC = 0;
	currentSpeedB = 0;
	currentSpeedC = 0;
	action = ACT_NONE;
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorC] = 0;

  distanceTargetB = mmToTicks(distanceMm);
  distanceTargetC = distanceTargetB;
  if(distanceMm < 0){
    action = ACT_BACKWARD;
    writeDebugStreamLine("Moving backward (%dmm = %dticks)", distanceMm, distanceTargetB);
  }else{
    action = ACT_FORWARD;
    writeDebugStreamLine("Moving forward (%dmm = %dticks)", distanceMm, distanceTargetB);
  }
  arrived = false;
  StartTask(timerAsservStdTask,10);
  while(!arrived){
    wait1Msec(asservPeriod);
    //if(SensorValue(touchSensor) == 1){arrived=true; killMe=true;}
  }
  wait1Msec(300);
}

void timerAsservStd()
{
	writeDebugStreamLine("Starting asserv, CSV:");
	while(!arrived)
	{
		//debugger = SensorValue(sonar);
		ClearTimer(T1);
		// execute task
		//PlayTone(784, 20);
		PlaySound(soundBlip);
		executePID();
		if(!arrived)
		{
			// wait remaining time
			int remaining = asservPeriod - time1[T1];
			if(remaining > 0) {
				wait1Msec(remaining);
				if(action != ACT_BACKWARD ) //&& SensorValue(sonar)<=limitForOponentStop
				{
					currentSpeedB = 0;
					currentSpeedC = 0;
					motor[motorA] = currentSpeedB;
					motor[motorC] = currentSpeedC;


					//while(SensorValue(sonar)<=limitForOponentStop && !arrived){} //Attente en cas de presence adverse
				}
			}
		}
	}
}



void executePID()
{

	// ===========
	// = MOTOR B =
	// ===========

	// Remaining distance for motor B
	int distanceB = distanceTargetB-nMotorEncoder[motorA];
	// DEBUG
	debug_ErrorB = distanceB;
	// Get the order for motor B from the PID
	float orderB = PidCompute(distanceB);

	// Limit acceleration
	if(action!=ACT_BACKWARD && orderB - currentSpeedB > maxAcceleration) { orderB = 0.0+currentSpeedB+maxAcceleration; }
	if(action==ACT_BACKWARD && orderB - currentSpeedB < -maxAcceleration) { orderB = 0.0+currentSpeedB-maxAcceleration; }
	// Limit Speed
	if(orderB > maxSpeed) { orderB = maxSpeed; }
	if(orderB < -maxSpeed) { orderB = -maxSpeed; }
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
	/*
	if(orderC>0 && orderC < minSpeed) { orderC = minSpeed; }
	if(orderC<0 && orderC > -minSpeed) { orderC = -minSpeed; }
	*/
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
	if(action == ACT_TURN_LEFT && distanceB < nbTicksToStopAsserv){arrived = true;}
}

int mmToTicks(int mm)
{
  return (int)(1.0*mm/distancePerTick);
}

int degToTicks(int deg)
{
  return mmToTicks((1.0*deg/360.0)*(2.0*PI*entrax));
}

task timerAsservStdTask()
{
	timerAsservStd();
}

#endif
