/*!
 * \file
 * \brief Implémentation de la classe Md25.
 */

//#include <stdlib.h>
#include "Md25.hpp"
#include "../../common/cpp/HostI2cBus.hpp"

pmx::Md25::Md25(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false)
{
	try
	{
		utils::HostI2cBus::instance().open();
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception open: " << e->what() << utils::end;
	}
	/*
	 try
	 {
	 utils::HostI2cBus::instance().setSlave(MD25_DEFAULT_ADDRESS);
	 connected_ = true;
	 } catch (utils::Exception * e)
	 {
	 //deactivate the device if not connected
	 connected_ = false;
	 logger().error() << "Exception setSlave: " << e->what() << utils::end;
	 }
	 */
	setMode(current_mode_);

	/*
	 //test de la valeur de batterie
	 float bat = getBatteryVolts();
	 if (bat < 11)
	 logger().info() << " !! RECHARGE BATTERIE MD25 NECESSAIRE !! (" << bat << " volts)" << utils::end; //!\todo Stopper le robot
	 else
	 logger().info() << "Batterie de motorisation ok (" << bat << " volts)" << utils::end;
	 */
}

int pmx::Md25::getSoftwareVersion(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_SOFTWAREVER_REG, &val);
		val = read_i2c(MD25_SOFTWAREVER_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getSoftwareVersion: " << e->what() << utils::end;
	}
	return val;
}

float pmx::Md25::getBatteryVolts(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_VOLTAGE_REG, &val);
		val = read_i2c(MD25_VOLTAGE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getBatteryVolts: " << e->what() << utils::end;
	}
	return (float) val / 10.0;
}

