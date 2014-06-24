/*!
 * \file
 * \brief Définition de la classe HostAdcPort, gestion du bus SPI pour Max1027 concernant la carte APF9328.
 */

#ifndef HOSTADCPORT_HPP
#define HOSTADCPORT_HPP

#include <string>

#include "Exception.hpp"
#include "Mutex.hpp"

struct as_max1027_device;

namespace utils
{

/*!
 * \brief Exception lancée s'il y a une erreur avec le max1027.
 */
class AdcException: public Exception
{
public:
	AdcException(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ AdcException() throw ()
	{
	}
};
class AdcWarning: public Exception
{
public:
	AdcWarning(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ AdcWarning() throw ()
	{
	}
};

class HostAdcPort: public utils::Mutex
{
public:

	/*!
	 * \brief Cette méthode statique retourne l'instance unique de la classe HostAdcPort.
	 * \return L'instance unique de la classe.
	 *
	 */
	static HostAdcPort & instance()
	{
		static HostAdcPort instance;
		return instance;
	}
private:
	/*!
	 * \brief Stored adc parameters.
	 */
	struct as_max1027_device *max1027_device_;

	/*!
	 * \brief true if the spi for adc is opened.
	 */
	int opened_;

	/*!
	 * \brief Constructeur de la classe.
	 */
	HostAdcPort();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~HostAdcPort()
	{

	}

public:

	/*!
	 * \brief Open adc.
	 */
	void open();

	/*!
	 * \brief Close adc.
	 */
	void close();

	int readTemp(void);

	void setAverage(int ave);

	int readMillivolt(int channel);

};
}

#endif
