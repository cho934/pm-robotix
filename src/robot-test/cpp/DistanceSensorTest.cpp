/*!
 * \file
 * \brief Implementation de la classe DistanceSensorTest.
 */

#include <iostream>
#include <cstdlib>
#include <as_devices/as_max1027.h>
#include "DistanceSensorTest.hpp"
#include "Robot.hpp"
#include "SimpleSensorListener.hpp"
#include "IrSensor.hpp"

void test::DistanceSensorTest::run(int argc, char *argv[]) {
    int average, timeSec;

    if (argc < 4) {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [TimeSec] [Average:4,8,16,32,1 for disabling]" << std::endl;
    }

    if (argc > 2) {
        timeSec = atoi(argv[2]);
    }else {
        //demande du port
        std::cout << "[TimeSec] : " << std::flush;
        std::cin >> timeSec;
    }

    if (argc > 3) {
        average = atoi(argv[3]);
    }else {
        //demande du port
        std::cout << "[Average:4,8,16,32,1 for disabling] : " << std::flush;
        std::cin >> average;
    }

    pmx::Robot robot;
    //Désactivation des moteurs, permet de ne pas envoyer d'action (applyMotorCode).
    robot.base().motorLeft().disabled(false);
    robot.base().motorRight().disabled(false);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().pidPositionEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidSpeedDesactivate();
    robot.firePulseEnabled(false);

    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    logger().info()
            << " Start IrSensor Listener"
            << utils::end;


    logger().info()
            << " irLeft       :"
            << " pin:" << robot.irSensorsGroup().irLeft().adcPin()
            << " Volt: " << robot.irSensorsGroup().irLeft().voltage()
            << " Dist: " << robot.irSensorsGroup().irLeft().distanceMm()
            << " mm " << (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "")
            << utils::end;

    logger().info()
            << " irCenter     :"
            << " pin:" << robot.irSensorsGroup().irCenter().adcPin()
            << " Volt: " << robot.irSensorsGroup().irCenter().voltage()
            << " Dist: " << robot.irSensorsGroup().irCenter().distanceMm()
            << " mm " << (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "")
            << utils::end;

    logger().info()
            << " irRight      :"
            << " pin:" << robot.irSensorsGroup().irRight().adcPin()
            << " Volt: " << robot.irSensorsGroup().irRight().voltage()
            << " Dist: " << robot.irSensorsGroup().irRight().distanceMm()
            << " mm " << (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "")
            << utils::end;

    logger().info()
            << " irRearCenter :"
            << " pin:" << robot.irSensorsGroup().irRearCenter().adcPin()
            << " Volt: " << robot.irSensorsGroup().irRearCenter().voltage()
            << " Dist: " << robot.irSensorsGroup().irRearCenter().distanceMm()
            << " mm " << (robot.irSensorsGroup().irRearCenter().distanceMm() > 300 ? " MAX " : "")
            << utils::end;

    robot.irSensorsGroup().changeTimeSpan(100);
    robot.irSensorsGroup().startTimer();

    while (robot.chronometerRobot().getElapsedTimeInSec() <= timeSec) {


        logger().info()
                << " irLeft    :"
                //<< " Volt: " << robot.irSensorsGroup().irLeft().voltage()
                << " Dist: " << robot.irSensorsGroup().irLeft().distanceMm()
                << " mm " << (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "")
                << utils::end;

        logger().info()
                << " irCenter  :"
                //<< " Volt: " << robot.irSensorsGroup().irCenter().voltage()
                << " Dist: " << robot.irSensorsGroup().irCenter().distanceMm()
                << " mm " << (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "")
                << utils::end;

        logger().info()
                << " irRight   :"
                //<< " Volt: " << robot.irSensorsGroup().irRight().voltage()
                << " Dist: " << robot.irSensorsGroup().irRight().distanceMm()
                << " mm " << (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "")
                << utils::end;
        logger().info()
                << " irRearCenter   :"
                //<< " Volt: " << robot.irSensorsGroup().irRearCenter().voltage()
                << " Dist: " << robot.irSensorsGroup().irRearCenter().distanceMm()
                << " mm " << (robot.irSensorsGroup().irRearCenter().distanceMm() > 300 ? " MAX " : "")
                << utils::end;

        logger().info() << utils::end;
        logger().info() << utils::end;
        usleep(400000);
    }

    robot.irSensorsGroup().stopTimer();

    logger().info()
            << " END irLeft    :"
            << " pin:" << robot.irSensorsGroup().irLeft().adcPin()
            << " Volt: " << robot.irSensorsGroup().irLeft().voltage()
            << " Dist: " << robot.irSensorsGroup().irLeft().distanceMm()
            << " mm " << (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "")
            << utils::end;

    logger().info()
            << " END irCenter  :"
            << " pin:" << robot.irSensorsGroup().irCenter().adcPin()
            << " Volt: " << robot.irSensorsGroup().irCenter().voltage()
            << " Dist: " << robot.irSensorsGroup().irCenter().distanceMm()
            << " mm " << (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "")
            << utils::end;

    logger().info()
            << " END irRight   :"
            << " pin:" << robot.irSensorsGroup().irRight().adcPin()
            << " Volt: " << robot.irSensorsGroup().irRight().voltage()
            << " Dist: " << robot.irSensorsGroup().irRight().distanceMm()
            << " mm " << (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "")
            << utils::end;


    logger().info() << "Robot Stop" << utils::end;
    robot.stop();
}
