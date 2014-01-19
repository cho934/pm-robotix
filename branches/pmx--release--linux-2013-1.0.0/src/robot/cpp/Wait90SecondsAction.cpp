/*!
 * \file
 * \brief Implémentation de la classe Wait90SecondsAction.
 */

#include "Wait90SecondsAction.hpp"
#include "Robot.hpp"
#include "LedIndicator.hpp"

pmx::Wait90SecondsAction::Wait90SecondsAction(pmx::Robot* robot) : robot_(robot)
{}

void
pmx::Wait90SecondsAction::execute()
{
    this->logger().info() << "start" << utils::end;

    
    sleep(90);
    

    //arret de tout les mécanismes
    this->robot_->stopDevices();

    //Gonfler le ballon pendant 10s
    //this->robot_->ledBar().startK2Mil(50000, 10000, false);

    this->robot_->ledBar().startAlternate(1000, 50000, 0xF0, 0x0F, false);
    
    // actionner le servomoteur
    robot_->servoBalloonInflate().turnMax(false);

    //sleep(3);
    pmx::LedIndicator::instance().alternate(20, 250000, 0xF0, 0x0F);

    robot_->servoBalloonInflate().turnMin(true);
    usleep(100000);

    this->robot_->ledBar().stopAndWait(true);

    //End of PMX
    this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << utils::end;
    this->logger().info() << "Real execution time: " << this->robot_->chronometerRobot().getElapsedTimeInSec() << utils::end;
    this->robot_->stop();
    printf("Wait 90s EXIT\n");
    exit(70);
}
