/*!
 * \file
 * \brief Définition de la classe HostGpioPort, gestion des ports gpio pour la carte APF9328.
 */

#ifndef HOSTGPIOPORT_H_
#define HOSTGPIOPORT_H_

#include <iostream>
#include <as_devices/as_gpio.h>
#include "../../common/cpp/Exception.hpp"
#include "../../common/cpp/Mutex.hpp"

namespace utils
{

/*!
 * \brief Exception lancée s'il y a une erreur avec les GPIO.
 */
class HostGpioException: public Exception
{
public:
	HostGpioException(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ HostGpioException() throw ()
	{
	}
};

class HostGpioPort: utils::Mutex
{
private:
	struct as_gpio_device *device_;
	int fd_; //pour ioctl
	char port_letter_;
	int pin_number_;
	static int* portA_opened_;
	static int* portB_opened_;
	static int* portC_opened_;
	static int* portD_opened_;

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	HostGpioPort();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~HostGpioPort();

	//version as_devices
	void openAs(char portLetter, int pinNum);
	void closeAs();

	/*!
	 * \brief Set the GPIO Direction by AsDevices.
	 * \param aDirection (0:in, 1:out)
	 */
	void setDirectionAs(int aDirection);
	void setValueAs(int aValue);

	//version ioctl
	void openIoctl(char portLetter, int pinNum);
	void closeIoctl();

	/*!
	 * \brief Set the GPIO Direction by ioctl.
	 * \param aDirection (0:in, 1:out)
	 */
	void setDirIoctl(int aDirection);
	void setValueIoctl(bool aValue);

private:

	void checkIf(int value);
	void setData(int value);

};
}

#endif
