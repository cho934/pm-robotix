/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */


#include "../Common/LogAppender/ConsoleAppender.hpp"
#include "../Common/LogAppender/FileAppender.hpp"
#include "../Common/LogAppender/Level.hpp"
#include "../Common/LogAppender/LoggerFactory.hpp"
#include "../Common/LogAppender/SvgAppender.hpp"

void utils::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());
	add("memory", new MemoryAppender());

	add(utils::Level::ERROR, "", "console");

	add(utils::Level::INFO, "LedBarTest", "console");

}
