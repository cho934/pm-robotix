/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include <iostream>
#include <cstdio>
#include "LedIndicatorTest.hpp"
#include "LedIndicator.hpp"
#include "LedBar.hpp"
#include "Robot.hpp"

void test::LedIndicatorTest::run(int, char *[])
{
    std::cout << "LedIndicatorTest - Blink LedIndicator board" << std::endl;
    int timeout = 20*1000;//en us

    pmx::Robot robot;
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.firePulseEnabled(false);
    robot.start();

    logger().info() << " ledBar().reset()" << utils::end;
    robot.ledBar().reset();
    usleep(1000000);
    logger().info() << " ledBar().flash()" << utils::end;
    robot.ledBar().flash();
    usleep(1000000);
    logger().info() << " ledBar().reset()" << utils::end;
    robot.ledBar().reset();
    sleep(3);
    logger().info() << " ledBar().blink()" << utils::end;
    robot.ledBar().blink(20, 100000);
    sleep(4);
    robot.ledBar().stop(true);
    
    logger().info() << " ledBar().k2Mil(100000)" << utils::end;
    robot.ledBar().k2Mil(100000);
    sleep(3);
    robot.ledBar().stop(true);

    logger().info() << " ledBar().k2Mil(50000)" << utils::end;
    robot.ledBar().k2Mil(50000);
    sleep(3);
    robot.ledBar().stop(true);
    
    while (true)
    {
        for (int i = 0; i < 8; i++)
        {
            logger().info() << i << " on" << utils::end;
            pmx::LedIndicator::instance().setOn(i);
            robot.ledBar().setOn(i);
            usleep(timeout);
        }
        
        for (int i = 0; i < 8; i++)
        {
            logger().info() << i << " off" << utils::end;
            pmx::LedIndicator::instance().setOff(i);
            robot.ledBar().setOff(i);
            usleep(timeout);
        }
        std::cout << "Appuyer sur ENTREE" << std::endl;
        getchar();
    }
}

