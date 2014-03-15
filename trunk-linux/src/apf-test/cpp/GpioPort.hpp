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

public:
	int gpio_open(char portLetter, int pinNum);

	int gpio_close(void);
	int gpio_set_pin_direction( int aDirection);
	int gpio_set_pin_value( int aValue);

};
}

#endif
