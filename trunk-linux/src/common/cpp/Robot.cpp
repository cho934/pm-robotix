/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include <iostream>
#include "Robot.hpp"
#include "Exception.hpp"
#include "HostI2cBus.hpp"


pmx::Robot::Robot()
		: base_(*this),
		  myColor_(pmx::PMXNOCOLOR),
		  groveColorSensor_(*this),
		  ledBar_(*this),
		  md25_(*this),
		  encoderLeft_(*this,'B', 17),
		  encoderRight_(*this,'D', 31),
		  //servoTest_(*this, 0),
		  servoDxlTest_(*this),
		  irSensorsGroup_(*this),
		  arduinoBoard_(*this),
		  gpioBoard_(*this)
{

	//Led indicator initialisation
	pmx::LedIndicator::instance().reset();


	//serial DXL
	//long baud = pmx::ServoMotorDxl::instance().dxlGetBaud(7);
	//logger().debug() << "baud dxl n°7= " << baud << utils::end;


}

void pmx::Robot::initialize(const std::string& prefix,
		utils::Configuration& configuration)
{
	logger().debug() << "initialize: " << prefix << utils::end;

}

void pmx::Robot::configure(const std::string & configurationFile)
{
	logger().debug() << "configure configurationFile=" << configurationFile
			<< utils::end;

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

	//close I2C
	utils::HostI2cBus::instance("Robot::stop").close_i2c();

	//close SPI
	utils::HostSpiBus::instance().close();

	//TODO Close ADC, serial ?


	this->stopDevices();
	this->stopManagers();

}

void pmx::Robot::stopDevices()
{
	this->base().stop();

	this->ledBar().stop(true);

}

void pmx::Robot::stopManagers()
{
	logger().debug("Stop managers");

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

void pmx::Robot::goToTeta(double x, double y, double teta, BaseWay way,
		bool detection)
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
