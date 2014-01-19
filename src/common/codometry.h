#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTION_CALIBRATION_H_
#include "cmotionCalibration.h"
#endif
//#ifndef _POSITION_H_
//#include "cposition.h"
//#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//every N period, we compute precise values for
//cos and sin of the robot angle
#define PRECISE_COMPUTATION_NTH_PERIOD		64

#ifndef M_2PI
#define M_2PI	(2*PI)
#endif

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! \brief Compute robot position using odometry
//!
//! \param dTheta displacement (rotation) of the robot in radian
//! \param dV displacement (forward) of the robot in vTops
void odo_Integration(float dTheta, float dV);

//! \brief Set robot position used by odometry
//!
//! \param dL vTops elapsed on left encoder since last integration
//! \param dR vTops elapsed on right encoder since last integration
void odo_SetPosition(float x, float y, float theta);

//! \brief Get current odometry robot position
//!
//! \param x [out] Robot position on x axis in meters
//! \param y [out] Robot position on y axis in meters
//! \param theta [out] Robot orientation in radians ]-Pi..Pi]
void odo_GetPositionXYTheta(float *x, float *y, float *theta);

//! \brief Get current odometry robot position
//!
//! \return Robot position in meters and angle in radian
//RobotPosition odo_GetPosition(void);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif //_ROBOT_ODOMETRY_H_
