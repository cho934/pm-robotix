#ifndef _MOTION_CALIBRATION_H_
#define _MOTION_CALIBRATION_H_

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _CONFIG_H_
#include "cconfig.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

typedef enum
{
	MOTOR_ENCODER,
	EXTERNAL_ENCODER,
}ODOMETRY_SENSOR;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! Initialization of the motion calibration module
void motion_CalibrationInit(void);
//! Set motion control sampling frequency and recompute value of sample time
void motion_SetSamplingFrequency(unsigned int periodMs);
//! speed used for all robot motion by default
void motion_SetDefaultSpeed(float speed);
float motion_GetDefaultSpeed(void);
//! acceleration used for all robot motion by default
void motion_SetDefaultAccel(float accel);
float motion_GetDefaultAccel(void);
//! deceleration used for all robot motion by default
void motion_SetDefaultDecel(float decel);
float motion_GetDefaultDecel(void);
// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif //_MOTION_CALIBRATION_H_
