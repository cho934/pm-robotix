/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 */

#include "../Common/State/StateAdjustRobotPosition.hpp"

#include "../Common/Asserv/Asserv.hpp"
#include "../Common/AsservIa/ccbase.h"
#include "../Log/Logger.hpp"
#include "SRobotExtended.hpp"

IAutomateState*
StateAdjustRobotPosition::execute(Robot& r, void *data)
{
	IAutomateState* result;

	this->logger().info() << "start 3" << logs::end;

	//Data* sharedData = (Data*) data;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);
	robot.asserv().start(); //config + thread + config resolution asserv


	logger().info() << "cc_getMatchColor()=" << cc_getMatchColor()<< logs::end;
	cc_setPosition(575.0, 1000.0, 0.0, cc_getMatchColor());

	logger().info() << "cc_getX()=" << cc_getX()<< logs::end;
	logger().info() << "cc_getY()=" << cc_getY()<< logs::end;
	logger().info() << "cc_getThetaInDegree()=" << cc_getThetaInDegree()<< logs::end;


	logger().info() << "Position adjusted." << logs::end;

	result = this->getState("next");

	return result;
}
