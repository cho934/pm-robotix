#ifndef ROBOT_HPP_
#define ROBOT_HPP_

#include "Action/Actions.hpp"

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

public:

	//Action => RobotElement
	Actions actions;

	//Asserv

	//IA

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
	 * \brief Start the robot (console for tests or main program)..
	 */
	void start(ConsoleManager manager, int argc, char** argv);

};

#endif
