/*!
 * \file
 * \brief Implémentation de la classe Robot.
 */

#include "Robot.hpp"

#include <unistd.h>

#include "Configuration.hpp"
#include "HostSpiBus.hpp"
#include "LedIndicator.hpp"

pmx::Robot::Robot() :
		base_(*this), myColor_(pmx::PMXNOCOLOR), runMode_(pmx::ROBOTHOMOLOGATION), groveColorSensor_(
				*this), ledBar_(*this), md25_(*this),
				//encoderLeft_(*this, 'B', 17), encoderRight_(*this, 'D', 31),
		//servoTest_(*this, 0),

		servoDxlTest_(*this, 1, 475, 841),

		 servoDxlLeft_(*this, 3, 520, 200),
		 servoDxlRight_(*this, 5, 480, 820),
		 servoDxlFront_(*this, 7, 570, 790),
		 servoDxlRear_(*this, 6, 570, 790),
		 /*servoDxlP14_(*this, 14, 531, 841),
		 servoDxlP4_(*this, 4, 531, 841),
		 servoDxlP6front_(*this, 6, 770, 540),
		 */
		irSensorsGroup_(*this),
/* arduinoBoardDuemilanove_(*this, 0x2A)
, arduinoBoardMega_(*this, 0x2B)
, arduinoBoardSeeed_(*this, 0x2C), */
gpioBoard_(*this), lcdBoard_(), clamp_(*this)
{

	//initialize i2C components
	groveColorSensor_.begin();
	//arduinoBoardDuemilanove_.begin();
	//arduinoBoardMega_.begin();
	//arduinoBoardSeeed_.begin();
	gpioBoard_.begin();
	lcdBoard_.begin(16, 2);
	md25_.begin();
	servoDxlTest_.begin();


	 servoDxlLeft_.begin();
	 servoDxlRight_.begin();
	 servoDxlFront_.begin();
	 servoDxlRear_.begin();
		/* servoDxlP6front_.begin();
	 servoDxlP4_.begin();
	 servoDxlP14_.begin();
	 */
	//Led indicator begin initialisation
	pmx::LedIndicator::instance().reset();

	usleep(300000);
}

void pmx::Robot::initialize(const std::string& prefix, utils::Configuration& conf)
{
	logger().debug() << "initialize: " << prefix << utils::end;

	this->clamp().initialize("servo-", conf);
}

void pmx::Robot::configure(const std::string & configurationFile)
{
	logger().debug() << "configure configurationFile=" << configurationFile << utils::end;

	utils::Configuration configuration;
	configuration.load(configurationFile);

	this->initialize("robot", configuration);
}

void pmx::Robot::start(int useExtEncoders, int startAsserv)
{
	//start action manager
	actionManager_.start("ActionManager");

	//config and start asserv
	int lRes = 0;
	int rRes = 0;
	float distRes = 0.0f;

	if (useExtEncoders)
	{
		lRes = 20100; //19885
		rRes = 20100; //20360
		distRes = 0.250f;
		logger().info("EXTERNAL ENCODERS USED");
	}
	else
	{
		lRes = 1136;
		rRes = 1136;
		distRes = 0.300f;
		logger().info("INTERNAL ENCODERS USED");
	}
	base().begin(lRes, rRes, distRes, startAsserv, useExtEncoders);

	logger().info("Robot is started");

}

void pmx::Robot::stop()
{
	logger().debug("Stop");
	this->base().stop();

	this->stopDevices();
	logger().debug() << "before  stopManagers" << utils::end;

	this->stopManagers();

	logger().debug() << "after stopManagers" << utils::end;
	usleep(200000);
}

void pmx::Robot::stopDevices()
{
	this->ledBar().stop(true);
	this->clamp().releaseLeftElement();
	this->clamp().releaseRightElement();
		//TODO autres
}

void pmx::Robot::stopManagers()
{
	irSensorsGroup_.stopTimer();
	logger().debug("Stop managers");
	actionManager_.stop();

//TODO  créer une Attente de la fin de l'actionManager à la place du usleep
	usleep(5000);

}

