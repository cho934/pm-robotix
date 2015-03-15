#ifndef LEDDRIVER_EV3_HPP_
#define LEDDRIVER_EV3_HPP_

#include "../Common/Action.Driver/ALedDriver.hpp"
#include "../Common/LogAppender/LoggerFactory.hpp"
#include "../Common/Macro.hpp"

class LedDriver: public ALedDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("LedDriver.EV3");
		return instance;
	}

	int nb_;

public:

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
