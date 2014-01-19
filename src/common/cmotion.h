#ifndef _MOTION_H_
#define _MOTION_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _ROBOT_TRAJECTORY_H_
#include "crobotTrajectory.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

typedef enum
{
	TRAJECTORY_RUNNING,
	ASSISTED_HANDLING,
	FREE_MOTION,
	DISABLE_PID,
} MOTION_STATE;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//motion control task
void motion_Compute(); //remove param void *p_arg for NXT
void motion_InitTimer(int periodMs);
void initPWM(void);
void signalEndOfTraj(void);
//declaration of some internal function :
//void path_Init(void);
//void path_TriggerWaypoint(TRAJ_STATE state);
//! Load motion control module
void motion_Init(void);
//! Stop motion control for a moment
void motion_FreeMotion(void);
void resetAllPIDErrors(void);
//! Set a robot command and execute it
void motion_SetCurrentCommand(RobotCommand *cmd);
//! Stop motion control and disable PID
void motion_DisablePID(void);
//! Assisted movement mode =)
void motion_AssistedHandling(void);
//! Stop motion control timer, used to shutdown motion control
void motion_StopTimer(void);
//! Directly set the pwm for the motor (used both internally and for test)
void setPWM(int pwmLeft, int pwmRight);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif //_MOTION_H_
