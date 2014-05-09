/*!
 * \file
 * \brief Implémentation de la classe HostI2cBus.
 */

#include "HostI2cBus.hpp"

#include <as_devices/as_i2c.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

utils::HostI2cBus::HostI2cBus()
		: device_(NULL), opened_(0)
{
}

int utils::HostI2cBus::isOpened(void)
{
	return opened_;
}

void utils::HostI2cBus::open(uchar slave_addr)
{
	if (opened_ == 0)
	{
		int i2c_id = 0; //Bus I2C sur la carte APF9328
		device_ = as_i2c_open(i2c_id);

		if (device_ == NULL)
		{
			throw new I2cException("Error HostI2cBus::open, can't open i2c port !");
		}
		else
		{
			opened_ = 1;
			setSlave(slave_addr);
		}
	}
	else //i2c already opened
	{
		throw new I2cWarning("Warning HostI2cBus::open, i2c bus already opened !");
	}
}

void utils::HostI2cBus::close_i2c(void)
{
	if (opened_ == 1)
	{
		int ret = as_i2c_close(device_);

		if (ret < 0)
		{
			throw new I2cException("Error HostI2cBus::close, can't close I2C !");
		}
		opened_ = 0;
	}
	else
	{
		//TODO en simulation, cette exception bloque !
		//throw new I2cWarning("Error HostI2cBus::close, i2c already closed !");
	}
}

void utils::HostI2cBus::setSlave(uchar slaveAddr)
{
	if (opened_ == 1)
	{
		int err = as_i2c_set_slave_addr(device_, slaveAddr);
		if (err < 0)
		{
			std::ostringstream msg;
			msg << "Error HostI2cBus::setSlave, can't set slave n°" << slaveAddr << "("
					<< reinterpret_cast<void*>(slaveAddr) << "), is the slave connected ?";
			throw new I2cException(msg.str());
		}
	}
	else
	{
		throw new I2cException("Error HostI2cBus::setSlave, i2c not opened !");
	}
}

int utils::HostI2cBus::readRegValue(uchar, uchar reg, uchar* data)
{
	if (opened_ == 1)
	{
		lock();
		int ret = 0;
		ret = as_i2c_read_reg(device_, reg, data, 1);
		if (ret < 0)
		{
			if (ret == -1)
			{
				unlock();
				throw new I2cException("Error HostI2cBus::readRegValue, WRITE error !");
			}
			if (ret == -2)
			{
				unlock();
				throw new I2cException("Error HostI2cBus::readRegValue, READ error !");
			}
			unlock();
			throw new I2cException("Error HostI2cBus::readRegValue, i2c error !");
		}
		//usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame
		unlock();
		return ret;
	}
	else
	{
		throw new I2cException("Error HostI2cBus::readRegValue, i2c not opened !");
	}
}

int utils::HostI2cBus::writeRegValue(uchar, uchar reg, uchar value)
{
	if (opened_ == 1)
	{
		lock();
		int result = 0;
		result = as_i2c_write_reg_byte(device_, reg, value);

		if (result < 0)
		{
			unlock();
			throw new I2cException("Error HostI2cBus::writeRegValue, i2c error !");
		}
		//usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame
		unlock();
		return result;
	}
	else
	{
		throw new I2cException("Error HostI2cBus::writeRegValue, i2c not opened !");
	}
}

int utils::HostI2cBus::readI2cSize(uchar, char *buf, size_t size) //TODO remove uchar
{
	if (opened_ == 1)
	{
		lock();
		int ret = 0;
		ret = as_i2c_read(device_, (unsigned char*) buf, size);
		if (ret < 0)
		{
			unlock();
			throw new I2cException("Error HostI2cBus::readI2cSize, i2c read error !");
		}
		unlock();
		return ret;
	}
	else
	{
		throw new I2cException("Error HostI2cBus::readI2cSize, i2c not opened !");
	}
}

int utils::HostI2cBus::writeI2cSize(uchar, const char *buf, size_t size) //TODO remove uchar
{
	if (opened_ == 1)
	{
		lock();
		int result = 0;
		result = as_i2c_write(device_, (unsigned char*) buf, size);
		if (result < 0)
		{
			unlock();
			throw new I2cException("Error HostI2cBus::writeI2cSize, i2c write error !");
		}
		unlock();
		return result;
	}
	else
	{
		throw new I2cException("Error HostI2cBus::writeI2cSize, i2c not opened !");
	}
}

