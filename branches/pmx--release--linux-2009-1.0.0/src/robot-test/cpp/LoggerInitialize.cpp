/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactory.hpp"
#include "ConsoleAppender.hpp"
#include "MemoryAppender.hpp"
#include "FileAppender.hpp"
#include "SvgAppender.hpp"

void
utils::LoggerFactory::initialize()
{
    add("console", new ConsoleAppender());
    add("memory", new MemoryAppender());
    add("speed-instant-csv", new FileAppender("speed-instant-manager.csv"));
    add("speed-average-csv", new FileAppender("speed-average-manager.csv"));
    add("log-pid-csv", new FileAppender("log-pid.csv"));
    add("positioncsv", new FileAppender("positionmanager.csv"));
    add("positionsvg", new SvgAppender("positionmanager.svg"));
    add("positionlog", new FileAppender("pos.log"));
    
    add(utils::Level::ERROR, "", "console");
    
    add(utils::Level::ERROR, "utils::Thread", "console");
    //add(utils::Level::ALL, "pmx::Motor", "console");
    //add(utils::Level::ALL, "pmx::MotorSpeedAction", "console");
    
    //INFO pour les tests
    add(utils::Level::INFO, "test::ContactTest", "console");
    add(utils::Level::INFO, "test::DistanceDetectorTest", "console");
    add(utils::Level::INFO, "test::ImpulsionsTest", "console");
    add(utils::Level::INFO, "test::LoggedSensorListener", "console");
    //add(utils::Level::INFO, "test::RobotMoveTest", "console");
    add(utils::Level::INFO, "test::ServoMotorsTest", "console");
    add(utils::Level::INFO, "test::RobotMoveByIncrementTest", "console");
    add(utils::Level::INFO, "test::SpeedTracer::csv", "speed-average-csv");
    add(utils::Level::INFO, "test::MovePositionTest", "console");
    add(utils::Level::INFO, "test::ColumnElementLeverTest", "console");
    
    //DEBUG
    //add(utils::Level::DEBUG, "pmx::MovementAction", "console");
    //add(utils::Level::DEBUG, "pmx::MovementAction::log", "positionlog");
    //add(utils::Level::DEBUG, "pmx::SpeedManager", "console");
    add(utils::Level::DEBUG, "pmx::OdometryPositionManager::csv", "positioncsv");
    add(utils::Level::DEBUG, "pmx::OdometryPositionManager::svg", "positionsvg");
    
    add(utils::Level::DEBUG, "pmx::SpeedManager::log-pid", "log-pid-csv");
    add(utils::Level::DEBUG, "pmx::SpeedManager::log", "positionlog");
    add(utils::Level::DEBUG, "test::RobotMoveTest", "console");
    add(utils::Level::DEBUG, "test::RobotMoveByPositionTest", "console");
    //add(utils::Level::DEBUG, "pmx::MotorWayAction", "console");
    add(utils::Level::DEBUG, "pmx::Base", "console");
    
    
}
