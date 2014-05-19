/*
 * ia.c
 *
 *  Created on: May 8, 2014
 *      Author: maillard
 */

#include "ia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ccbase.h"


int _zones_count = 0;
ZONE* _zones[100];

int _zones_path_count = 0;
ZONE_PATH* _zones_path[100];

int _actions_count = 0;
ACTIONS* _actions[200];

void ia_addAction(const char* name, RobotAction action) {
	ACTIONS *a = (ACTIONS*) calloc(1, sizeof(ACTIONS));
	strcpy(a->name, name);
	a->action = action;
	a->completed = FALSE;
	_actions[_actions_count] = a;
	_actions_count++;
}

void ia_createZone(const char* name, float minX, float minY, float width,
		float height, float startX, float startY, float startAngle) {
	ZONE *z = (ZONE*) calloc(1, sizeof(ZONE));
	z->minX = minX;
	z->minY = minY;
	z->width = width;
	z->height = height;
	z->startX = startX;
	z->startY = startY;
	z->startAngle = startAngle;
	strcpy(z->name, name);
	_zones[_zones_count] = z;
	_zones_count++;
}

void ia_printZone(ZONE *z) {
	printf("ZONE: %s (%f,%f) w:%f h:%f start:%f,%f %f degrees\n", z->name,
			z->minX, z->minY, z->width, z->height, z->startX, z->startY,
			z->startAngle);
}
void ia_checkZones() {
	if (_zones_count <= 0) {
		printf("%s (line %d) : Error : no zones defined\n", __FUNCTION__,
		__LINE__);
		exit(2);
	}

	int i, j;
	for (i = 0; i < _zones_count; i++) {
		ZONE *z = _zones[i];
		if (z->width <= 0) {
			printf("%s (line %d) : Error : negative width for zone %s\n",
					__FUNCTION__,
					__LINE__, z->name);
			exit(2);
		}
		if (z->height <= 0) {
			printf("%s (line %d) : Error : negative height for zone %s\n",
					__FUNCTION__,
					__LINE__, z->name);
			exit(2);
		}
		// Check existing zone path
		for (j = 0; j < _zones_count; j++) {
			if (i != j) {
				ZONE *z2 = _zones[j];
				ZONE_PATH* p = ia_getZonePath(z, z2);
				if (p == NULL) {
					printf("%s (line %d) : Error : no path from %s and %s\n",
							__FUNCTION__,
							__LINE__, z->name, z2->name);
					exit(2);
				}
			}
		}
	}
}
void ia_setPath(const char* zone1Name, const char* zone2Name, float x, float y) {
	ZONE_PATH *zp = (ZONE_PATH*) calloc(1, sizeof(ZONE_PATH));
	zp->z1 = ia_getZone(zone1Name);
	zp->z2 = ia_getZone(zone2Name);
	zp->x = x;
	zp->y = y;
	_zones_path[_zones_path_count] = zp;
	_zones_path_count++;

}
ZONE_PATH* ia_getZonePath(ZONE *z1, ZONE *z2) {
	int i;
	for (i = 0; i < _zones_path_count; i++) {
		ZONE_PATH *zp = _zones_path[i];
		if ((zp->z1 == z1 && zp->z2 == z2) || (zp->z1 == z2 && zp->z2 == z1)) {
			return zp;
		}
	}
	return NULL;
}

void ia_start() {
	ia_checkZones();
	if (_actions_count <= 0) {
		printf("%s (line %d) : Error : no actions defined\n", __FUNCTION__,
		__LINE__);
		exit(2);
	}
	boolean allDone = FALSE;
	while (!allDone) {
		allDone = TRUE;
		int i = 0;
		for (i = 0; i < _actions_count; i++) {
			ACTIONS *z = _actions[i];
			if (z->completed == FALSE) {
				printf("\n== ia is executing actions [%d/%d] : %s\n", i + 1,
						_actions_count, z->name);
				printf("state before actions : %s : (%f,%f) %f\n", z->name,
						cc_getX(), cc_getY(), cc_getThetaInDegree());
				boolean done = (*z->action)();
				if (!done) {
					allDone = FALSE;
				}
				z->completed = done;
				printf("state after actions : %s : (%f,%f) %f\n", z->name,
						cc_getX(), cc_getY(), cc_getThetaInDegree());
			}

		}
		sleep(1);
	}
}

ZONE* ia_getZone(const char* zoneName) {
	int i = 0;
	for (i = 0; i < _zones_count; i++) {
		ZONE *z = _zones[i];
		if (strcmp(zoneName, z->name) == 0) {
			return z;
		}
	}
	return NULL;
}
ZONE* ia_getZoneAt(float x, float y) {
	int i = 0;
	for (i = 0; i < _zones_count; i++) {
		ZONE *z = _zones[i];
		if (z->minX < x && z->minY < y && (z->minX + z->width) > x
				&& (z->minY + z->height) > y) {
			return z;
		}
	}
	return NULL;
}

ZONE* ia_getNearestZoneFrom(float x, float y) {
	if (ia_getZoneAt(x, y) != NULL) {
		return ia_getZoneAt(x, y);
	}
	ZONE *result = _zones[0];
	float minDist2 = 8888888888888.0f;
	int i = 0;
	for (i = 0; i < _zones_count; i++) {
		ZONE *z = _zones[i];
		float x1 = z->minX + z->width / 2.0f;
		float y1 = z->minY + z->height / 2.0f;
		float d = x1 * x1 + y1 * y1;
		if (d < minDist2) {
			minDist2 = d;
			result = z;
		}
	}
	return result;
}
