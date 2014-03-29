/*!
 * \file
 * \brief Définition de la classe HostI2cBus.
 */

#ifndef HOSTI2CBUS_H_
#define HOSTI2CBUS_H_

#include <as_devices/as_i2c.h>
#include "../../common/cpp/Exception.hpp"
#include "../../common/cpp/Mutex.hpp"


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

class HostI2cBus //: public utils::Mutex
{
private:
	struct as_i2c_device *i2c_device_;
	int opened_;

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	HostI2cBus();
	//GpioPort(char portLetter, int pinNum);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~HostI2cBus();

public:
	void openI2c();
	void closeI2c();



};
}

#endif
