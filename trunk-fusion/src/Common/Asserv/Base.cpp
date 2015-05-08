/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include "Base.hpp"

#include <stdlib.h>
#include <cstdio>

#include "../AsservIa/ccbase.h"
#include "../AsservIa/encoder.h"
#include "../AsservIa/global.h"
#include "../AsservIa/motion.h"
#include "../AsservIa/robot_unitConversion.h"
#include "../AsservIa/path_manager.h"
#include "../AsservIa/robot.hpp"
#include "../AsservIa/robot_trajectory.h"


Base::Base()
{
}

void Base::begin(int lResolution, int rResolution, float dist, int startAsserv, int useExtEncoders)
{

	if (useExtEncoders)
	{
		useExternalEncoders = 1;
	}
	else
	{
		useExternalEncoders = 0;
	}
	robot_init();

	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);
	/*
	 #ifdef LOG_PID
	 initLog(lResolution, rResolution, dist);
	 #endif
	 #ifdef LOG_PID_APPENDER

	 if (utils::LoggerFactory::logger("motion").isActive(utils::Level::DEBUG)) {
	 utils::LoggerFactory::logger("motion").debug() << "// encoder resolution in tick per meter" << utils::end;
	 utils::LoggerFactory::logger("motion").debug() << "leftResolution:" << lResolution << "" << utils::end;
	 utils::LoggerFactory::logger("motion").debug() << "rightResolution:" << rResolution << "" << utils::end;
	 utils::LoggerFactory::logger("motion").debug() << "// distance between the 2 encoders in meter" << utils::end;
	 utils::LoggerFactory::logger("motion").debug() << "encoderDistance:" << dist << "" << utils::end;
	 utils::LoggerFactory::logger("motion").debug()
	 << "// time (ms), dAlpha (ticks), dDelta (ticks), lpower (0-100), rpower (0-100), order0, order1, lastpos0, lastpos1, x (mm), y (mm), theta (rad)"
	 << utils::end;
	 }

	 #endif*/

	//printf("Encoders resolution: %d %d , distance: %f\n", lResolution, rResolution, dist);
	if (startAsserv > 0)
	{
		motion_Init();
		robot_initPID();
	}

}

void Base::stop()
{
	motion_StopTimer();
}


void Base::printPosition()
{
	printf("POS: (%f mm,%f mm) %f deg\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
	//utils::SvgWriter::writePosition(cc_getX(), cc_getY(), cc_getTheta(), utils::SVG_POS_ROBOT);
}

TRAJ_STATE Base::launchAndEndAfterCmd(RobotCommand* cmd)
{

	//printf("Check cmd\n");
	checkRobotCommand(cmd);

	path_LaunchTrajectory(cmd);
	//printf("path_WaitEndOfTrajectory\n");
	TRAJ_STATE result = path_WaitEndOfTrajectory();
	printPosition();
	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result, TRAJ_OK);


	robot_setMotorLeftSpeed(0);
	robot_setMotorRightSpeed(0);
	free(cmd);
	printPosition();


	 #ifdef LOG_PID
	 closeLog();	//TODO est-ce bien ici le close log ? meme si plusieurs launch l'un après l'autre ?
	 #endif

	return result;

}

void Base::collisionOccured(int front)
{
	cc_collisionOccured(front);
}

int Base::getMatchColor()
{
	return cc_getMatchColor();
}

void Base::setMatchColor(int color)
{
	cc_setMatchColor(color);
}

void Base::assistedHandling()
{
	cc_AssistedHandling();
}

TRAJ_STATE Base::move(int mm)
{
	return cc_move(mm, cc_motion_GetDefaultSpeed(), cc_motion_GetDefaultAccel(), cc_motion_GetDefaultDecel());
}

TRAJ_STATE Base::movexyteta(int backward, float x, float y, float thetaInDegree)
{
	movexytetaSpeedAcc(backward, x, y, thetaInDegree, cc_motion_GetDefaultSpeed(),
			cc_motion_GetDefaultAccel(), cc_motion_GetDefaultDecel());
}

TRAJ_STATE Base::movexytetaSpeedAcc(int backward, float x, float y, float thetaInDegree, float VMax,
		float Accel, float Decel)
{
	if (backward == 0)
	{
		return cc_moveForwardAndRotateTo(x, y, thetaInDegree, VMax, Accel, Decel);
	}
	else
	{
		return cc_moveBackwardAndRotateTo(x, y, thetaInDegree, VMax, Accel, Decel);
	}
}

void Base::findPidAD(float degrees, int mm, int sec)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	float radians = (degrees * M_PI) / 180.0f;
	motion_StepOrderAD(cmd, convertDistTovTops(radians * distEncoderMeter / 2.0f),
			meters / valueVTops, sec);
	launchAndEndAfterCmd(cmd);
}

void Base::setupPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd)
{
	robot_initPID_AD(Ap, Ai, Ad, Dp, Di, Dd);
}

void Base::setupPID_LR(float Lp, float Li, float Ld, float Rp, float Ri, float Rd)
{
	robot_initPID_LR(Lp, Li, Ld, Rp, Ri, Rd);
}

void Base::findPidLR(int posLmm, int posRmm, int sec)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float posLm = posLmm / 1000.0f;
	float posRm = posRmm / 1000.0f;
	motion_StepOrderLR(cmd, posLm / valueVTops, posRm / valueVTops, sec);
	launchAndEndAfterCmd(cmd);
}

void Base::LineSpeedAcc(int mm, float VMax, float Accel, float Decel)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_LineSpeedAcc(cmd, meters, VMax, Accel, Decel);
	launchAndEndAfterCmd(cmd);
}

void Base::RotateSpeedAcc(int degrees, float VMax, float Accel, float Decel)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float radians = (degrees * M_PI) / 180.0f;
	motion_RotateSpeedAcc(cmd, radians, VMax, Accel, Decel);
	launchAndEndAfterCmd(cmd);
}

void Base::SpeedControlLR(float spLeft, int distLeftmm, float accLeft, float spRight,
		int distRightmm, float accRight)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float distLeftm = distLeftmm / 1000.0;
	float distRightm = distRightmm / 1000.0;

	motion_SpeedControlLR(cmd, spLeft, distLeftm, accLeft, spRight, distRightm, accRight);
	launchAndEndAfterCmd(cmd);
}

void Base::ArcRotate(int degrees, float radiusMM)
{
	//TODO mettre dans ccbase
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	motion_ArcRotate(cmd, degrees * M_PI / 180.0, radiusMM / 1000.0);
	launchAndEndAfterCmd(cmd);
}


