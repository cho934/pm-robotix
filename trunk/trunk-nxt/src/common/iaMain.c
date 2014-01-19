#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Sensor, S2,     TOUCH_SENSOR,    sensorTouch)
#pragma config(Sensor, S3,     SONAR,          sensorSONAR)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MOTOR_PUSH,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)


#ifndef _IAMAIN__
#define _IAMAIN__ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "iaMain.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#include "iaMain.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#include "crobotTrajWrappers.c"
#include "iaDecisionMaker.c"
#include "pmSensors.c"
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES

TRAJ_STATE ts;
bool engageOponentDetection = false;

// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES
void ia_Init()
{
	// Initialize odometry, depending on the robot's position
	if (pmInitColor == PM_INIT_COLOR_BLUE) {
		odo_SetPosition(0.079, 1.684, 0);
	} else {
		odo_SetPosition(2.921, 1.684, PI);
	}
	// Init decisionMaker
	dm_init();
}

void ia_start()
{
	StartTask(iaTask, 5);
}

task iaTask()
{
	nMotorEncoder[MOTOR_PUSH] = 0;
	motion_DoLine(0.05);
	int canrun = 1;
	float x1, y1, theta1;
	while (canrun == 1) {
		odo_GetPositionXYTheta(&x1, &y1, &theta1);
		writeDebugStreamLine("iaMain.c : taking new decision");
		dm_takeDecision(x1, y1, theta1);
		if (!ia_actions_isEmpty)
		{
			ia_actions_end = false;
			writeDebugStreamLine("iaMain.c : Starting the execution of tasks");
			StartTask (iaActionsExecute, 5);
			while (!ia_actions_end)
			{
				if (sensorFrontOponentDetected && engageOponentDetection)
				{
					writeDebugStreamLine("iaMain.c : Oponent detected, stoping the execution");
					int remainingDetectionOccurences = IA_TIME_OF_OPONENT_WAIT;
					StopTask(iaActionsExecute);
					// Stops the engines
					nxt_stopMotionITTask();
					motor[MOTOR_PUSH] = 0;
					motor[MOTOR_LEFT] = 0;
					motor[MOTOR_RIGHT] = 0;
					nVolume = 4;
		      PlaySoundFile("wally.rso");
		      while(SensorValue(sonar)<20){}
		      while (bSoundActive){}
		      nVolume = 1;
					while (remainingDetectionOccurences > 0 && sensorFrontOponentDetected)
					{
						remainingDetectionOccurences--;
						wait1Msec(IA_PERIOD_OF_OPONENT_WAIT);
					}
					//TODO2014 interfacer !
					nxt_startMotionITTask(5, valueSample * 1000);
					if (sensorFrontOponentDetected)
					{
						writeDebugStreamLine("iaMain.c : Oponent detected too long, taking a new decision");
						ia_actions_end = true;
					} else {
						writeDebugStreamLine("iaMain.c : Oponent moved, trying to reexecute the decision");
						StartTask (iaActionsExecute, 5);
					}
				}
				wait1Msec(100);
				EndTimeSlice();
			}
			engageOponentDetection = false;
		} else {
			writeDebugStreamLine("iaMain.c : No decision took. Waiting one second");
			wait1Msec(1000);
		}
		EndTimeSlice();
	}
}

