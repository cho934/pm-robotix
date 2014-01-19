/*!
 * \file
 * \brief Implémentation de la classe SimpleSensor.
 */

#include "SimpleSensor.hpp"
#include "SimpleSensorListener.hpp"
#include "Robot.hpp"

pmx::SimpleSensor::SimpleSensor(pmx::Robot & robot, ushort mu, ushort pin)
: ARobotElement(robot), listenerStopped_(false), mu_(mu), pin_(pin), state_(false)
{
}

void
pmx::SimpleSensor::wait()
{
    this->stop(false);
    this->robot().addListener(new pmx::SimpleSensorListener(*this));
}
