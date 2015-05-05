/*!
 * \file
 * \brief Définition de la classe Robot.
 */

#ifndef PMX_ROBOT_HPP
#define PMX_ROBOT_HPP

#include <string>

#include "ActionManager.hpp"
#include "Adafruit_RGBLCDShield.hpp"
#include "ArduinoBoard.hpp"
#include "Base.hpp"
#include "BaseWay.hpp"
#include "Chronometer.hpp"
#include "ExtEncoder.hpp"
#include "GpioBoard.hpp"
#include "GroveColorSensor.hpp"
//#include "IInitialized.hpp"
#include "IrSensorsGroup.hpp"
#include "LedBar.hpp"

#include "Logger.hpp"
#include "LoggerFactory.hpp"
#include "Md25.hpp"
#include "RobotColor.hpp"
#include "ServoMotorDxlObject.hpp"

namespace pmx {

/*!
 * \brief Enumération du mode de programmation.
 */
enum RobotMode {
	ROBOTMATCHES, ROBOTHOMOLOGATION, ROBOTTABLETEST
};

/*!
 * \brief Cette classe représente le robot.
 *
 * Cette classe maitresse de l'application représente le robot et permet
 * d'accéder à l'ensemble de ses éléments.
 */
class Robot: public IInitialized {
public:

	static Robot & instance() {
		static Robot instance;
		return instance;
	}

private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Robot.
	 */
	static inline const utils::Logger & logger() {
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Robot");
		return instance;
	}

	/*!
	 * \brief Assure la gestion des actions du robot.
	 */
	pmx::ActionManager actionManager_;

	/*!
	 * \brief chronometerRobot.
	 */
	utils::Chronometer chronometerRobot_;

	/*!
	 * \brief Base roulante du robot.
	 */
	pmx::Base base_;

	/*!
	 * \brief Couleur du robot.
	 */
	pmx::RobotColor myColor_;

	/*!
	 * \brief Mode de match (matches ou homologation).
	 */
	pmx::RobotMode runMode_;

	/*!
	 * \brief GroveColorSensor.
	 */
	pmx::GroveColorSensor groveColorSensor_;

	/*!
	 * \brief Barre de LED.
	 */
	pmx::LedBar ledBar_;

	/*!
	 * \brief MotorisationMd25.
	 */
	pmx::Md25 md25_;

	/*!
	 * \brief Encoder Left;.
	 */
	pmx::ExtEncoder encoderLeft_;

	/*!
	 * \brief Encoder Right;.
	 */
	pmx::ExtEncoder encoderRight_;

	/*!
	 * \brief Servomotor standard de test.
	 */
	//pmx::ServoMotorStdObject servoTest_;

	/*!
	 * \brief Servomotor ax12 de test.
	 */
	pmx::ServoMotorDxlObject servoDxlTest_;
	/*
	pmx::ServoMotorDxlObject servoDxlLeft_;

	pmx::ServoMotorDxlObject servoDxlRight_;
	pmx::ServoMotorDxlObject servoDxlBallLaunch_;
	pmx::ServoMotorDxlObject servoDxlFiletLaunch_;
	pmx::ServoMotorDxlObject servoDxlP4_;
	pmx::ServoMotorDxlObject servoDxlP6front_;
	pmx::ServoMotorDxlObject servoDxlP14_;
*/
	/*!
	 * \brief Groupe de détecteur IR.
	 */
	pmx::IrSensorsGroup irSensorsGroup_;

	/*!
	 * \brief Connexion Arduino par I2C.
	 */
	pmx::ArduinoBoard arduinoBoardDuemilanove_;

	/*!
	 * \brief Connexion Arduino par I2C.
	 */
	pmx::ArduinoBoard arduinoBoardMega_;

	/*!
	 * \brief Connexion Arduino par I2C.
	 */
	pmx::ArduinoBoard arduinoBoardSeeed_;

	/*!
	 * \brief Connexion Gpio par I2C.
	 */
	pmx::GpioBoard gpioBoard_;

	/*!
	 * \brief Connexion LCD par I2C.
	 */
	pmx::Adafruit_RGBLCDShield lcdBoard_;

	/*!
	 * \brief Constructeur de la classe.
	 */
	Robot();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~Robot() {
	}

public:

	/*!
	 * \brief Cette méthode retourne l'objet de manipulation de la base
	 * roulante du robot.
	 * \return La base roulante du robot.
	 */
	inline pmx::Base & base() {
		return base_;
	}

	/*!
	 * \brief Retourne la couleur du robot.
	 */
	inline pmx::RobotColor myColor() const {
		return myColor_;
	}

	/*!
	 * \brief Enregistre la couleur du robot.
	 */
	inline void myColorIs(pmx::RobotColor color) {
		this->myColor_ = color;
		if (color == pmx::PMXYELLOW)
			base().setMatchColor(0);
		if (color == pmx::PMXGREEN)
			base().setMatchColor(1);
		if (color == pmx::PMXNOCOLOR)
			base().setMatchColor(0);
	}

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du chronometer.
	 * \return Le chronometer.
	 */
	inline utils::Chronometer & chronometerRobot() {
		return chronometerRobot_;
	}

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du GroveColorSensor.
	 * \return Le GroveColorSensor.
	 */
	inline pmx::GroveColorSensor & groveColorSensor() {
		return groveColorSensor_;
	}

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du ledBar.
	 * \return Le ledBar.
	 */
	inline pmx::LedBar & ledBar() {
		return ledBar_;
	}

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du ledBar.
	 * \return Le ledBar.
	 */
	inline pmx::Md25 & md25() {
		return md25_;
	}

