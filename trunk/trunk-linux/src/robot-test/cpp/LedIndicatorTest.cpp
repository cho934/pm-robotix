/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include "../../common/cpp/LedIndicator.hpp"
#include "LedIndicatorTest.hpp"

#include <unistd.h>

#include "../../common/cpp/Robot.hpp"

void robottest::LedIndicatorTest::run(int, char *[])
{
	logger().info() << "-----------------------------------------------" << utils::end;
	logger().info() << "LedIndicatorTest - Blink Led board" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();


	pmx::LedIndicator::instance().reset();

	pmx::LedIndicator::instance().blink(20, 200000);

	for (int i = 1; i <= 128; i = i * 2)
	{
		pmx::LedIndicator::instance().flashValue(i);
		usleep(100000);
	}

	pmx::LedIndicator::instance().flash();
	usleep(500000);
	pmx::LedIndicator::instance().reset();

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

