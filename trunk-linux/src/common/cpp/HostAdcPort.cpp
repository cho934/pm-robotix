/*!
 * \file
 * \brief Implémentation de la classe HostAdcPort.
 */

#include "HostAdcPort.hpp"

#include <as_devices/as_max1027_3_3.h>


utils::HostAdcPort::HostAdcPort()
		: max1027_device_(NULL), opened_(0)
{
}

void utils::HostAdcPort::open()
{
	AS_max1027_mode mode = AS_MAX1027_SLOW;

	int apf9328_spiNum = 1; //MAX1027_SPI_NUM on APF9328

	if (opened_ == 0)
	{
		max1027_device_ = as_max1027_open(apf9328_spiNum, mode);
		if (max1027_device_ == NULL)
		{
			throw new AdcException(
					"Error HostAdcPort::open can't open max1027. Have you execute the cmd :modprobe max1027 ?");
		}
		else
		{
			opened_ = 1;
		}
	}
	else //spi for adc max 1027 already opened
	{
		throw new AdcWarning("Warning HostAdcPort::open max1027 already opened !");
	}

	//configure average
	setAverage(32);
}

void utils::HostAdcPort::close(void)
{
	if (opened_ == 1)
	{
		int ret = as_max1027_close(max1027_device_);
		if (ret < 0)
		{
			throw new AdcException("Error HostAdcPort::close, can't close max1027 !");
		}
		opened_ = 0;
	}
	else
	{
		throw new AdcException("Error HostAdcPort::close, max1027 already closed !");
	}
}

int utils::HostAdcPort::readTemp(void)
{
	int temp = 0;
	int ret = as_max1027_read_temperature_mC(max1027_device_, &temp);
	if (ret < 0)
	{
		throw new AdcException("Error HostAdcPort::close, can't reading temperature on max1027 !");
	}
	return temp;
}

void utils::HostAdcPort::setAverage(int ave) //4, 8, 16, 32
{
	int ret = as_max1027_set_averaging_3_3(max1027_device_, ave);

	if (ret < 0)
	{
		throw new AdcException("Error HostAdcPort::close, can't set averaging on max1027 !");
	}
}

int utils::HostAdcPort::readMillivolt(int channel)
{
	int value = 0;
	int ret = as_max1027_get_value_milliVolt(max1027_device_, channel, &value);
	if (ret < 0)
	{
		throw new AdcException("Error HostAdcPort::close, can't read voltage on max1027 !");
	}
	return value;
}
