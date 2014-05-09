/*!
 * \file
 * \brief Implémentation de la classe ArduinoBoard.
 */

#include "ArduinoBoard.hpp"

#include <unistd.h>

#include "Exception.hpp"
#include "HostI2cBus.hpp"

pmx::ArduinoBoard::ArduinoBoard(pmx::Robot & robot, int addr)
		: ARobotElement(robot), connected_(false), addr_(addr)
{
}

void pmx::ArduinoBoard::init()
{
	try
	{
		//open i2c and setslave
		ardui_i2c_.open(addr_);

		int ack = 0;
		ack = launchCmd("ACK", "Acknowledge");

		if (ack == 125)
		{
			connected_ = true;
		}
		else
		{
			logger().error() << "init() : ArduinoBoard is now OFF, ack=" << (int) ack  << " not eq 125 !"<< utils::end;
		}

	} catch (utils::Exception * e)
	{
		logger().error() << "init()::Exception - ArduinoBoard(" << addr_ << ") NOT CONNECTED !!! (ack test) " //<< e->what()
				<< utils::end;
	}
}

// function for launch command
int pmx::ArduinoBoard::launchCmd(const char command[3], const char action[10])
{
	if (!connected_)
	{
		logger().error() << "launchCmd() : ArduinoBoard NOT CONNECTED !" << utils::end;
		return 0;
	}

	int ret = 0;

	try
	{
		writeI2c_3Bytes(command);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception launchCmd() : write i2c : action=" << action << " - " << e->what()
				<< utils::end;
	}

	// give arduino some reaction time
	usleep(1000); //TODO ?

	try
	{
		ret = readI2c_1Byte();
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception testCommand() : read i2c" << e->what() << utils::end;
	}

	// check response: 0 = error / 1 = success
	if (ret == 1 || ret ==125)
	{
		logger().debug() << "success" << utils::end;
	}
	else
	{
		logger().debug() << "error" << utils::end;
	}
	return ret;

}

int pmx::ArduinoBoard::readI2c_1Byte()
{
	char buf[2];
	ardui_i2c_.readI2cSize(addr_, buf, 1);
	return buf[0];
}

void pmx::ArduinoBoard::writeI2c_3Bytes(const char *buf)
{
	ardui_i2c_.writeI2cSize(addr_, buf, 3);
}

