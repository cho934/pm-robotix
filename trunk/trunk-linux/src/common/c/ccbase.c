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
boolean ignoreCollision = FALSE;

void cc_AssistedHandling()
{
	motion_AssistedHandling();
}

void launchAndWait(RobotCommand* cmd)
{
	checkRobotCommand(cmd);
	path_LaunchTrajectory(cmd);

	TRAJ_STATE result = path_WaitEndOfTrajectory();
	printf("path_WaitEndOfTrajectory returned : %d : TRAJ_OK=%d TRAJ_COLLISION=%d\n", result, TRAJ_OK, TRAJ_COLLISION);
	free(cmd);
}

// if distance <0, move backward
void cc_move(float distanceInMM)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = distanceInMM / 1000.0f;
	motion_Line(cmd, meters);
	launchAndWait(cmd);
}

void cc_moveForwardTo(float xMM, float yMM)
{
	if (cc_getMatchColor() != 0)
	{
		//yMM = -yMM;
		xMM = 3000 - xMM;
	}

	float dx = xMM - cc_getX();
	float dy = yMM - cc_getY();
	float aRadian = atan2(dy, dx);
	if (cc_getMatchColor() != 0)
	{
		cc_rotateTo(180 - (aRadian * 180.0f) / M_PI);
	}
	else
	{
		cc_rotateTo((aRadian * 180.0f) / M_PI);
	}

	float dist = sqrt(dx * dx + dy * dy);
	//printf("xMM=%f yMM=%f dx=%f dy=%f dist=%f\n", xMM, yMM,dx,dy,dist);
	cc_move(dist);
}
void cc_moveForwardAndRotateTo(float xMM, float yMM, float thetaInDegree)
{
	/*if (matchColor != 0)
	 {
	 thetaInDegree = (- thetaInDegree);
	 }*/

	cc_moveForwardTo(xMM, yMM);
	//printf("thetaInDegree = %f\n", thetaInDegree);
	cc_rotateTo(thetaInDegree);
}
void cc_moveBackwardTo(float xMM, float yMM)
{
	if (cc_getMatchColor() != 0)
	{
		//yMM = -yMM;
		xMM = 3000 - xMM;
	}

	float dx = xMM - cc_getX();
	float dy = yMM - cc_getY(); //-500 -x = -900
	float aRadian = atan2(dy, dx);
	if (cc_getMatchColor() != 0)
	{
		cc_rotateTo(180 - ((M_PI + aRadian) * 180.0f) / M_PI); //TODO angle au plus court ?
	}
	else
	{
		cc_rotateTo(((M_PI + aRadian) * 180.0f) / M_PI); //TODO angle au plus court ?
	}

	float dist = sqrt(dx * dx + dy * dy);
	cc_move(-dist);
}
void cc_moveBackwardAndRotateTo(float xMM, float yMM, float thetaInDegree)
{
	/*
	 if (matchColor != 0)
	 {
	 thetaInDegree = (- thetaInDegree);
	 }*/
	cc_moveBackwardTo(xMM, yMM);
	cc_rotateTo(thetaInDegree);
}
void cc_rotateAbs(float degrees)
{
	if (cc_getMatchColor() != 0)
	{
		degrees = -degrees;
	}
	//reduction de 0 à 360
	if (degrees > 360)
	{
		degrees = ( (int)(degrees * 1000.0f) % 360000) / 1000.0f;
	}
	if (degrees < -360)
	{
		int d =(int) -(degrees * 1000.0f);
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
	launchAndWait(cmd);
}
void cc_rotateLeft(float degrees)
{
	cc_rotateAbs(degrees);
}
void cc_rotateRight(float degrees)
{
	cc_rotateAbs(-degrees);
}

void cc_rotateTo(float thetaInDegree)
{
	int c = ignoreCollision;
	ignoreCollision = TRUE;

	if (cc_getMatchColor() != 0)
	{
		thetaInDegree = 180.0 - thetaInDegree;
	}

	float currentThetaInDegree = cc_getThetaInDegree();
	//printf("ccbase.c cc_rotateTo %f deg   current=%f \n", thetaInDegree, currentThetaInDegree);
	float delta = thetaInDegree - currentThetaInDegree;

	float turn = ((int) (delta * 1000.0f) % 360000) / 1000.0f;

	//printf("ccbase.c cc_rotateAbs %f deg   delta=%f deg\n ", turn, delta);
	if (cc_getMatchColor() != 0)
	{
		turn = -turn;
	}
	cc_rotateAbs(turn); //cho use Abs not left!!

	ignoreCollision = c;
}
void cc_setPosition(float xMM, float yMM, float thetaDegrees, int matchColor)
{
	if (matchColor != 0)
	{
		//yMM = -yMM;
		xMM = 3000 - xMM;
		thetaDegrees = 180.0 - thetaDegrees;
	}

	odo_SetPosition(xMM / 1000.0, yMM / 1000.0, thetaDegrees * M_PI / 180.0);
}

// position x,x in mm
float cc_getX()
{
	RobotPosition p = odo_GetPosition();
	return p.x * 1000.0f;
}
float cc_getY()
{
	RobotPosition p = odo_GetPosition();
	return p.y * 1000.0f;
}
// angle in radian
float cc_getTheta()
{
	RobotPosition p = odo_GetPosition();
	return p.theta;
}
// angle in degrees
float cc_getThetaInDegree()
{
	RobotPosition p = odo_GetPosition();
	return (p.theta * 180.0f) / M_PI;
}

void cc_setIgnoreCollision(boolean b)
{
	ignoreCollision = b;
}

void cc_collisionOccured()
{
	if (!ignoreCollision)
		path_CollisionOnTrajectory();
}

void cc_setMatchColor(int color)
{
	matchColor = color;
}
int cc_getMatchColor()
{
	return matchColor;
}

void cc_setMirrorCoordinates(boolean)
{

}
void cc_goToZone(const char *zoneName)
{
	ZONE* z = ia_getZone(zoneName);
	//printf("%s (line %d) : goToZone %s\n", __FUNCTION__, __LINE__, zoneName);
	if (z == NULL)
	{
		printf("%s %d : unable to get zone %s\n", __FUNCTION__, __LINE__, zoneName);
	}
	else
	{
		ZONE *zCurrent = ia_getNearestZoneFrom(cc_getX(), cc_getY());
		ZONE_PATH *path = ia_getZonePath(zCurrent, z);
		printf("%s (line %d) : goToZone FROM %s TO %s using path (%f,%f)\n", __FUNCTION__,__LINE__, zCurrent->name, z->name, path->x, path->y);

		if (cc_getMatchColor() != 0)
		{
			cc_moveForwardTo(3000 - path->x, path->y);
			// Move to destinatio
			cc_moveForwardAndRotateTo(3000 - z->startX, z->startY, 180-z->startAngle);
		}
		else
		{
			cc_moveForwardTo(path->x, path->y);
			// Move to destination
			cc_moveForwardAndRotateTo(z->startX, z->startY, z->startAngle);
		}
	}
}
