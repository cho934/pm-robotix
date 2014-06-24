/*!
 * \file
 * \brief Implémentation de la classe RobotElementExample.
 */

#include "RobotElementExample.hpp"
#include "Robot.hpp"
#include "ARobotElement.hpp"


pmx::RobotElementExample::RobotElementExample(pmx::Robot & robot)
		: ARobotElement(robot), connected_(false)
{

}


