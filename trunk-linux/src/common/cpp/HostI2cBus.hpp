/*!
 * \file
 * \brief Définition de la classe HostI2cBus, gestion du bus i2c pour APF9328.
 */

#ifndef HOSTI2CBUS_HPP
#define HOSTI2CBUS_HPP

#include <stddef.h>
#include <string>

#include "Exception.hpp"
#include "Macro.hpp"
#include "Mutex.hpp"

struct as_i2c_device;

namespace utils
{

/*!
 * \brief Exception lancée s'il y a une erreur avec l'I2C.
 */
class I2cException: public Exception
{
public:
	I2cException(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ I2cException() throw ()
	{
	}
};

class I2cWarning: public Exception
{
public:
	I2cWarning(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ I2cWarning() throw ()
	{
	}
};

class HostI2cBus: public utils::Mutex
{
public:

	/*!
	 * \brief Cette méthode statique retourne l'instance unique de la classe HostI2cBus.
	 * \return L'instance unique de la classe.
	 *
	 */
	static HostI2cBus & instance()
	{
		static HostI2cBus instance;
		return instance;
	}
private:
	/*!
	 * \brief Stored i2c parameters.
	 */
	struct as_i2c_device *device_;

	/*!
	 * \brief true if the i2c is opened.
	 */
	int opened_;

	/*!
	 * \brief Constructeur de la classe.
	 */
	HostI2cBus();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~HostI2cBus()
	{
		/*
		close();
		if (opened_ == 1)
		{
			throw new I2cException("Error i2c bus not closed");
		}*/
	}

public:
	/*!
	 * \brief Read a byte from the given register.
	 *
	 * \param   reg   the given register.
	 * \param   data   the read value.
	 *
	 * \return return 0 on success, -1 on write error (\e reg byte), -2 on read error.
	 */
	int readRegValue(uchar slave_addr, uchar reg, uchar* data);

	/*!
	 * \brief Write a byte to the I2C given register.
	 *
	 * \param   reg   register to write.
	 * \param   value   value to apply.
	 *
	 * \return 0 on success, -1 on error.
	 */
	int writeRegValue(uchar slave_addr, uchar reg, uchar value);


	int readI2cSize(uchar slave_addr, char *buf, size_t size);

	int writeI2cSize(uchar slave_addr, const char *buf, size_t size);


	/*!
	 * \brief Open i2c.
	 */
	void open();

	/*!
	 * \brief Close i2c.
	 */
	void close_i2c();

private:
	/*!
	 * \brief Set the slave by his address.
	 * \param   slaveAddr	slave address.
	 */
	void setSlave(uchar slaveAddr);

};
}

#endif
