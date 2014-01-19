/*!
 * \file
 * \brief Implémentation de la classe ServoMotor.
 * \deprecated
 */

#include "ServoMotor.hpp"
#include "Robot.hpp"


pmx::ServoMotorAction::ServoMotorAction(const pmx::ServoMotor & servomotor)
: servomotor_(servomotor), chronometerServo_(), pulse_(false)
{}

pmx::ServoMotor::ServoMotor(pmx::Robot & robot, ushort dm, ushort pin, int speed)
: ARobotElement(robot), active_(false), state_(false), dm_(dm), pin_(pin), values_(), speed_(speed)
{
    logger().debug() << "ServoMotor::ServoMotor()" << utils::end;
}

void
pmx::ServoMotor::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    this->values_.clear();
    this->values_.push_back(configuration.getInt(prefix + "-pushed"));
    this->values_.push_back(configuration.getInt(prefix + "-retired"));
    this->speed_ = configuration.getInt(prefix + "-speed");
}

bool pmx::ServoMotorAction::execute(IRobotOut * out)
{
    if (servomotor_.active())
    {
        if (!chronometerServo_.started())
        {
            logger().debug("ServoMotorAction::execute() - start chronometer");
            //démarrage du chronometer pour la période
            chronometerServo_.start();
            //démarrage front montant
            logger().debug() << "ServoMotorAction::execute() - up [chronometer:" << time << "]" << utils::end;
            out->setValue(servomotor_.dm(), servomotor_.pin(), true);
            pulse_ = true;
        }
        else
        {
            long time = chronometerServo_.getElapsedTimeInMicroSec();
            //activation front descendant
            if (servomotor_.state() && pulse_ && time >= servomotor_.values()[servomotor_.currentValue()])
            {
                logger().debug() << "ServoMotorAction::execute() - down [chronometer:" << time << "]" << utils::end;
                out->setValue(servomotor_.dm(), servomotor_.pin(), false);
                pulse_ = false;
            }
            //fin de la période
            else if (! pulse_ && time >= servomotor_.speed())
            {
                logger().debug() << "ServoMotorAction::execute() - stop [chronometer:" << time << "]" << utils::end;
                chronometerServo_.stop();
            }
        }
    }
    return true;
}