task iaActionsExecute()
{
	float x1, y1, theta1;
	ACTION_TYPE actionType;
	float actionValue, actionTurnValue, actionMoveValue;
	while (!ia_actions_end) {
		odo_GetPositionXYTheta(&x1, &y1, &theta1);
		dm_actionsNext(&actionType, &actionValue, &actionTurnValue, &actionMoveValue, x1, y1, theta1);
		writeDebugStreamLine("iaMain.c : action returned");
		if (actionType != ACTION_TYPE_END)
		{
			if (actionType == ACTION_TYPE_MOVE){
				writeDebugStreamLine("iaMain.c : Action Pile: moving %f", actionValue);
				EndTimeSlice();
				engageOponentDetection = true;
				ts = motion_DoLine(actionValue);
				engageOponentDetection = false;
			} else if (actionType == ACTION_TYPE_MOVE_NO_DETECT){
				writeDebugStreamLine("iaMain.c : Action Pile: moving %f (without detection)", actionValue);
				EndTimeSlice();
				ts = motion_DoLine(actionValue);
			} else if (actionType == ACTION_TYPE_TURN){
				writeDebugStreamLine("iaMain.c : Action Pile: turning %f", actionValue);
				EndTimeSlice();
				ts = motion_DoRotate(actionValue);
			} else if (actionType == ACTION_TYPE_TURN_TO_ANGLE){
				writeDebugStreamLine("iaMain.c : Action Pile: turning %f", actionValue);
				EndTimeSlice();
				ts = motion_DoRotate(actionValue);
			} else if (actionType == ACTION_TYPE_TURN_AND_MOVE){
				writeDebugStreamLine("iaMain.c : Action Pile: Turning %f, and moving %f", actionTurnValue, actionMoveValue);
				EndTimeSlice();
				ts = motion_DoRotate(actionTurnValue);
				engageOponentDetection = true;
				ts = motion_DoLine(actionMoveValue);
				engageOponentDetection = false;
			} else if (actionType == ACTION_TYPE_TURN_AND_MOVE_NO_DETECT){
				//writeDebugStreamLine("iaMain.c : Turning %f, and moving %f (without detection)", actionTurnValue, actionMoveValue);
				EndTimeSlice();
				ts = motion_DoRotate(actionTurnValue);
				ts = motion_DoLine(actionMoveValue);
			} else if (actionType == ACTION_TYPE_PUSH){
				int target;
				if (actionValue == 0)
				{
					target = 180 - nMotorEncoder[MOTOR_PUSH];
				} else {
					target = 0 - nMotorEncoder[MOTOR_PUSH];
				}
				//writeDebugStreamLine("iaMain.c : Pushing %f. Current position = %f, target = %f", actionValue, nMotorEncoder[MOTOR_PUSH], target);
				if (target != 0)
				{
					nMotorEncoderTarget[MOTOR_PUSH] = target;
					if (target > 0)
					{
						motor[MOTOR_PUSH] = 75;
					} else {
						motor[MOTOR_PUSH] = -75;
					}
					while(nMotorRunState[MOTOR_PUSH] != runStateIdle){}
					motor[MOTOR_PUSH] = 0;
				}
			} else {
				//writeDebugStreamLine("ERROR iaMain.c : Action Pile: unknown action type");
			}
			dm_actionsFinishCurrentAction();
		} else {
			//writeDebugStreamLine("iaMain.c : End of actions. Finishing the decision.");
			dm_actionsFinishCurrentDecision();
			ia_actions_end = true;
		}
	}
}
// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS
#if(PROJECT_MAIN_FILE == "iaMain.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------

	task main()
	{
		/*
		//motion_Init();
		writeDebugStreamLine("iaMain.c : testing");
		// Setting init values to standard test ones
		pmInitIA = PM_INIT_IA_TABLE_TEST;
		pmInitColor = PM_INIT_COLOR_BLUE;
		// Launches the IA
		ia_Init();
		ia_start();
    wait1Msec(90000);
		writeDebugStreamLine("iaMain.c : testing END");
		*/
		int target[5];
		target[0] = 90;
		target[1] = 180;
		target[2] = 360;
		target[3] = -90;
		target[4] = 1;

		nMotorEncoder[MOTOR_PUSH] = 0;

		for (int ii=0; ii<5; ii++)
		{
			//writeDebugStreamLine("Moving to %i", target[ii]);
			nMotorEncoderTarget[MOTOR_PUSH] = target[ii];
			if (nMotorEncoder[MOTOR_PUSH] < target[ii])
			{
				motor[MOTOR_PUSH] = 75;
			} else if (nMotorEncoder[MOTOR_PUSH] > target){
				motor[MOTOR_PUSH] = -75;
			}
			while(nMotorRunState[MOTOR_PUSH] != runStateIdle){}
			motor[MOTOR_PUSH] = 0;
			//writeDebugStreamLine("after %i: %f", target[ii], nMotorEncoder[MOTOR_PUSH]);
			wait1Msec(3000);
		}
	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
