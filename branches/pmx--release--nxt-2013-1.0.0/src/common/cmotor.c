#ifndef _MOTOR
#define _MOTOR // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "cmotor.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTOR_H_
#include "cmotor.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
//! motors used for motion (left / right and virtual alpha / delta)
MOTOR motors[MAX_MOTION_CONTROL_TYPE_NUMBER][MOTOR_PER_TYPE];
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#include "cpid.c"
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

void initMotor(MOTOR *motor)
{
	int i;
	motor->PIDSys = pid_Create();
	motor->lastPos = 0;
	motor->posIndex = 0;

	for(i=0; i<MOTOR_SPEED_PERIOD_NB; i++)
	{
		motor->prevPos[i] = 0;
	}
}

void motors_ConfigAllIMax(long imax)
{
	int i,j;
	for(i=0; i<(int)MAX_MOTION_CONTROL_TYPE_NUMBER; i++)
		for(j=0; j<MOTOR_PER_TYPE; j++)
		pid_ConfigIMax(motors[i][j].PIDSys, imax);
}

void updateMotor(MOTOR *motor, long delta)
{
	//update position
	motor->lastPos += delta;

	#if(LEVEL_MOTOR <= DEBUG)
	writeDebugStreamLine("cmotor.c : updateMotor : delta=%d  motor->lastPos=%d  ", delta, motor->lastPos);
	#endif

	//store new value
	motor->prevPos[motor->posIndex] = motor->lastPos;

	//increment position table index
	motor->posIndex++;
	if(motor->posIndex >= MOTOR_SPEED_PERIOD_NB)
	{
		motor->posIndex = 0;
	}
}

long getMotorSpeed(MOTOR *motor)
{
	//motor->posIndex is always the index of the oldest position
	//so speed is the difference of current position and oldest
	long speed = (motor->lastPos - motor->prevPos[motor->posIndex]) / (MOTOR_SPEED_PERIOD_NB-1);
	//CORRECT_DELTA_OVERFLOW(speed, MAX_ENCODER_ABS_VTOPS);

	return speed;
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "cmotor.c")
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
