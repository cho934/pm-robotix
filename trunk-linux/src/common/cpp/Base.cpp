/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include "Base.hpp"

#include <math.h>
#include <stdlib.h>
#include <cstdio>

#include "../c/ccbase.h"
#include "../c/encoder.h"
#include "../c/global.h"
#include "../c/motion.h"
#include "../c/path_manager.h"
#include "../c/robot.h"
#include "../c/robot_unitConversion.h"
#include "Level.hpp"
#include "Logger.hpp"
#include "SvgWriter.hpp"

pmx::Base::Base(pmx::Robot & robot)
		: ARobotElement(robot)
{
}

void pmx::Base::begin(int lResolution, int rResolution, float dist, int startAsserv)
{
	robot_init();

	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);

#ifdef LOG_PID
	initLog(lResolution, rResolution, dist);
#endif
#ifdef LOG_PID_APPENDER

	if (utils::LoggerFactory::logger("motion").isActive(utils::Level::DEBUG))
	{
		utils::LoggerFactory::logger("motion").debug() << "// encoder resolution in tick per meter" << utils::end;
		utils::LoggerFactory::logger("motion").debug() << "leftResolution:" << lResolution << "" << utils::end;
		utils::LoggerFactory::logger("motion").debug() << "rightResolution:" << rResolution << "" << utils::end;
		utils::LoggerFactory::logger("motion").debug() << "// distance between the 2 encoders in meter" << utils::end;
		utils::LoggerFactory::logger("motion").debug() << "encoderDistance:" << dist << "" << utils::end;
		utils::LoggerFactory::logger("motion").debug()
				<< "// time (ms), dAlpha (ticks), dDelta (ticks), lpower (0-100), rpower (0-100), order0, order1, lastpos0, lastpos1, x (mm), y (mm), theta (rad)"
				<< utils::end;
	}

#endif

	//printf("Encoders resolution: %d %d , distance: %f\n", lResolution, rResolution, dist);

	if (startAsserv > 0)
	{
		motion_Init();
		robot_initPID();
	}
}

void pmx::Base::initialize(const std::string& prefix, utils::Configuration&)
{
	logger().debug() << "initialize: " << prefix << utils::end;

}

void pmx::Base::printPosition()
{
	printf("START: (%f mm,%f mm) %f deg\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
}

void pmx::Base::launchAndEndAfterCmd(RobotCommand* cmd)
{
	//printf("Check cmd\n");
	checkRobotCommand(cmd);

	path_LaunchTrajectory(cmd);
	printf("path_WaitEndOfTrajectory\n");
	int result = path_WaitEndOfTrajectory();

	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result, TRAJ_OK);

	//robot_setMotorLeftSpeed(0);
	//robot_setMotorRightSpeed(0);
	free(cmd);

#ifdef LOG_PID
	closeLog();	//TODO est-ce bien ici le close log ? meme si plusieurs launch l'un après l'autre ?
#endif
}

void pmx::Base::move(int mm)
{
	cc_move(mm);
}

void pmx::Base::movexyteta(int backward, float x, float y, float thetaInDegree)
{
	if(backward == 0)
	{
		cc_moveForwardAndRotateTo(x, y, thetaInDegree);
	}else
	{
		cc_moveBackwardAndRotateTo(x, y, thetaInDegree);
	}
}

void pmx::Base::findPidAD(float degrees, int mm, int sec)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	float radians = (degrees * M_PI) / 180.0f;
	motion_StepOrderAD(cmd, convertDistTovTops(radians * distEncoderMeter / 2.0f), meters / valueVTops, sec);
	launchAndEndAfterCmd(cmd);
}

void pmx::Base::setupPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd)
{
	robot_initPID_AD(Ap, Ai, Ad, Dp, Di, Dd);
}

void pmx::Base::MoveLineSpeedAcc(int mm,  float VMax, float Accel, float Decel )
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_LineSpeedAcc(cmd, meters, VMax, Accel, Decel);
	launchAndEndAfterCmd(cmd);
}
