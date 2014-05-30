/*
 * ia.c
 *
 *  Created on: May 8, 2014
 *      Author: maillard
 */

#include "ia.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../common/cpp/SvgWriter.hpp"
#include "ccbase.h"
#include "robot.h"

int _zones_count = 0;
ZONE* _zones[100];

int _zones_path_count = 0;
ZONE_PATH* _zones_path[100];

int _actions_count = 0;
ACTIONS* _actions[200];
void ia_clear(){
	_zones_count=0;
	_zones_path_count=0;
	_actions_count = 0;
}
void ia_addAction(const char* name, RobotAction action)
{
	ACTIONS *a = (ACTIONS*) calloc(1, sizeof(ACTIONS));
	strcpy(a->name, name);
	a->action = action;
	a->completed = FALSE;
	_actions[_actions_count] = a;
	_actions_count++;
}

void ia_createZone(const char* name, float minX, float minY, float width, float height, float startX, float startY,
		float startAngleDeg)
{
	ZONE *z = (ZONE*) calloc(1, sizeof(ZONE));
	z->minX = minX;
	z->minY = minY;
	z->width = width;
	z->height = height;
	z->startX = startX;
	z->startY = startY;
	z->startAngle = startAngleDeg;

	if (cc_getMatchColor() != 0)
	{
		//yMM = -yMM;
		z->startX = 3000 - z->startX;
		z->minX = 3000 - z->width - z->minX;
		z->startAngle = 180.0 - z->startAngle;
		printf("ia_createZone %s RED\n",name);
	}else{
		printf("ia_createZone %s YELLOW\n",name);
	}

	strcpy(z->name, name);
	_zones[_zones_count] = z;
	_zones_count++;

	//log SVG
	utils
::SvgWriter::writeZone(z->name, z->minX, z->minY, z->width, z->height, z->startX, z->startY, z->startAngle* M_PI/180.0);
}

void ia_printZone(ZONE *z)
{
printf("ZONE: %s (%f,%f) w:%f h:%f start:%f,%f %f degrees\n", z->name, z->minX, z->minY, z->width, z->height, z->startX,
		z->startY, z->startAngle);
}
void ia_checkZones()
{
if (_zones_count <= 0)
{
	printf("%s (line %d) : Error : no zones defined\n", __FUNCTION__,
	__LINE__);
	exit(2);
}

int i, j;
for (i = 0; i < _zones_count; i++)
{
	ZONE *z = _zones[i];
	if (z->width <= 0)
	{
		printf("%s (line %d) : Error : negative width for zone %s\n", __FUNCTION__,
		__LINE__, z->name);
		exit(2);
	}
	if (z->height <= 0)
	{
		printf("%s (line %d) : Error : negative height for zone %s\n", __FUNCTION__,
		__LINE__, z->name);
		exit(2);
	}
	// Check existing zone path
	for (j = 0; j < _zones_count; j++)
	{
		if (i != j)
		{
			ZONE *z2 = _zones[j];
			ZONE_PATH* p = ia_getZonePath(z, z2);
			if (p == NULL)
			{
				printf("%s (line %d) : Error : no path from %s and %s\n", __FUNCTION__,
				__LINE__, z->name, z2->name);
				exit(2);
			}
		}
	}
}
}
void ia_setPath(const char* zone1Name, const char* zone2Name, float x, float y)
{
ZONE_PATH *zp = (ZONE_PATH*) calloc(1, sizeof(ZONE_PATH));
zp->z1 = ia_getZone(zone1Name);
zp->z2 = ia_getZone(zone2Name);
zp->x = x;
zp->y = y;

//printf("ia_setPath cc_getMatchColor=%d\n", cc_getMatchColor());
if (cc_getMatchColor() != 0)
{
	//yMM = -yMM;
	zp->x = 3000 - zp->x;
}
_zones_path[_zones_path_count] = zp;
_zones_path_count++;

utils
::SvgWriter::writeIaPath(zone1Name, zone2Name, zp->x, zp->y);

}

ZONE_PATH* ia_getZonePath(ZONE *z1, ZONE *z2)
{
int i;
for (i = 0; i < _zones_path_count; i++)
{
ZONE_PATH *zp = _zones_path[i];
if ((zp->z1 == z1 && zp->z2 == z2) || (zp->z1 == z2 && zp->z2 == z1))
{
	return zp;
}
}
printf("ia_getZonePath return NULL!!!");
return NULL;
}

void ia_start()
{
ia_checkZones();
if (_actions_count <= 0)
{
printf("%s (line %d) : Error : no actions defined\n", __FUNCTION__,
__LINE__);
exit(2);
}
boolean allDone = FALSE;
while (!allDone)
{
allDone = TRUE;
int i = 0;
for (i = 0; i < _actions_count; i++)
{
	ACTIONS *z = _actions[i];
	if (z->completed == FALSE)
	{
		printf("\n== ia is executing actions [%d/%d] : %s\n", i + 1, _actions_count, z->name);
		printf("state before actions : %s : (%f,%f) %f\n", z->name, cc_getX(), cc_getY(), cc_getThetaInDegree());
		printf("encoders: %ld,%ld\n",robot_getLeftExternalCounter(),robot_getRightExternalCounter());
		boolean done = (*z->action)();
		if (!done)
		{
			allDone = FALSE;
		}
		z->completed = done;
		if(!done){
			printf("state after actions : %s : (%f,%f) %f FAILED\n", z->name, cc_getX(), cc_getY(), cc_getThetaInDegree());
		}
		printf("state after actions : %s : (%f,%f) %f\n", z->name, cc_getX(), cc_getY(), cc_getThetaInDegree());
	}

}
sleep(1);
}
}

ZONE* ia_getZone(const char* zoneName)
{
int i = 0;
for (i = 0; i < _zones_count; i++)
{
ZONE *z = _zones[i];
if (strcmp(zoneName, z->name) == 0)
{
	return z;
}
}
return NULL;
}
ZONE* ia_getZoneAt(float x, float y)
{
printf("ia_getZoneAt : (%f,%f) \n", x, y);
int i = 0;
for (i = 0; i < _zones_count; i++)
{
ZONE *z = _zones[i];
if (z->minX < x && z->minY < y && (z->minX + z->width) > x && (z->minY + z->height) > y)
{
	return z;
}
}
return NULL;
}

ZONE* ia_getNearestZoneFrom(float x, float y)
{
	ZONE *result=ia_getZoneAt(x, y) ;
	if (result!= NULL){
		printf("ia_getNearestZoneFrom is current zone : %s : (%f,%f) \n", result->name, cc_getX(), cc_getY());
		return result;
	}

	int i = 0;
	result = _zones[i];
	float minDist2 = 8888888888888.0f;

	for (i = 0; i < _zones_count; i++){

ZONE *z = _zones[i];
float x1 = z->minX + z->width / 2.0f;
float y1 = z->minY + z->height / 2.0f;
float dx = x1 - x;
float dy = y1 - y;
float d = dx * dx + dy * dy;
if (d < minDist2)
{
	minDist2 = d;
	result = z;
	//printf("0000005result %s \n", result->name);
}
//printf("ia_getNearestZoneFrom for %f; %s (%f,%f) ? (%f,%f)\n", d, z->name, x, y, x1, y1);
}
printf("end ia_getNearestZoneFrom\n");
return result;
}
