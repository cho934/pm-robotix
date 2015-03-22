#ifndef ALEDDRIVER_HPP_
#define ALEDDRIVER_HPP_

#include "../Utils/Macro.hpp"

#define LED_OFF 0
#define LED_GREEN 1
#define LED_RED 2
#define LED_ORANGE 3

class ALedDriver
{

public:
	/*!
	 * \brief LedDriver instance creation.
	 */
	static ALedDriver * create(int nb);

	/*!
	 * \brief Set led value.
	 *
	 * \param index
	 * 				The position of the led in the ledBar (between 0 to nb).
	 * \param color
	 * 				The color of the led.
	 */
	virtual void setBit(int index, int color) = 0;

	/*!
	 * \brief Set color where hex=1. Set 0 where hex=0.
	 *
	 * \param hexPosition
	 * 				The values of the whole ledbar.
	 * \param color
	 * 				The color of the led setted to 1 in hex.
	 */
	virtual void setBytes(uint hex, int color) = 0;

	/*!
	 * \brief Destructor.
	 */
	virtual ~ALedDriver()
	{
	}

protected:

	/*!
	 * \brief Constructor.
	 */
	ALedDriver()
	{
	}

};

#endif
