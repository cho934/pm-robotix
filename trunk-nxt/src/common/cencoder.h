#ifndef _ENCODER_H_
#define _ENCODER_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS
//! Initialisation
void encoder_Init(void);

//! Set distance between encoder
//! \param dist Encoder distance in meters
void encoder_SetDist(float dist);

//! Set encoder resolution and recompute value of vTops etc...
//! \param leftTicksPerM left encoder resolution in ticks per meter
//! \param rightTicksPerM right encoder resolution in ticks per meter
void encoder_SetResolution(long leftTicksPerM, long rightTicksPerM);

//! Get new encoders values
//!
//! \param dLeft left motor motion in [vTops]
//! \param dRight right motor motion in [vTops]
//! \param dAlpha alpha motor motion in [vTops]
//! \param dDelta delta motor motion in [vTops]
void encoder_ReadSensor(long *dLeft, long *dRight, long *dAlpha, long *dDelta);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_ENCODER_H_