int pmx::Md25::getAccelerationRate()
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_ACCELRATE_REG, &val);
		val = read_i2c(MD25_ACCELRATE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getAccelerationRate: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor1Speed(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_SPEED1_REG, &val);
		val = read_i2c(MD25_SPEED1_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getMotor1Speed: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor2Speed(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_SPEED2_REG, &val);
		val = read_i2c(MD25_SPEED2_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getMotor2Speed: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor1Current(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_CURRENT1_REG, &val);
		val = read_i2c(MD25_CURRENT1_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getMotor1Current: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor2Current(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_CURRENT2_REG, &val);
		val = read_i2c(MD25_CURRENT2_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getMotor2Current: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMode(void)
{
	uint8_t val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_MODE_REG, &val);
		val = read_i2c(MD25_MODE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getMode: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getNbErrors(void)
{
	//TODO return errorCount_;
	return 0;
}

int pmx::Md25::getEncoder(long *pvalue, uint8_t MD25Register)
{
	uint8_t encoder2 = 0;
	uint8_t encoder5 = 0;
	uint8_t encoder4 = 0;
	uint8_t encoder3 = 0;
	int err = 0;
	try
	{
		////err = utils::HostI2cBus::instance().readRegisterbyte(MD25Register, &encoder2);
		////err += utils::HostI2cBus::instance().readRegisterbyte(MD25Register + 1, &encoder3);
		////err += utils::HostI2cBus::instance().readRegisterbyte(MD25Register + 2, &encoder4);
		////err += utils::HostI2cBus::instance().readRegisterbyte(MD25Register + 3, &encoder5);

		encoder2 = read_i2c(MD25Register);
		encoder3 = read_i2c(MD25Register + 1);
		encoder4 = read_i2c(MD25Register + 2);
		encoder5 = read_i2c(MD25Register + 3);

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getEncoder: " << e->what() << utils::end;
	}
	*pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;

	logger().debug() << "MD25:getEncoder: " << MD25Register << " " << encoder5 << " " << encoder4 << " " << encoder3
			<< " " << *pvalue << utils::end;

	return err;
}

long pmx::Md25::ensureGetEncoder(long last, uint8_t MD25Register)
{
	long value = 0;
	int err = getEncoder(&value, MD25Register);
	if (err < 0 || value > last + 100) //filtrage par rapport à l'ancienne valeur
	{
		value = 0;
		int err2 = getEncoder(&value, MD25Register);
		if (err2 < 0 || value > last + 100) //filtrage par rapport à l'ancienne valeur
		{
			return last;
		}
		else
		{
			return value;
		}
	}
	else
	{
		return value;
	}
	return last;
}

void pmx::Md25::setMode(uint8_t mode)
{
	try
	{
		////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_MODE_REG, mode);
		write_i2c(MD25_MODE_REG, mode);
		current_mode_ = mode;
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::getEncoder: " << e->what() << utils::end;
	}
}

void pmx::Md25::setAccelerationRate(uint8_t rate)
{
	try
	{
		/////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_ACCELRATE_REG, rate);
		write_i2c(MD25_ACCELRATE_REG, rate);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::setAccelerationRate: " << e->what() << utils::end;
	}
}

void pmx::Md25::setCommand(uint8_t command)
{
	try
	{
		////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_CMD_REG, command);
		write_i2c(MD25_CMD_REG, command);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::setCommand: " << e->what() << utils::end;
	}
}

void pmx::Md25::setSpeedRegisters(uint8_t speed_1, uint8_t speed_2)
{
	ensureSetSpeed(speed_1, MD25_SPEED1_REG);
	ensureSetSpeed(speed_2, MD25_SPEED2_REG);
}

void pmx::Md25::ensureSetSpeed(uint8_t speed, uint8_t reg)
{
	int err = setSpeedReg(speed, reg);
	if (err != 0)
	{
		logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (1) : err=" << err
				<< utils::end;
		int err2 = setSpeedReg(speed, reg);
		if (err2 != 0)
		{
			logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (2) : err=" << err2
					<< utils::end;
		}
	}
}

int pmx::Md25::setSpeedReg(uint8_t speed, uint8_t reg)
{
	uint8_t read;
	//int err = 0;
	try
	{
		////err = utils::HostI2cBus::instance().writeRegisterbyte(reg, speed);
		write_i2c(reg, speed);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::setSpeedReg: write :" << e->what() << utils::end;
	}
	try
	{
		////err = utils::HostI2cBus::instance().readRegisterbyte(reg, &read);
		read = read_i2c(reg);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception Md25::setSpeedReg: write :" << e->what() << utils::end;
	}
	//if (current_mode_ == MD25_MODE_1 || current_mode_ == MD25_MODE_3) {
	//if (speed >= 0) {
	if (speed == read)
	{
		return 0;
	}
	else
	{
		logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read
				<< utils::end;
		return read;
	}
	//}else {
	//    if ((speed + 256) == read) //decalage de 256 par rapport à la lecture.
	//    {
	//        return 0;
	//    }else {
	//        logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read << utils::end;
	//        return read;
	//    }
	//}
	//}else {
	//    if (speed == read) {
	//        return 0;
	//    }else {
	//        logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read << utils::end;
	//        return read;
	//    }
	//}
}

int pmx::Md25::stopMotor(uint8_t reg)
{
	int ret;
	switch (current_mode_)
	{
	case MD25_MODE_0:
	case MD25_MODE_2:
		try
		{
			/////ret = utils::HostI2cBus::instance().writeRegisterbyte(reg, 128);
			write_i2c(reg, 128);
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception Md25::stopMotor mode 1:" << e->what() << utils::end;
		}
		break;
	case MD25_MODE_1:
	case MD25_MODE_3:
		try
		{
			////ret = utils::HostI2cBus::instance().writeRegisterbyte(reg, 0);
			write_i2c(reg, 0);
		} catch (utils::Exception * e)
		{
			logger().error() << "Exception Md25::stopMotor mode3:" << e->what() << utils::end;
		}
		break;
	}
	return ret;
}

int pmx::Md25::stopMotors(void)
{
	int res1 = stopMotor(MD25_SPEED1_REG);
	//if (res1 == 0)
	//logger().debug() << "stopMotor1:ok" << utils::end;
	int tmp = 0;
	while (res1 < 0) //try 5 times
	{
		logger().error() << "apply stopMotor1: error" << utils::end;
		res1 = stopMotor(MD25_SPEED1_REG);
		//if (res1 == 0)
		//    logger().debug() << "stopMotor1:ok" << utils::end;
		tmp++;
		if (tmp > 5)
		{
			logger().error() << "stopMotor1: error > 5" << utils::end;
			return -3;
		}
	}

	int res2 = stopMotor(MD25_SPEED2_REG);
	//if (res2 == 0)
	//    logger().debug() << "stopMotor2:ok" << utils::end;
	tmp = 0;
	while (res2 < 0) //try 5 times
	{
		logger().error() << "apply stopMotor2: error" << utils::end;
		res2 = stopMotor(MD25_SPEED2_REG);
		//if (res2 == 0)
		//logger().debug() << "stopMotor2:ok" << utils::end;
		tmp++;
		if (tmp > 5)
		{
			logger().error() << "stopMotor2: error > 5" << utils::end;
			return -3;
		}
	}
	return 0;
}

void pmx::Md25::write_i2c(uint8_t command, uint8_t value)
{
	try
	{
		utils::HostI2cBus::instance().writeRegValue(MD25_DEFAULT_ADDRESS, command, value);

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception GroveColorSensor::write_i2c: " << e->what() << utils::end;
	}
}

uint8_t pmx::Md25::read_i2c(uint8_t command)
{
	try
	{
		uint8_t receivedVal = 0;
		utils::HostI2cBus::instance().readRegValue(MD25_DEFAULT_ADDRESS, command, &receivedVal);
		return receivedVal;

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception GroveColorSensor::read_i2c: " << e->what() << utils::end;
	}
	return 0;
}

