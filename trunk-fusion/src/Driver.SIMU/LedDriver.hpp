#ifndef PMX_LEDDRIVER_HPP_
#define PMX_LEDDRIVER_HPP_

#include "../Action.Driver/ALedDriver.hpp"

class LedDriver: public ALedDriver
{

public:

	/*!
	 * \brief Liste des gpio à utiliser.
	 */
	int gpio[8];
	int nb_;

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
