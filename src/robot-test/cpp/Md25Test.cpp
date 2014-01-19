/*!
 * \file
 * \brief Implémentation de la classe ApfI2cTest, utilisation I²C de la carte DevLightV2.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Md25Test.hpp"
#include "Chronometer.hpp"
#include "PositionManager.hpp"

void test::Md25Test::run(int argc, char *argv[])
{
    float bat = 0;
    int soft = 0;
    long encoder1 = 0;
    long encoder2 = 0;
    int reg = 1;

    std::cout << "test::Md25Test: Start" << std::endl;
    int speedR, speedL, dist, acc;

    if (argc < 6)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [speedL(1)(0=>255)] [speedR(2)(0=>255)] [dist(tick)] [Acc:1,2,3,5,10] [Regulation:0,1]" << std::endl;
    }

    if (argc > 2)
    {
        speedL = atoi(argv[2]);
        std::cout << "speedL(1): " << atoi(argv[2]) << std::endl;
    }else
    {
        //demande de la distance x
        std::cout << "speedL(1): " << std::flush;
        std::cin >> speedL;
    }

    if (argc > 3)
    {
        speedR = atoi(argv[3]);
        std::cout << "speedR(2): " << atoi(argv[3]) << std::endl;
    }else
    {
        //demande de la distance y
        std::cout << "speedR(2): " << std::flush;
        std::cin >> speedR;
    }

    if (argc > 4)
    {
        dist = atoi(argv[4]);
        std::cout << "dist: " << atoi(argv[4]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "dist: " << std::flush;
        std::cin >> dist;
    }

    if (argc > 5)
    {
        acc = atoi(argv[5]);
        std::cout << "acc: " << atoi(argv[5]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "acc: " << std::flush;
        std::cin >> acc;
    }
    if (acc != 1 && acc != 2 && acc != 3 && acc != 5 && acc != 10)
        acc = 5;

    if (argc > 6)
    {
        reg = atoi(argv[6]);
        std::cout << "reg: " << atoi(argv[6]) << std::endl;
    }else
    {
        //demande de la vitesse moteur droit à appliquer
        std::cout << "reg: " << std::flush;
        std::cin >> reg;
    }

    bat = utils::Md25::instance().getBatteryVolts(); 
    soft = utils::Md25::instance().getSoftwareVersion();
    std::cout << "MD25:getBatteryVolts   : " << bat << " :MD25:getSoftwareVersion: " << soft << std::endl;


    utils::Chronometer chrono;
    chrono.start();

    long now = chrono.getElapsedTimeInMicroSec();
    long prec = now;

    //config MD25
    utils::Md25::instance().setMode(MD25_MODE_0); //mode0 => 0-128-255
    utils::Md25::instance().setAccelerationRate(acc);


    if (reg == 1)
        utils::Md25::instance().setCommand(MD25_ENABLE_SPEED_REGULATION);
    else
        utils::Md25::instance().setCommand(MD25_DISABLE_SPEED_REGULATION);

    utils::Md25::instance().setCommand(MD25_RESET_ENCODERS);
    usleep(500);

    logger().info() << "Go to : dist(tick)=" << dist << " dist(mm)= " << dist * pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE << utils::end;
    
    logger().info() <<" MD25_SPEED1_REG speedL=" << speedL
            << " MD25_SPEED2_REG speedR=" << speedR
            << utils::end;

    //utils::Md25::instance().setSpeedRegisters(speedR, speedL);

    utils::Md25::instance().ensureSetSpeed(speedL, MD25_SPEED1_REG);
    utils::Md25::instance().ensureSetSpeed(speedR, MD25_SPEED2_REG);

    while (abs(encoder1) < abs(dist) && abs(encoder2) < abs(dist))
    {

        encoder1 = utils::Md25::instance().ensureGetEncoder(encoder1, MD25_ENCODER1_REG);
        encoder2 = utils::Md25::instance().ensureGetEncoder(encoder2, MD25_ENCODER2_REG);

        logger().info() << "MD25:getEncoder1 L: " << encoder1 << " getEncoder2 R: " << encoder2 << utils::end;

        int err = utils::Md25::instance().getNbErrors();
        if (err > 10)
        {
            logger().error() << "-------------" << err << utils::end;
            break;
        }
    }
    logger().info() << "End - stopMotors" << utils::end;
    utils::Md25::instance().stopMotors();
    while (now < prec + 2000000)
    {
        utils::Md25::instance().stopMotors();
        usleep(1000);
        now = chrono.getElapsedTimeInMicroSec();
    }
    logger().info() << "stopMotors Done!" << utils::end;
    encoder1 = utils::Md25::instance().ensureGetEncoder(encoder1, MD25_ENCODER1_REG);
    encoder2 = utils::Md25::instance().ensureGetEncoder(encoder2, MD25_ENCODER2_REG);

    logger().info() << "MD25:getEncoder1: " << encoder1 << " getEncoder2: " << encoder2 
            << utils::end;
    logger().info() << "Arrived : dist(tick)=" << dist << " dist(mm)= " << dist * pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE << utils::end;

}
