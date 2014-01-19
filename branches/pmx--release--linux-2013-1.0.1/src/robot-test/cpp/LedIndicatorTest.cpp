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

    std::cout << "test 00" << std::endl;
    pmx::Robot robot;
    std::cout << "test 000" << std::endl;
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.firePulseEnabled(false);
    std::cout << "test 01" << std::endl;
    robot.start();
    std::cout << "test 02" << std::endl;

    logger().info() << " ledBar().reset()" << utils::end;
    robot.ledBar().reset();
    sleep(1);

    logger().info() << " ledBar().flash()" << utils::end;
    robot.ledBar().flash();
    sleep(1);


    robot.ledBar().reset();
    logger().info() << " ledBar().startBlinkPin(3, 30, 50000, true)" << utils::end;
    robot.ledBar().startBlinkPin(3, 30, 50000, true);

    logger().info() << " ledBar()startBlinkPin(4, 10, 200000, false)" << utils::end;
    robot.ledBar().startBlinkPin(4, 10, 200000, false);
    pmx::LedIndicator::instance().blinkPin(4, 10, 200000);
    sleep(2);
    robot.ledBar().stopAndWait(true);

    robot.ledBar().reset();
    logger().info() << " ledBar().startBlink(30, 50000, true)" << utils::end;
    robot.ledBar().startBlink(30, 50000, true);

    logger().info() << " ledBar().startBlink(10, 200000, false)" << utils::end;
    robot.ledBar().startBlink(10, 200000, false);
    pmx::LedIndicator::instance().blink(10, 200000);
    sleep(2);
    robot.ledBar().stopAndWait(true);

    robot.ledBar().reset();
    logger().info() << " ledBar().startK2Mil(2, 200000, true)" << utils::end;
    robot.ledBar().startK2Mil(2, 200000, true);


    robot.ledBar().reset();
    logger().info() << " ledBar().startK2Mil(3, 100000, false) + sleep 10" << utils::end;
    robot.ledBar().startK2Mil(3, 100000, false);
    sleep(6);
    robot.ledBar().stopAndWait(true);

    robot.ledBar().reset();
    logger().info() << " ledBar().flashValue(0xAA) + LEDIndicator + sleep 2" << utils::end;
    robot.ledBar().flashValue(0xAA);
    pmx::LedIndicator::instance().flashValue(0xAA);
    sleep(2);


    robot.ledBar().reset();
    logger().info() << " ledBar().startAlternate(20, 200000, 0x33, 0xCC, true)" << utils::end;
    robot.ledBar().startAlternate(20, 200000, 0x33, 0xCC, true);

    robot.ledBar().reset();
    logger().info() << " ledBar().startAlternate(20, 200000, 0xC3, 0x3C, false) + LEDIndicator + sleep 5" << utils::end;
    robot.ledBar().startAlternate(20, 200000, 0xC3, 0x3C, false);
    pmx::LedIndicator::instance().alternate(20, 200000, 0xC3, 0x3C);
    sleep(3);
    robot.ledBar().stopAndWait(true);

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
        usleep(300);
        logger().info() << "Appuyer sur ENTREE" << utils::end;
        //std::cout << "Appuyer sur ENTREE" << std::endl;
        getchar();
    }
}

