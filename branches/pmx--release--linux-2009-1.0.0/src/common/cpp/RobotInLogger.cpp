/*!
 * \file
 * \brief Implémentation de la classe RobotInLogger.
 * \todo Logger les infos demandées.
 */

#include "sys/time.h"
#include "RobotInLogger.hpp"

#include <iostream>

pmx::RobotInLogger::RobotInLogger()
{}

bool pmx::RobotInLogger::getValue(ushort, ushort)
{
    return false;
}

int pmx::RobotInLogger::getValues(ushort)
{
    return 0;
}

bool pmx::RobotInLogger::getImpRight()
{
    utils::LoggerFactory::logger("pmx::RobotInLogger").info("onRightPulse");
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_usec / 10000) % 2 == 1;
}

bool pmx::RobotInLogger::getImpLeft()
{
    utils::LoggerFactory::logger("pmx::RobotInLogger").info("onRightPulse");
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_usec / 10000) % 2 == 1;
}

bool pmx::RobotInLogger::getImpLeftWay()
{
    return 0;
}

bool pmx::RobotInLogger::getImpRightWay()
{
    return 0;
}
