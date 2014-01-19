#ifndef _ROBOT_TRAJECTORY_H_
#define _ROBOT_TRAJECTORY_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTOR_SPEED_ORDER_H_
#include "cmotorSpeedCmd.h"
#endif
#ifndef _MOTOR_POSITION_ORDER_H_
#include "cmotorPositionCmd.h"
#endif
#ifndef _MOTOR_STEP_ORDER_H_
#include "cmotorStepCmd.h"
#endif
#ifndef _MOTION_PRIV_H_
#include "cmotion_priv.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

//! possible return state of a trajectory
typedef enum
{
	TRAJ_OK,				//trajectory successfully completed
	TRAJ_ERROR,				//unknown error (not implemented !)
	TRAJ_COLLISION,			//trajectory interrupted because of a collision
	TRAJ_NEAR_OBSTACLE,		//trajectory interrupted because of a near collision
	TRAJ_CANCELLED,			//trajectory cancelled by remote user (for debug only)
	TRAJ_INTERRUPTED,		//trajectory interrupted by software
} TRAJ_STATE;

typedef union
{
	PositionCommand posCmd[MOTOR_PER_TYPE];
	SpeedCommand speedCmd[MOTOR_PER_TYPE];
	StepCommand stepCmd[MOTOR_PER_TYPE];
}UNIONCMD;

//! structure used internally to define a robot trajectory command
typedef struct
{
	MOTOR_COMMAND_TYPE cmdType;
	MOTION_CONTROL_TYPE mcType;

	UNIONCMD cmd;
	//anonymous union that stock data structure for every possible type of motor command
	//structures share the same memory (wich you can interpret as needed)
	//union
	//{
	//	PositionCommand posCmd[MOTOR_PER_TYPE];
	//	SpeedCommand speedCmd[MOTOR_PER_TYPE];
	//	StepCommand stepCmd[MOTOR_PER_TYPE];
	//}cmd;
	//PositionCommand posCmd[MOTOR_PER_TYPE];
	//SpeedCommand speedCmd[MOTOR_PER_TYPE];
	//StepCommand stepCmd[MOTOR_PER_TYPE];

} RobotCommand;

typedef struct
{
	float V0;
	float A0;
	float D1;
	float D2;
	float Beta;
	float Epsilon;
} ClothoidParam;

// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

//! Initialisation of the module
void traj_Init(void);

//! Order a straight line movement of the specified distance
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param dist Distance to run in meter
void motion_Line(RobotCommand *out_cmd, float dist);
//! Order a straight line movement of the specified distance with a specific speed
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param dist Distance to run in meter
//! \param VMax Maximum goal speed of each encoder wheel in meter/second
void motion_LineSpeed(RobotCommand *out_cmd, float dist, float VMax);
//! Order a straight line movement of the specified distance with a specific speed and acceleration
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param dist Distance to run in meter
//! \param VMax Maximum goal speed of each encoder wheel in meter/second
//! \param Accel Acceleration used to attain the VMax speed in m/s/s
//! \param Decel Deceleration used to stop the movement in m/s/s
void motion_LineSpeedAcc(RobotCommand *out_cmd, float dist, float VMax, float Accel, float Decel);

//! Order a pure rotation movement of the specified angle
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param angle Angle to run in radian
void motion_Rotate(RobotCommand *out_cmd, float angle);
//! Order a pure rotation movement of the specified angle with a specific speed
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param angle Angle to run in radian
//! \param VMax Maximum goal speed of each encoder wheel in meter/second
void motion_RotateSpeed(RobotCommand *out_cmd, float angle, float VMax);
//! Order a pure rotation movement of the specified angle with a specific speed and acceleration
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param angle Angle to run in radian
//! \param VMax Maximum goal speed of each encoder wheel in meter/second
//! \param Accel Acceleration used to attain the VMax speed in m/s/s
//! \param Decel Deceleration used to stop the movement in m/s/s
void motion_RotateSpeedAcc(RobotCommand *out_cmd, float angle, float VMax, float Accel, float Decel);

//! Order a arc-circle curve movement of the specified angle and radius
//! \param out_cmd Resulting command that will be interpreted by path_manager
//! \param angle Angle of the arc-circle curve in radian (2*Pi make a complete circle)
//! \param radius Radius of the arc-circle in meter
void motion_ArcRotate(RobotCommand *out_cmd, float angle, float radius);
void motion_ArcRotateSpeed(RobotCommand *out_cmd, float angle, float radius, float VMax);
void motion_ArcRotateSpeedAcc(RobotCommand *out_cmd, float angle, float radius, float VMax, float Accel, float Decel);


//! Control the speed of both motors
//! \param out_cmd Resulting command that will be interpreted by path_manager
void motion_SpeedControlLR(RobotCommand *out_cmd,
						float spLeft, float distLeft, float accLeft,
						float spRight, float distRight, float accRight);

void motion_SpeedControlLRDecel(RobotCommand *out_cmd,
						float spLeft, float distLeft, float accLeft, float decLeft,
						float spRight, float distRight, float accRight, float decRight);

void motion_SpeedControlLRV0(RobotCommand *out_cmd,
						float V0Left, float spLeft, float distLeft, float accLeft,
						float V0Right, float spRight, float distRight, float accRight);

void motion_SpeedControlLRTime(RobotCommand *out_cmd,
							float V0Left, float TLeft, float accLeft,
							float V0Right, float TRight, float accRight);

//! Control the speed of alpha-delta virtual motors
//! \param out_cmd Resulting command that will be interpreted by path_manager
void motion_SpeedControlAD(RobotCommand *out_cmd, float spAlpha, float distAlpha, float accAlpha, float spDelta, float distDelta, float accDelta);

//! Control the speed of alpha-delta virtual motors during a few ms
//! \param out_cmd Resulting command that will be interpreted by path_manager
void motion_SpeedControlADMaxTime(RobotCommand *out_cmd,
								float spAlpha, float accAlpha,
								float spDelta, float accDelta,
								int duringMs);

//! Test PID system with step order response
//! \param out_cmd Resulting command that will be interpreted by path_manager
void motion_StepOrderLR(RobotCommand *out_cmd, long posLeft, long posRight);

//! Test PID system with step order response
//! \param out_cmd Resulting command that will be interpreted by path_manager
void motion_StepOrderAD(RobotCommand *out_cmd, long posAlpha, long posDelta);

// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
