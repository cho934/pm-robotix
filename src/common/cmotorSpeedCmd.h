#ifndef _MOTOR_SPEED_ORDER_H_
#define _MOTOR_SPEED_ORDER_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//possible phase of a speed trajectory :
typedef enum
{
	SP_PRE_PHASE,			//trajectory not yet started
	SP_ACCEL_PHASE,			//acceleration (or deceleration) phase to reach goal speed
	SP_CONSTANT_PHASE,		//motor has reached final speed
	SP_END_PHASE,			//trajectory ended
} SPEED_PHASE;

//precomputed values defining the complete trajectory
typedef struct
{
	SPEED_PHASE phase;		//current phase
	long order0;			//motor position at trajectory start
	long period0;			//nb of period at the start of trajectory
	long period1;			//nb of period at end of acceleration (deceleration)
	long period2;			//nb of period at end of trajectory
	long Acceleration;		//acceleration used in movement in vTops/sample/sample
	long V0;				//start speed in vTops/sample
	long VGoal;			//goal speed in vTops/sample
	long lastOrder;		//current ordered position of motor
} SpeedCommand;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! \brief Create a trajectory for one motor with a trapezoidal speed curve
//!
//! The trajectory start with a speed='V0' then accelerate with a rate of
//! 'Accel' until it reaches speed='VGoal', then when the total ran distance
//! is equal to distMax, the motor stops.
//!
//! \param out_command Result of the computation
//! \param V0 Speed at the start of the command
//! \param VGoal Speed to attain in vTops/sample
//! \param distMax Maximum distance to run in vTops
//! \param Accel Acceleration in vTops/sample^2
void ComputeSpeedCommand( SpeedCommand *out_cmd,
long V0,
long VGoal,
long distMax,
long Accel);

//! \brief Create a trajectory for one motor with a trapezoidal speed curve
//!
//! The trajectory start with a speed='V0' then accelerate with a rate of
//! 'Accel' during 'Time' periods
//!
//! \param out_command Result of the computation
//! \param V0 Speed at the start of the command
//! \param Time Number of period of the acceleration
//! \param Accel Acceleration in vTops/sample^2
void ComputeSpeedCommandTime( SpeedCommand *out_cmd,
long V0,
long Time,
long Accel);

//! \brief Create a trajectory for one motor with a trapezoidal speed curve
//!
//! The trajectory start with a speed='V0' then accelerate with a rate of
//! 'Accel' but stop after 'Time' periods
//!
//! \param out_command Result of the computation
//! \param V0 Speed at the start of the command
//! \param Time Number of period of the acceleration
//! \param Accel Acceleration in vTops/sample^2
void ComputeSpeedCommandMaxTime( SpeedCommand *out_cmd,
long V0,
long VGoal,
long Accel,
long Time);

//! Configure the command for the current configuration of the motor.
//! You must execute this function before you launch the command.
//! \param out_cmd Result of the computation
//! \param lastPos Last position of motor
//! \param periodNb Current integration period number
void LoadSpeedCommand( SpeedCommand *out_cmd, long lastPos, long periodNb);

//! \brief Compute the current order to apply on motor
//!
//! \param motor Id number of motor
//! \param PeriodN Motion control period number
//! \param order Output of the computation
//! \return Is the path completed ?
bool GetSpeedOrder(SpeedCommand *speedCmd, long PeriodN, long *out_order);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_MOTOR_SPEED_ORDER_H_
