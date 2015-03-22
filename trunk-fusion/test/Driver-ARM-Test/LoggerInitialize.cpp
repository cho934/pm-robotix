/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../../src/Common/LogAppender/ConsoleAppender.hpp"
#include "../../src/Common/LogAppender/Level.hpp"
#include "../../src/Common/LogAppender/LoggerFactory.hpp"

void logs::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());
	add("memory", new MemoryAppender());

	add(logs::Level::ERROR, "", "console");

}
