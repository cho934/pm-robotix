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
    debugThread("Wait90SecondsAction");
    this->logger().info() << "start" << utils::end;
    
    sleep(89);
    this->robot_->ledBar().k2Mil(10000);
    pmx::LedIndicator::instance().blink(10, 50000);

    this->logger().info() << "Stop of the Robot : END of MATCH 90 !" << utils::end;
    this->logger().info() << "Real execution time: " << this->robot_->chronometerRobot().getElapsedTimeInSec() << utils::end;
    this->robot_->stop();
    printf("Wait 90s EXIT\n");
    exit(70);
}
