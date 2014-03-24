/*!
 * \file
 * \brief Définition de la classe GpioPort.
 */

#ifndef GPIOPORT_H_
#define GPIOPORT_H_

#include <as_devices/as_gpio.h>
#include "../../common/cpp/Exception.hpp"
#include "../../common/cpp/Mutex.hpp"


namespace utils
{

/*!
 * \brief Exception lancée s'il y a une erreur avec les GPIO.
 */
class GpioException: public Exception
{
public:
	GpioException(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ GpioException() throw ()
	{
	}
};

class GpioPort // : public utils::Mutex
{
private:
	struct as_gpio_device *device_;
	int opened_;
	int fd_;//pour ioctl

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	GpioPort();
	//GpioPort(char portLetter, int pinNum);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~GpioPort();

public:
	void openAs(char portLetter, int pinNum);
	void closeAs(void);

	/*!
	 * \brief Set the GPIO Direction.
	 * \param aDirection (0:in, 1:out)
	 */
	void setDirectionAs(int aDirection);
	void setValueAs(int aValue);

	void openIoctl(char portLetter, int pinNum);
	void closeIoctl(void);
	void setDirIoctl(int aDirection);
	void setValueIoctl(bool aValue);

};
}

#endif
