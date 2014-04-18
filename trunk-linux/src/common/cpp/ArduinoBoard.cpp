/*!
 * \file
 * \brief Implémentation de la classe ArduinoBoard.
 */

#include "ArduinoBoard.hpp"

#include "Exception.hpp"
#include "HostI2cBus.hpp"
#include "Mutex.hpp"

pmx::ArduinoBoard::ArduinoBoard(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false)
{
	try
	{
		utils::HostI2cBus::instance().open();
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception open: " << e->what() << utils::end;
	}
}

// function for launch command
void pmx::ArduinoBoard::launchCmd(const char command[3], const char action[10])
{
	int ret = 0;

	try
	{
		writeI2c_3Bytes(command);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ArduinoBoard::launchCmd : write i2c : action=" << action << " - " << e->what()
				<< utils::end;
	}

	// give arduino some reaction time
	usleep(1000);

	try
	{
		ret = readI2c_1Byte();
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception ArduinoBoard::testCommand : read i2c" << e->what() << utils::end;
	}

	// check response: 0 = error / 1 = success
	if (ret == 1)
	{
		logger().debug() << "success" << utils::end;
	}
	else
	{
		logger().debug() << "error" << utils::end;
	}

}

int pmx::ArduinoBoard::readI2c_1Byte()
{
	char buf[2];
	lock();
	utils::HostI2cBus::instance().readI2cSize(ARDUINOBOARD_ADDR, buf, 1);
	unlock();
	return buf[0];
}

void pmx::ArduinoBoard::writeI2c_3Bytes(const char *buf)
{
	lock();
	utils::HostI2cBus::instance().writeI2cSize(ARDUINOBOARD_ADDR, buf, 3);
	unlock();
}

