/*!
 * \file
 * \brief Implémentation de la classe Md25.
 */

#include "Md25.hpp"

#include <unistd.h>

#include "Exception.hpp"
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
		{
			connected_ = true;

			//SETUP MD25
			setup();
		}
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

void pmx::Md25::setup()
{
	setMode(MD25_MODE_1); //mode0 => 0-128-255   ;  mode1 => -128+127
	setAccelerationRate(10); //Acc:1,2,3,5,10
	setCommand(MD25_ENABLE_SPEED_REGULATION);
	setCommand(MD25_RESET_ENCODERS);
}

int pmx::Md25::getSoftwareVersion(void)
{
	uchar val = 0;
	val = read_i2c(MD25_SOFTWAREVER_REG);
	return val;
}

float pmx::Md25::getBatteryVolts(void)
{
	return (float) getValue(MD25_VOLTAGE_REG) / 10.0;
}

int pmx::Md25::getAccelerationRate()
{
	return getValue(MD25_ACCELRATE_REG);
}

int pmx::Md25::getMotor1Speed(void)
{
	return getValue(MD25_SPEED1_REG);
}

int pmx::Md25::getMotor2Speed(void)
{
	return getValue(MD25_SPEED2_REG);
}

int pmx::Md25::getMotor1Current(void)
{
	return getValue(MD25_CURRENT1_REG);
}

int pmx::Md25::getMotor2Current(void)
{
	return getValue(MD25_CURRENT2_REG);
}

int pmx::Md25::getMode(void)
{
	return getValue(MD25_MODE_REG);
}

uchar pmx::Md25::getValue(uchar reg)
{
	if (!connected_)
	{
		logger().error() << "Md25::getCommand : return 0; MD25 NOT CONNECTED !" << utils::end;
		return 0;
	}
	uchar val = 0;
	try
	{
		val = read_i2c(reg);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception getCommand: " << e->what() << utils::end;
	}
	return val;

}

void pmx::Md25::getEncoder(long *pvalue, uchar MD25Register) //TODO void
{
	if (!connected_)
	{
		logger().error() << "getEncoder : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	uchar encoder2 = 0;
	uchar encoder5 = 0;
	uchar encoder4 = 0;
	uchar encoder3 = 0;

	encoder2 = read_i2c(MD25Register);
	encoder3 = read_i2c(MD25Register + 1);
	encoder4 = read_i2c(MD25Register + 2);
	encoder5 = read_i2c(MD25Register + 3);

	*pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;

	/*
	 uchar buff[4];
	 int ret = read_i2c_4Bytes(MD25Register, buff);

	 encoder2 = buff[0];
	 encoder3 = buff[1];
	 encoder4 = buff[2];
	 encoder5 = buff[3];

	 *pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;
	 */
	/*
	 logger().debug() << "getEncoder: MD25Register=" << reinterpret_cast<void*>(MD25Register) << " "
	 << reinterpret_cast<void*>(encoder5) << " " << reinterpret_cast<void*>(encoder4) << " "
	 << reinterpret_cast<void*>(encoder3) << " " << reinterpret_cast<void*>(encoder2) << " " << (long) *pvalue
	 << utils::end;
	 */

}

long pmx::Md25::ensureGetEncoder(long, uchar MD25Register)
{
	if (!connected_)
	{
		logger().error() << "ensureGetEncoder : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return 0.0;
	}
	long value = 0;

	try
	{
		getEncoder(&value, MD25Register);

	} catch (utils::Exception * e)
	{
		logger().error() << "1=>ensureGetEncoder::Exception on getEncoder :" << e->what() << utils::end;

		try
		{
			getEncoder(&value, MD25Register);

		} catch (utils::Exception * e)
		{
			logger().error() << "2=>ensureGetEncoder::Exception on getEncoder :" << e->what() << utils::end;
			try
			{
				getEncoder(&value, MD25Register);

			} catch (utils::Exception * e)
			{
				logger().error() << "3=>ensureGetEncoder::Exception on getEncoder :" << e->what() << utils::end;
				getEncoder(&value, MD25Register);
			}
		}
	}

	return value;
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
	try
	{
		setSpeedReg(speed, reg);
	} catch (utils::Exception * e)
	{
		logger().error() << "1=>Exception ensureSetSpeed: setSpeedReg :" << e->what() << utils::end;
		try
		{
			setSpeedReg(speed, reg);
		} catch (utils::Exception * e)
		{
			logger().error() << "2=>Exception ensureSetSpeed: setSpeedReg :" << e->what() << utils::end;
			try
			{
				setSpeedReg(speed, reg);
			} catch (utils::Exception * e)
			{
				logger().error() << "3=>Exception ensureSetSpeed: setSpeedReg :" << e->what() << utils::end;
				setSpeedReg(speed, reg);
			}
		}
	}
}

void pmx::Md25::setSpeedReg(int speed, uchar reg)
{
	if (!connected_)
	{
		logger().error() << "setSpeedReg : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	if ((speed < 0 || speed > 255) && (current_mode_ == MD25_MODE_0 || current_mode_ == MD25_MODE_2))
	{
		logger().error() << "setSpeedReg ERROR : MODE=" << current_mode_ << " ; must 0 < speed < 255 !" << utils::end;
		return;
	}
	if ((speed < -128  || speed > 127) && (current_mode_ == MD25_MODE_1 || current_mode_ == MD25_MODE_3))
	{
		logger().error() << "setSpeedReg ERROR : MODE=" << current_mode_ << " ; must -128 < speed < 127 !" << utils::end;
		return;
	}

	write_i2c(reg, speed);

	//Compare with the read register
	uchar reading = getValue(reg);
	if (speed != reading)
	{
		logger().error() << "=> ERROR COMPARAISON setSpeedReg" << (int) reg << " : write != read :" << (int) speed
				<< " / " << (int) reading << utils::end;
	}
}

void pmx::Md25::stopMotor(uchar reg)
{
	if (!connected_)
	{
		logger().error() << "stopMotor : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return;
	}
	switch (current_mode_)
	{
	case MD25_MODE_0:
	case MD25_MODE_2:
		ensureSetSpeed(128, reg);
		break;
	case MD25_MODE_1:
	case MD25_MODE_3:
		ensureSetSpeed(0, reg);
		break;
	}
}

void pmx::Md25::stopMotors(void)
{
	if (!connected_)
	{
		logger().error() << "stopMotors : return 0 : MD25 NOT CONNECTED !" << utils::end;
		return;
	}

	stopMotor(MD25_SPEED1_REG);
	stopMotor(MD25_SPEED2_REG);
}

void pmx::Md25::write_i2c(uchar command, uchar value)
{
	md25_i2c_.writeRegValue(MD25_DEFAULT_ADDRESS, command, value);
}

uchar pmx::Md25::read_i2c(uchar command)
{
	uchar receivedVal = 0;
	md25_i2c_.readRegValue(MD25_DEFAULT_ADDRESS, command, &receivedVal);
	return receivedVal;
}
/*
 //TODO ne marche pas
 int pmx::Md25::read_i2c_4Bytes(uchar reg, uchar *data)
 {

 int ret = md25_i2c_.readReg_nValue(reg, data, 4);
 return ret;
 }
 */
