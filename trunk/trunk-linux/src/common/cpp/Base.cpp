/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include "Base.hpp"

#include <stdlib.h>
#include <cstdio>

#include "../c/ccbase.h"
#include "../c/encoder.h"
#include "../c/motion.h"
#include "../c/path_manager.h"
#include "../c/robot.h"
#include "Logger.hpp"

pmx::Base::Base(pmx::Robot & robot)
		: ARobotElement(robot)
{
}

void pmx::Base::begin(int lResolution, int rResolution, float dist, int startAsserv)
{
	robot_init();

	encoder_SetDist(dist);
	encoder_SetResolution(lResolution, rResolution);

	//initLog(lResolution, rResolution, dist);

	printf("Encoders resolution: %d %d , distance: %f\n", lResolution, rResolution, dist);

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
	printf("START: (%f,%f) %f\n", cc_getX(), cc_getY(), cc_getThetaInDegree());
}

void pmx::Base::launchAndEndAfterCmd(RobotCommand* cmd)
{
	printf("Check cmd\n");
	checkRobotCommand(cmd);

	path_LaunchTrajectory(cmd);
	printf("path_WaitEndOfTrajectory\n");
	int result = path_WaitEndOfTrajectory();

	printf("path_WaitEndOfTrajectory returned : %d : %d\n", result, TRAJ_OK);

	robot_setMotorLeftSpeed(0);
	robot_setMotorRightSpeed(0);
	free(cmd);
	//closeLog();

}

void pmx::Base::motionLine(int mm)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_Line(cmd, meters);
	printf("Loading line command for %d mm (%f meters)\n", mm, meters);
	launchAndEndAfterCmd(cmd);

}

void pmx::Base::pidD(int mm)
{
	RobotCommand* cmd = (RobotCommand*) malloc(sizeof(RobotCommand));
	float meters = mm / 1000.0f;
	motion_StepOrderAD(cmd, 0.0f, meters / valueVTops, 5);

	launchAndEndAfterCmd(cmd);
}
