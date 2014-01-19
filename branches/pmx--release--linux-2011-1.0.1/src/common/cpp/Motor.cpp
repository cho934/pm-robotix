/*!
 * \file
 * \brief Implémentation de la classe Motor.
 */

#include "Motor.hpp"
#include "Robot.hpp"
#include <cmath>

bool pmx::MotorWayAction::execute(IRobotOut * out)
{
    logger().debug() << " pmx::MotorWayAction::execute " << utils::end;
    logger().debug() << motor_.location() << " sens demande:" << this->wayToApply_ << utils::end;
    ushort DMPin;
    if (motor_.location() == pmx::LEFT)
    {
        logger().debug() << " LEFT :" << motor_.location() << utils::end;
        DMPin = pmx::IRobotOut::PIN0;
    }
    else if (motor_.location() == pmx::RIGHT)
    {
        logger().debug() << " RIGHT :" << motor_.location() << utils::end;
        DMPin = pmx::IRobotOut::PIN1;
    }
    
    if (this->wayToApply_ == pmx::FORWARD )
    {
        logger().debug() << " out->setValue()" << true << utils::end;
        out->setValue(pmx::IRobotOut::DM2, DMPin, true);
        logger().debug() << " mise à jour de la valeur interne" << utils::end;
        motor_.way(pmx::FORWARD);//mise à jour de la valeur interne.
        //logger().debug() << " mise à jour FORWARD:ok" << utils::end;
    }else if (this->wayToApply_ == pmx::BACK )
    {
        logger().debug() << " out->setValue()" << false << utils::end;
        out->setValue(pmx::IRobotOut::DM2, DMPin, false);
        logger().debug() << " mise à jour de la valeur interne" << utils::end;
        motor_.way(pmx::BACK);//mise à jour de la valeur interne.
        //logger().debug() << " mise à jour BACK:ok" << utils::end;
    }
    motor_.wayApplied(true); //notification
    return false; //l'action se supprime après execution.
}

bool pmx::MotorSpeedAction::execute(IRobotOut * out)
{
    logger().debug() << " execute : " << motor_.location() << utils::end;

    //Utilisation du DAC (MAX5821) de l'APF9328
    if (motor_.location() == pmx::LEFT)
    {
        out->setValues(pmx::IRobotOut::DAC_MOTOR_LEFT, static_cast<ushort>(speedMotorCode_));
    } else if (motor_.location() == pmx::RIGHT)
    {
        out->setValues(pmx::IRobotOut::DAC_MOTOR_RIGHT, static_cast<ushort>(speedMotorCode_));
    }
 
    return false; //l'action se supprime après execution.
}

pmx::Motor::Motor(pmx::Robot & robot, const MotorLocation & location, const MotorWay way, double gradient, double yIntersept)
: ARobotElement(robot), location_(location), way_(way), gradient_(gradient), yIntersept_(yIntersept), orderSpeed_(0), orderTick_(0), oldOrderTick_(0), orderPosition_(0), disabled_(false)
{

}

/*!
 * \brief Récupère les infos du fichier de configuration
 */
void
pmx::Motor::initialize(const std::string& , utils::Configuration& )
{
    
}

/*!
 * \brief conversion
 * \todo convertToSpeed deprecated
 * \deprecated
 */
double
pmx::Motor::convertToSpeed(int motorCode)
{
    return this->gradient_ * motorCode + this->yIntersept_;
}

/*!
 * \brief conversion vitesse en motorCode
 * \todo convertToMotorCode deprecated
 * \deprecated
 */
int
pmx::Motor::convertToMotorCode(double speed)
{
    double motorCode = (speed - this->yIntersept_) / this->gradient_;
    int roundedMotorCode = (int) round(motorCode);

    //saturation de la puissance appliquee aux moteurs : motorCode
    if (roundedMotorCode < 0)
    {
        return 0;
    }
    else if(roundedMotorCode > 1023)
    {
        return 1023;
    }
    else
    {
        return roundedMotorCode;
    }
}

void
pmx::Motor::applyMotorCode(int motorCode)
{
    if(this->disabled_ == false)
    {
        logger().debug() << "Motor applyMotorCode:" << motorCode << utils::end;
        this->robot().addAction(new pmx::MotorSpeedAction(*this, motorCode));
    }
}

void
pmx::Motor::applyWay(const pmx::MotorWay way)
{
    if(this->disabled_ == false)
    {
        this->wayApplied_ = false;
        logger().debug() << "Motor applyWay:" << way << utils::end;
        this->robot().addAction(new pmx::MotorWayAction(*this, way));
    }
}
