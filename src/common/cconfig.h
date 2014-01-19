#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef _DEBUG__
#include "cdebug.c"
#endif


//tell the program if external sensor and/or motor encoder are available
#define USE_EXTERN_ENCODER 0
#define USE_ENCODER 1
#define SLIPPAGE_DETECTION 0

//! max ratio between vTops and ticks (it corresponds to the ratio of the most accurate encoder)
//vTops is a virtual measure distance to avoid floating point computation
#define VTOPS_PER_TICKS				0x0800 //2048

#define MAX_ENCODER_ABS_VTOPS			(VTOPS_PER_TICKS*0x000FFFFF) //TODO
//#define MAX_EXTERN_ENCODER_ABS_VTOPS (VTOPS_PER_TICKS*0x000FFFFF)

//#define DEFAULT_SAMPLING_FREQ			20	//Hz  => relace by DEFAULT_SAMPLING_PERIOD_Ms
#define DEFAULT_SAMPLING_PERIOD_Ms  10 //=>tous les 10ms => 100Hz

#define DEFAULT_ENCODER_DIST			0.139 //defaut encoder distance in meter
#define DEFAULT_LEFT_TICKS_PER_M		1446 //1436 1446
#define DEFAULT_RIGHT_TICKS_PER_M		1446 //1454 1446

#define DEFAULT_SPEED					0.3 //in meters/second //max = 0.8
#define DEFAULT_ACCEL					0.3 //in meters/second^2 //max = 2.5
#define DEFAULT_DECEL					0.3 //in meters/second^2 //max = 2.5

#define DEFAULT_SLIPPAGE				600000

#define SLIPPAGE_RATIO			300000
#define CALIB_SPEED_NB			6


#endif
