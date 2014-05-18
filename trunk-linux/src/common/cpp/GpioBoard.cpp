/*!
 * \file
 * \brief Implémentation de la classe GpioBoard.
 */

#include "GpioBoard.hpp"

#include <unistd.h>

#include "HostI2cBus.hpp"

pmx::GpioBoard::GpioBoard(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false), port0Value_(0), port1Value_(0)
{
}

void pmx::GpioBoard::begin()
{
	try
	{
		//open i2c and setslave
		i2cGB_.open(GPIOBOARD_PCA9555);

		//TODO ajouter un test sur une entrée IN

		connected_ = true;
		setup(); //setup and enable IN/OUT
	} catch (utils::Exception * e)
	{
		logger().error() << "init()::Exception - GpioBoard NOT CONNECTED !!! (error on open()) " //<< e->what()
				<< utils::end;
	}
}

void pmx::GpioBoard::setup()
{
	if (!connected_)
	{
		logger().error() << "setup() : GpioBoard NOT CONNECTED !" << utils::end;
		return;
	}

	write_i2c(CONFIG_P0, 0x00); //defines all pins on Port0 are outputs
	write_i2c(OUT_P0, 0x00); //clears all relays

	write_i2c(CONFIG_P1, 0xFF); //defines all pins on Port1 are inputs
	write_i2c(IN_P1, 0x00); //clears all relays
	usleep(PAUSE);
}

void pmx::GpioBoard::setValueP0(int port, int pin, int value)
{
	if (!connected_)
	{
		logger().error() << "setValueP0() : GpioBoard NOT CONNECTED !" << utils::end;
		return;
	}

	int out = 0;

	if (value == 1)
		out = port0Value_ | (0x01 << pin);
	else if (value == 0)
		out = port0Value_ & (0xFE << pin);

	write_i2c(port, out);
}

void pmx::GpioBoard::setOnP0(int pin) // 0 à 7
{
	setValueP0(OUT_P0, pin, 1);
}

void pmx::GpioBoard::setOffP0(int pin) // 0 à 7
{
	setValueP0(OUT_P0, pin, 0);
}

uchar pmx::GpioBoard::getValueP1(int pin)
{
	if (!connected_)
	{
		logger().error() << "getValueP1() : return 0; GpioBoard NOT CONNECTED !" << utils::end;
		return 0;
	}
	uchar in = read_i2c(IN_P1);
	logger().debug() << "getValueP1 in = " << reinterpret_cast<void*>(in) << utils::end;
	uchar intmp = (in >> pin) & 0x01;
	logger().debug() << "getValueP1 in" << pin << "=" << reinterpret_cast<void*>(intmp) << utils::end;
	return intmp;
}

void pmx::GpioBoard::write_i2c(uchar command, uchar value)
{
	i2cGB_.writeRegValue(GPIOBOARD_PCA9555, command, value);
}

uchar pmx::GpioBoard::read_i2c(uchar command)
{
	uchar receivedVal = 0;
	i2cGB_.readRegValue(GPIOBOARD_PCA9555, command, &receivedVal);
	return receivedVal;
}

