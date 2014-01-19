/*!
 * \file
 * \brief Implémentation de la classe ServoMotorObject.
 * \deprecated
 */

#include "ServoMotorObject.hpp"
#include "RobotInOutFactory.hpp"
#include "Robot.hpp"

pmx::ServoMotorObjectAction::ServoMotorObjectAction(pmx::ServoMotorObject & servomotor, pmx::ServoMotorObjectActionName action, bool freewheeling)
: servomotor_(servomotor), action_(action), lastTime_(0), mode_(0), freewheeling_(freewheeling)
{
    chrono_.start();
}

pmx::ServoMotorObject::ServoMotorObject(pmx::Robot & robot, int servoId)
: ARobotElement(robot), stateOpened_(0), actionStopped_(0), id_(servoId)
{
    logger().debug() << "ServoMotorObject::ServoMotorObject()" << utils::end;
}

void
pmx::ServoMotorObject::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "ServoMotorObject::initialize() prefix=" << prefix << utils::end;
    this->valMin_ = configuration.getInt(prefix + "-Min");
    this->valMed_ = configuration.getInt(prefix + "-Med");
    this->valMax_ = configuration.getInt(prefix + "-Max");
    this->valSpeed_ = configuration.getInt(prefix + "-Speed");
}

bool pmx::ServoMotorObjectAction::execute(IRobotOut * out) //\TODO remplacer IRobotOut par RobotInOutFactory::instance
{
    //logger().debug() << "execute()" << utils::end;

    if (servomotor_.stop())
    {
        return !servomotor_.stop(); //l'action se supprime.
    }

    pmx::ServoMotorApf * servo = pmx::RobotInOutFactory::instance()->outServoMotor();
    if(servo == NULL)
        logger().error() << "ERROR pmx::ServoMotorObjectAction::execute : pmx::RobotInOutFactory::instance()->outServoMotor() is NULL" << utils::end;
    //logger().debug() << " getServoCurrentPosition ID=" << this->servomotor_.id() << " pos=" << servo->getServoCurrentPosition(this->servomotor_.id()) << utils::end;

    switch(this->action_)
    {
        case pmx::SERVOTURNMIN :

            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(this->servomotor_.id(), this->servomotor_.min());
                servo->setServoEnable(this->servomotor_.id(), 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if ((mode_ == 1 &&  servo->getServoCurrentPosition(this->servomotor_.id()) == this->servomotor_.min())
                    || chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 10000000)//timeout de 10s
            {
                logger().debug() << "\nmode1" << utils::end;
                if(freewheeling_)
                    servo->setServoEnable(this->servomotor_.id(), 0); //freewheeling

                //this->servomotor_.Arrived(1);
                mode_ = 0;
                return false; //l'action se supprime.
            }else
            {
                return true; //on garde l'action en vie
            }
            break;

        case pmx::SERVOTURNMED :
            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(this->servomotor_.id(), this->servomotor_.med());
                servo->setServoEnable(this->servomotor_.id(), 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if ((mode_ == 1 && servo->getServoCurrentPosition(this->servomotor_.id()) == this->servomotor_.med())
                    || chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 10000000) //timeout de 10s
            {
                logger().debug() << "\nmode1" << utils::end;
                if(freewheeling_)
                    servo->setServoEnable(this->servomotor_.id(), 0); //freewheeling

                //this->servomotor_.Arrived(1);
                mode_ = 0;
                return false;//l'action se supprime.
            }else
            {
                return true;
            }
            break;

        case pmx::SERVOTURNMAX :
            if(mode_ == 0)
            {
                logger().debug() << "\nmode0" << utils::end;
                servo->setServoPosition(this->servomotor_.id(), this->servomotor_.max());
                servo->setServoEnable(this->servomotor_.id(), 1);
                mode_ = 1;
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                return true; //on garde l'action en vie
            }

            if ((mode_ == 1 && servo->getServoCurrentPosition(this->servomotor_.id()) == this->servomotor_.max())
                    || chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 10000000) //timeout de 10s
            {
                logger().debug() << "\nmode1" << utils::end;
                if(freewheeling_)
                    servo->setServoEnable(this->servomotor_.id(), 0); //freewheeling

                //this->servomotor_.Arrived(1);
                mode_ = 0;
                return false;//l'action se supprime.
            }else
            {
                return true;
            }
            break;

        //case pmx::FREEWHEELING :
            //!\todo OPENLITTLE
            //break;

        default : logger().error() << "switch : mauvaise action requise !!" << utils::end;
            break;
    }
    return false; //l'action se supprime.
}

void
pmx::ServoMotorObject::turnMin(bool freewheeling)
{
    this->robot().addAction(new pmx::ServoMotorObjectAction(*this, pmx::SERVOTURNMIN, freewheeling));
}

void
pmx::ServoMotorObject::turnMed(bool freewheeling)
{
    this->robot().addAction(new pmx::ServoMotorObjectAction(*this, pmx::SERVOTURNMED, freewheeling));
}

void
pmx::ServoMotorObject::turnMax(bool freewheeling)
{
    this->robot().addAction(new pmx::ServoMotorObjectAction(*this, pmx::SERVOTURNMAX, freewheeling));
}

