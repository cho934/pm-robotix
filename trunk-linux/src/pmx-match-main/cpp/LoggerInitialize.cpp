/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/ConsoleAppender.hpp"
#include "../../common/cpp/MemoryAppender.hpp"
#include "../../common/cpp/FileAppender.hpp"
#include "../../common/cpp/SvgAppender.hpp"

void
utils::LoggerFactory::initialize() {
    add("odometry-svg", new SvgAppender("pos.svg"));
    add(utils::Level::DEBUG, "utils::SvgWriter::svg", "odometry-svg");

    add("console", new ConsoleAppender());
    add(utils::Level::ERROR, "", "console");

    add(utils::Level::DEBUG, "main", "console");
    add(utils::Level::DEBUG, "pmx::StateWaitForReboot", "console");
    add(utils::Level::DEBUG, "pmx::StateInitialize", "console");
    add(utils::Level::DEBUG, "pmx::StateAdjustRobotPosition", "console");
    add(utils::Level::DEBUG, "pmx::StateWaitForStart", "console");
    add(utils::Level::DEBUG, "pmx::StateIADecisionMaker", "console");
}
