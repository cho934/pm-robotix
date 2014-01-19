/*!
 * \file
 * \brief Implémentation de la classe RobotOutLogger.
 */

#include "RobotOutLogger.hpp"

pmx::RobotOutLogger::RobotOutLogger()
{}

void
pmx::RobotOutLogger::setValue(ushort demultiplexor, ushort pin, bool state)
{
    logger().info() << "[dm:" << demultiplexor << "] [pin:" << pin << "] [state:" << state << "]" << utils::end;
}

void
pmx::RobotOutLogger::setValues(ushort demultiplexor, ushort value)
{
    logger().info() << "[dm:" << demultiplexor << "] [value:" << value << "]" << utils::end;
}
