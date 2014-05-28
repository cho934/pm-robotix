/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include "Robot.hpp"

#include <unistd.h>

#include "Configuration.hpp"
#include "HostSpiBus.hpp"
#include "LedIndicator.hpp"

pmx::Robot::Robot()
		: base_(*this), myColor_(pmx::PMXNOCOLOR), runMode_(pmx::ROBOTHOMOLOGATION), groveColorSensor_(*this), ledBar_(
				*this), md25_(*this), encoderLeft_(*this, 'B', 17), encoderRight_(*this, 'D', 31),
		//servoTest_(*this, 0),
		servoDxlTest_(*this), irSensorsGroup_(*this), arduinoBoardDuemilanove_(*this, 0x2A), arduinoBoardMega_(*this,
				0x2B), arduinoBoardSeeed_(*this, 0x2C), gpioBoard_(*this), lcdBoard_()
{

	//initialize i2C components
	groveColorSensor_.begin();
	arduinoBoardDuemilanove_.begin();
	arduinoBoardMega_.begin();
	arduinoBoardSeeed_.begin();
	gpioBoard_.begin();
	lcdBoard_.begin(16, 2);
	md25_.begin();
	servoDxlTest_.begin();

	//Led indicator begin initialisation
	pmx::LedIndicator::instance().reset();

	usleep(300000);
}

void pmx::Robot::initialize(const std::string& prefix, utils::Configuration&)
{
	logger().debug() << "initialize: " << prefix << utils::end;

}

void pmx::Robot::configure(const std::string & configurationFile)
{
	logger().debug() << "configure configurationFile=" << configurationFile << utils::end;

	utils::Configuration configuration;
	configuration.load(configurationFile);

	this->initialize("robot", configuration);
}

void pmx::Robot::start(int useExtEncoders)
{
	//start action manager
	actionManager_.start("ActionManager");

	//config and start asserv
	int lRes = 0;
	int rRes = 0;
	float distRes = 0.0f;

	if (useExtEncoders)
	{
		lRes = 20100;//19885
		rRes = 20100; //20360
		distRes = 0.250f;
		logger().debug("EXTERNAL ENCODERS USED");
	}
	else
	{
		lRes = 1136;
		rRes = 1136;
		distRes = 0.300f;
	}
	base().begin(lRes, rRes, distRes, 1, useExtEncoders);

	logger().info("Robot is started");

}

void pmx::Robot::stop()
{
	logger().info("Stop");

	this->stopDevices();
	logger().debug() << "before  stopManagers" << utils::end;

	this->stopManagers();

	logger().debug() << "after stopManagers" << utils::end;
}

void pmx::Robot::stopDevices()
{
	//this->base().stop();

	this->ledBar().stop(true);

}

void pmx::Robot::stopManagers()
{
	irSensorsGroup_.stopTimer();
	logger().debug("Stop managers");
	actionManager_.stop();

//TODO  créer une Attente de la fin de l'actionManager à la place du usleep
	usleep(5000);

}

