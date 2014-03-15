/*!
 * \file
 * \brief Définition de la classe GpioPort.
 */

#ifndef GPIOPORT_H_
#define GPIOPORT_H_

#include <as_devices/as_gpio.h>

namespace utils
{

class GpioPort
{

public:
	static as_gpio_device & PortB()
	{
		/*static as_gpio_device *instance;
		instance->port_letter = 'B';
		int err = as_gpio_get_port_letter(instance);
		return instance;*/
	}

	static as_gpio_device & PortD()
	{
		/*static as_gpio_device instance = as_gpio_get_port_letter('D');
		return instance;*/
	}

private:
	/*!
	 * \brief Constructeur de la classe.
	 *
	 * Ce constructeur est privé pour empécher la création d'une instance
	 * de la classe.
	 */
	GpioPort();

public:
	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~GpioPort();

};
}

#endif
