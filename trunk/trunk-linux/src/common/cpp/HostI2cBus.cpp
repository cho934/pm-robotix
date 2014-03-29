/*!
 * \file
 * \brief Implémentation de la classe HostI2cBus.
 */

#include <iostream>
#include "HostI2cBus.hpp"

utils::HostI2cBus::HostI2cBus()
		: i2c_device_(NULL), opened_(0)
{
}

utils::HostI2cBus::~HostI2cBus()
{
	if (opened_ == 1)
	{
		throw new I2cException("Error i2c  not closed properly");
	}
}

void utils::HostI2cBus::openI2c()
{
	int i2c_id = 0; //Bus I2C sur la carte APF9328
	i2c_device_ = as_i2c_open(i2c_id);

	if (i2c_device_ == NULL)
	{
		throw new I2cException(
				"Error can't open i2c port");
	}
	else
		opened_ = 1;

}

void utils::HostI2cBus::closeI2c(void)
{
	int ret = as_i2c_close(i2c_device_);
	if (ret < 0)
	{
		throw new I2cException("Error, can't close I2C");

	}
	opened_ = 0;
}

