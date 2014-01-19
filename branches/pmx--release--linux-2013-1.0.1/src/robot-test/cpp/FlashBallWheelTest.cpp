/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include <iostream>
#include <cstdio>
#include "FlashBallWheelTest.hpp"
#include "Robot.hpp"

void test::FlashBallWheelTest::run(int argc, char *argv[])
{
    int time;
    int order;
    int P,I,D;
    std::cout << "FlashBallWheelTest - Start" << std::endl;

    std::cout << "USAGE: PMX_TEST " << argv[1] << " [Tps(sec)] [OrderTick] [P] [I] [D]" << std::endl;
    
    if (argc > 2)
    {
        time = atoi(argv[2]);
        std::cout << "Temps en sec: " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande du temps de marche
        std::cout << "Temps en sec: " << std::flush;
        std::cin >> time;
    }

    if (argc > 3)
    {
        order = atoi(argv[3]);
        std::cout << "order (en ticks): " << atoi(argv[3]) << std::endl;
    }else
    {
        std::cout << "order (en ticks): " << std::flush;
        std::cin >> order;
    }

    if (argc > 4)
    {
        P = atoi(argv[4]);
        std::cout << "P: " << atoi(argv[4]) << std::endl;
    }else
    {
        std::cout << "P: " << std::flush;
        std::cin >> P;
    }

    if (argc > 5)
    {
        I = atoi(argv[5]);
        std::cout << "I: " << atoi(argv[5]) << std::endl;
    }else
    {
        std::cout << "I: " << std::flush;
        std::cin >> I;
    }

    if (argc > 6)
    {
        D = atoi(argv[6]);
        std::cout << "D: " << atoi(argv[6]) << std::endl;
    }else
    {
        std::cout << "D: " << std::flush;
        std::cin >> D;
    }

    pmx::Robot robot;

    //désactivation de l'avance du robot
    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.base().pidSpeedMotorRedYellowActivate(false);
/*
    logger().info() << "WARNING : using file robot_pmxtest.conf..." << utils::end;
    robot.configure("robot_pmxtest.conf");
    */
    robot.chronometerRobot().start(); //Chronometre général (match) du robot
    robot.start(); //lancement des threads
    robot.base().pidSpeedStart();

    robot.base().pidSpeedInitialize(pmx::MRED, P, I, D);

    robot.base().flashBallWheel().orderTick(order);
    robot.base().pidSpeedMotorRedYellowActivate(true);

    sleep(time);

    logger().debug() << "chrono stop" << utils::end;
    robot.chronometerRobot().stop();
    logger().debug() << "robot stop" << utils::end;
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}

