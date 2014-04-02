/*!
 * \file
 * \brief Définition de la classe LedBar.
 */
#ifndef PMX_LEDBAR_HPP
#define	PMX_LEDBAR_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"
#include "LoggerFactory.hpp"
#include "IAction.hpp"
#include "Macro.hpp"
#include "Chronometer.hpp"

namespace pmx
{

/*!
 * \brief Enumération des libellés des actions de la barre de leds.
 */
enum LedBarActionName
{
	/*!
	 * \brief Libellé de l'action permettant d'allumer/eteindre une led.
	 */
	LEDBARSET,

	/*!
	 * \brief Libellé de l'action permettant un clignotement à la "K2000".
	 */
	LEDBARK2MIL,

	/*!
	 * \brief Libellé de l'action permettant un reset de toute la barre de led.
	 */
	LEDBARRESET,

	/*!
	 * \brief Libellé de l'action permettant d'allumer toutes les leds.
	 */
	LEDBARFLASH,

	/*!
	 * \brief Libellé de l'action permettant d'allumer les leds par rapport à une valeur hexa.
	 */
	LEDBARFLASHVALUE,

	/*!
	 * \brief Libellé de l'action permettant un clignotement de la barre de led.
	 */
	LEDBARBLINK,

	/*!
	 * \brief Libellé de l'action permettant un clignotement d'un pin de la barre de led.
	 */
	LEDBARBLINKPIN,

	/*!
	 * \brief Libellé de l'action permettant un clignotement alternatif sur 2 valeurs définies de la barre de led.
	 */
	LEDBARALTERNATE

};
/*!
 * \brief Cette classe permet d'interagir avec la série de 8 leds sur la
 * carte de demultiplexage.
 *
 */
class LedBar: public ARobotElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedBar.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::LedBar");
		return instance;
	}

	/*!
	 * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération des actions.
	 */
	bool actionStopped_;

	/*!
	 * \brief Permet de savoir si une action est en cours.
	 */
	bool actionRunning_;

	/*!
	 * \brief Position de la led.
	 */
	ushort position_;

	/*!
	 * \brief Statut de la led a appliquer.
	 */
	bool status_;

	/*!
	 * \brief Nombre de clignotement à faire.
	 */
	uint nb_;

	/*!
	 * \brief Temps de pause (en us).
	 */
	uint timeus_;

	/*!
	 * \brief Première Valeur de clignotement.
	 */
	uint hex_;

	/*!
	 * \brief 2ème valeur de clignotement.
	 */
	uint hexNext_;

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	LedBar(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~LedBar()
	{
	}

	inline void stop(bool value)
	{
		this->actionStopped_ = value;
	}
	inline bool stop() const
	{
		return actionStopped_;
	}

	inline void stopAndWait(bool value)
	{
		this->actionStopped_ = value;
		while (this->actionRunning_)
		{
			usleep(1000);
		}
	}

	inline void actionRunning(bool value)
	{
		this->actionRunning_ = value;
	}
	inline bool actionRunning() const
	{
		return actionRunning_;
	}

	inline void position(ushort value)
	{
		this->position_ = value;
	}
	inline ushort position() const
	{
		return position_;
	}

	inline void status(bool value)
	{
		this->status_ = value;
	}
	inline bool status() const
	{
		return status_;
	}

	inline void nb(uint value)
	{
		this->nb_ = value;
	}
	inline uint nb() const
	{
		return nb_;
	}

	inline void timeus(uint value)
	{
		this->timeus_ = value;
	}
	inline uint timeus() const
	{
		return timeus_;
	}

	inline void hexValue(uint value)
	{
		this->hex_ = value;
	}
	inline uint hexValue() const
	{
		return hex_;
	}

	inline void hexValueNext(uint value)
	{
		this->hexNext_ = value;
	}
	inline uint hexValueNext() const
	{
		return hexNext_;
	}

	/*!
	 * \brief Lance l'action de changer le statut d'une led.
	 *
	 * \param position La position de la led (de 0 à 7).
	 * \param status Le statut de la led.
	 */
	void startSet(ushort position, bool status);

	/*!
	 * \brief Lance l'action d'allumer toutes les leds.
	 */
	void startFlash();

	/*!
	 * \brief Lance l'action d'allumer les leds selon la valeur hexValue.
	 */
	void startFlashValue(uint hexValue);

	/*!
	 * \brief Lance l'action de faire clignoter toutes les leds nb fois tous les timeus.
	 */
	void startBlink(uint nb, uint timeus, bool wait);

	/*!
	 * \brief Lance l'action de faire clignoter une led nb fois tous les timeus.
	 */
	void startBlinkPin(int position, uint nb, uint timeus, bool wait);

	/*!
	 * \brief Lance l'action de faire alterner les leds selon les valeurs hexValue et hexValueNext.
	 * Doit être stoppé par stop.
	 */
	void startAlternate(uint nb, uint timeus, uint hexValue, uint hexValueNext, bool wait);

	/*!
	 * \brief Eteint toutes les leds.
	 */
	void startReset();

	/*!
	 * \brief Lance l'action d'allumer les leds à la "K2000".
	 */
	void startK2Mil(uint nb, uint timeus, bool wait);

	/*!
	 * \brief Active une led spécifique.
	 * \param position La position de la led (de 0 à 7).
	 */
	inline void startSetOn(ushort position)
	{
		this->startSet(position, true);
	}

	/*!
	 * \brief Désactive une led spécifique.
	 * \param position La position de la led (de 0 à 7).
	 */
	inline void startSetOff(ushort position)
	{
		this->startSet(position, false);
	}

};

/*!
 * \brief Cette action permet de definir les actions concernant la barre de leds.
 *
 */
class LedBarAction: public IAction
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedBarAction.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::LedBarAction");
		return instance;
	}

	/*!
	 * \brief Référence vers la LedBar associée.
	 */
	LedBar & ledBar_;

	/*!
	 * \brief libellé de l'action à exécuter.
	 */
	LedBarActionName action_;

	utils::Chronometer chrono_;

	long lastTime_;

	uint i_;

	uint j_;

	uint k_;

	bool inc_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 * \param ledBar
	 *        Reference vers la LedBar associée.
	 */
	LedBarAction(LedBar & ledBar, pmx::LedBarActionName action);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~LedBarAction()
	{
	}

	/*!
	 * \brief Execution de l'action.
	 */
	virtual bool execute();

	/*!
	 * \brief Retourne la description de l'action.
	 */
	virtual inline std::string info()
	{
		return "LedBarAction";
	}
};

}

#endif	/* PMX_LEDBAR_HPP */

