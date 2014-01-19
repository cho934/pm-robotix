
#ifndef _MOTION_PRIV_H_
#define _MOTION_PRIV_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
//#include "motor_PID.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//! Macro that correct integer overflow for a difference of two value
//! typically when you calculate an error using error = new-old, and new has overflowed
//! the macro substract or add the maximum value if needed to compensate the overflow of new
#define CORRECT_DELTA_OVERFLOW(value, max_value) {if((value)>(max_value/2))value-=max_value; else if((value)<(-(max_value/2)))value+=max_value;}

//! Macro that bound an integer to a maximum absolute value
//! for instance :
//! BOUND_INT(i, 100) with i==143 set i=100
//! BOUND_INT(i, 100) with i==-160 set i=-100
//! BOUND_INT(i, 100) with i==-16 set i=-16
#define BOUND_INT(value, max_abs) {if(value>max_abs)value=max_abs; else if(value<-max_abs)value=-max_abs;}

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//different kind of command generation
typedef enum
{
	POSITION_COMMAND,
	SPEED_COMMAND,
	STEP_COMMAND,
} MOTOR_COMMAND_TYPE;

//different kind of command interpretation (virtual motors)
typedef enum
{
	LEFT_RIGHT,
	ALPHA_DELTA,
	MAX_MOTION_CONTROL_TYPE_NUMBER,
} MOTION_CONTROL_TYPE;

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_MOTION_PRIV_H_
