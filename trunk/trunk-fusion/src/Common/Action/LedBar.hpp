#ifndef LEDBAR_HPP_
#define LEDBAR_HPP_

#include "../Action.Driver/ALedDriver.hpp"
#include "../../Common/Macro.hpp"


class LedBar
{
private:
	/*!
	 * Number of led in the LedBar.
	 */
	int nbLed_;

public:
	ALedDriver* leddriver;

	/*!
	 * \brief Constructor.
	 *
	 * \param nb Number of leds in the LedBar.
	 */
	LedBar(int nb);

	/*!
	 * \brief Destructor.
	 */
	~LedBar();

	/*!
	 * \brief Change le statut d'une led.
	 * \param position La position de la led.
	 * \param color La couleur de la led, 0:OFF, 1:GREEN, and optional 2:RED 3:ORANGE)
	 */
	void set(int position, int color);

	/*!
	 * \brief Active une led spécifique.
	 * \param position La position de la led.
	 */
	inline void setOn(int position)
	{
		this->set(position, 1);
	}

	/*!
	 * \brief Désactive une led spécifique.
	 * \param position La position de la led.
	 */
	inline void setOff(int position)
	{
		this->set(position, 0);
	}

	/*!
	 * \brief Allume/eteint les leds définit par hexValue, max = 0xFF.
	 */
	void flash(uint hexPosition, int color);

	/*!
	 * \brief Clignote toutes les leds nb fois.
	 */
	void blink(uint nb, uint timeus, int color = 1);

	/*!
	 * \brief Clignote une led nb fois pendant timeus.
	 */
	void blinkPin(int position, uint nb, uint timeus, int color = 1);

	/*!
	 * \brief Clignote toutes les leds nb fois sur les 2 valeurs hex val1 et val2.
	 */
	void alternate(uint nb, uint timeus, uint beginVal, uint endVal,
			int beginColor = 1, int endColor = 0);

	/*!
	 * \brief Clignote toutes les leds nb fois sur les 2 valeurs hex val1 et val2.
	 */
	void k2mil(uint nb, uint timeus, int color = 1);

};

#endif
