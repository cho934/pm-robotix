/*!
 * \file
 * \brief Implémentation de la classe ServoMotor2p.
 * \deprecated
 */

#include "ServoMotor2p.hpp"
#include "Robot.hpp"


pmx::ServoMotor2pAction::ServoMotor2pAction(const pmx::ServoMotor2p & servomotor)
: servomotor_(servomotor), chronometerServo_(), pulse_(false)
{}

pmx::ServoMotor2p::ServoMotor2p(pmx::Robot & robot, ushort dm, ushort pin, int angleMin, int angleMax, int speed)
: ARobotElement(robot), active_(false), state_(false), dm_(dm), pin_(pin), angleMin_(angleMin), angleMax_(angleMax), speed_(speed)
{
    logger().debug() << "ServoMotor::ServoMotor2p()" << utils::end;
}

void
pmx::ServoMotor2p::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    this->angleMin_ = configuration.getInt(prefix + "-angleMin");
    this->angleMax_ = configuration.getInt(prefix + "-angleMax");
    this->speed_ = configuration.getInt(prefix + "-speed");
}

bool pmx::ServoMotor2pAction::execute(IRobotOut * out)
{
    if (servomotor_.active())
    {
        if (!chronometerServo_.started())
        {
            logger().debug("ServoMotor2pAction::execute() - start chronometer");
            //démarrage du chronometer pour la période
            chronometerServo_.start();
            //démarrage front montant
            logger().debug() << "ServoMotor2pAction::execute() - up [chronometer:" << time << "]" << utils::end;
            out->setValue(servomotor_.dm(), servomotor_.pin(), true);
            pulse_ = true;
        }
        else
        {
            long time = chronometerServo_.getElapsedTimeInMicroSec();
            //activation front descendant
            if ((servomotor_.state() && pulse_ && time >= servomotor_.angleMin()) || (!servomotor_.state() && pulse_ && time >= servomotor_.angleMax()))
            {
                logger().debug() << "ServoMotor2pAction::execute() - down [chronometer:" << time << "]" << utils::end;
                out->setValue(servomotor_.dm(), servomotor_.pin(), false);
                pulse_ = false;
            }
            //fin de la période
            else if (! pulse_ && time >= servomotor_.speed())
            {
                logger().debug() << "ServoMotor2pAction::execute() - stop [chronometer:" << time << "]" << utils::end;
                chronometerServo_.stop();
            }
        }
    }
    return true;
}
