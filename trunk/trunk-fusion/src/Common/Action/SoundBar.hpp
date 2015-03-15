#ifndef SOUNDBAR_HPP_
#define SOUNDBAR_HPP_

#include "../LogAppender/LoggerFactory.hpp"
#include "../Macro.hpp"
#include "../Action.Driver/ASoundDriver.hpp"

class SoundBar
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref SoundBar.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("SoundBar");
		return instance;
	}

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
	 * \brief Prononce PMX.
	 */
	void speakPMX();

};

#endif
