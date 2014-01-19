/*!
 * \file
 * \brief Implémentation de la classe SimpleSensor.
 */

#include "SimpleSensor.hpp"
#include "Robot.hpp"

pmx::SimpleSensor::SimpleSensor(pmx::Robot & robot, ushort mu, ushort pin)
: ARobotElement(robot), mu_(mu), pin_(pin)
{
}
