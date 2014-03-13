/*!
 * \file
 * \brief Implémentation de la classe RobotInOutFactory.
 */

#include <istream>
#include "RobotInOutFactory.hpp"
#include "RobotInOutSimulate.hpp"
#include "RobotInOutApf.hpp"

pmx::RobotInOutFactory * pmx::RobotInOutFactory::instance() //singleton
{
	static pmx::RobotInOutFactory * instance = new pmx::RobotInOutFactory();
	return instance;
}

pmx::RobotInOutFactory::RobotInOutFactory()
		: inOut_(NULL)
{
	logger().debug("pmx::RobotInOutFactory::RobotInOutFactory()");

	if (access("/etc/machine", F_OK) == 0)
	{
		logger().info("Use of the Apf in/out");
		pmx::RobotInOutApf * apf = new pmx::RobotInOutApf();
		inOut_ = apf;
	}
	else
	{
		logger().info("Use of simulated in/out");
		inOut_ = new pmx::RobotInOutSimulate();
	}
}

