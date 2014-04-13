/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlObject.
 */

#include "ServoMotorDxlObject.hpp"
#include "Robot.hpp"

pmx::ServoMotorDxlObject::ServoMotorDxlObject(pmx::Robot & robot)
		: ARobotElement(robot), id_(7), stateOpened_(0), actionStopped_(0)
{
	logger().debug() << "ServoMotorDxlObject::ServoMotorDxlObject()" << utils::end;

	//initialise 1 seul servo pour cet objet.
	long temp = pmx::ServoMotorDxl::instance().dxlGetTemperature(id_);
	logger().info() << "Temperature dxl n°" << id_ << " =" << temp << utils::end;

}

void pmx::ServoMotorDxlObject::turnMin()
{
	logger().debug() << "turn min" << utils::end;
	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, 100);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}

	//TODO return pos
}

void pmx::ServoMotorDxlObject::turnMax()
{
	logger().debug() << "turn max" << utils::end;

	int finished = 0;
	long moving = 0;
	pmx::ServoMotorDxl::instance().dxlSetPos(id_, 900);
	while (pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_) == 1)
	{
		moving = pmx::ServoMotorDxl::instance().dxlGetAcMoving(id_);
		finished = pmx::ServoMotorDxl::instance().dxlGetPos(id_);
		logger().debug() << "moving=" << moving << " finished=" << finished << utils::end;
		usleep(100000);
	}
}

