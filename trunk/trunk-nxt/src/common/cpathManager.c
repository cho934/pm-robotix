#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)

#ifndef _PATH_MANAGER
#define _PATH_MANAGER // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "cpathManager.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _PATH_MANAGER_H_
#include "cpathManager.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
WAYPOINT nextWaypoint;
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#ifndef _MOTION
#include "cmotion.c"
#endif
#ifndef _ROBOT_TRAJECTORY
#include "crobotTrajectory.c"
#endif
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
//bool waitingSemaphore;
//static OS_EVENT *semWaypoint;
//TSemaphore  semWaypoint;
static TRAJ_STATE trajState;
static bool waiting;
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

//collision handler
//static HANDLED ex_defaultCollisionCallback(void)
//{
//	motion_FreeMotion();

//	if(waitingSemaphore)
//	{
//		path_TriggerWaypoint(TRAJ_COLLISION);
//	}

//	LOG_DEBUG("Collision Handler...");
//	return IT_HANDLED;
//}


void path_Init()
{
	waiting = true;

	//REGISTER_LOG_CLIENT("PATH");

	//waitingSemaphore = FALSE;
	//semWaypoint = OSSemCreate(0);
	//if(semWaypoint == NULL)
	//{
	//	LOG_ERROR("Unable to create waypoint semaphore");
	//}



//TODO Gerer les collision
	//ex_PushITHandler(COLLISION, ex_defaultCollisionCallback);
	//ex_PushITHandler(APPROACHING_COLLISION, ex_defaultCollisionCallback);
}

void path_SetNextWaypoint(WAYPOINT *wp)
{
	nextWaypoint = *wp;
}

//! Trigger the current waypoint
//! motion control internal function
void path_TriggerWaypoint(TRAJ_STATE state)
{
	if(nextWaypoint.type != WP_NOT_SET)
	{
		trajState = state;
		//OSLastError = OSSemPost(semWaypoint);
		//LOG_TEST_OS_ERROR(OSLastError);

		waiting = false;
		// release the semaphore if we have it
		//if(bDoesTaskOwnSemaphore(semWaypoint))
  //  	SemaphoreUnlock(semWaypoint);
	}
}

TRAJ_STATE path_WaitWaypoint()
{
	if(RobotMotionState == TRAJECTORY_RUNNING)
	{
		//! Wait for waypoint semaphore
		//waitingSemaphore = true;

		//OSSemPend(semWaypoint, 0, &OSLastError);
		//LOG_TEST_OS_ERROR(OSLastError);

		//SemaphoreLock(semWaypoint);
		//if ( bDoesTaskOwnSemaphore(semWaypoint) )
		//{

		waiting = true;
		while (waiting)
		{
			Sleep(5);
			EndTimeSlice();
		}

		//waitingSemaphore = false;

		//if(OSLastError == 0)
			return trajState;
		//else
		//	return TRAJ_ERROR;
			//}else
			//{
			//	return TRAJ_ERROR;
			//}
	}
	else
	{
		return TRAJ_ERROR;
	}
}

TRAJ_STATE path_WaitEndOfTrajectory()
{
	WAYPOINT eot;
	eot.type = WP_END_OF_TRAJ;
	path_SetNextWaypoint(&eot);

	return path_WaitWaypoint();
}

TRAJ_STATE path_WaitEndOfTrajectoryType(WAYPOINT_TYPE type)
{
	WAYPOINT eot;
	eot.type = type;
	path_SetNextWaypoint(&eot);

	return path_WaitWaypoint();
}

void path_LaunchTrajectory(RobotCommand *traj)
{
	//OSSemSet(semWaypoint, 0, &OSLastError);
	//LOG_TEST_OS_ERROR(OSLastError);

	// Init the semaphore
	//SemaphoreInitialize(semWaypoint);
	//SemaphoreLock(semWaypoint);

	motion_SetCurrentCommand(traj);
}

void path_CancelTrajectory()
{
	//if(waitingSemaphore)
	//{
		motion_FreeMotion();
		path_TriggerWaypoint(TRAJ_CANCELLED);
	//}
}

void path_InterruptTrajectory()
{
	//if(waitingSemaphore)
	//{
		motion_FreeMotion();
		path_TriggerWaypoint(TRAJ_INTERRUPTED);
	//}
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "cpathManager.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{


	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
