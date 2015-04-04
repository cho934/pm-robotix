/*
 * global.h
 *
 *  Created on: Feb 3, 2014
 *      Author: maillard
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

//dupliquer de math.h car inexistant dans le compilo EV3
# define M_E		2.7182818284590452354	/* e */
# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

//#define DEBUG_MOTION
//#define DEBUG_ENCODER
//#define DEBUG_PID
//#define LOG_PID
#define LOG_SVG_APPENDER //log c++ pour activer le SVG
#define LOG_PID_APPENDER  //log c++ pour activer le fileAppender

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

//#define MAX_PWM_VALUE 128
extern int maxPwmValue;

#define MAX_PID_SYSTEM_NUMBER	6


//#define defaultVmax 		1.0f
extern float defaultVmax;
//#define defaultAcc 		1.0f
extern float defaultAcc;
//#define defaultDec		1.0f
extern float defaultDec;

//vTops is a virtual measure distance to avoid floating point computation
//#define VTOPS_PER_TICKS 1000 //1000 => ROBOT_TEST 13 -700  1.0 0.8 1.5  0.0015 0.0008 0.000002
extern int vtopsPerTicks;

// Attention ces valeurs sont couplées
//#define DEFAULT_SAMPLING_FREQ 100 // en Hz (cad combien de fois par seconde)
extern int defaultSamplingFreq;
//#define valueSample 0.01f //(1f/DEFAULT_SAMPLING_FREQ)
extern float valueSample;

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

#ifdef __cplusplus
}
#endif

#endif /* GLOBAL_H_ */
