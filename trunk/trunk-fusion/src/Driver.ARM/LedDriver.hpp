#ifndef LEDDRIVER_HPP_
#define LEDDRIVER_HPP_

#include "../Common/Action.Driver/ALedDriver.hpp"

#include <as_devices/cpp/as_gpio.hpp>

#define IN (char*)0
#define OUT (char*)1

class LedDriver: public ALedDriver
{

public:

	/*!
	 * \brief Liste des gpio à utiliser.
	 */
	AsGpio * gpio[8];

	virtual void set(int position, int aValue);

	/*!
	 * \brief Constructor.
	 */
	LedDriver(int nb);

	/*!
	 * \brief Destructor.
	 */
	virtual ~LedDriver();

};

#endif
