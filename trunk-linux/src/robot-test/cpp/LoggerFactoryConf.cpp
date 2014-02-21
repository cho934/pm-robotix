/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactoryConf.hpp"

#include "../../common/cpp/ConsoleAppender.hpp"
#include "../../common/cpp/MemoryAppender.hpp"
#include "../../common/cpp/FileAppender.hpp"
#include "../../common/cpp/SvgAppender.hpp"

void
utils::LoggerFactoryConf::initialize() {
    add("console", new ConsoleAppender());
    //add("memory", new MemoryAppender());
    //add("speed-tracer-csv", new FileAppender("speed-tracer-file.csv"));
    add("odometry-svg", new SvgAppender("positionmanager.svg"));
    add("position-csv", new FileAppender("positionmanager.csv"));

    //add("odometry-csv", new FileAppender ("odo.csv"));

    add(utils::Level::ERROR, "", "console");

    //Pour RobotMoveByIncrementTest
    //add(utils::Level::INFO, "test::SpeedTracerFusion::csv", "speed-tracer-csv");
    add(utils::Level::INFO, "test::RobotMoveByIncrementTest", "console");

    //Pour RobotFindPidTest
    add(utils::Level::INFO, "test::RobotNoPidTest", "console");
    add(utils::Level::INFO, "test::RobotFindPidTest", "console");
    add(utils::Level::INFO, "test::RobotFindPidPositionTest", "console");
    add(utils::Level::DEBUG, "utils::SvgWriter::svg", "odometry-svg");
    //add(utils::Level::DEBUG, "pmx::OdometryPositionManager::csv", "odometry-csv");

    //Pour RobotMoveTest
    add(utils::Level::DEBUG, "test::RobotMoveTest", "console");

    //Pour RobotMoveByPositionTest
    add(utils::Level::DEBUG, "test::RobotMoveByPositionTest", "console");
    add(utils::Level::INFO, "pmx::SpeedManagerFusion", "console");
    add(utils::Level::DEBUG, "pmx::SpeedManagerFusion::logpid", "position-csv");

    //Pour RobotMoveByPositionTest
    add(utils::Level::DEBUG, "test::RobotMoveByXYTest", "console");

    //INFO pour les programmes de tests :
    add(utils::Level::INFO, "test::OutPinsTest", "console");
    add(utils::Level::INFO, "test::InPinsTest", "console");
    add(utils::Level::INFO, "test::OutAllPinsTest", "console");
    add(utils::Level::INFO, "test::ContactTest", "console");
    add(utils::Level::INFO, "test::ImpulsionsTest", "console");
    add(utils::Level::INFO, "test::LoggedSensorListener", "console");
    add(utils::Level::INFO, "test::LedIndicatorTest", "console");
    add(utils::Level::INFO, "test::ApfOutTest", "console");
    add(utils::Level::INFO, "test::ApfOutDacTest", "console");
    add(utils::Level::INFO, "test::ApfInTest", "console");
    add(utils::Level::INFO, "test::ApfInModeTest", "console");
    add(utils::Level::INFO, "test::ApfInXenomaiTest", "console");
    add(utils::Level::INFO, "test::DistanceSensorTest", "console");
    add(utils::Level::DEBUG, "test::ServoTest", "console");
    add(utils::Level::INFO, "test::RobotMoveToPawnTest", "console");
    add(utils::Level::INFO, "test::Md25Test", "console");
    add(utils::Level::INFO, "test::StateTest", "console");
    add(utils::Level::INFO, "test::StateInit", "console");
    add(utils::Level::INFO, "test::StrategyOne", "console");
    add(utils::Level::INFO, "test::StrategyTwo", "console");
    add(utils::Level::INFO, "test::FlashBallWheelTest", "console");
    add(utils::Level::INFO, "test::ServoAdjustmentTest", "console");



    //INFO OBJETS
    //add(utils::Level::INFO, "pmx::Robot", "console");


    //DEBUG
    //add(utils::Level::DEBUG, "pmx::Robot", "console");
    //add(utils::Level::DEBUG, "pmx::MotorWithMd25SpeedAction", "console");
    //add(utils::Level::DEBUG, "pmx::OdometryAction", "console");
    add(utils::Level::DEBUG, "pmx::Base", "console");
    //add(utils::Level::INFO, "utils::Md25", "console");
    //add(utils::Level::DEBUG, "pmx::IrSensor", "console");
    //add(utils::Level::DEBUG, "pmx::IrSensorListener", "console");
    //add(utils::Level::DEBUG, "pmx::Motor", "console");
    //add(utils::Level::DEBUG, "utils::PID", "console");
    //add(utils::Level::DEBUG, "utils::Timer", "console");
    //add(utils::Level::DEBUG, "pmx::SensorManager", "console");
   // add(utils::Level::DEBUG, "pmx::RobotInOutApf", "console");
    //add(utils::Level::DEBUG, "utils::Configuration", "console");
    //add(utils::Level::DEBUG, "pmx::LedBar", "console");
    //add(utils::Level::DEBUG, "pmx::LedBarAction", "console");
    //add(utils::Level::DEBUG, "pmx::ClampAction", "console");
    //add(utils::Level::DEBUG, "pmx::ActionManager", "console");
    //add(utils::Level::DEBUG, "pmx::IrSensorsGroup", "console");
    //add(utils::Level::DEBUG, "pmx::ServoMotorObject", "console");
    //add(utils::Level::DEBUG, "pmx::ServoMotorObjectAction", "console");
    //add(utils::Level::DEBUG, "pmx::ServoMotorApf", "console");




}
