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
#include "ia.h"
#include "motion.h"
#include "encoder.h"
#include "robot_odometry.h"
#include "log.h"
#include "global.h"
#include "path_manager.h"

int matchColor = 0; //0=default color of the match (yellow)
boolean ignoreFrontCollision = TRUE;
boolean ignoreRearCollision = TRUE;

float cc_getRelativeX(float x) {
	if (cc_getMatchColor() != 0) {
		return 3000 - x;
	}
	return x;
}
float cc_getRelativeAngle(float degrees) {
	if (cc_getMatchColor() != 0) {
		return 180 - degrees;
	}
	return degrees;
}
void cc_AssistedHandling() {
	motion_AssistedHandling();
}

TRAJ_STATE launchAndWait(RobotCommand* cmd) {
	checkRobotCommand(cmd);
	path_LaunchTrajectory(cmd);

	TRAJ_STATE result = path_WaitEndOfTrajectory();
	printf("path_WaitEndOfTrajectory returned : %d : TRAJ_OK=%d TRAJ_COLLISION=%d\n", result, TRAJ_OK, TRAJ_COLLISION);
	free(cmd);
	return result;
}

// if distance <0, move backward
TRAJ_STATE cc_move(float distanceInMM) {
	if (distanceInMM > 0) {
		ignoreRearCollision = TRUE;
	} else {
		ignoreFrontCollision = TRUE;
	}
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = distanceInMM / 1000.0f;
	motion_Line(cmd, meters);
	return launchAndWait(cmd);
}

TRAJ_STATE cc_moveForwardTo(float xMM, float yMM) {
	float dx = cc_getRelativeX(xMM) - cc_getX();
	float dy = yMM - cc_getY();
	float aRadian = atan2(dy, dx);
	TRAJ_STATE ts = cc_rotateTo(cc_getRelativeAngle((aRadian * 180.0f) / M_PI));
	float dist = sqrt(dx * dx + dy * dy);
	return cc_move(dist);
}
TRAJ_STATE cc_moveForwardAndRotateTo(float xMM, float yMM, float thetaInDegree) {
	TRAJ_STATE ts;
	ts = cc_moveForwardTo(xMM, yMM);
	if (ts != TRAJ_OK)
		return ts;
	//printf("thetaInDegree = %f\n", thetaInDegree);
	ts = cc_rotateTo(thetaInDegree);
	return ts;
}
TRAJ_STATE cc_moveBackwardTo(float xMM, float yMM) {
	if (cc_getMatchColor() != 0) {
		xMM = 3000 - xMM;
	}
	float dx = xMM - cc_getX();
	float dy = yMM - cc_getY(); //-500 -x = -900
	float aRadian = atan2(dy, dx);

	TRAJ_STATE ts = cc_rotateTo(cc_getRelativeAngle(((M_PI + aRadian) * 180.0f) / M_PI)); //TODO angle au plus court ?

	float dist = sqrt(dx * dx + dy * dy);
	return cc_move(-dist);
}
TRAJ_STATE cc_moveBackwardAndRotateTo(float xMM, float yMM, float thetaInDegree) {
	TRAJ_STATE ts;
	ts = cc_moveBackwardTo(xMM, yMM);
	if (ts != TRAJ_OK)
		return ts;
	ts = cc_rotateTo(thetaInDegree);
	return ts;
}
TRAJ_STATE cc_rotateAbs(float degrees) {
	int f = ignoreFrontCollision;
	int b = ignoreRearCollision;
	ignoreFrontCollision = TRUE;
	ignoreRearCollision = TRUE;

	if (cc_getMatchColor() != 0) {
		degrees = -degrees;
	}
	//reduction de 0 à 360
	if (degrees > 360) {
		degrees = ((int) (degrees * 1000.0f) % 360000) / 1000.0f;
	}
	if (degrees < -360) {
		int d = (int) -(degrees * 1000.0f);
		d = d % 360000;
		degrees = -d / 1000.0f;
	}

	// OPTIMISER la rotation -PI < a < PI
	if (degrees >= 180)
		degrees -= 360;
	if (degrees < -180)
		degrees += 360;

	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float rad = (degrees * M_PI) / 180.0f;
	motion_Rotate(cmd, rad);
	TRAJ_STATE ts = launchAndWait(cmd);
	ignoreFrontCollision = f;
	ignoreRearCollision = b;
	return ts;
}
TRAJ_STATE cc_rotateLeft(float degrees) {
	return cc_rotateAbs(degrees);
}
TRAJ_STATE cc_rotateRight(float degrees) {
	return cc_rotateAbs(-degrees);
}

