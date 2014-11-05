#ifndef ROBOT_HPP_
#define ROBOT_HPP_

#include "./Action/Actions.hpp"
#include "ConsoleManager.hpp"

class Robot
{
public:

	//Action => RobotElement
	Actions actions;

	//Asserv

	//IA

	/*!
	 * \brief Constructor.
	 */
	Robot()
	{
	}

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
