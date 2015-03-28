//drivers...EV3

#include "AsservDriver.hpp"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>

#include "../Common/Utils/Exception.hpp"

using namespace std;
using namespace ev3dev;


AAsservDriver * AAsservDriver::create()
{
	static AsservDriver *instance = new AsservDriver();
	return instance;
}

AsservDriver::AsservDriver() :
		connected_(0)
{
	cout << "AsservDriver" << endl;
	//TEST Motors if connected
	motor arrMotors[4] =
	{
	{ OUTPUT_A },
	{ OUTPUT_B },
	{ OUTPUT_C },
	{ OUTPUT_D } };

	for (unsigned i = 0; i < 4; ++i)
	{

		motor &m = arrMotors[i];
		if (m.connected())
		{
			cout << "(" << 1 + i << ") " << m.type() << " motor on port " << m.port_name() << endl;
			if (m.port_name() == OUTPUT_A)
			{
				_motor_left = OUTPUT_A;
				cout << "A Connected" << endl;
				connected_++;
			}
			if (m.port_name() == OUTPUT_D)
			{
				_motor_right = OUTPUT_D;
				cout << "D Connected" << endl;
				connected_++;
			}

		}
		else
		{
			cout << "(" << 1 + i << ") " << "No Motor" << endl;
		}

	}

//TODO ajouter un parametre pour que les tests moteurs ne s'execute pas si les moteurs ne sont pas connectés
	sleep(1);

	if (connected_ >= 2) //if both motors are connected, then initialize each motor.
	{
		_motor_left.reset();
		_motor_right.reset();
		_motor_left.set_run_mode(motor::run_mode_forever);
		_motor_right.set_run_mode(motor::run_mode_forever);

		_motor_left.set_position_mode(motor::position_mode_absolute);
		_motor_right.set_position_mode(motor::position_mode_absolute);

		_motor_left.set_stop_mode(motor::stop_mode_brake);
		_motor_right.set_stop_mode(motor::stop_mode_brake);
	}

}

void AsservDriver::setMotorLeftPower(int power, int timems)
{
	if (time > 0)
	{
		_motor_left.set_run_mode(motor::run_mode_time);
		_motor_left.set_time_setpoint(timems);
	}
	else
	{
		_motor_left.set_run_mode(motor::run_mode_forever);
	}
	if (_motor_left.regulation_mode() == motor::mode_on)
	{
		//avec regulation
		//TODO verif de -900 à +900
		_motor_left.set_pulses_per_second_setpoint(power);
	}
	else
	{
		//sans regulation
		//TODO verif de -100 à +100
		_motor_left.set_duty_cycle_setpoint(power);
	}

	_motor_left.run();
}
void AsservDriver::setMotorRightPower(int power, int timems)
{
	if (time > 0)
	{
		_motor_right.set_run_mode(motor::run_mode_time);
		_motor_right.set_time_setpoint(timems);
	}
	else
	{
		_motor_right.set_run_mode(motor::run_mode_forever);
	}
	if (_motor_right.regulation_mode() == motor::mode_on)
	{
		//avec regulation
		//TODO verif de -900 à +900
		_motor_right.set_pulses_per_second_setpoint(power);
	}
	else
	{
		//sans regulation
		//TODO verif de -100 à +100
		_motor_right.set_duty_cycle_setpoint(power);
	}

	_motor_right.run();
}

long AsservDriver::getLeftExternalEncoder()
{
	return 0; //TODO getLeftExternalEncoder
}
long AsservDriver::getRightExternalEncoder()
{
	return 0; //TODO getRightExternalEncoder
}

long AsservDriver::getLeftInternalEncoder()
{
	//+/- 2,147,483,648
	return _motor_left.position();

}
long AsservDriver::getRightInternalEncoder()
{
	return _motor_right.position();
}

void AsservDriver::stopMotorLeft()
{
	_motor_left.set_duty_cycle_setpoint(0);
	_motor_left.run();
	_motor_left.stop();
}
void AsservDriver::stopMotorRight()
{
	_motor_right.set_duty_cycle_setpoint(0);
	_motor_right.run();
	_motor_right.stop();
}

int AsservDriver::getMotorLeftCurrent()
{
	return 0;
}
int AsservDriver::getMotorRightCurrent()
{
	return 0;
}

void AsservDriver::enableHardRegulation(bool enable)
{
	if (enable)
	{
		_motor_left.set_regulation_mode(motor::mode_on);
		_motor_right.set_regulation_mode(motor::mode_on);
	}
	else
	{
		_motor_left.set_regulation_mode(motor::mode_off);
		_motor_right.set_regulation_mode(motor::mode_off);
	}

}