	/*!
	 * \brief Cette methode retourne le codeur gauche.
	 * \return encoderLeft_.
	 */
	inline pmx::ExtEncoder & encoderLeft() {
		return encoderLeft_;
	}

	/*!
	 * \brief Cette methode retourne le codeur droit.
	 * \return encoderRight_.
	 */
	inline pmx::ExtEncoder & encoderRight() {
		return encoderRight_;
	}

	/*!
	 * \brief Cette methode retourne le servomotor test.
	 * \return servoTest_.
	 */
//	inline pmx::ServoMotorStdObject & servoTest()
//	{
//		return servoTest_;
//	}
	/*!
	 * \brief Cette methode retourne le servomotor test.
	 * \return servoTest_.
	 */

	inline pmx::ServoMotorDxlObject & servoDxlTest() {
		return servoDxlTest_;
	}
	/*
	inline pmx::ServoMotorDxlObject & servoDxlLeft() {
		return servoDxlLeft_;
	}
	inline pmx::ServoMotorDxlObject & servoDxlRight() {
		return servoDxlRight_;
	}
	inline pmx::ServoMotorDxlObject & servoDxlBallLaunch() {
		return servoDxlBallLaunch_;
	}
	inline pmx::ServoMotorDxlObject & servoDxlFiletLaunch() {
		return servoDxlFiletLaunch_;
	}
	inline pmx::ServoMotorDxlObject & servoDxlP6front() {
		return servoDxlP6front_;
	}
	inline pmx::ServoMotorDxlObject & servoDxlP4() {
		return servoDxlP4_;
	}

	inline pmx::ServoMotorDxlObject & servoDxlP14() {
		return servoDxlP14_;
	}*/

	/*!
	 * \brief Cette methode retourne le groupe de détecteur IR.
	 * \return irSensorsGroup_.
	 */
	inline pmx::IrSensorsGroup & irSensorsGroup() {
		return irSensorsGroup_;
	}

	/*!
	 * \brief Cette methode retourne l'objet arduinoBoardDuemilanove.
	 * \return arduinoBoardDuemilanove_.
	 */
	inline pmx::ArduinoBoard & arduinoBoardDuemilanove() {
		return arduinoBoardDuemilanove_;
	}

	/*!
	 * \brief Cette methode retourne l'objet arduinoBoardDuemilanove.
	 * \return arduinoBoardMega_.
	 */
	inline pmx::ArduinoBoard & arduinoBoardMega() {
		return arduinoBoardMega_;
	}

	/*!
	 * \brief Cette methode retourne l'objet arduinoBoardDuemilanove.
	 * \return arduinoBoardSeeed_.
	 */
	inline pmx::ArduinoBoard & arduinoBoardSeeed() {
		return arduinoBoardSeeed_;
	}

	/*!
	 * \brief Cette methode retourne l'objet GpioBoard.
	 * \return gpioBoard_.
	 */
	inline pmx::GpioBoard & gpioBoard() {
		return gpioBoard_;
	}

	/*!
	 * \brief Cette methode retourne l'objet lcdBoard.
	 * \return lcdBoard_.
	 */
	inline pmx::Adafruit_RGBLCDShield & lcdBoard() {
		return lcdBoard_;

	}

	/*!
	 * \brief Retourne le mode de match du robot.
	 */
	inline pmx::RobotMode myRunningMode() const {
		return runMode_;
	}

	/*!
	 * \brief Enregistre le mode de match du robot.
	 */
	inline void runMode(pmx::RobotMode mode) {
		this->runMode_ = mode;
	}

	/*!
	 * \brief Ajout d'une action.
	 * \param action
	 *        L'action à ajouter.
	 */
	inline void addAction(IAction * action) {
		logger().debug() << "Robot addAction" << utils::end;
		actionManager_.addAction(action);
	}

	/*!
	 * \brief Active le robot.
	 *
	 * Cette méthode lance les différents threads associés et initialise
	 * le système.
	 */
	void start(int useExtEncoders, int startAsserv);

	/*!
	 * \brief Arrete le robot et libère les ressources associés.
	 */
	void stop();

	/*!
	 * \brief Arrete le thread sensorManager et actionManager.
	 */
	void stopManagers();

	/*!
	 * \brief Arrete les composant du robot.
	 */
	void stopDevices();

	/*!
	 * \brief Initialise les paramètres du robot via un fichier de configuration.
	 */
	virtual void initialize(const std::string & prefix, utils::Configuration & configuration);
	/*!
	 * \brief Lance l'initialisation par fichier de configuration
	 */
	void configure(const std::string & configurationFile);

	void goTo(double x, double y, BaseWay way, bool detection);

	void goToTeta(double x, double y, double teta, BaseWay way, bool detection);
};
}

#endif
