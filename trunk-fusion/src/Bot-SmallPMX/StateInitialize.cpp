/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "../Common/State/StateInitialize.hpp"

#include <unistd.h>

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Action/ButtonBar.hpp"
#include "../Common/Action/LedBar.hpp"
#include "../Common/Action.Driver/AButtonDriver.hpp"
#include "../Common/Action.Driver/ALedDriver.hpp"
#include "../Common/Robot.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"

class IAutomateState;

IAutomateState*
StateInitialize::execute(Robot& r, void *data)
{
	this->logger().info() << "start 2" << logs::end;
	Data* sharedData = (Data*) data;
	//SRobotExtended* robot = (SRobotExtended*) &r;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	if (!sharedData->skipSetup())
	{

		logger().info() << "Please choose color..." << logs::end;
		while (!robot.actions.buttonBar().pressed(BUTTON_ENTER_KEY)
				|| robot.getMyColor() == PMXNOCOLOR)
		{
			if (robot.actions.buttonBar().pressed(BUTTON_RIGHT_KEY))
			{
				robot.setMyColor(PMXYELLOW);

				logger().debug() << "=> YELLOW..." << logs::end;
			}
			if (robot.actions.buttonBar().pressed(BUTTON_LEFT_KEY))
			{
				robot.setMyColor(PMXGREEN);
				logger().debug() << "=> GREEN..." << logs::end;
			}
			if (robot.actions.buttonBar().pressed(BUTTON_UP_KEY))
			{
				logger().debug() << "=> Initialize mechanical..." << logs::end;

				robot.actions.supportSystem().straighten(900, 1500);
				usleep(300000);
				robot.actions.supportSystem().incline(900, 1500);
				//pause avec le tracksystem
				robot.actions.trackSystem().moveForward(800, 0);
				//pause avec le redcarpetsystem
				robot.actions.redcarpetSystem().leftDeploy();
				robot.actions.redcarpetSystem().rightDeploy();
				robot.actions.trackSystem().stopMotor();
				//sleep(1);

				robot.actions.supportSystem().straighten(900, 1500);

			}
			if (robot.actions.buttonBar().pressed(BUTTON_BACK_KEY))
			{
				robot.actions.supportSystem().stopMotor();
				robot.actions.redcarpetSystem().releaseAll();
			}
			if (robot.actions.buttonBar().pressed(BUTTON_DOWN_KEY))
			{
				robot.actions.supportSystem().resetPosition(2);
				robot.actions.supportSystem().straighten(900, 1500);
			}

			if (robot.getMyColor() == PMXNOCOLOR)
			{
				robot.actions.ledBar().set(0, LED_RED);
				robot.actions.ledBar().set(1, LED_RED);
			}
			if (robot.getMyColor() == PMXYELLOW)
			{
				robot.actions.ledBar().setOff(1);
				robot.actions.ledBar().set(0, LED_ORANGE);
			}
			if (robot.getMyColor() == PMXGREEN)
			{
				robot.actions.ledBar().setOff(0);
				robot.actions.ledBar().set(1, LED_GREEN);
			}

			usleep(800);
		}

	}
	else
	{
		logger().info() << "skipSetup..." << logs::end;
		if (robot.getMyColor() == PMXNOCOLOR)
		{
			robot.actions.ledBar().set(0, LED_RED);
			robot.actions.ledBar().set(1, LED_RED);
		}
		if (robot.getMyColor() == PMXYELLOW)
		{
			robot.actions.ledBar().setOff(1);
			robot.actions.ledBar().set(0, LED_ORANGE);
		}
		if (robot.getMyColor() == PMXGREEN)
		{
			robot.actions.ledBar().setOff(0);
			robot.actions.ledBar().set(1, LED_GREEN);
		}
	}

	if (robot.getMyColor() == PMXGREEN)
		logger().info() << "color is : GREEN" << logs::end;
	if (robot.getMyColor() == PMXYELLOW)
		logger().info() << "color is : YELLOW" << logs::end;
	if (robot.getMyColor() == PMXNOCOLOR)
	{
		logger().error() << "color is : NOCOLOR" << logs::end;
		exit(0);
	}

	return this->getState("next");
}
