#include "Wait90SecondsAction.hpp"
#include "Robot.hpp"
#include "LedIndicator.hpp"

pmx::Wait90SecondsAction::Wait90SecondsAction(pmx::Robot* robot) : robot_(robot)
{}

void
pmx::Wait90SecondsAction::execute()
{
    this->logger().info() << "start" << utils::end;
    
    sleep(88);
    this->robot_->ledBar().k2Mil();
    pmx::LedIndicator::instance().blink(10);

    this->logger().info() << "stop of the Robot : END MATCH !" << utils::end;
    this->logger().info() << "real execution time: " << this->robot_->chronometerRobot().getElapsedTimeInSec() << utils::end;
    this->robot_->stop();
    exit(0);
}
