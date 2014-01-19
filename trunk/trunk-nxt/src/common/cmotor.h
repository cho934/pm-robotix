#ifndef _MOTOR_H_
#define _MOTOR_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _PID_H_
#include "cpid.h"
#endif

#ifndef _MOTION_PRIV_H_
#include "cmotion_priv.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//LEFT - RIGHT
#define LEFT_MOTOR		0
#define RIGHT_MOTOR		1
//ALPHA - DELTA (virtual motors)
#define ALPHA_MOTOR		0
#define DELTA_MOTOR		1
//Two motors per set
#define MOTOR_PER_TYPE	2
//Number of period used to compute motor speed
#define MOTOR_SPEED_PERIOD_NB		9

//! structure used internally for stocking current value for each motors
typedef struct
{
	PID_SYSTEM PIDSys;
	long lastPos;

	int posIndex;
	long prevPos[MOTOR_SPEED_PERIOD_NB];	//previous value of position for speed computation
} MOTOR;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! initialisation of the motor structure
void initMotor(MOTOR *motor);
//config iMax for all motors
void motors_ConfigAllIMax(long imax);
//! update motor position and store value for speed computation
void updateMotor(MOTOR *motor, long delta);
//! Compute current motor speed
long getMotorSpeed(MOTOR *motor);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_MOTOR_H_
