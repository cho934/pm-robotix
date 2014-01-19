#ifndef _ROBOT_TRAJ_WRAPPERS_H_
#define _ROBOT_TRAJ_WRAPPERS_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _ROBOT_TRAJECTORY_H_
#include "crobotTrajectory.h"
#endif
#ifndef _PATH_MANAGER_H_
#include "cpathManager.h"
#endif
#include "cposition.h"
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//! macro that translate movement for arc circle trajectory
#define motion_DoArcLeftForward(angle, radius) motion_DoArcRotate(fabs(angle), fabs(radius))
#define motion_DoArcRightForward(angle, radius) motion_DoArcRotate(-fabs(angle), -fabs(radius))
#define motion_DoArcLeftBackward(angle, radius) motion_DoArcRotate(-fabs(angle), fabs(radius))
#define motion_DoArcRightBackward(angle, radius) motion_DoArcRotate(fabs(angle), -fabs(radius))

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! This module provide higher level control on the motion control module
//! AI and strategy software can use this primitives directly

//! Compute and launch trajectory
//! \sa motion_Line
TRAJ_STATE motion_DoLine(float dist);

//! Compute and launch trajectory
//! \sa motion_Rotate
TRAJ_STATE motion_DoRotate(float angle);

//! Compute and launch trajectory
//! \sa motion_ArcRotate
TRAJ_STATE motion_DoArcRotate(float angle, float radius);

//! Compute the displacement needed on alpha and delta to reach the point x2, y2
//! from the point x1, y1 starting with the orientation theta1
void computeAlphaDelta(float x1, float y1, float theta1, float x2, float y2, float *out_angle, float *out_dist);

float math_atan2f(float y, float x);

//! Goto (x2,y2) from (x1,y1,theta1) using Turn-Stop-Line motion
TRAJ_STATE motion_GoToTSLFrom(float x1, float y1, float theta1, float x2, float y2);

//! Goto (x,y) using Turn-Stop-Line motion
TRAJ_STATE motion_GoToTSL(float x, float y);

//! Goto (x,y) using speed motion
TRAJ_STATE motion_GoToSpeed(float x, float y);

//! Goto a list of (x,y) position using speed motion
TRAJ_STATE motion_GoToSpeedPath(Position *pos, int nb);

//! Orient toward the given angle
TRAJ_STATE motion_OrientTo(float angle);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_ROBOT_TRAJ_WRAPPERS_H_
