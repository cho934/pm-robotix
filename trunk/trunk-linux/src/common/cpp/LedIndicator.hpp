/*!
 * \file
 * \brief Définition de la classe LedIndicator.
 *
 */

#ifndef PMX_LEDINDICATOR_HPP
#define PMX_LEDINDICATOR_HPP

#include <string>

#include "Mutex.hpp"
#include "Macro.hpp"
#include "HostGpioPort.hpp"

namespace pmx
{
/*!
 * \brief Cette classe permet d'interagir avec la série de 8 leds.
 *
 * Cette classe est implémentée comme un singleton afin de pouvoir être
 * utilisée à tout endroit du programme sans difficulté, en contrepartie
 * les sorties pour les leds doivent être dédiées.
 */
class LedIndicator: utils::Mutex
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

	utils::HostGpioPort * paths[8];

private:

	/*!
	 * \brief Constructeur par défaut.
	 */
	LedIndicator()
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
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~LedIndicator()
	{
		for (int i = 0; i < 8; i++)
		{
			paths[i]->closeIoctl();
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
};
}

#endif
