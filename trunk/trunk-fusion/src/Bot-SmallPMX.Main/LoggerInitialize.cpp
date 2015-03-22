/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */


#include "../Log/Appender/FileAppender.hpp"
#include "../Log/Appender/SvgAppender.hpp"
#include "../Log/Appender/ConsoleAppender.hpp"
#include "../Log/Level.hpp"
#include "../Log/LoggerFactory.hpp"

void logs::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());
	add("memory", new MemoryAppender());

	add(logs::Level::ERROR, "", "console");

	add(logs::Level::INFO, "LedBarTest", "console");
	add(logs::Level::INFO, "SoundBarTest", "console");


	//add(logs::Level::DEBUG, "ActionManager", "console");
	//add(logs::Level::DEBUG, "Actions", "console");
	add(logs::Level::INFO, "LedBar", "console");
	add(logs::Level::INFO, "LedBarAction", "console");
	add(logs::Level::INFO, "SoundBar", "console");
	add(logs::Level::INFO, "SoundBarAction", "console");

	//DRIVER
	add(logs::Level::INFO, "LedDriver.SIMU", "console");
	add(logs::Level::INFO, "SoundDriver.SIMU", "console");
}
