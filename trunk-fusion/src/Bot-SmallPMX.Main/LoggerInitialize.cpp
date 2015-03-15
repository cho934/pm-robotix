/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../Common/LogAppender/ConsoleAppender.hpp"
#include "../Common/LogAppender/FileAppender.hpp"
#include "../Common/LogAppender/Level.hpp"
#include "../Common/LogAppender/LoggerFactory.hpp"
#include "../Common/LogAppender/SvgAppender.hpp"

void logs::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());
	add("memory", new MemoryAppender());

	add(logs::Level::ERROR, "", "console");

	add(logs::Level::INFO, "LedBarTest", "console");
	add(logs::Level::INFO, "SoundBarTest", "console");


	//add(logs::Level::DEBUG, "ActionManager", "console");
	//add(logs::Level::DEBUG, "Actions", "console");
	add(logs::Level::DEBUG, "LedBar", "console");
	add(logs::Level::DEBUG, "LedBarAction", "console");
	add(logs::Level::DEBUG, "SoundBar", "console");
	add(logs::Level::DEBUG, "SoundBarAction", "console");

	//DRIVER
	add(logs::Level::INFO, "LedDriver.SIMU", "console");
	add(logs::Level::INFO, "SoundDriver.SIMU", "console");
}
