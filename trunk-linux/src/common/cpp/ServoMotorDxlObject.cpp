/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlObject.
 */

#include "ServoMotorDxlObject.hpp"
#include "Robot.hpp"


pmx::ServoMotorDxlObject::ServoMotorDxlObject(pmx::Robot & robot, int servoId)
		: ARobotElement(robot), stateOpened_(0), actionStopped_(0)
{
	logger().debug() << "ServoMotorDxlObject::ServoMotorDxlObject()" << utils::end;

	//initialise 1 seul servo pour cet objet.
	//servo1_ = new pmx::Dxl::instance().

}


void pmx::ServoMotorDxlObject::turnMin()
{

}

void pmx::ServoMotorDxlObject::turnMax()
{

}


