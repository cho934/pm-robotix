/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactory.hpp"
#include "MemoryAppender.hpp"
#include "FileAppender.hpp"
#include "ConsoleAppender.hpp"
#include "SvgAppender.hpp"

void
utils::LoggerFactory::initialize()
{
    add("text", new FileAppender("robot.log"));
    add("console", new ConsoleAppender());
    //add("memory", new MemoryAppender());
    add("odometry-svg", new SvgAppender("positionmanager.svg"));
    //add("position-csv", new FileAppender("positionmanager.csv"));
    
    add(utils::Level::INFO, "", "console");
    //add(utils::Level::ERROR, "pmx::SpeedManagerFusion::logpid", "console");
    
    
    add(utils::Level::DEBUG, "utils::SvgWriter::svg", "odometry-svg");



    //add(utils::Level::DEBUG, "pmx::LedBar", "console");
    //add(utils::Level::DEBUG, "pmx::LedBarAction", "console");
    //add(utils::Level::DEBUG, "pmx::RobotInOutApf", "console");
    add(utils::Level::DEBUG, "pmx::Base", "console");

    //add(utils::Level::DEBUG, "pmx::SpeedManagerFusion", "console");
    //add(utils::Level::DEBUG, "pmx::SpeedManagerFusion", "memory");
    //add(utils::Level::DEBUG, "pmx::SpeedManagerFusion::logpid", "position-csv");

    //add(utils::Level::DEBUG, "pmx::ActionManager", "console");
    //add(utils::Level::DEBUG, "pmx::SensorManager", "console");
    //add(utils::Level::DEBUG, "pmx::IrSensor", "console");
    //add(utils::Level::DEBUG, "pmx::IrSensorListener", "console");

}
