#ifndef PMX_ROBOT_HPP
#define PMX_ROBOT_HPP

#include "../Action/Actions.hpp"
#include "ConsoleUnitTestManager.hpp"


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

	void start(ConsoleUnitTestManager manager, int argc, char** argv);

};

#endif
