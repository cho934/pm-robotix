/*!
 * \file
 * \brief Implémentation de la classe RobotOpponentTest.
 */

#include "RobotOpponentTest.hpp"
#include "Robot.hpp"

void test::RobotOpponentTest::run(int argc, char *argv[])
{
    logger().info() << " Start" << utils::end;
    //std::cout << "test::RobotOpponentTest: Start" << std::endl;
    pmx::Robot robot;

    robot.start();
    robot.chronometerRobot().start();

    robot.ledBar().blink(6);
    robot.ledBar().k2Mil();

    bool collision = false;
    bool collisionOld = false;


    robot.opponentDetector().addOpponentListener();
    robot.opponentDetector().active(true);

    while(robot.chronometerRobot().getElapsedTimeInSec() <= 15)
    {
        /*while(robot.opponentDetector().received() == false) //attente de la reponse
        {
            usleep(100);
        }*/
        collision = robot.opponentDetector().imminenteCollision();
        if(collision != collisionOld)
        {
            logger().debug() << "detect :" << collision << utils::end;
            if(collision)
            {
                logger().debug() << "!!!! collision !!!!" << utils::end;
            }
        }
        collisionOld = collision;
    }

    robot.chronometerRobot().stop();
    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}

