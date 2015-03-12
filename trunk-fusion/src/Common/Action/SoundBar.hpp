#ifndef SOUNDBAR_HPP_
#define SOUNDBAR_HPP_

#include "../Action.Driver/ASoundDriver.hpp"
#include "../../Common/Macro.hpp"

class SoundBar
{
private:

public:
	ASoundDriver* sounddriver;

	/*!
	 * \brief Constructor.
	 */
	SoundBar();

	/*!
	 * \brief Destructor.
	 */
	~SoundBar();

	/*!
	 * \brief Clignote toutes les leds nb fois.
	 */
	void playPMX();

};

#endif
