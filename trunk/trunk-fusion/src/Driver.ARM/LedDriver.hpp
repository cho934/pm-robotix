#ifndef ARMA_LEDDRIVER_HPP_
#define ARMA_LEDDRIVER_HPP_

#include "../Common/Action.Driver/ALedDriver.hpp"

//#include <as_devices/cpp/as_gpio.hpp>

#define IN (char*)0
#define OUT (char*)1

class LedDriver: public ALedDriver
{

public:

	/*!
	 * \brief Liste des gpio à utiliser.
	 */
	//AsGpio * gpio[8];

	virtual void setBit(int index, int color);

	virtual void setBytes(uint hex, int color);

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
