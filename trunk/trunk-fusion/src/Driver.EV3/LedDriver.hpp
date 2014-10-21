#ifndef PMX_LEDDRIVER_HPP_
#define PMX_LEDDRIVER_HPP_

#include "../Action.Driver/ALedDriver.hpp"

class LedDriver: public ALedDriver
{

public:

	void set(int position, int aValue);

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
