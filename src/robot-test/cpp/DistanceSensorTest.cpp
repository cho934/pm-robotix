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

void test::DistanceSensorTest::run(int argc, char *argv[])
{
    int average, timeSec;

    if (argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [TimeSec] [Average:4,8,16,32,1 for disabling]" << std::endl;
    }

    if (argc > 2)
    {
        timeSec = atoi(argv[2]);
    }
    else
    {
        //demande du port
        std::cout << "[TimeSec] : " << std::flush;
        std::cin >> timeSec;
    }

    if (argc > 3)
    {
        average = atoi(argv[3]);
    }
    else
    {
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

    struct as_max1027_device *max1027_dev;
    max1027_dev = as_max1027_open(1, AS_MAX1027_SLOW);//MAX1027_SPI_NUM = 1 on APF9328
    as_max1027_set_averaging(max1027_dev, average);
    as_max1027_close(max1027_dev);
    
    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    logger().info()
            << " Start IrSensor Listener"
            << utils::end;
    robot.opponentIrSensorCenter().changeFrequency(10);
    robot.opponentIrSensorLeft().changeFrequency(10);
    robot.opponentIrSensorRight().changeFrequency(10);

    robot.opponentIrSensorLeft().startTimer();
    usleep(2000);
    robot.opponentIrSensorRight().startTimer();
    usleep(2000);
    robot.opponentIrSensorCenter().startTimer();



    while(robot.chronometerRobot().getElapsedTimeInSec() <= timeSec)
    {
        

         logger().info()
            << " opponentIrSensorLeft    :"
            << " pin:" << robot.opponentIrSensorLeft().adcPin()
            << " Volt: " << robot.opponentIrSensorLeft().voltage()
            << " Dist: " << robot.opponentIrSensorLeft().distanceMm()
            << " mm" << (robot.opponentIrSensorLeft().distanceMm() > 300 ?" MAX ":"")
            << utils::end;

         logger().info()
            << " opponentIrSensorCenter  :"
            << " pin:" << robot.opponentIrSensorCenter().adcPin()
            << " Volt: " << robot.opponentIrSensorCenter().voltage()
            << " Dist: " << robot.opponentIrSensorCenter().distanceMm()
            << " mm" << (robot.opponentIrSensorCenter().distanceMm() > 1500 ?" MAX ":"")
            << utils::end;

          logger().info()
            << " opponentIrSensorRight   :"
            << " pin:" << robot.opponentIrSensorRight().adcPin()
            << " Volt: " << robot.opponentIrSensorRight().voltage()
            << " Dist: " << robot.opponentIrSensorRight().distanceMm()
            << " mm" << (robot.opponentIrSensorRight().distanceMm() > 300 ?" MAX ":"")
            << utils::end;

         logger().info() << utils::end;
         usleep(5000);
    }

    robot.opponentIrSensorLeft().stopTimer();
    robot.opponentIrSensorRight().stopTimer();
    robot.opponentIrSensorCenter().stopTimer();


    /*
    robot.opponentIrSensorLeft().getObjectDistance();//active le listener:
    robot.opponentIrSensorRight().getObjectDistance();//active le listener:

    sleep(1);
    
    robot.opponentIrSensorLeft().active(true); //activation des calculs
    robot.opponentIrSensorRight().active(true); //activation des calculs

    int nb = 100;
    for(int i=0;i<nb;i++)
    {
     logger().info() << "active ? : "
             << " " << robot.opponentIrSensorLeft().active()
             << " " << robot.opponentIrSensorRight().active()
             << utils::end;

        logger().info() << i << " opponentIrSensorLeft  :"
                << " pin:" << robot.opponentIrSensorLeft().adcPin()
                << " Volt: " << robot.opponentIrSensorLeft().voltage()
                << " Dist: " << robot.opponentIrSensorLeft().distanceMm()
                << " mm" << (robot.opponentIrSensorLeft().distanceMm() > 1500 ?" MAX ":" ")
                << utils::end;
        logger().info()
                << i << " opponentIrSensorRight  :"
                << " pin:" << robot.opponentIrSensorRight().adcPin()
                << " Volt: " << robot.opponentIrSensorRight().voltage()
                << " Dist: " << robot.opponentIrSensorRight().distanceMm()
                << " mm" << (robot.opponentIrSensorRight().distanceMm() > 1500 ?" MAX ":"")
                << utils::end;

        robot.opponentIrSensorLeft().reset();
        robot.opponentIrSensorRight().reset();

        //logger().info() << utils::end;
        usleep(300000);
    }


   
    //Arret des listeners
    robot.opponentIrSensorLeft().stopListener(true);
    robot.opponentIrSensorRight().stopListener(true);
*/
    logger().info() << "Stop" << utils::end;
    robot.stop();
}
