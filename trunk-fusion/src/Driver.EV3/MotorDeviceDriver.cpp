//drivers...EV3

#include "MotorDeviceDriver.hpp"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>

#include "../Common/Utils/Exception.hpp"

using namespace std;
using namespace ev3dev;

AMotorDeviceDriver * AMotorDeviceDriver::create()
{
	static MotorDeviceDriver *instance = new MotorDeviceDriver();
	return instance;
}

MotorDeviceDriver::MotorDeviceDriver() :
		connected_(0)
{
	logger().debug() << "MotorDeviceDriver()" << logs::end;
	//TEST Motors if connected

	motor m = motor(OUTPUT_B);
	if (m.connected())
	{
		if (m.port_name() == OUTPUT_B)
		{
			_motor_device = OUTPUT_B;
			logger().debug() << m.type() << " motor on port " << m.port_name() << " - Connected" << logs::end;
			connected_++;
		}
	}
	else
	{
		logger().error() << " Motor B " << " not connected !!" << logs::end;
	}

	if (connected_ == 1) //if  motor is connected, then initialize it.
	{
		_motor_device.reset();

		_motor_device.set_position_mode(motor::position_mode_absolute);

		_motor_device.set_stop_mode(motor::stop_mode_brake);

		enableHardRegulation(true);
	}
}

// -900 < power < +900
void MotorDeviceDriver::setMotorPower(int power, int timems)
{
	if (connected_ == 1)
	{
		power = -power;

		if ((power < -900))
		{
			cout << "ERROR setMotorLeftPower exceed -900!" << endl;
			power = -900;
		}
		else if (power > 900)
		{
			cout << "ERROR setMotorLeftPower exceed +900!" << endl;
			power = 900;
		}
		else
		{
			if (timems > 0)
			{
				_motor_device.set_run_mode(motor::run_mode_time);
				_motor_device.set_time_sp(timems);
			}
			else
			{
				_motor_device.set_run_mode(motor::run_mode_forever);
			}
			if (_motor_device.regulation_mode() == motor::mode_on)
			{
				//avec regulation
				//TODO verif de -900 à +900
				_motor_device.set_pulses_per_second_sp(power);
			}
			else
			{
				//sans regulation
				//TODO verif de -100 à +100
				_motor_device.set_duty_cycle_sp(power / 9);
			}

			_motor_device.start();
		}
	}
}

long MotorDeviceDriver::getInternalEncoder()
{
	if (connected_ == 1)
	{
		//+/- 2,147,483,648
		return _motor_device.position();
	}
	else
		return 0;
}

void MotorDeviceDriver::stopMotor()
{
	if (connected_ == 1)
	{
		setMotorPower(0, 0);
		_motor_device.stop();
	}
}

void MotorDeviceDriver::resetEncoder()
{

}

int MotorDeviceDriver::getMotorCurrent()
{
	return 0;
}

void MotorDeviceDriver::enableHardRegulation(bool enable)
{
	if (connected_ == 1)
	{
		if (enable)
		{
			_motor_device.set_regulation_mode(motor::mode_on);
		}
		else
		{
			_motor_device.set_regulation_mode(motor::mode_off);
		}
	}
}
