#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)

#ifndef _NXT
#define _NXT // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "cnxt.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#include "cnxt.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#ifndef _DEBUG__
#include "cdebug.c"
#endif
#ifndef _CONFIG_H_
#include "cconfig.h"
#endif
#ifndef __HTANG_H__
#include "drivers/hitechnic-angle.h"
#endif
#ifndef __TMR_H__
#include "drivers/timer.h"
#endif
#ifndef _MOTION
#include "cmotion.c"
#endif
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
static long nxtSamplingPeriodMs;
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

void nxt_InitPIDSpeedCtrl()
{
	// Configuration Speed PID on each motor
	nPidUpdateInterval = 10; // A good interval is 20.
	nPidUpdateInterval12V = 10;
	nPidUpdateIntervalNxt = 10;
	nMotorPIDSpeedCtrl[MOTOR_LEFT] = mtrSpeedReg; //RIGHT
	nMotorPIDSpeedCtrl[MOTOR_RIGHT] = mtrSpeedReg; //LEFT
	nMaxRegulatedSpeed12V = 750;
}

void nxt_startMotionITTask(short motionPriority, long motionSamplingPeriodMs)
{
	//PlayTone(784, 20);
	PlaySound(soundShortBlip);
	nxtSamplingPeriodMs = motionSamplingPeriodMs;
	StartTask(nxt_motionTask, motionPriority);
}

void nxt_stopMotionITTask()
{
	//PlayTone(784, 20);
	StopTask(nxt_motionTask);
	PlaySound(soundShortBlip);
	while(bSoundActive) EndTimeSlice();
}

task nxt_motionTask()
{
	#if(LEVEL_NXT <= DEBUG)
	writeDebugStreamLine("Executing nxt_motionTask.");
	#endif

	// Create Timer
	int TMRmotion = TMRnewTimer();
	// Configure timer
	TMRsetup(TMRmotion, nxtSamplingPeriodMs);
	// Reset and start timer
	TMRreset(TMRmotion);
	while(1)
	{
		// If timer expires, make a small noise and reset it.
		if (TMRisExpired(TMRmotion))
		{
			//PlayTone(784, 20);
			//PlaySound(soundShortBlip);
			//while(bSoundActive) EndTimeSlice();

			motion_Compute();
			TMRreset(TMRmotion);
		}

		EndTimeSlice();
	}
}

void nxt_ResetAngleEncoder()
{
	HTANGresetAccumulatedAngle(HTANG_LEFT);
	HTANGresetAccumulatedAngle(HTANG_RIGHT);
}

void nxt_ResetMotorEncoder()
{
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
}

long nxt_ReadAngleEncoderLeft()
{
	long htangL = HTANGreadAccumulatedAngle(HTANG_LEFT); //en pas = degre
	if(htangL == -1)
	{
		#if(LEVEL_NXT <= ERROR)
		writeDebugStreamLine("cnxt.c ERROR HTANGreadAccumulatedAngle HTANG_LEFT");
		#endif
		//return -1;
	}
	return -htangL;
}
long nxt_ReadAngleEncoderRight()
{
	long htangR = HTANGreadAccumulatedAngle(HTANG_RIGHT); //en pas = degre //signe invers mcanique oblige
	if(htangR == -1)
	{
		#if(LEVEL_NXT <= ERROR)
		writeDebugStreamLine("cnxt.c ERROR HTANGreadAccumulatedAngle HTANG_RIGHT");
		#endif
		//return -1;
	}
	return htangR;
}

long nxt_ReadMotorEncoderLeft()
{
	return -nMotorEncoder[MOTOR_LEFT];
}
long nxt_ReadMotorEncoderRight()
{
	return -nMotorEncoder[MOTOR_RIGHT];
}

void nxt_ApplyMotorLeft(int orderLeft)
{
	motor[MOTOR_LEFT] = -orderLeft;
}
void nxt_ApplyMotorRight(int orderRight)
{
	motor[MOTOR_RIGHT] = -orderRight;
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "cnxt.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note			 tests the nxt functions and determine the way of each encoder.
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{
		initDebug();

		nxt_ResetAngleEncoder();
		nxt_ResetMotorEncoder();

		nxt_ApplyMotorLeft(10);
		nxt_ApplyMotorRight(10);

		while (1)
		{
			long hleft = nxt_ReadAngleEncoderLeft();
			long hright = nxt_ReadAngleEncoderRight();

			long mleft = nxt_ReadMotorEncoderLeft();
			long mright = nxt_ReadMotorEncoderRight();

			writeDebugStreamLine("hleft:%d, hright:%d, mleft:%d, mright:%d", hleft, hright, mleft, mright);
			Sleep(300);
		}
	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
