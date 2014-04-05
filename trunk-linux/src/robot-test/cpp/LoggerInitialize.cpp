/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/ConsoleAppender.hpp"
#include "../../common/cpp/MemoryAppender.hpp"
#include "../../common/cpp/FileAppender.hpp"
#include "../../common/cpp/SvgAppender.hpp"

void utils::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());

	add(utils::Level::ERROR, "", "console");

	add(utils::Level::INFO, "robottest::LedIndicatorTest", "console");
	add(utils::Level::INFO, "robottest::GroveColorTest", "console");
	add(utils::Level::INFO, "robottest::LedBarTest", "console");


	add(utils::Level::DEBUG, "pmx::Robot", "console");
	add(utils::Level::DEBUG, "pmx::GroveColorSensor", "console");
	add(utils::Level::DEBUG, "pmx::ActionManager", "console");
	add(utils::Level::DEBUG, "pmx::ExtEncoder", "console");

}
