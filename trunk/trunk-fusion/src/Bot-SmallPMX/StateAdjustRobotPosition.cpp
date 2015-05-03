/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 */

#include "../Common/State/StateAdjustRobotPosition.hpp"

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"

IAutomateState*
StateAdjustRobotPosition::execute(Robot& r, void *data)
{
	IAutomateState* result;

	this->logger().info() << "start 3" << logs::end;

	//Data* sharedData = (Data*) data;
	//SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	logger().debug() << "Position adjusted." << logs::end;

	result = this->getState("next");

	return result;
}
