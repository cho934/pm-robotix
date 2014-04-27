/*
 * types.h
 *
 *  Created on: Feb 3, 2014
 *      Author: maillard
 */

#ifndef TYPES_H_
#define TYPES_H_

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define int8 char
#define int16 short
#define int32 int
#define BOOL int
typedef int boolean;
#define EXPORTED_FUNCTION
#ifndef NULL
	#define NULL 0
#endif
#define FALSE 0
#define TRUE 1


#define M_2PI 6.28318530718

typedef struct RobotPosition {
	float x;
	float y;
	float theta;
} RobotPosition;
typedef struct Position {
	float x;
	float y;

} Position;
#endif /* TYPES_H_ */
