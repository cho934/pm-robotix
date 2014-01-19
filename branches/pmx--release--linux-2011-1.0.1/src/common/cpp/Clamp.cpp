/*!
 * \file
 * \brief Implémentation de la classe Clamp (Pince).
 */
#include "Clamp.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"


pmx::Clamp::Clamp(pmx::Robot & robot)
: ARobotElement(robot), stateOpened_(0), actionStopped_(0)
{}

pmx::ClampAction::ClampAction(pmx::Clamp & clamp, pmx::ClampActionName action)
: clamp_(clamp), action_(action), lastTime_(0), mode_(0)
{
    chrono_.start();
}

bool pmx::ClampAction::execute(IRobotOut *)
{
    //logger().debug() << "execute()" << utils::end;

    if (clamp_.stop())
    {
        return !clamp_.stop(); //l'action se supprime.
    }

    pmx::ServoMotorApf * servo = pmx::RobotInOutFactory::instance()->outServoMotor();

    switch(this->action_)
    {
        case pmx::OPENWIDE :

            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(pmx::CLAMPLEFT, this->clamp_.clampLeftWideOpened());
                servo->setServoPosition(pmx::CLAMPRIGHT, this->clamp_.clampRightWideOpened());
                servo->setServoEnable(pmx::CLAMPLEFT, 1);
                servo->setServoEnable(pmx::CLAMPRIGHT, 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 1000000)
            {
                logger().debug() << "\nmode1" << utils::end;
                servo->setServoEnable(pmx::CLAMPLEFT, 0); //freewheeling
                servo->setServoEnable(pmx::CLAMPRIGHT, 0); //freewheeling
                this->clamp_.stateOpened(1);
                mode_ = 0;
                return false;
            }else
            {
                return true;
            }
            break;

        case pmx::OPENMEDIUM :
            //!\todo OPENMEDIUM
            break;
            
        case pmx::OPENLITTLE :
            //!\todo OPENLITTLE
            break;
            
        case pmx::CLOSE :

            if(mode_ == 0)
            {
                logger().info() << "close mode 0" << utils::end;
                servo->setServoPosition(pmx::CLAMPLEFT, this->clamp_.clampLeftClosed());
                servo->setServoPosition(pmx::CLAMPRIGHT, this->clamp_.clampRightClosed());
                servo->setServoEnable(pmx::CLAMPLEFT, 1);
                servo->setServoEnable(pmx::CLAMPRIGHT, 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }
            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 1000000)
            {
                logger().info() << "close mode 1" << utils::end;
                servo->setServoEnable(pmx::CLAMPLEFT, 0); //freewheeling
                servo->setServoEnable(pmx::CLAMPRIGHT, 0); //freewheeling
                this->clamp_.stateOpened(0);
                mode_ = 0;
                return false;
            }else
            {
                return true;
            }

            break;

        case pmx::KEEPCLOSE :

            if(mode_ == 0)
            {
                logger().info() << "KEEPCLOSE mode 0" << utils::end;
                servo->setServoPosition(pmx::CLAMPLEFT, this->clamp_.clampLeftClosed());
                servo->setServoPosition(pmx::CLAMPRIGHT, this->clamp_.clampRightClosed());
                servo->setServoEnable(pmx::CLAMPLEFT, 1);
                servo->setServoEnable(pmx::CLAMPRIGHT, 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }
            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 1000000)
            {
                logger().info() << "KEEPCLOSE mode 1" << utils::end;
               //no freewheeling
                this->clamp_.stateOpened(0);
                mode_ = 0;
                return false;
            }
            return true;
            break;

        default : logger().error() << "switch : mauvaise action requise !!" << utils::end;
            break;
    }
    return false; //l'action se supprime.
}

void
pmx::Clamp::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "initialize: " << prefix << utils::end;

    this->clampLeftWideOpened_ = configuration.getInt(prefix + "-Left" + "-wideopened");
    this->clampLeftMediumOpened_ = configuration.getInt(prefix + "-Left" + "-mediumopened");
    this->clampLeftLittleOpened_ = configuration.getInt(prefix + "-Left" + "-littleopened");
    this->clampLeftClosed_ = configuration.getInt(prefix + "-Left" + "-closed");
    this->clampRightWideOpened_ = configuration.getInt(prefix + "-Right" + "-wideopened");
    this->clampRightMediumOpened_ = configuration.getInt(prefix + "-Right" + "-mediumopened");
    this->clampRightLittleOpened_ = configuration.getInt(prefix + "-Right" + "-littleopened");
    this->clampRightClosed_ = configuration.getInt(prefix + "-Right" + "-closed");

}

void
pmx::Clamp::openWidePosition()
{
    this->robot().clamp().stateOpened(0);

    this->robot().addAction(new pmx::ClampAction(*this, pmx::OPENWIDE));
}

void
pmx::Clamp::openMediumPosition()
{
    //todo
}

void
pmx::Clamp::openLittlePosition()
{
    //todo
}

void
pmx::Clamp::keepClose()
{
    this->robot().clamp().stateOpened(1);
    this->robot().addAction(new pmx::ClampAction(*this, pmx::KEEPCLOSE));
}

void
pmx::Clamp::close()
{
    this->robot().clamp().stateOpened(1);
    this->robot().addAction(new pmx::ClampAction(*this, pmx::CLOSE));
}
