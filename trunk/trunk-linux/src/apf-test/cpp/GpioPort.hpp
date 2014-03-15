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
private:
	struct as_gpio_device *gpio_dev;

public:
	/*!
	 * \brief Constructeur de la classe.
	 *
	 * Ce constructeur est privé pour empécher la création d'une instance
	 * de la classe.
	 */
	GpioPort(char portLetter);

public:
	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~GpioPort();

public:
	int gpio_close(void);
	int gpio_set_pin_direction(int pinNum, int aDirection);
	int gpio_set_pin_value(int pinNum, int aValue);

};
}

#endif
