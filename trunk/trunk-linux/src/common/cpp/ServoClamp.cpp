/*!
 * \file
 * \brief Implémentation de la classe ServoClamp.
 */

#include "ServoClamp.hpp"

#include <unistd.h>
#include <string>

#include "Configuration.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

pmx::ServoClamp::ServoClamp(pmx::Robot & robot) :
		ARobotElement(robot)
{
	logger().debug() << "ServoClamp::ServoClamp()" << utils::end;

	//initialise les servos par ID

	servos_[LEFT_CLAMP] = new utils::ServoMotorStd(LEFT_CLAMP);
	servos_[LEFT_ELEVATOR] = new utils::ServoMotorStd(LEFT_ELEVATOR);
	servos_[LEFT_DOOR] = new utils::ServoMotorStd(LEFT_DOOR);

	servos_[RIGHT_CLAMP] = new utils::ServoMotorStd(RIGHT_CLAMP);
	servos_[RIGHT_CLAMP]->isInverted();
	servos_[RIGHT_ELEVATOR] = new utils::ServoMotorStd(RIGHT_ELEVATOR);
	servos_[RIGHT_ELEVATOR]->isInverted();
	servos_[RIGHT_DOOR] = new utils::ServoMotorStd(RIGHT_DOOR);
	servos_[RIGHT_DOOR]->isInverted();

}

void pmx::ServoClamp::initialize(const std::string& prefix, utils::Configuration& configuration)
{
	logger().error() << "ServoClamp::initialize() prefix=" << prefix << utils::end;
	try
	{
		clampLMin_ = configuration.getInt(prefix + "clampLMin_");
		clampLMed_ = configuration.getInt(prefix + "clampLMed_");
		clampLMax_ = configuration.getInt(prefix + "clampLMax_");
		clampLSpeed_ = configuration.getInt(prefix + "clampLSpeed_");

		clampRMin_ = configuration.getInt(prefix + "clampRMin_");
		clampRMed_ = configuration.getInt(prefix + "clampRMed_");
		clampRMax_ = configuration.getInt(prefix + "clampRMax_");
		clampRSpeed_ = configuration.getInt(prefix + "clampRSpeed_");

		elevatorLMin_ = configuration.getInt(prefix + "elevatorLMin_");
		elevatorLMed_ = configuration.getInt(prefix + "elevatorLMed_");
		elevatorLMax_ = configuration.getInt(prefix + "elevatorLMax_");
		elevatorLSpeed_ = configuration.getInt(prefix + "elevatorLSpeed_");

		elevatorRMin_ = configuration.getInt(prefix + "elevatorRMin_");
		elevatorRMed_ = configuration.getInt(prefix + "elevatorRMed_");
		elevatorRMax_ = configuration.getInt(prefix + "elevatorRMax_");
		elevatorRSpeed_ = configuration.getInt(prefix + "elevatorRSpeed_");

		doorLMin_ = configuration.getInt(prefix + "doorLMin_");
		doorLMed_ = configuration.getInt(prefix + "doorLMed_");
		doorLMax_ = configuration.getInt(prefix + "doorLMax_");
		doorLSpeed_ = configuration.getInt(prefix + "doorLSpeed_");

		doorRMin_ = configuration.getInt(prefix + "doorRMin_");
		doorRMed_ = configuration.getInt(prefix + "doorRMed_");
		doorRMax_ = configuration.getInt(prefix + "doorRMax_");
		doorRSpeed_ = configuration.getInt(prefix + "doorRSpeed_");

	} catch (utils::Exception* e)
	{
		logger().error() << "ERROR " << e->what() << utils::end;
	}

	setSpeed(LEFT_CLAMP, clampLSpeed_);
	setSpeed(RIGHT_CLAMP, clampRSpeed_);
	setSpeed(LEFT_ELEVATOR, elevatorLSpeed_);
	setSpeed(RIGHT_ELEVATOR, elevatorRSpeed_);
	setSpeed(LEFT_DOOR, doorLSpeed_);
	setSpeed(RIGHT_DOOR, doorRSpeed_);

}

