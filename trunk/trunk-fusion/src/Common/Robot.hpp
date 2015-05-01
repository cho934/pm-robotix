#ifndef COMMON_ROBOT_HPP_
#define COMMON_ROBOT_HPP_

#include "../Log/LoggerFactory.hpp"
#include "Action/Actions.hpp"
#include "Utils/Chronometer.hpp"

class ConsoleManager;

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

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	Robot();

	/*!
	 * \brief Destructor.
	 */
	virtual inline ~Robot()
	{
	}

	Robot(Robot const&);              // Don't Implement
	void operator=(Robot const&); // Don't implement

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du chronometer.
	 * \return Le chronometer.
	 */
	inline utils::Chronometer & chrono()
	{
		return chrono_;
	}

	//Action => RobotElement
	Actions actions;

	//Asserv

	//IA

	/*!
	 * \brief Start the robot (console for tests or main program)..
	 */
	void start(ConsoleManager manager, int argc, char** argv);

};

#endif
