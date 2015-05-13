/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 */

#include "../Common/State/StateAdjustRobotPosition.hpp"

#include <unistd.h>

#include "../Common/Action/ButtonBar.hpp"
#include "../Common/Action.Driver/AButtonDriver.hpp"
#include "../Common/Asserv/Asserv.hpp"
#include "../Common/AsservIa/ccbase.h"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"
#include "SActionsExtended.hpp"
#include "SRobotExtended.hpp"

IAutomateState*
StateAdjustRobotPosition::execute(Robot& r, void *data)
{
	IAutomateState* result = NULL;

	this->logger().info() << "start 3" << logs::end;

	Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);
	robot.asserv().start(); //config + thread + config resolution asserv

	logger().info() << "cc_getMatchColor()=" << cc_getMatchColor() << logs::end;
	//cc_setPosition(575.0, 1000.0, 0.0, cc_getMatchColor());
	cc_setPosition(575.0, 1000.0, 0.0, cc_getMatchColor());

	logger().info() << "cc_getX()=" << cc_getX() << logs::end;
	logger().info() << "cc_getY()=" << cc_getY() << logs::end;
	logger().info() << "cc_getThetaInDegree()=" << cc_getThetaInDegree() << logs::end;

	logger().info() << "Position adjusted." << logs::end;
/*
	logger().info() << "strategy = " << sharedData->strategy() << logs::end;

	if (!sharedData->skipSetup() && (sharedData->strategy() == "none"))
	{
		logger().info() << "Please choose strategy and press enter..." << logs::end;
		while (!robot.actions().buttonBar().pressed(BUTTON_ENTER_KEY)
				|| (sharedData->strategy() == "none"))
		{
			//logger().info() << "strategy = " << sharedData->strategy() << logs::end;
			if (robot.actions().buttonBar().pressed(BUTTON_UP_KEY))
			{
				logger().debug() << "=> FirstSteps...FIRST STEPS" << logs::end;
				sharedData->strategy("FirstSteps");
			}

			if (robot.actions().buttonBar().pressed(BUTTON_DOWN_KEY))
			{
				logger().debug() << "=> FirstCarpet...FIRST CARPET" << logs::end;
				sharedData->strategy("FirstCarpet");
			}

			if (robot.actions().buttonBar().pressed(BUTTON_BACK_KEY))
			{
				logger().error() << "=> BACK" << logs::end;
				exit(0);
				result = this->getState("waitForReboot2");
				return result;
			}

			usleep(100000);
		}
	}

	if (sharedData->strategy() == "FirstSteps")
	{
		logger().info() << "STEPS STEPS STEPS" << logs::end;
	}

	if (sharedData->strategy() == "FirstCarpet")
	{
		logger().info() << "CARPET CARPET CARPET" << logs::end;
	}
*/
	result = this->getState("next");

	return result;
}
