//drivers...EV3

#include "ServoDeviceDriver.hpp"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>

#include "../Common/Utils/Exception.hpp"

using namespace std;
using namespace ev3dev;

AServoDeviceDriver * AServoDeviceDriver::create()
{
	static ServoDeviceDriver *instance = new ServoDeviceDriver();
	return instance;
}

ServoDeviceDriver::ServoDeviceDriver() :
		connected_(0)
{
	logger().debug() << "ServoDeviceDriver()" << logs::end;

	motor m = motor(OUTPUT_C);
	if (m.connected())
	{
		if (m.port_name() == OUTPUT_C)
		{
			_servo_device = OUTPUT_C;
			logger().debug() << m.type() << " motor on port " << m.port_name() << " - Connected"
					<< logs::end;
			connected_++;
		}
	}
	else
	{
		logger().error() << " Motor OUTPUT_C " << " not connected !!" << logs::end;
	}

	if (connected_ == 1) //if both motors are connected, then initialize each motor.
	{
		_servo_device.reset();

		_servo_device.set_position_mode(motor::position_mode_absolute);

		_servo_device.set_stop_mode(motor::stop_mode_brake);

		enableHardRegulation(true);
	}
}

void ServoDeviceDriver::setMotorPosition(int pos, int ramptimems, int power)
{
	if (connected_ == 1)
	{
		_servo_device.set_position_sp(pos);
		enableHardRegulation(true);
		_servo_device.set_run_mode(motor::run_mode_position);
		_servo_device.set_position_mode(motor::position_mode_absolute);
		_servo_device.set_stop_mode(motor::stop_mode_hold);
		_servo_device.set_pulses_per_second_sp(power);
		_servo_device.set_ramp_up_sp(ramptimems);
		_servo_device.set_ramp_down_sp(ramptimems);
		_servo_device.start();
	}
}

long ServoDeviceDriver::getInternalEncoder()
{
	if (connected_ == 1)
	{
		//+/- 2,147,483,648
		return _servo_device.position();
	}
	else
		return 0;
}

void ServoDeviceDriver::stopMotor()
{
	if (connected_ == 1)
	{
		_servo_device.set_stop_mode(motor::stop_mode_brake);
		_servo_device.stop();
	}
}

void ServoDeviceDriver::resetEncoder(int pos)
{
	if (connected_ == 1)
	{
		_servo_device.set_position(pos);
	}
}

int ServoDeviceDriver::getMotorCurrent()
{
	return 0;
}

void ServoDeviceDriver::enableHardRegulation(bool enable)
{
	if (connected_ == 1)
	{
		if (enable)
		{
			_servo_device.set_regulation_mode(motor::mode_on);
		}
		else
		{
			_servo_device.set_regulation_mode(motor::mode_off);
		}
	}
}
