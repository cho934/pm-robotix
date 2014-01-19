/*!
 * \file
 * \brief Implémentation de la classe RobotInSimulate.
 * \todo Logger les infos demandées.
 * \deprecated
 */

#include "sys/time.h"
#include "RobotInSimulate.hpp"

#include <iostream>

pmx::RobotInSimulate::RobotInSimulate()
{
}

int pmx::RobotInSimulate::getValue(ushort, ushort)
{
    return 0;
}

int pmx::RobotInSimulate::getValues(ushort)
{
    return 0;
}

bool pmx::RobotInSimulate::getImpRight()
{
    utils::LoggerFactory::logger("pmx::RobotInSimulate").info("onRightPulse");
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_usec / 10000) % 2 == 1;
}

bool pmx::RobotInSimulate::getImpLeft()
{
    utils::LoggerFactory::logger("pmx::RobotInSimulate").info("onRightPulse");
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_usec / 10000) % 2 == 1;
}

bool pmx::RobotInSimulate::getImpLeftWay()
{
    return 0;
}

bool pmx::RobotInSimulate::getImpRightWay()
{
    return 0;
}

bool * pmx::RobotInSimulate::getImp()
{
    bool * temp;
    return temp;
}
