/*!
 * \file
 * \brief Définition de la classe ServoClamp.
 */

#ifndef PMX_SERVOCLAMP_HPP
#define	PMX_SERVOCLAMP_HPP

#include "ARobotElement.hpp"
#include "Macro.hpp"
#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Chronometer.hpp"
#include "IInitialized.hpp"
#include "ServoMotorStd.hpp"

namespace pmx
{

#define LEFT_ELEVATOR 0
#define LEFT_CLAMP 1
#define LEFT_DOOR 2

#define RIGHT_ELEVATOR 7
#define RIGHT_CLAMP 6
#define RIGHT_DOOR 5

/*!
 * \brief Cette classe représente l'un des servomoteurs fonctionnant en 3 positions du robot.
 *
 */
class ServoClamp: public ARobotElement
{
private:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoClamp.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoClamp");
		return instance;
	}

	utils::ServoMotorStd * servos_[8];

	int clampLMin_;
	int clampLMed_;
	int clampLMax_;
	int clampLSpeed_;
	int clampRMin_;
	int clampRMed_;
	int clampRMax_;
	int clampRSpeed_;

	int elevatorLMin_;
	int elevatorLMed_;
	int elevatorLMax_;
	int elevatorLSpeed_;
	int elevatorRMin_;
	int elevatorRMed_;
	int elevatorRMax_;
	int elevatorRSpeed_;

	int doorLMin_;
	int doorLMed_;
	int doorLMax_;
	int doorLSpeed_;
	int doorRMin_;
	int doorRMed_;
	int doorRMax_;
	int doorRSpeed_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoClamp(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~ ServoClamp()
	{
	}

	/*!
	 * \brief Configure la position du servomotor par le fichier de configuration.
	 */
	virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

	void setPosition(int id, int value, bool hold);
	void release(int id);
	void setSpeed(int id, int speed);
	int getPosition(int id);

	void closeLeftClamp();
	void openLeftClamp();
	void openLeftClampALittle();
	void upLeftElement();
	void downLeftElement(bool withClampPressure);
	void releaseLeftElement();
	void openLeftDoor();
	void openLeftDoorALittle();
	void closeLeftDoor();

	void readyToTakeLeftElement();
	void takeLeftElement();
	void pushLeft();

	void closeRightClamp();
	void openRightClamp();
	void openRightClampALittle();
	void upRightElement();
	void downRightElement(bool withClampPressure);
	void releaseRightElement();
	void openRightDoor();
	void openRightDoorALittle();
	void closeRightDoor();

	void readyToTakeRightElement();
	void takeRightElement();
	void pushRight();

};
}

#endif

