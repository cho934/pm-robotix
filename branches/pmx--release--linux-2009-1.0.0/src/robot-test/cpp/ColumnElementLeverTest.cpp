/*!
 * \file
 * \brief Implementation de la classe ColumnElementLeverTest.
 */

#include <iostream>
#include "ColumnElementLeverTest.hpp"
#include "Robot.hpp"

void test::ColumnElementLeverTest::run(int , char *[])
{
    pmx::Robot robot;
    robot.configure("robot.conf");
    robot.start();
    
    logger().info() << "rightPushElement retired " << utils::end;
    robot.rightPushElement().returnCentralePosition();
    usleep(3000000);
    robot.rightPushElement().active(false);
    //pushed
    logger().info() << "rightPushElement pushed " << utils::end;
    robot.rightPushElement().stackElement();
    usleep(3000000);
    robot.rightPushElement().active(false);
    
    
    logger().info() << "DM:" << robot.leftLever().dm() << " - pin:" << robot.leftLever().pin() << utils::end;
    
      
    logger().info() << "Empile un element à gauche" << utils::end;
    robot.leftLever().stackElement();
    usleep(4000000);
    robot.leftLever().active(false);
    
    logger().info() << "Position centrale droite : regler la position..." << utils::end;
    robot.rightLever().returnCentralePosition();
    usleep(8000000);
    robot.rightLever().active(false);
    
    logger().info() << "Empile un element à droite" << utils::end;
    robot.rightLever().stackElement();
    usleep(4000000);
    robot.rightLever().active(false);
    
    
    logger().info() << "Position centrale gauche : regler la position..." << utils::end;
    robot.leftLever().returnCentralePosition();
    usleep(8000000);
    robot.leftLever().active(false);
    
    logger().info() << "Empile un element à gauche" << utils::end;
    robot.leftLever().stackElement();
    usleep(4000000);
    robot.leftLever().active(false);
    
    logger().info() << "Position centrale droite" << utils::end;
    robot.rightLever().returnCentralePosition();
    usleep(3000000);
    robot.rightLever().active(false);
    
    logger().info() << "Empile un element à droite" << utils::end;
    robot.rightLever().stackElement();
    usleep(3000000);
    robot.rightLever().active(false);
        
    logger().info() << "Position centrale gauche" << utils::end;
    robot.leftLever().returnCentralePosition();
    usleep(3000000);
    robot.leftLever().active(false);
    
    logger().info() << "Empile un element à gauche" << utils::end;
    robot.leftLever().stackElement();
    usleep(4000000);
    robot.leftLever().active(false);
    
    
    logger().info() << "rightPushElement retired " << utils::end;
    robot.rightPushElement().returnCentralePosition();
    usleep(3000000);
    robot.rightPushElement().active(false);
    //pushed
    logger().info() << "rightPushElement pushed " << utils::end;
    robot.rightPushElement().stackElement();
    usleep(3000000);
    robot.rightPushElement().active(false);
    
    
    
    robot.stop();
}
