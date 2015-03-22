#ifndef SIMULAUNCHER_LEDDRIVER_HPP_
#define SIMULAUNCHER_LEDDRIVER_HPP_

#include "../Common/Action.Driver/ALedDriver.hpp"

class LedDriver: public ALedDriver
{

public:

	virtual void setBit(int position, int color);

	virtual void setBytes(uint hexPosition, int color);

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
