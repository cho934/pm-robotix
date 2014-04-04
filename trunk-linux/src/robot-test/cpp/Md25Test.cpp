/*!
 * \file
 * \brief Implémentation de la classe Md25Test.
 */

#include "Md25Test.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::Md25Test::run(int, char *[])
{
	logger().info() << "-------------------------------------------------------------------------------" << utils::end;
	logger().info() << "Md25Test - Go" << utils::end;


	try
	{
		pmx::Robot robot;

		if (robot.md25().isConnected())
		{


		}
		else
		{
			logger().info() << "Md25Test not connected !" << utils::end;
		}
	} catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what() << utils::end;
	}

	logger().info() << "End of RobotTest." << utils::end;
}

