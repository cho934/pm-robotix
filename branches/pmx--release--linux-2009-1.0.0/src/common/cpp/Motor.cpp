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
    logger().debug() << motor_.location() << " sens demande:" << this->way_ << utils::end;
    ushort DMWrCs;
    if (motor_.location() == pmx::LEFT)
    {
        logger().debug() << " LEFT :" << motor_.location() << utils::end;
        DMWrCs = pmx::IRobotOut::DM5;
    }
    else if (motor_.location() == pmx::RIGHT)
    {
        logger().debug() << " RIGHT :" << motor_.location() << utils::end;
        DMWrCs = pmx::IRobotOut::DM6;
    }
    
    if (this->way_ == pmx::FORWARD)
    {
        logger().debug() << " out->setValue()" << false << utils::end;
        out->setValue(DMWrCs, pmx::IRobotOut::PIN0, false);
        logger().debug() << " mise à jour de la valeur interne" << utils::end;
        motor_.way(pmx::FORWARD);//mise à jour de la valeur interne.
        logger().debug() << " mise à jour FORWARD:ok" << utils::end;
    }else if (this->way_ == pmx::BACK)
    {
        logger().debug() << " out->setValue()" << true << utils::end;
        out->setValue(DMWrCs, pmx::IRobotOut::PIN0, true);
        logger().debug() << " mise à jour de la valeur interne" << utils::end;
        motor_.way(pmx::BACK);//mise à jour de la valeur interne.
        logger().debug() << " mise à jour BACK:ok" << utils::end;
    }
    return false; //l'action se supprime après execution.
}

bool pmx::MotorSpeedAction::execute(IRobotOut * out)
{
    logger().debug() << " pmx::MotorSpeedAction::execute " << utils::end;
    ushort DMWordSpeed;
    ushort DMWrCs;
    
    // Choix de la position moteur "droit" ou moteur "gauche"
    // afin de permettre d'affecter la bonne configuration de brochage
    // la configuration requise est la suivante:
    //DMx   : puissance du moteur
    //DMx+1 : configuration
    //DMx+1 : PIN0 : marche avant/arriere
    //DMx+1 : PIN1 : WR|
    //DMx+1 : PIN2 : CS|
    /// \todo Externaliser la configuration des DM et des PIN
    
    if (motor_.location() == pmx::LEFT)
    {
        logger().debug() << " LEFT :" << motor_.location() << " speedMotorCode_:" << speedMotorCode_ << utils::end;
        DMWordSpeed = pmx::IRobotOut::DM4;
        DMWrCs = pmx::IRobotOut::DM5;
    }
    else if (motor_.location() == pmx::RIGHT)
    {
        logger().debug() << " RIGHT :" << motor_.location() << " speedMotorCode_:" << speedMotorCode_ << utils::end;
        DMWordSpeed = pmx::IRobotOut::DM7;
        DMWrCs = pmx::IRobotOut::DM6;
    }
    
    // \todo check du temps d'execution de la première execution sur chaque moteur au démarrage, voir si cela vient d'un pb à l'execution !
    
    out->setValue(DMWrCs, pmx::IRobotOut::PIN2, false);
    out->setValue(DMWrCs, pmx::IRobotOut::PIN1, false);
    out->setValues(DMWordSpeed, static_cast<ushort>(speedMotorCode_));
    out->setValue(DMWrCs, pmx::IRobotOut::PIN1, true);
    out->setValue(DMWrCs, pmx::IRobotOut::PIN1, false);
    out->setValue(DMWrCs, pmx::IRobotOut::PIN2, true);
    
    return false;
}

pmx::Motor::Motor(pmx::Robot & robot, const MotorLocation & location, const MotorWay way, double gradient, double yIntersept, const utils::PID & pid)
: ARobotElement(robot), location_(location), way_(way), gradient_(gradient), yIntersept_(yIntersept), orderSpeed_(0), manager_(NULL), speedCorrectionEnabled_(true)
{
    this->manager_ = pmx::SpeedManager::createInstance(this, pid);
    robot.addListener(this->manager_);
}

void
pmx::Motor::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    this->gradient_ = configuration.getDouble(prefix + "-gradient");
    this->yIntersept_ = configuration.getDouble(prefix + "-yIntersept");
    this->manager_->initialize(prefix + "-manager", configuration);
}

double
pmx::Motor::convertToSpeed(int motorCode)
{
    return this->gradient_ * motorCode + this->yIntersept_;
}

int
pmx::Motor::convertToMotorCode(double speed)
{
    double motorCode = (speed - this->yIntersept_) / this->gradient_;
    int roundedMotorCode = (int) round(motorCode);
    
    if (roundedMotorCode < 0)
    {
        return 0;
    }
    else if(roundedMotorCode > 253)
    {
        return 253;
    }
    else
    {
        return roundedMotorCode;
    }
}

void
pmx::Motor::applyMotorCode(int motorCode)
{
    this->robot().addAction(new pmx::MotorSpeedAction(*this, motorCode));
}

void
pmx::Motor::applyWay(const pmx::MotorWay way)
{
    this->robot().addAction(new pmx::MotorWayAction(*this, way));
}

void
pmx::Motor::speedCorrectionEnabled(double P, double I, double D)
{
    this->speedCorrectionEnabled_ = true;
    this->manager_->initializeSpeedControler(utils::PID(P, I, D));
}
