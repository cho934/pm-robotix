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
			cout << "(" << 1 + i << ") " << m.type() << " motor on port " << m.port_name() << flush;
			if (m.port_name() == OUTPUT_A)
			{
				_motor_right = OUTPUT_A;
				cout << " - Motor A Connected (RIGHT)" << endl;
				connected_++;
			}
			else if (m.port_name() == OUTPUT_D)
			{
				_motor_left = OUTPUT_D;
				cout << " - Motor D Connected (LEFT)" << endl;
				connected_++;
			}
			else
				cout << endl;
		}
		else
		{
			cout << "(" << 1 + i << ") " << "No Motor" << endl;
		}
	}

//TODO ajouter un parametre pour que les tests moteurs ne s'execute pas si les moteurs ne sont pas connectés
	//sleep(1);

	if (connected_ >= 2) //if both motors are connected, then initialize each motor.
	{
		_motor_left.reset();
		_motor_right.reset();

		//_motor_left.set_position_mode(motor::position_mode_absolute);
		//_motor_right.set_position_mode(motor::position_mode_absolute);

		_motor_left.set_stop_mode(motor::stop_mode_brake);
		_motor_right.set_stop_mode(motor::stop_mode_brake);

		enableHardRegulation(true);
	}
}

void AsservDriver::setMotorLeftPosition(int ticks, int power)
{
	_motor_left.reset();
	enableHardRegulation(true);
	_motor_left.set_stop_mode(motor::stop_mode_brake);
	_motor_left.set_position_mode(motor::position_mode_relative);
	_motor_left.set_run_mode(motor::run_mode_position);

	_motor_left.set_position_sp(ticks);
	_motor_left.set_pulses_per_second_sp(power);
	_motor_left.set_ramp_up_sp(3000);
	_motor_left.set_ramp_down_sp(4000);
	_motor_left.start();

}

void AsservDriver::setMotorRightPosition(int ticks, int power)
{
	_motor_right.reset();
	enableHardRegulation(true);
	_motor_right.set_stop_mode(motor::stop_mode_brake);
	_motor_right.set_position_mode(motor::position_mode_relative);
	_motor_right.set_run_mode(motor::run_mode_position);

	_motor_right.set_position_sp(ticks);
	_motor_right.set_pulses_per_second_sp(power);
	_motor_right.set_ramp_up_sp(3000);
	_motor_right.set_ramp_down_sp(4000);
	_motor_right.start();
}

// -900 < power < +900
void AsservDriver::setMotorLeftPower(int power, int timems)
{

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
			_motor_left.set_run_mode(motor::run_mode_time);
			_motor_left.set_time_sp(timems);
			usleep(timems*1000);
		}
		else
		{
			_motor_left.set_run_mode(motor::run_mode_forever);
		}
		if (_motor_left.regulation_mode() == motor::mode_on)
		{
			//avec regulation
			//TODO verif de -900 à +900
			_motor_left.set_pulses_per_second_sp(power);
		}
		else
		{
			//sans regulation
			//TODO verif de -100 à +100
			_motor_left.set_duty_cycle_sp(power / 9);
		}

		_motor_left.start();
	}
}
void AsservDriver::setMotorRightPower(int power, int timems)
{
	if ((power < -900))
	{
		cout << "ERROR setMotorRightPower exceed -900!" << endl;
		power = -900;
	}
	else if (power > 900)
	{
		cout << "ERROR setMotorRightPower exceed +900!" << endl;
		power = 900;
	}
	else
	{
		if (timems > 0)
		{
			_motor_right.set_run_mode(motor::run_mode_time);
			_motor_right.set_time_sp(timems);
			usleep(timems*1000);
		}
		else
		{
			_motor_right.set_run_mode(motor::run_mode_forever);
		}
		if (_motor_right.regulation_mode() == motor::mode_on)
		{
			//avec regulation
			//TODO verif de -900 à +900
			_motor_right.set_pulses_per_second_sp(power);
		}
		else
		{
			//sans regulation
			//TODO verif de -100 à +100
			_motor_right.set_duty_cycle_sp(power);
		}
		_motor_right.start();
	}
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
	//_motor_left.set_duty_cycle_sp(0);
	_motor_left.stop();
}
void AsservDriver::stopMotorRight()
{
	//_motor_right.set_duty_cycle_sp(0);
	_motor_right.stop();
}

void AsservDriver::resetEncoder()
{

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
