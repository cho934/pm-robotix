/*
 * ccbase.h
 *
 *  Created on: Apr 27, 2014
 *      Author: maillard
 */

#ifndef CCBASE_H_
#define CCBASE_H_

#include "global.h"
// if distance <0, move backward
void cc_move(float distanceInMM);

void cc_moveForwardTo(float x, float y);
void cc_moveForwardAndRotateTo(float x, float y, float thetaInDegree);
void cc_moveBackwardTo(float x, float y);
void cc_moveBackwardAndRotateTo(float x, float y, float thetaInDegree);

void cc_rotateLeft(float degres);
void cc_rotateRight(float degres);
void cc_rotateTo(float theta);

// position x,x in mm
float cc_getX();
float cc_getY();
// angle in degree
float cc_getThetaInDegree();
// angle in radian
float cc_getTheta();

void cc_setIgnoreCollision(boolean b);
boolean cc_collisionOccured();

void cc_setMirrorCoordinates(boolean b);

void cc_goToZone(const char *zoneName);

#endif
