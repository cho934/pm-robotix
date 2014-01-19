/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactory.hpp"
#include "FileAppender.hpp"
#include "ConsoleAppender.hpp"
#include "SvgAppender.hpp"

void
utils::LoggerFactory::initialize()
{
    add("text", new FileAppender("robot.log"));
    add("console", new ConsoleAppender());
    add("positionsvg", new SvgAppender("positionmanager.svg"));
    
    add(utils::Level::INFO, "", "console");
    add(utils::Level::DEBUG, "pmx::OdometryPositionManager::svg", "positionsvg");
    add(utils::Level::DEBUG, "pmx::MovementAction", "console");
    
}