TRAJ_STATE cc_rotateTo(float thetaInDegree) {

	float currentThetaInDegree = cc_getThetaInDegree();
	//printf("ccbase.c cc_rotateTo %f deg   current=%f \n", thetaInDegree, currentThetaInDegree);
	float delta = cc_getRelativeAngle(thetaInDegree) - currentThetaInDegree;

	float turn = ((int) (delta * 1000.0f) % 360000) / 1000.0f;

	//printf("ccbase.c cc_rotateAbs %f deg   delta=%f deg\n ", turn, delta);
	if (cc_getMatchColor() != 0) {
		turn = -turn;
	}
	TRAJ_STATE ts = cc_rotateAbs(turn); //cho use Abs not left!!

	return ts;
}

void cc_setPosition(float xMM, float yMM, float thetaDegrees, int matchColor) {
	if (matchColor != 0) {
		//yMM = -yMM;
		xMM = 3000 - xMM;
		thetaDegrees = 180.0 - thetaDegrees;
	}

	odo_SetPosition(xMM / 1000.0, yMM / 1000.0, thetaDegrees * M_PI / 180.0);
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
// angle in degrees
float cc_getThetaInDegree() {
	RobotPosition p = odo_GetPosition();
	return (p.theta * 180.0f) / M_PI;
}

void cc_setIgnoreFrontCollision(boolean b) {
	ignoreFrontCollision = b;
}
void cc_setIgnoreRearCollision(boolean b) {
	ignoreRearCollision = b;
}
void cc_collisionOccured(int front) {
	printf("TTTTTTTTTTTTTTEST : front=%d ignoreFrontCollision=%d ignoreRearCollision=%d\n", front, ignoreFrontCollision,
			ignoreRearCollision);
	if (front && !ignoreFrontCollision) {
		printf("===>cc_collisionOccured on front ignoreFrontCollision=%d\n ", ignoreFrontCollision);
		path_CollisionOnTrajectory();
	} else if (!front && !ignoreRearCollision) {
		printf("===>cc_collisionOccured on rear ignoreFrontCollision=%d\n ", ignoreRearCollision);
		path_CollisionRearOnTrajectory();
	}
}

void cc_setMatchColor(int color) {
	matchColor = color;
}
int cc_getMatchColor() {
	return matchColor;
}

void cc_setMirrorCoordinates(boolean b) {

}

TRAJ_STATE cc_goToZone(const char *zoneName) {
	ZONE* z = ia_getZone(zoneName);
	TRAJ_STATE ts;
	printf("%s (line %d) : goToZone %s\n", __FUNCTION__, __LINE__, zoneName);

	if (z == NULL) {
		printf("ERROR: %s %d : unable to get zone %s\n", __FUNCTION__, __LINE__, zoneName);
		return TRAJ_ERROR;
	}

	ZONE *zCurrent = ia_getNearestZoneFrom(cc_getX(), cc_getY());
	if (zCurrent == NULL) {
		printf("ERROR: cc_goToZone ia_getNearestZoneFrom return NULL !!");
		return TRAJ_ERROR;
	}

	ZONE_PATH *path = ia_getZonePath(zCurrent, z);

	if (path != NULL) {
		printf("%s (line %d) : goToZone FROM %s TO %s using path (%f,%f)\n", __FUNCTION__, __LINE__, zCurrent->name,
				z->name, path->x, path->y);
		ts = cc_moveForwardTo(cc_getRelativeX(path->x), path->y);
		if (ts != TRAJ_OK) {
			return ts;
		}
	} else {
		printf("%s (line %d) : goToZone FROM %s TO %s with NO path \n", __FUNCTION__, __LINE__, zCurrent->name,
				z->name);
	}
	ts = cc_moveForwardAndRotateTo(cc_getRelativeX(z->startX), z->startY, cc_getRelativeAngle(z->startAngle));
	return ts;

}
