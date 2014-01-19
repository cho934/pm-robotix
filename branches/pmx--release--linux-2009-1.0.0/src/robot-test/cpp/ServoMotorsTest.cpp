/*!
 * \file
 * \brief Implementation de la classe ServoMotorsTest.
 */

#include <list>
#include <vector>
#include <iostream>
#include "ServoMotorsTest.hpp"
#include "Robot.hpp"

void test::ServoMotorsTest::run(int , char *[])
{
    
    pmx::Robot robot;
    robot.configure("robot.conf");
    robot.start();
    
    logger().info() << "Shovel : DM:" << robot.shovel().dm() << " - pin:" << robot.shovel().pin() << utils::end;
    //retired
    logger().info() << "shovel retired : GoPosition(0)" << utils::end;
    robot.shovel().GoPosition(0);
    usleep(2000000);
    //pushed
    logger().info() << "shovel pushed : GoPosition(1)" << utils::end;
    robot.shovel().GoPosition(1);
    usleep(2000000);
    
    logger().info() << "shovel retired : GoPosition(0)" << utils::end;
    robot.shovel().GoPosition(0);
    usleep(2000000);
    //pushed
    logger().info() << "shovel pushed : GoPosition(1)" << utils::end;
    robot.shovel().GoPosition(1);
    usleep(2000000);
    
    robot.stop();
}
