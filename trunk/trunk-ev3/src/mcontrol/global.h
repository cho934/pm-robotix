/*
 * global.h
 *
 *  Created on: Feb 3, 2014
 *      Author: maillard
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "types.h"

#define LWHEEL 0
#define RWHEEL 1
#define slippageThreshold 10

#define FRONT_SHOCK 0
#define BACK_SHOCK 1
#define isSendErrorsEnabled 0
#define valueSample 1

//#define DEFAULT_SAMPLING_FREQ 100

//some values goes in pair :
//the first one is the measured/real one
//the second one is an integer approximation using funny units (vTops and sample)

//ratio vTops/ticks for left encoder
uint32 leftEncoderRatio;
//ratio vTops/ticks for right encoder
uint32 rightEncoderRatio;

//distance between both encoder wheels in vTops
uint32 distEncoder;
//distance between both encoder wheels in meters
float distEncoderMeter;
float valueVTops;
#endif /* GLOBAL_H_ */
