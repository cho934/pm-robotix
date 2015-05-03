#ifndef COMMON_ROBOT_HPP_
#define COMMON_ROBOT_HPP_

#include "../Log/LoggerFactory.hpp"
#include "Action/Actions.hpp"
#include "Asserv/Asserv.hpp"
#include "Utils/Chronometer.hpp"

class ConsoleManager;

enum RobotColor
{
	PMXNOCOLOR, PMXYELLOW, PMXGREEN
};

class Robot
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Robot.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Robot");
		return instance;
	}

	utils::Chronometer chrono_;

	RobotColor myColor_;

public:

	//Action => RobotElement
	Actions  actions;

	//Asserv
	Asserv  asserv;

	//IA

	/*!
	 * \brief Constructeur de la classe.
	 */
	Robot();

	/*!
	 * \brief Destructor.
	 */
	virtual ~Robot()
	{
	}

	void operator=(Robot const&); // Don't implement

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du chronometer.
	 * \return Le chronometer.
	 */
	utils::Chronometer & chrono()
	{
		return chrono_;
	}

	/*!
	 * \brief Retourne la couleur du robot.
	 */
	RobotColor getMyColor() const
	{
		return myColor_;
	}

	/*!
	 * \brief Enregistre la couleur du robot.
	 */
	void setMyColor(RobotColor color)
	{
		this->myColor_ = color;
	}

	/*!
	 * \brief Start the robot (console for tests or main program)..
	 */
	void start(ConsoleManager manager, int argc, char** argv);

	void moveForward(int mm, int power);



	void stop(); //TODO fonction implénetée dans SRobotExtended...avec les objets extended. Ne peut pas créer de cpp sinon impossible d'instancier plusieurs robots dans simulation.

};

#endif
