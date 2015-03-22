#ifndef LEDDRIVER_HPP_
#define LEDDRIVER_HPP_

#include "../Common/Action.Driver/ALedDriver.hpp"
#include "../Common/LogAppender/LoggerFactory.hpp"
#include "../Common/Utils/Macro.hpp"

#define NB_GPIO 8 //max number of led

class LedDriver: public ALedDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedDriver(SIMU).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("LedDriver.SIMU");
		return instance;
	}

	int nb_;

public:

	/*!
	 * \brief Liste des gpio à utiliser pour BIG-PMX.
	 */
	int gpio[NB_GPIO]; //TODO faire un malloc dynamique avec nb
	uint hexa;


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
