/*!
 * \file
 * \brief Implementation de la classe StepperTest.
 */

#include <iostream>
#include "StepperTest.hpp"
#include "Robot.hpp"

void test::StepperTest::run(int, char *[])
{
    pmx::Robot robot;
    robot.start();

    logger().debug() << "Go" << utils::end;
    
    //TODO tourner dans les 2 sens.
    robot.stepper().turn();
    usleep(10000000);
    robot.stepper().stop();
    
  
    robot.stop();
    
}

