#ifndef _MOTOR_POSITION_ORDER_H_
#define _MOTOR_POSITION_ORDER_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTOR_H_
#include "cmotor.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//possible phase of a position trajectory :
typedef enum
{
	TR_PRE_PHASE,			//trajectory not yet started
	TR_ACCEL_PHASE,			//0 - acceleration phase to reach goal speed
	TR_CONSTANT_PHASE,		//1 - motor has reached final speed
	TR_DECEL_PHASE,			//2 - deceleration phase before reaching goal position
	TR_END_PHASE,			//3 - motor has reached desired position
} TRAJ_PHASE;

//precomputed values defining the complete trajectory
typedef struct
{
	TRAJ_PHASE phase;		//current phase
	long period0;     		//period number of the start of trajectory
	long order0;			//motor position at trajectory start
	long VMax;				//goal speed in vTops/sample
	long order3;			//goal position
	long T01;				//number of sample between accel and constant phase
	long T12;				//number of sample between contant and decel phase
	long T23;				//number of sample between decel and end phase
	long Acceleration;		//acceleration used in movement in vTops/sample/sample
	long Deceleration;		//deceleration used in movement in vTops/sample/sample
	long lastOrder;		//current ordered position of motor
} PositionCommand;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! \brief Create a trajectory for one motor with a trapezoidal speed curve
//!
//! The trajectory start with a speed=0 then accelerate at a rate equal to
//! 'Accel' until it reaches speed='VMax' before the end of the path
//! the wheel decelerate with a rate of 'Decel' then stop.
//!
//! \param motor Id number of motor on wich to apply the trajectory
//! \param out_command Result of the computation
//! \param dist Distance to run in meters
//! \param VMax Maximum speed at the wheel in meters/second
//! \param Accel Acceleration in meters/second^2
//! \param Decel Deceleration in meters/second^2
void ComputePositionCommand (PositionCommand *out_cmd,
long dist,
long VMax,
long Accel,
long Decel);

//! Configure the command for the current configuration of the motor.
//! You must execute this function before you launch the command.
//! \param out_command Result of the computation
//! \param motor Id number of motor on wich to apply the trajectory
void LoadPositionCommand (PositionCommand *out_cmd, MOTOR *motor, long periodNb);

//! \brief Compute the current order to apply on motor
//!
//! \param motor Id number of motor
//! \param posCommand The command that will be interpreted
//! \param Tn Motion control period number
//! \param out_Order Result of the computation
//! \return Is the path completed ?
bool GetPositionOrder(PositionCommand *posCmd,
long Tn,
long *out_Order);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_MOTOR_POSITION_ORDER_H_
