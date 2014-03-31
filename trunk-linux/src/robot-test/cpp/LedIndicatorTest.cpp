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
	std::cout << "LedIndicatorTest - Blink LedIndicator board" << std::endl;

try
{

	pmx::Robot robot;

	pmx::LedIndicator::instance().reset();

	pmx::LedIndicator::instance().blink(30,200000);

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
	std::cout << "Exception : " << e->what() << std::endl;
}

}

