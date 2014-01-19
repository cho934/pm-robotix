#ifndef _PATH_MANAGER_H_
#define _PATH_MANAGER_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
//#ifndef _MOTION_H_
//#include "cmotion.h"
//#endif
#ifndef _ROBOT_TRAJECTORY_H_
#include "crobotTrajectory.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

typedef enum
{
	WP_NOT_SET,				//no waypoint set for the moment
	WP_POS_ALPHA_SUPERIOR,	//waypoint triggered when alpha value is above threshold value
	WP_POS_ALPHA_INFERIOR,	//waypoint triggered when alpha value is below threshold value
	WP_POS_DELTA_SUPERIOR,	//waypoint triggered when delta value is above threshold value
	WP_POS_DELTA_INFERIOR,	//waypoint triggered when delta value is below threshold value
	WP_END_OF_TRAJ,			//waypoint when both motor command are finished
} WAYPOINT_TYPE;

//! structure used to represent trajectory waypoint
typedef struct
{
	WAYPOINT_TYPE type;
	long threshold;
} WAYPOINT;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

void path_Init(void);

void path_TriggerWaypoint(TRAJ_STATE state);

//! Set the next waypoint
void path_SetNextWaypoint(WAYPOINT *wp);

//! \brief Wait for the current waypoint
//!
//! You must have called path_SetNextWaypoint before
TRAJ_STATE path_WaitWaypoint(void);

//! \brief Wait for the end of the current trajectory
//!
//! This is an utility function that call
//! path_SetNextWaypoint and path_WaitWaypoint()
TRAJ_STATE path_WaitEndOfTrajectory(void);

//! Execute trajectory, this is an asynchronous call
void path_LaunchTrajectory(RobotCommand *traj);

//! Cancel the current trajectory and stop the robot
//!
//! Mostly needed for remote control, use collision function
//! when a collision is detected.
void path_CancelTrajectory(void);

//! Interrupt current trajectory and stop robot
//!
//! Used to stop on a particular event (for instance actuator event)
void path_InterruptTrajectory(void);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_PATH_MANAGER_H_
