/*!
 * \file
 * \brief Implémentation de la classe HostI2cBus.
 */

#include <iostream>
#include <sstream>
#include "HostI2cBus.hpp"

utils::HostI2cBus::HostI2cBus()
		: device_(NULL), opened_(0)
{
}

void utils::HostI2cBus::open()
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
			opened_ = 1;
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
		throw new I2cException("Error HostI2cBus::close, i2c already closed !");
	}
}

void utils::HostI2cBus::setSlave(uint8_t slaveAddr)
{
	if (opened_ == 1)
	{
		int err = as_i2c_set_slave_addr(device_, slaveAddr);
		printf("err= %d\n", err);
		if (err < 0)
		{

			std::ostringstream msg;
			msg << "Error HostI2cBus::setSlave, can't set slave n°" << slaveAddr << "("
					<< reinterpret_cast<void*>(slaveAddr) << "), is the slave connected ?";
			throw new I2cException(msg.str());
		}

		usleep(5000); //TODO ?fréq i2c à 100kHz : attente de l'application complète de la trame
	}
	else
	{
		throw new I2cException("Error HostI2cBus::setSlave, i2c not opened !");
	}
}

int utils::HostI2cBus::readRegValue(uint8_t slave_addr, uint8_t reg, uint8_t* data)
{
	if (opened_ == 1)
	{
		lock();
		int ret = 0;
		setSlave(slave_addr);
		ret = as_i2c_read_reg(device_, reg, data, 1);
		if (ret < 0)
		{
			if (ret == -1)
			{
				unlock();
				throw new I2cException("Error HostI2cBus::readRegValue, WRITE error !");
				//std::cout << "as_i2c_read_reg_byte: reg " << (int) reg << " WRITE error!" << std::endl;
			}
			if (ret == -2)
			{
				unlock();
				throw new I2cException("Error HostI2cBus::readRegValue, READ error !");
				//std::cout << "as_i2c_read_reg_byte: reg " << (int) reg << " READ error!" << std::endl;
			}
			unlock();
			throw new I2cException("Error HostI2cBus::readRegValue, i2c error !");
		}

		//TODO usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame

		unlock();
		return ret;
	}
	else
	{
		throw new I2cException("Error HostI2cBus::readRegValue, i2c not opened !");
	}
}

int utils::HostI2cBus::writeRegValue(uint8_t slave_addr, uint8_t reg, uint8_t value)
{
	lock();
	int result = 0;

	setSlave(slave_addr);
	result = as_i2c_write_reg_byte(device_, reg, value);

	if (result < 0)
	{
		unlock();
		throw new I2cException("Error HostI2cBus::writeRegValue, i2c error !");
		//std::cout << "as_i2c_write_reg_byte: reg=" << (int) reg << " val=" << (int) value << " !" << std::endl;
	}

	//TODO usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame

	unlock();
	return result;
}
