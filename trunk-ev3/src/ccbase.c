/*
 * ccbase.c
 *
 *  Created on: Apr 27, 2014
 *      Author: maillard
 */
#include "ccbase.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "robot.h"

#include "mcontrol/motion.h"
#include "mcontrol/encoder.h"
#include "mcontrol/robot_odometry.h"
#include "log.h"
#include "mcontrol/global.h"
#include "mcontrol/path_manager.h"
boolean ignoreCollision = FALSE;

void launchAndWait(RobotCommand* cmd) {
	checkRobotCommand(cmd);
	path_LaunchTrajectory(cmd);
	printf("path_WaitEndOfTrajectory\n");
	int result = path_WaitEndOfTrajectory();
	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result, TRAJ_OK);
	free(cmd);
}

// if distance <0, move backward
void cc_move(float distanceInMM) {
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = distanceInMM / 1000.0f;
	motion_Line(cmd, meters);
	printf("Loading line command for %f mm (%f meters)\n", distanceInMM,
			meters);
	launchAndWait(cmd);
}

void cc_moveForwardTo(float x, float y) {
	float dx = x - cc_getX();
	float dy = y - cc_getY();
	float aRadian = atan2(dy, dx);
	cc_rotateTo((aRadian * 180.0f) / M_PI);
	float dist = sqrt(dx * dx + dy * dy);
	cc_move(dist);

}
void cc_moveForwardAndRotateTo(float x, float y, float thetaInDegree) {
	cc_moveForwardTo(x, y);
	cc_rotateTo(thetaInDegree);
}
void cc_moveBackwardTo(float x, float y) {
	float dx = x - cc_getX();
	float dy = y - cc_getY();
	float aRadian = atan2(dy, dx);
	cc_rotateTo(M_PI + (aRadian * 180.0f) / M_PI);
	float dist = sqrt(dx * dx + dy * dy);
	cc_move(-dist);
}
void cc_moveBackwardAndRotateTo(float x, float y, float thetaInDegree) {
	cc_moveBackwardTo(x, y);
	cc_rotateTo(thetaInDegree);
}
void cc_rotateLeft(float degrees) {
	cc_rotateRight(-degrees);
}
void cc_rotateRight(float degrees) {
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float rad = (degrees * M_PI) / 180.0f;
	motion_Rotate(cmd, rad);
	printf("Loading rotate command %f degrees (%f rad)\n", degrees, rad);
	launchAndWait(cmd);
}

void cc_rotateTo(float thetaInDegree) {
	float currentThetaInDegree = cc_getThetaInDegree();
	float delta = thetaInDegree - currentThetaInDegree;
	float turn = ((int) (delta * 1000.0f) % 360) / 1000.0f;
	cc_rotateRight(turn);
}

// position x,x in mm
float cc_getX() {
	RobotPosition p = odo_GetPosition();
	return p.x;
}
float cc_getY() {
	RobotPosition p = odo_GetPosition();
	return p.y;
}
// angle in radian
float cc_getTheta() {
	RobotPosition p = odo_GetPosition();
	return p.theta;
}
// angle in radian
float cc_getThetaInDegree() {
	RobotPosition p = odo_GetPosition();
	return (p.theta * 180.0f) / M_PI;
}

void cc_setIgnoreCollision(boolean b) {
	ignoreCollision = b;
}

boolean cc_collisionOccured() {
	return FALSE;
}

void cc_setMirrorCoordinates(boolean b) {

}
