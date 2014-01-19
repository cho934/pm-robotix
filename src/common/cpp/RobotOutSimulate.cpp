/*!
 * \file
 * \brief Implémentation de la classe RobotOutSimulate.
 */

#include "RobotOutSimulate.hpp"

pmx::RobotOutSimulate::RobotOutSimulate()
{
}

void
pmx::RobotOutSimulate::setValue(ushort demultiplexor, ushort pin, bool state)
{
    logger().info() << "[dm:" << demultiplexor << "] [pin:" << pin << "] [state:" << state << "]" << utils::end;
}

void
pmx::RobotOutSimulate::setValues(ushort demultiplexor, int value)
{
    logger().info() << "[dm:" << demultiplexor << "] [value:" << value << "]" << utils::end;
}
