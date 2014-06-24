/*!
 * \file
 * \brief Définition de la classe ServoMotorStdObject (example avec 3 positions + freewheeling).
 */

#ifndef PMX_SERVOMOTORSTDOBJECT_HPP
#define	PMX_SERVOMOTORSTDOBJECT_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"
#include "ServoMotorStd.hpp"

namespace pmx
{

/*!
 * \brief Enumération des libellés des actions des SERVOMOTEURS.
 */
enum ServoMotorObjectActionName
{
	SERVOTURNMIN, SERVOTURNMED, SERVOTURNMAX, FREEWHEELING
};

/*!
 * \brief Cette classe représente l'un des servomoteurs fonctionnant en 3 positions du robot.
 *
 */
class ServoMotorStdObject: public ARobotElement
{
private:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorObject.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorObject");
		return instance;
	}

	utils::ServoMotorStd * servo_;

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
	ServoMotorStdObject(pmx::Robot & robot, int servoId);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ ServoMotorStdObject()
	{
	}


	inline int id() const
	{
		return servo_->getServoId();
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

	/*!
	 * \brief Configure la position du servomotor par le fichier de configuration.
	 */
	virtual void initialize(const std::string& prefix, utils::Configuration& configuration);


	void turnMin();

	void turnMax();


	/*!
	 * \brief Lance l'action de positionner le servomotor sur sa position min.
	 */
	virtual void startTurnMin(bool freewheeling);
	/*!
	 * \brief Lance l'action de positionner le servomotor sur sa position medium.
	 */
	virtual void startTurnMed(bool freewheeling);
	/*!
	 * \brief Lance l'action de positionner le servomotor sur sa position max.
	 */
	virtual void startTurnMax(bool freewheeling);
	/*!
	 * \brief Lance l'action de supprimer le controle de puissance.
	 */
	virtual void startFreeWheeling(bool freewheeling);
};

/*!
 * \brief Cette action permet de definir le déplacement angulaire du servomoteur.
 *
 * \bug Externaliser cette classe.
 */
class ServoMotorObjectAction: public IAction
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorObjectAction.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorObjectAction");
		return instance;
	}

	/*!
	 * \brief Référence vers le servomoteur associé.
	 */
	ServoMotorStdObject & servomotor_;

	/*!
	 * \brief libellé de l'action à exécuter.
	 */
	ServoMotorObjectActionName action_;

	/*!
	 * \brief chronomètre de la pince permettant de définir le temps d'ouverture/fermeture.
	 */
	utils::Chronometer chrono_;

	/*!
	 * \brief dernier temps issu du chronometre.
	 */
	long lastTime_;

	/*!
	 * \brief mode d'action.
	 */
	int mode_;

	/*!
	 * \brief définit si la puissance du servomotor doit être maintenue.
	 */
	bool freewheeling_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 * \param servomotor
	 *        Reference vers le servomoteur associé.
	 */
	ServoMotorObjectAction(ServoMotorStdObject & servomotor, pmx::ServoMotorObjectActionName action, bool freewheeling);
	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ServoMotorObjectAction()
	{
	}

	virtual bool execute();

	virtual inline std::string info()
	{
		return "ServoMotorObjectAction";
	}
};
}
;

#endif

