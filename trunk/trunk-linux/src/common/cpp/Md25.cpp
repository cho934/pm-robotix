/*!
 * \file
 * \brief Implémentation de la classe Md25.
 */

#include "Md25.hpp"

#include <unistd.h>

#include "Exception.hpp"
//#include "HostI2cBus.hpp"
#include "Logger.hpp"

pmx::Md25::Md25(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false), current_mode_(MD25_MODE_0)
{
}

void pmx::Md25::init()
{
	try
	{
		//open i2c and setslave
		md25_i2c_.open(MD25_DEFAULT_ADDRESS);

		//test getSoftware
		int soft = getSoftwareVersion();
		logger().debug() << "soft=" << soft << utils::end;
		if (soft == 3)
			connected_ = true;
		else
		{
			logger().error() << "init() : MD25 is now OFF, Software=" << (int) soft << " not eq 3 !" << utils::end;
		}
	} catch (utils::Exception * e)
	{

		logger().error() << "init()::Exception - Md25 NOT CONNECTED !!! (getSoftwareVersion test) " //<< e->what()
				<< utils::end;
	}
}

int pmx::Md25::getSoftwareVersion(void)
{
	uchar val = 0;
	val = read_i2c(MD25_SOFTWAREVER_REG);
	return val;
}

float pmx::Md25::getBatteryVolts(void)
{
	if (!connected_)
	{
		logger().error() << "getBatteryVolts : return 0; MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		val = read_i2c(MD25_VOLTAGE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getBatteryVolts: return 0; " << e->what() << utils::end;
		val = 0;
	}
	return (float) val / 10.0;
}

int pmx::Md25::getAccelerationRate()
{
	if (!connected_)
	{
		logger().error() << "getAccelerationRate : return 0; MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_ACCELRATE_REG, &val);
		val = read_i2c(MD25_ACCELRATE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getAccelerationRate: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor1Speed(void)
{
	if (!connected_)
	{
		logger().error() << "Md25::getMotor1Speed : return 0; MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_SPEED1_REG, &val);
		val = read_i2c(MD25_SPEED1_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getMotor1Speed: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor2Speed(void)
{
	if (!connected_)
	{
		logger().error() << "Md25::getMotor2Speed : return 0; MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_SPEED2_REG, &val);
		val = read_i2c(MD25_SPEED2_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getMotor2Speed: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor1Current(void)
{
	if (!connected_)
	{
		logger().error() << "Md25::getMotor1Current : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_CURRENT1_REG, &val);
		val = read_i2c(MD25_CURRENT1_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getMotor1Current: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMotor2Current(void)
{
	if (!connected_)
	{
		logger().error() << "Md25::getMotor2Current : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_CURRENT2_REG, &val);
		val = read_i2c(MD25_CURRENT2_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getMotor2Current: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getMode(void)
{
	if (!connected_)
	{
		logger().error() << "Md25::getMode : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar val = 0;
	try
	{
		////int err = utils::HostI2cBus::instance().readRegisterbyte(MD25_MODE_REG, &val);
		val = read_i2c(MD25_MODE_REG);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getMode: " << e->what() << utils::end;
	}
	return val;
}

int pmx::Md25::getNbErrors(void)
{
	//TODO return errorCount_;
	return 0;
}

int pmx::Md25::getEncoder(long *pvalue, uchar MD25Register)
{
	if (!connected_)
	{
		logger().error() << "getEncoder : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	uchar encoder2 = 0;
	uchar encoder5 = 0;
	uchar encoder4 = 0;
	uchar encoder3 = 0;
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
		logger().error() << "Exception getEncoder: " << e->what() << utils::end;
	}
	*pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;

	logger().debug() << "getEncoder: " << MD25Register << " " << encoder5 << " " << encoder4 << " " << encoder3
			<< " " << *pvalue << utils::end;

	return err;
}

long pmx::Md25::ensureGetEncoder(long last, uchar MD25Register)
{
	if (!connected_)
	{
		logger().error() << "ensureGetEncoder : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
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

void pmx::Md25::setMode(uchar mode)
{
	if (!connected_)
	{
		logger().error() << "setMode : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	try
	{
		////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_MODE_REG, mode);
		write_i2c(MD25_MODE_REG, mode);
		current_mode_ = mode;
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getEncoder: " << e->what() << utils::end;
	}
}

void pmx::Md25::setAccelerationRate(uchar rate)
{
	if (!connected_)
	{
		logger().error() << "setAccelerationRate : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	try
	{
		/////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_ACCELRATE_REG, rate);
		write_i2c(MD25_ACCELRATE_REG, rate);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception setAccelerationRate: " << e->what() << utils::end;
	}
}

void pmx::Md25::setCommand(uchar command)
{
	if (!connected_)
	{
		logger().error() << "setCommand : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	try
	{
		////int err = utils::HostI2cBus::instance().writeRegisterbyte(MD25_CMD_REG, command);
		write_i2c(MD25_CMD_REG, command);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception setCommand: " << e->what() << utils::end;
	}
}

void pmx::Md25::setSpeedRegisters(int speed_1, int speed_2)
{
	if (!connected_)
	{
		logger().error() << "setSpeedRegisters : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	ensureSetSpeed(speed_1, MD25_SPEED1_REG);
	ensureSetSpeed(speed_2, MD25_SPEED2_REG);
}

void pmx::Md25::ensureSetSpeed(int speed, uchar reg)
{
	if (!connected_)
	{
		logger().error() << "ensureSetSpeed : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
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

int pmx::Md25::setSpeedReg(int speed, uchar reg)
{
	if (!connected_)
	{
		logger().error() << "setSpeedReg : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0;
	}
	uchar reading = 0;
	//int err = 0;
	try
	{
		////err = utils::HostI2cBus::instance().writeRegisterbyte(reg, speed);
		write_i2c(reg, speed);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception setSpeedReg: write :" << e->what() << utils::end;
	}
	try
	{
		////err = utils::HostI2cBus::instance().readRegisterbyte(reg, &read);
		reading = read_i2c(reg);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception setSpeedReg: write :" << e->what() << utils::end;
	}
	//if (current_mode_ == MD25_MODE_1 || current_mode_ == MD25_MODE_3) {
	//if (speed >= 0) {
	if (speed == reading)
	{
		return 0;
	}
	else
	{
		logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read
				<< utils::end;
		return reading;
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

int pmx::Md25::stopMotor(uchar reg)
{
	if (!connected_)
	{
		logger().error() << "stopMotor : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0;
	}
	int nb_err = 0;
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
			logger().error() << "Exception stopMotor mode 1:" << e->what() << utils::end;
			nb_err++;
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
			logger().error() << "Exception stopMotor mode3:" << e->what() << utils::end;
			nb_err++;
		}
		break;
	}
	return nb_err;
}

int pmx::Md25::stopMotors(void)
{
	if (!connected_)
	{
		logger().error() << "stopMotors : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0;
	}
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

void pmx::Md25::write_i2c(uchar command, uchar value)
{
	md25_i2c_.writeRegValue(MD25_DEFAULT_ADDRESS, command, value);
	//utils::HostI2cBus::instance("Md25::write_i2c").writeRegValue(MD25_DEFAULT_ADDRESS, command, value);
}

int pmx::Md25::read_i2c(uchar command)
{
	uchar receivedVal = 0;
	md25_i2c_.readRegValue(MD25_DEFAULT_ADDRESS, command, &receivedVal);
	//utils::HostI2cBus::instance("Md25::read_i2c").readRegValue(MD25_DEFAULT_ADDRESS, command, &receivedVal);
	return receivedVal;
}

