/*!
 * \file
 * \brief Implémentation de la classe IrSensor.
 */

#include <cmath>
#include "IrSensor.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"

pmx::IrSensor::IrSensor(pmx::Robot & robot, ushort adcPin, int type)
: ARobotElement(robot), 
adcPin_(adcPin), type_(type), voltage_(0), distanceMm_(9999.0)
{
}

void pmx::IrSensor::reset() {
    logger().debug() << "              !! reset !! " << utils::end;
    this->voltage_ = 0;
    this->distanceMm_ = 9999.0;
}
