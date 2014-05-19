/*
 * global.h
 *
 *  Created on: Feb 3, 2014
 *      Author: maillard
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define DEBUG_MOTION
// #define DEBUG_ENCODER
// #define DEBUG_PID

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

#define LWHEEL 0
#define RWHEEL 1
#define slippageThreshold 10

#define FRONT_SHOCK 0
#define BACK_SHOCK 1
#define isSendErrorsEnabled 0

#define MAX_PWM_VALUE 100

#define MAX_PID_SYSTEM_NUMBER	6

//vTops is a virtual measure distance to avoid floating point computation
#define VTOPS_PER_TICKS 2048 //1000

// Attention ces valeurs sont couplées
#define DEFAULT_SAMPLING_FREQ 100 // en Hz (cad combien de fois par seconde)
#define valueSample 0.01f //(1f/DEFAULT_SAMPLING_FREQ)

//some values goes in pair :
//the first one is the measured/real one
//the second one is an integer approximation using funny units (vTops and sample)

//ratio vTops/ticks for left encoder
extern uint32 leftEncoderRatio;
//ratio vTops/ticks for right encoder
extern uint32 rightEncoderRatio;

//distance between both encoder wheels in vTops
extern uint32 distEncoder;
//distance between both encoder wheels in meters
extern float distEncoderMeter;
extern float valueVTops;

typedef struct RobotPosition {
	float x;
	float y;
	float theta;
} RobotPosition;
typedef struct Position {
	float x;
	float y;

} Position;

#endif /* GLOBAL_H_ */
