
/*
 * ccbase.h
 *
 *  Created on: Apr 27, 2014
 *      Author: maillard
 */

#ifndef CCBASE_H_
#define CCBASE_H_

/* Some useful constants.  */




#include "global.h"
#include "path_manager.h"
#include "robot_trajectory.h"

TRAJ_STATE launchAndWait(RobotCommand* cmd);

// if distance <0, move backward
TRAJ_STATE cc_move(float distanceInMM);

TRAJ_STATE cc_moveForwardTo(float x, float y);
TRAJ_STATE cc_moveForwardAndRotateTo(float x, float y, float thetaInDegree);
TRAJ_STATE cc_moveBackwardTo(float x, float y);
TRAJ_STATE cc_moveBackwardAndRotateTo(float x, float y, float thetaInDegree);

TRAJ_STATE cc_rotateLeft(float degres);
TRAJ_STATE cc_rotateRight(float degres);
TRAJ_STATE cc_rotateTo(float theta);

//x,y en mm
void cc_setPosition(float xMM, float yMM, float theta,int color);
float cc_getRelativeX(float x);
// position x,x in mm
float cc_getX();
float cc_getY();
// angle in degree
float cc_getThetaInDegree();
// angle in radian
float cc_getTheta();

void cc_setIgnoreFrontCollision(boolean b);
void cc_setIgnoreRearCollision(boolean b);
void cc_collisionOccured(int front);

void cc_setMatchColor(int color);
int cc_getMatchColor();

void cc_AssistedHandling();

void cc_setMirrorCoordinates(boolean b);

TRAJ_STATE cc_goToZone(const char *zoneName);

#endif
