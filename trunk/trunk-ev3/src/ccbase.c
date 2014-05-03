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

void cc_moveForwardTo(float xMM, float yMM) {
	float dx = xMM - cc_getX();
	float dy = yMM - cc_getY();

	float aRadian = atan2(dy, dx);

	printf("cc_moveForwardTo:(%f,%f) -> (%f,%f) : DX,DY: %f %f -> rotate %f\n",
			cc_getX(), cc_getY(), xMM, yMM, dx, dy, aRadian);

	cc_rotateTo((aRadian * 180.0f) / M_PI);
	printf("cc_moveForwardTo AFTER ROTATE: (%f,%f) %f\n", cc_getX(), cc_getY(),
			cc_getThetaInDegree());
	float dist = sqrt(dx * dx + dy * dy);
	printf("cc_moveForwardTo MOVE FORWARD: %f\n", dist);
	cc_move(dist);
	printf("cc_moveForwardTo AFTER MOVE: (%f,%f) %f\n", cc_getX(), cc_getY(),
			cc_getThetaInDegree());
}
void cc_moveForwardAndRotateTo(float xMM, float yMM, float thetaInDegree) {
	cc_moveForwardTo(xMM, yMM);
	cc_rotateTo(thetaInDegree);
}
void cc_moveBackwardTo(float xMM, float yMM) {
	float dx = xMM - cc_getX();
	float dy = yMM - cc_getY();
	float aRadian = atan2(dy, dx);
	cc_rotateTo(M_PI + (aRadian * 180.0f) / M_PI);
	float dist = sqrt(dx * dx + dy * dy);
	cc_move(-dist);
}
void cc_moveBackwardAndRotateTo(float xMM, float yMM, float thetaInDegree) {
	cc_moveBackwardTo(xMM, yMM);
	cc_rotateTo(thetaInDegree);
}
void cc_rotateLeft(float degrees) {
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float rad = (degrees * M_PI) / 180.0f;
	motion_Rotate(cmd, rad);
	printf("Loading rotate command %f degrees (%f rad)\n", degrees, rad);
	launchAndWait(cmd);
}
void cc_rotateRight(float degrees) {
	cc_rotateLeft(-degrees);
}

void cc_rotateTo(float thetaInDegree) {
	float currentThetaInDegree = cc_getThetaInDegree();
	float delta = thetaInDegree - currentThetaInDegree;

	float turn = ((int) (delta * 1000.0f) % 360000) / 1000.0f;

	printf("delta in degrees:%f -> %f\n", delta, turn);
	cc_rotateLeft(turn);
}

// position x,x in mm
float cc_getX() {
	RobotPosition p = odo_GetPosition();
	return p.x * 1000.0f;
}
float cc_getY() {
	RobotPosition p = odo_GetPosition();
	return p.y * 1000.0f;
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
