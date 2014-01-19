/*!
 * \file
 * \brief Implementation de la classe DistanceSensorTest.
 */

#include <iostream>
#include "DistanceSensorTest.hpp"
#include "Robot.hpp"
#include "SimpleSensorListener.hpp"
#include "IrSensor.hpp"
#include <as_devices/as_max1027.h>

void test::DistanceSensorTest::run(int argc, char *argv[])
{
    int average;

    if (argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [Average:4,8,16,32,1 for disabling]" << std::endl;
    }

    if (argc > 2)
    {
        average = atoi(argv[2]);
    }
    else
    {
        //demande du port
        std::cout << "[Average:4,8,16,32,1 for disabling] : " << std::flush;
        std::cin >> average;
    }

    pmx::Robot robot;
    //Désactivation des moteurs, car ce n'est pas ce que l'on veut tester
    robot.base().motorLeft().disabled(true);
    robot.base().motorRight().disabled(true);

    struct as_max1027_device *max1027_dev;
    max1027_dev = as_max1027_open(1, AS_MAX1027_SLOW);//MAX1027_SPI_NUM = 1 on APF9328
    as_max1027_set_averaging(max1027_dev, average);
    as_max1027_close(max1027_dev);
    
    robot.start();
    robot.chronometerRobot().start(); //Chronometre général (match) du robot

    //pawnLeftIrSensor
    robot.pawnLeftIrSensor().getObjectDistance();//active le listener:   
    //pawnRightIrSensor
    robot.pawnRightIrSensor().getObjectDistance();//active le listener:

    robot.opponentIrSensor().getObjectDistance();//active le listener:

    sleep(1);
    
    robot.pawnLeftIrSensor().active(true); //activation des calculs
    robot.pawnRightIrSensor().active(true); //activation des calculs
    robot.opponentIrSensor().active(true); //activation des calculs

    int nb = 100;
    for(int i=0;i<nb;i++)
    {
     logger().info() << "active ? : " << robot.pawnLeftIrSensor().active() << " "<< robot.pawnRightIrSensor().active() << " "<< robot.opponentIrSensor().active() << utils::end;

        logger().info() << i << " pawnLeftIrSensor  :"
                << " pin:" << robot.pawnLeftIrSensor().adcPin()
                << " Volt: " << robot.pawnLeftIrSensor().voltage()
                << " Dist: " << robot.pawnLeftIrSensor().distanceMm()
                << " mm" << (robot.pawnLeftIrSensor().distanceMm() > 350 ?" MAX ":"")
                << utils::end;



        logger().info() << i << " pawnRightIrSensor :"
                << " pin:" << robot.pawnRightIrSensor().adcPin()
                << " Volt: " << robot.pawnRightIrSensor().voltage()
                << " Dist: " << robot.pawnRightIrSensor().distanceMm()
                << " mm" << (robot.pawnRightIrSensor().distanceMm() > 350 ?" MAX ":"")
                << utils::end;



        logger().info() << i << " opponentIrSensor  :"
                << " pin:" << robot.opponentIrSensor().adcPin()
                << " Volt: " << robot.opponentIrSensor().voltage()
                << " Dist: " << robot.opponentIrSensor().distanceMm()
                << " mm" << (robot.opponentIrSensor().distanceMm() > 1500 ?" MAX ":"")
                << utils::end;

        logger().info() << utils::end;
        usleep(300000);
    }


   
    //Arret des listeners
    robot.pawnLeftIrSensor().stop(true);
    robot.pawnRightIrSensor().stop(true);
    robot.opponentIrSensor().stop(true);

    logger().info() << "Stop" << utils::end;
    robot.stop();
}
