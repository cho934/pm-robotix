/*!
 * \file
 * \brief Implémentation de la classe IrSensor.
 */

#include <cmath>
#include "IrSensor.hpp"
#include "Robot.hpp"
#include "HostAdcPort.hpp"

pmx::IrSensor::IrSensor(pmx::Robot & robot, ushort adcPin, int type)
		: ARobotElement(robot), adcPin_(adcPin), type_(type), voltage_(0), distanceMm_(9999.0)
{
	try
	{
		utils::HostAdcPort::instance().open();

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception IrSensor init: " << e->what() << utils::end;
	}
	try
	{
		int temp = utils::HostAdcPort::instance().readTemp();
		logger().info() << "temp" << adcPin << " " << temp << utils::end;

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception IrSensor init: " << e->what() << utils::end;
	}

}

void pmx::IrSensor::reset()
{
	logger().debug() << "              !! reset !! " << utils::end;
	this->voltage_ = 0;
	this->distanceMm_ = 9999.0;
}

int pmx::IrSensor::getVoltage()
{
	try
	{
		voltage_ = utils::HostAdcPort::instance().readMillivolt(adcPin_);
		logger().debug() << "getAdcValue" << adcPin_ << " = " << voltage_ << utils::end;

	} catch (utils::Exception * e)
	{
		logger().error() << "Exception IrSensor getAdcValue: " << e->what() << utils::end;
	}
	return voltage_;
}

int pmx::IrSensor::getDistance()
{
	try
	{
		voltage_ = getVoltage();
		distanceMm_ = gp2Convert(type_, voltage_);
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception IrSensor getDistance: " << e->what() << utils::end;
	}
	if (distanceMm_ >= 9999.0)
	{
		distanceMm_ = 9999.0;
	}
	return (int)distanceMm_;
}

double pmx::IrSensor::gp2Convert(int type, int value)
{
	double distanceMillimetre = 0.0;
	if (type == 80)
	{
		//distanceMillimetre = 270.0 * pow(value * 2.5 / 128.0 * 3.3 / 5.0, -1.1); //pour le 80cm //a simplifier si le calcul est bon pour 3.3V

		//distanceMillimetre = pow((valeur * 2.5 / 128.0), -1.1) * 270.0; //version 5V

		if (value > 2500) //saturation
		{
			distanceMillimetre = 55;

		}
		else if (value < 200) //saturation
		{
			distanceMillimetre = 600;
		}
		else
		{
			distanceMillimetre = 845000 * pow(value, -1.15);
		}
	}
	if (type == 30)
	{
		//!\todo version 30cm
		distanceMillimetre = 93620.1 * pow(value, -0.949);
		//y = 9362,1x-0,949
	}
	if (type == 150)
	{
		//!\todo version 150cm
		//y = 135300x-1,112
		distanceMillimetre = 1353000 * pow(value, -1.112);
	}

	return distanceMillimetre;
}

