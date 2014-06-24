/*!
 * \file
 * \brief Définition de la classe ServoMotorDxlObject.
 */

#ifndef PMX_SERVOMOTORDXLOBJECT_HPP
#define	PMX_SERVOMOTORDXLOBJECT_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"


namespace pmx
{

/*!
 * \brief Cette classe représente un objet example avec un ax12.
 *
 */
class ServoMotorDxlObject: public ARobotElement
{
private:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorDxlObject.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorDxlObj"); //Ne fct pas avec pmx::ServoMotorDxlObject
		return instance;
	}

	/*!
	 * \brief tested if the servo is connected.
	 */
	bool connected_;

	/*!
	 * \brief ID du servomoteur.
	 */
	int id_;

	/*!
	 * \brief Position de la pince; 0:fermée; 1:ouverte.
	 */
	int stateOpened_;

	/*!
	 * \brief Permet de stopper l'action et qu'elle se termine à la prochaine itération.
	 */
	bool actionStopped_;

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
	ServoMotorDxlObject(pmx::Robot & robot, int id, int min, int max);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ ServoMotorDxlObject()
	{
	}

	inline int id() const
	{
		return id_;
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

	void freeMotion();

	void enable();

	void displayInfos();

	void begin();

};

}

#endif