void pmx::ServoClamp::closeLeftClamp()
{
	setPosition(LEFT_CLAMP, clampLMax_, true);
}

void pmx::ServoClamp::openLeftClamp()
{
	setPosition(LEFT_CLAMP, clampLMin_, true);
}

void pmx::ServoClamp::openLeftClampALittle()
{
	setPosition(LEFT_CLAMP, clampLMed_, true);
}



void pmx::ServoClamp::upLeftElement()
{
	closeLeftClamp();
	setPosition(LEFT_ELEVATOR, elevatorLMin_, true);
}

void pmx::ServoClamp::downLeftElement(bool withClampPressure)
{
	if (withClampPressure)
		closeLeftClamp();
	else
		openLeftClamp();//setPosition(LEFT_CLAMP, clampLMin_, false);

	setPosition(LEFT_ELEVATOR, elevatorLMax_, true);
}

void pmx::ServoClamp::releaseLeftElement()
{
	int pose = getPosition(LEFT_ELEVATOR);
	setPosition(LEFT_ELEVATOR, pose, false);
	int posc = getPosition(LEFT_CLAMP);
	setPosition(LEFT_CLAMP, posc, false);
	int posd = getPosition(LEFT_DOOR);
	setPosition(LEFT_DOOR, posd, false);

}
void pmx::ServoClamp::openLeftDoor()
{
	setPosition(LEFT_DOOR, doorLMax_, false);
}
void pmx::ServoClamp::openLeftDoorALittle()
{

	setPosition(LEFT_DOOR, doorLMed_, false);
}
void pmx::ServoClamp::closeLeftDoor()
{
	setPosition(LEFT_DOOR, doorLMin_, false);
}

void pmx::ServoClamp::closeRightClamp()
{

}
void pmx::ServoClamp::openRightClamp()
{

}

void pmx::ServoClamp::releaseRightElement()
{

}
void pmx::ServoClamp::openRightDoor()
{

}
void pmx::ServoClamp::closeRightDoor()
{

}

//__________________________

void pmx::ServoClamp::readyToTakeLeftElement()
{
	logger().debug() << "readyToTakeLeftElement " << utils::end;
	openLeftClamp();
	downLeftElement(false);
	closeLeftDoor();
	openLeftClamp();

}
void pmx::ServoClamp::takeLeftElement()
{
	logger().debug() << "takeLeftElement " << utils::end;
	openLeftDoorALittle();
	openLeftClampALittle();
	downLeftElement(false);
	upLeftElement();
	closeLeftDoor();
}
void pmx::ServoClamp::pushLeft()
{
	logger().debug() << "pushLeft " << utils::end;
	downLeftElement(true);
	openLeftDoor();
	openLeftClamp();
	releaseLeftElement();
}

//________________________________
void pmx::ServoClamp::readyToTakeRightElement()
{

}
void pmx::ServoClamp::takeRightElement()
{

}
void pmx::ServoClamp::pushRight()
{

}

void pmx::ServoClamp::setPosition(int id, int value, bool hold)
{
	servos_[id]->setServoEnable(1);
	servos_[id]->setServoPosition(value);

	logger().debug() << "servo (" << id << ") from " << getPosition(id) << " to position " << value
			<< utils::end;
	int pos = getPosition(id);
	if (pos < value)
	{
		while (pos < value) //TODO Timeout ?
		{
			//logger().debug() << "while < " << pos << utils::end;
			usleep(10000);
			pos = getPosition(id);
		}
	}
	else
	{
		while (pos > value)
		{
			//logger().debug() << "while > " << pos << utils::end;
			usleep(10000);
			pos = getPosition(id);
		}
	}

	if (!hold)
	{
		servos_[id]->setServoEnable(0);
	}
}

void pmx::ServoClamp::release(int id)
{
	servos_[id]->setServoEnable(0);
}
void pmx::ServoClamp::setSpeed(int id, int speed)
{
	servos_[id]->setServoSpeed(speed);
}

int pmx::ServoClamp::getPosition(int id)
{
	return servos_[id]->getServoCurrentPosition();
}

