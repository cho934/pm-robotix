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

    add("console", new ConsoleAppender());
    //add("memory", new MemoryAppender());
    add("odometry-svg", new SvgAppender("positionmanager.svg"));
    //add("position-csv", new FileAppender("positionmanager.csv"));
    
    add(utils::Level::ERROR, "", "console");
    //add(utils::Level::DEBUG, "pmx::SpeedManagerFusion::logpid", "position-csv");
    
    
    add(utils::Level::DEBUG, "utils::SvgWriter::svg", "odometry-svg");
    add(utils::Level::INFO, "pmx::Robot", "console");
    add(utils::Level::DEBUG, "main", "console");

    //liste des strategies
    add(utils::Level::DEBUG, "pmx::MoveCatchStrategy", "console");
    add(utils::Level::DEBUG, "pmx::MoveReleaseStrategy", "console");
    add(utils::Level::DEBUG, "pmx::PushGoldBarStrategy", "console");
    add(utils::Level::DEBUG, "pmx::PushBottleStrategy", "console");


    add(utils::Level::DEBUG, "pmx::StateAdjustRobotPosition", "console");
    add(utils::Level::DEBUG, "pmx::StateInitialize", "console");
    add(utils::Level::DEBUG, "pmx::StateWaitForReboot", "console");
    add(utils::Level::DEBUG, "pmx::StateWaitForStart", "console");
    add(utils::Level::DEBUG, "pmx::Wait90SecondsAction", "console");
    add(utils::Level::DEBUG, "pmx::StateDecisionMaker", "console");
    
    //debug

    //add(utils::Level::DEBUG, "pmx::SpeedManagerFusion", "console");
    //add(utils::Level::INFO, "pmx::RobotInOutApf", "console");
   //add(utils::Level::DEBUG, "pmx::Base", "console");
   //add(utils::Level::INFO, "pmx::IrSensor", "console");
  //      add(utils::Level::DEBUG, "pmx::Fork", "console");


    //thread
    //add(utils::Level::INFO, "pmx::ActionManager", "console");
    //add(utils::Level::DEBUG, "pmx::SensorManager", "console");


}
