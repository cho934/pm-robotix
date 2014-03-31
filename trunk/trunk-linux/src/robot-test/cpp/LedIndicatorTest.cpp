/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include <iostream>
#include <cstdio>
#include "LedIndicatorTest.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/LedIndicator.hpp"
#include "../../common/cpp/Exception.hpp"

void robottest::LedIndicatorTest::run(int, char *[])
{
	logger().info() << "LedIndicatorTest - Blink LedIndicator board" << utils::end;

	try
	{
		pmx::Robot robot;

		pmx::LedIndicator::instance().reset();

		pmx::LedIndicator::instance().blink(20,200000);

		for(int i=1;i<=128;i=i*2)
		{
			pmx::LedIndicator::instance().flashValue(i);
			usleep(100000);
		}

		pmx::LedIndicator::instance().flash();
		usleep(500000);
		pmx::LedIndicator::instance().reset();
	}
	catch (utils::Exception * e)
	{
		logger().error() << "Exception : " << e->what()  << utils::end;
	}
	logger().info() << "End of RobotTest." << utils::end;
}

