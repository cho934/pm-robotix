/*!
 * \file
 * \brief Implémentation de la classe Fork (Fourchette).
 */

#include "Fork.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"

pmx::Fork::Fork(pmx::Robot & robot, int servoNum)
: ARobotElement(robot), servoNum_(servoNum), state_(0), actionStopped_(0)
{}

pmx::ForkAction::ForkAction(pmx::Fork & fork, pmx::ForkActionName action)
: fork_(fork), action_(action), lastTime_(0), mode_(0)
{
    chrono_.start();
}

bool pmx::ForkAction::execute(IRobotOut *)
{
    //logger().debug() << "execute()" << utils::end;

    if (fork_.stop())
    {
        return !fork_.stop(); //l'action se supprime.
    }

    pmx::ServoMotorApf * servo = pmx::RobotInOutFactory::instance()->outServoMotor();

    switch(this->action_)
    {
        case pmx::FORKHIGH :

            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(this->fork_.servoNum(), this->fork_.forkHighPosition());
                
                servo->setServoEnable(this->fork_.servoNum(), 1);
                
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 1000000) //todo utiliser servo->getServoPosition() ?
            {
                logger().debug() << "\nmode1" << utils::end;
                servo->setServoEnable(this->fork_.servoNum(), 0); //freewheeling
                this->fork_.state(1);
                mode_ = 0;
                return false;
            }else
            {
                return true;
            }
            break;

        case pmx::FORKLOW :

            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(this->fork_.servoNum(), this->fork_.forkLowPosition());

                servo->setServoEnable(this->fork_.servoNum(), 1);

                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 1000000) //todo utiliser servo->getServoPosition() ?
            {
                logger().debug() << "\nmode1" << utils::end;
                servo->setServoEnable(this->fork_.servoNum(), 0); //freewheeling
                this->fork_.state(1);
                mode_ = 0;
                return false;
            }else
            {
                return true;
            }
            break;

        default : logger().error() << "switch : mauvaise action requise !!" << utils::end;
            break;
    }
    return false; //l'action se supprime.
}

void
pmx::Fork::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "initialize: " << prefix << utils::end;

    this->forkHighPosition_ = configuration.getInt(prefix + "-highposition");
    this->forkLowPosition_ = configuration.getInt(prefix + "-lowposition");

}

void
pmx::Fork::goHighPosition()
{
    this->state(0);
    this->robot().addAction(new pmx::ForkAction(*this, pmx::FORKHIGH));
}
void
pmx::Fork::keepHighPosition()
{
    this->state(0);

    this->robot().addAction(new pmx::ForkAction(*this, pmx::FORKKEEPHIGH));
}

void
pmx::Fork::goLowPosition()
{
    this->state(0);

    this->robot().addAction(new pmx::ForkAction(*this, pmx::FORKLOW));
}
void
pmx::Fork::keepLowPosition()
{
    this->state(0);

    this->robot().addAction(new pmx::ForkAction(*this, pmx::FORKKEEPLOW));
}

void pmx::Fork::waitPositionReached(){
    while(state_ != 1)
    {
        usleep(10000);
    }
}



