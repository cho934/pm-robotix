/*!
 * \file
 * \brief Définition de la classe LedIndicator.
 *
 */

#ifndef PMX_LEDINDICATOR_HPP
#define PMX_LEDINDICATOR_HPP

#include <string>

#include "Macro.hpp"
#include "HostGpioPort.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{

/*!
 * \brief Cette classe permet d'interagir avec la série de 8 leds.
 *
 * Cette classe est implémentée comme un singleton afin de pouvoir être
 * utilisée à tout endroit du programme sans difficulté, en contrepartie
 * les sorties pour les leds doivent être dédiées.
 */
class LedIndicator
{
public:

	/*!
	 * \brief Cette méthode statique retourne l'instance unique de la classe
	 * LedIndicator.
	 * \return L'instance unique de la classe.
	 *
	 */
	static LedIndicator & instance()
	{
		static LedIndicator instance;
		return instance;
	}

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::LedIndicator");
		return instance;
	}

	/*!
	 * \brief Liste des gpio à utiliser.
	 */
	utils::HostGpioPort * paths[8];

private:

	/*!
	 * \brief Constructeur par défaut.
	 */
	LedIndicator()
	{
		try
		{
			for (int i = 0; i < 8; i++)
			{
				paths[i] = new utils::HostGpioPort();
			}

			paths[0]->openIoctl('A', 4);
			paths[1]->openIoctl('A', 5);
			paths[2]->openIoctl('A', 6);
			paths[3]->openIoctl('A', 9);
			paths[4]->openIoctl('A', 8);
			paths[5]->openIoctl('A', 7);
			paths[6]->openIoctl('A', 10);
			paths[7]->openIoctl('A', 11);
			for (int i = 0; i < 8; i++)
			{
				paths[i]->setDirIoctl(1);
			}

		} catch (utils::Exception * e)
		{
			logger().error() << "Exception : " << e->what() << utils::end;
		}
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~LedIndicator()
	{
		try
		{
			for (int i = 0; i < 8; i++)
			{
				paths[i]->closeIoctl();
			}
			/*
			 for (int i = 0; i < 8; i++)
			 {
			 paths[i]->closeAs();
			 }*/

		} catch (utils::Exception * e)
		{
			logger().error() << "Exception : " << e->what() << utils::end;
		}
	}

public:

	/*!
	 * \brief Change le statut d'une led.
	 * \param position La position de la led (de 0 à 7).
	 * \param status Le statut de la led.
	 */
	void set(int position, int status);

	/*!
	 * \brief Active une led spécifique.
	 * \param position La position de la led (de 0 à 7).
	 */
	inline void setOn(int position)
	{
		this->set(position, 1);
	}

	/*!
	 * \brief Désactive une led spécifique.
	 * \param position La position de la led (de 0 à 7).
	 */
	inline void setOff(int position)
	{
		this->set(position, 0);
	}

	/*!
	 * \brief Désactive toutes les leds.
	 */
	void reset();

	/*!
	 * \brief Allume toutes les leds.
	 */
	void flash();

	/*!
	 * \brief Allume les leds définit par hexValue, max = 0xFF.
	 */
	void flashValue(uint hexValue);

	/*!
	 * \brief Clignote toutes les leds nb fois.
	 */
	void blink(uint nb, uint timeus);

	/*!
	 * \brief Clignote une led nb foispendant timeus.
	 */
	void blinkPin(int position, uint nb, uint timeus);

	/*!
	 * \brief Clignote toutes les leds nb fois sur les 2 valeurs hex val1 et val2.
	 */
	void alternate(uint nb, uint timeus, uint val1, uint val2);

	//TODO k2mil()

};
}

#endif
