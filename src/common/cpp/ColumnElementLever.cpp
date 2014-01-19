/*!
 * \file
 * \brief Implémentation de la classe ColumnElementLever.
 */

#include "ColumnElementLever.hpp"
#include "Robot.hpp"

pmx::ColumnElementLever::ColumnElementLever(pmx::Robot & robot, ushort dm, ushort pin, int angleMin, int angleMax, int speed)
: ARobotElement(robot), active_(false), state_(false), dm_(dm), pin_(pin), angleMin_(angleMin), angleMax_(angleMax), speed_(speed)
{
    logger().debug() << "ColumnElementLever::ColumnElementLever()" << utils::end;
}

void
pmx::ColumnElementLever::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    this->angleMin_ = configuration.getInt(prefix + "-angleMin");
    this->angleMax_ = configuration.getInt(prefix + "-angleMax");
    this->speed_ = configuration.getInt(prefix + "-speed");
}

pmx::ColumnElementLeverAction::ColumnElementLeverAction(const pmx::ColumnElementLever & lever)
: lever_(lever), chronometer_(), pulse_(false)
{}

bool pmx::ColumnElementLeverAction::execute(IRobotOut * out)
{
    if (lever_.active())
    {
        if (!chronometer_.started())
        {
            logger().debug("ColumnElementLeverAction::execute() - start chronometer");
            //démarrage du chronometer pour la période
            chronometer_.start();
            //démarrage front montant
            logger().debug() << "ColumnElementLeverAction::execute() - up [chronometer:" << time << "]" << utils::end;
            out->setValue(lever_.dm(), lever_.pin(), true);
            pulse_ = true;
        }
        else
        {
            long time = chronometer_.getElapsedTimeInMicroSec();
            //activation front descendant
            if ((lever_.state()==0 && pulse_ && time >= lever_.angleMax()) || 
                (lever_.state()==1 && pulse_ && time >= lever_.angleMin()))
            {
                logger().debug() << "ColumnElementLeverAction::execute() - down [chronometer:" << time << "]" << utils::end;
                out->setValue(lever_.dm(), lever_.pin(), false);
                pulse_ = false;
            }
            //fin de la période
            else if (! pulse_ && time >= lever_.speed())
            {
                logger().debug() << "ColumnElementLeverAction::execute() - stop [chronometer:" << time << "]" << utils::end;
                chronometer_.stop();
            }
        }
    }
    return true;
}
