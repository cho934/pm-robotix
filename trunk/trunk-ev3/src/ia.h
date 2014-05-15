/*
 * ia.h
 *
 *  Created on: May 8, 2014
 *      Author: maillard
 */

#ifndef IA_H_
#define IA_H_

#include "global.h"

typedef boolean (*RobotAction)(void);

typedef struct {
	char name[400];
	// in mm
	float minX;
	float minY;
	float width;
	float height;
	float startX;
	float startY;
	// in degrees
	float startAngle;
} ZONE;

typedef struct {
	ZONE *z1;
	ZONE *z2;
	float x;
	float y;
} ZONE_PATH;

typedef struct {
	char name[400];
	RobotAction action;
	boolean completed;
} ACTIONS;

void ia_start();

void ia_createZone(const char* name, float minX, float minY, float width,
		float height, float startX, float startY, float startAngle);
ZONE* ia_getZone(const char* zoneName);
ZONE* ia_getZoneAt(float x, float y);
ZONE* ia_getNearestZoneFrom(float x, float y);

void ia_setPath(const char* zone1Name, const char* zone2Name, float x, float y);
ZONE_PATH* ia_getZonePath(ZONE *z1, ZONE *z2);

void ia_addAction(const char* name, RobotAction action);

#endif /* IA_H_ */
