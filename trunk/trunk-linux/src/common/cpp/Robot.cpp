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
		: 	base_(*this),
			myColor_(pmx::PMXNOCOLOR),
			runMode_(pmx::ROBOTHOMOLOGATION),
			groveColorSensor_(*this),
			ledBar_(*this),
			md25_(*this),
			encoderLeft_(*this, 'B', 17),
			encoderRight_(*this, 'D', 31),
			//servoTest_(*this, 0),
			servoDxlTest_(*this),
			irSensorsGroup_(*this),
			arduinoBoardDuemilanove_(*this, 0x2A),
			arduinoBoardMega_(*this, 0x2B),
			arduinoBoardSeeed_(*this, 0x2C),
			gpioBoard_(*this),
			lcdBoard_()
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

}

void pmx::Robot::initialize(const std::string& prefix, utils::Configuration& configuration)
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

void pmx::Robot::start()
{
	actionManager_.start();

	logger().info("Robot is started");

}

void pmx::Robot::stop()
{
	logger().info("Stop");

	//close SPI
	utils::HostSpiBus::instance().close();

	//TODO Close ADC, serial ?

	this->stopDevices();
	logger().debug() << "before  stopManagers" << utils::end;

	this->stopManagers();

	logger().debug() << "after stopManagers" << utils::end;
}

void pmx::Robot::stopDevices()
{
	this->base().stop();

	this->ledBar().stop(true);

}

void pmx::Robot::stopManagers()
{
	logger().debug("Stop managers");
	actionManager_.stop();
//todo Attente fin manager
	usleep(5000);

}

void pmx::Robot::goTo(double x, double y, BaseWay way, bool detection)
{
	/*

	 if (detection == true)
	 {
	 irSensorsGroup().startTimer();
	 }

	 base().arrivedDestination(false);
	 bool opponentDetected = false;

	 while (base().arrivedDestination() == false)
	 {
	 opponentDetected = base().checkOpponent();
	 if (!opponentDetected)
	 {
	 opponentDetected = base().movexy(x, y, way, detection);

	 if (opponentDetected == true)
	 {
	 base().stop();
	 logger().info() << " !! opponentDetected time="
	 << chronometerRobot().getElapsedTimeInSec()
	 << utils::end;
	 }
	 }
	 else
	 {
	 base().stop();
	 logger().info() << " sleep" << utils::end;
	 sleep(1);
	 }
	 }

	 if (detection == true)
	 {
	 irSensorsGroup().stopTimer();
	 }*/

}

void pmx::Robot::goToTeta(double x, double y, double teta, BaseWay way, bool detection)
{

	/*
	 if (detection == true)
	 {
	 irSensorsGroup().startTimer();
	 }

	 base().arrivedDestination(false);
	 bool opponentDetected = false;

	 while (base().arrivedDestination() == false)
	 {
	 opponentDetected = base().checkOpponent();
	 if (!opponentDetected)
	 {
	 opponentDetected = base().movexyTeta(x, y, way, teta, detection);

	 if (opponentDetected == true)
	 {
	 base().stop();
	 logger().info() << " !! opponentDetected time="
	 << chronometerRobot().getElapsedTimeInSec()
	 << utils::end;
	 }
	 }
	 else
	 {
	 base().stop();
	 logger().info() << " sleep" << utils::end;
	 sleep(1);
	 }
	 }

	 if (detection == true)
	 {
	 irSensorsGroup().stopTimer();
	 }*/

}
