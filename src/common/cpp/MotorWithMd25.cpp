/*!
 * \file
 * \brief Implémentation de la classe MotorWithMd25.
 */

#include <cmath>
#include "MotorWithMd25.hpp"
#include "Robot.hpp"

bool pmx::MotorWithMd25SpeedAction::execute(IRobotOut * out)
{
    logger().debug() << " execute : " << motor_.location() << utils::end;

    if (motor_.location() == pmx::MLEFT)
    {
        if (motor_.speedMotorCode() > 127 || motor_.speedMotorCode() < -128)
            logger().error() << "motorlocation:" << motor_.location() << ": applyMotorCode out of range : " << motor_.speedMotorCode() << utils::end;
        else
            out->setValues(pmx::IRobotOut::MD25_MOTOR_LEFT, motor_.speedMotorCode());
    }else if (motor_.location() == pmx::MRIGHT)
    {
        if (motor_.speedMotorCode() > 127 || motor_.speedMotorCode() < -128)
            logger().error() << "motorlocation:" << motor_.location() << ": applyMotorCode out of range : " << motor_.speedMotorCode() << utils::end;
        else
            out->setValues(pmx::IRobotOut::MD25_MOTOR_RIGHT, motor_.speedMotorCode());
    }

    return false; //l'action se supprime après execution.
}

pmx::MotorWithMd25::MotorWithMd25(pmx::Robot & robot, const MotorLocation & location)
: ARobotElement(robot), location_(location), orderSpeed_(0), orderTick_(0), 
        oldOrderTick_(0), orderPositionTick_(0), disabled_(false),
        speedMotorCode_(0)
{
}

/*!
 * \brief Récupère les infos du fichier de configuration
 */
void
pmx::MotorWithMd25::initialize(const std::string&, utils::Configuration&)
{
}

/*!
 * \brief Applique un motorcode de -127 à 128.
 */
void
pmx::MotorWithMd25::applyMotorCode(int motorCode)
{
    if (this->disabled_ == false)
    {
        logger().debug() << "Motor applyMotorCode:" << motorCode << utils::end;
        this->robot().addAction(new pmx::MotorWithMd25SpeedAction(*this, motorCode));
    }
}
