/*!
 * \file
 * \brief Définition de la classe ServoMotorObject (example avec 3 positions + freewheeling).
 */

#ifndef PMX_SERVOMOTORDXLOBJECT_HPP
#define	PMX_SERVOMOTORDXLOBJECT_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"
#include "ServoMotorDxl.hpp"

namespace pmx
{


/*!
 * \brief Cette classe représente l'un des servomoteurs fonctionnant en 3 positions du robot.
 *
 */
class ServoMotorDxlObject: public ARobotElement
{
private:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorObject.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorDxlObject");
		return instance;
	}

	pmx::ServoMotorDxl * servo1_;

	/*!
	 * \brief Position de la pince; 0:fermée; 1:ouverte.
	 */
	int stateOpened_;

	/*!
	 * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
	 */
	bool actionStopped_;

	/*!
	 * \brief Brochage du servomoteur.
	 */
	//int id_;

	/*!
	 * \brief Angle minimum (en millisecond).
	 */
	int valMin_;

	/*!
	 * \brief Angle minimum (en millisecond).
	 */
	int valMed_;

	/*!
	 * \brief Angle maximum (en millisecond).
	 */
	int valMax_;

	/*!
	 * \brief vitesse de rotation (en millisecond de 5000ms à 300000ms).
	 */
	int valSpeed_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoMotorDxlObject(pmx::Robot & robot, int servoId);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ ServoMotorDxlObject()
	{
	}


	inline int id() const
	{
		//return servo1_->getServoId();
		//TODO
	}


	inline void stop(bool value)
	{
		this->actionStopped_ = value;
	}
	inline bool stop() const
	{
		return actionStopped_;
	}

	inline int stateOpened() const
	{
		return stateOpened_;
	}
	inline void stateOpened(int stateOpened)
	{
		this->stateOpened_ = stateOpened;
	}

	inline int min() const
	{
		return valMin_;
	}
	inline void min(int min)
	{
		this->valMin_ = min;
	}

	inline int med() const
	{
		return valMed_;
	}
	inline void med(int med)
	{
		this->valMed_ = med;
	}

	inline int max() const
	{
		return valMax_;
	}
	inline void max(int max)
	{
		this->valMax_ = max;
	}




	void turnMin();

	void turnMax();

};

}

#endif

