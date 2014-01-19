#include "MovePositionTest.hpp"
#include "Robot.hpp"
#include "MovementAction.hpp"
#include <cmath>

void
test::MovePositionTest::run(int argc, char* argv[])
{
    logger().info() << "test::RobotMoveTest: Start" << utils::end;
    double targetX;
    double targetY;
    
    if(argc > 2 && argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [targetX] [targetY]" << std::endl;
    }
    
    if(argc < 4)
    {
        std::cout << "target-x: " << std::flush;
        std::cin >> targetX;
        std::cout << "target-y: " << std::flush;
        std::cin >> targetY;
    }
    else
    {
        targetX = atof(argv[2]);
        targetY = atof(argv[3]);
    }
    
    pmx::Robot robot;
    robot.configure("robot.conf");
    robot.start();
    robot.chronometerRobot().start();
    
    //robot.base().motorLeft().speedCorrectionEnabled(4, 0.435, 0);
    //robot.base().motorRight().speedCorrectionEnabled(6.975, 0.373, 0);
    //robot.base().motorRight().speedCorrectionEnabled(5, 0.435, 0);
    //robot.base().motorLeft().orderSpeed(150);
    //robot.base().motorRight().orderSpeed(150);
    
    /*
    //pmx::MovementAction* mouvementAction = robot.moveTo(targetX, targetY);
    pmx::MovementAction* movementAction = new pmx::MovementAction(robot, targetX, targetY);
    robot.addAction(movementAction);

    while(movementAction->arrived() == false)
    {
        pthread_yield();
    }
    */
    
    robot.base().movexy(targetX, targetY);
    
    while(robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        pthread_yield();
    }
    logger().info() << "Arrived" << utils::end;
    robot.base().stop();
    
    robot.chronometerRobot().stop();
    
    robot.stop();
}
