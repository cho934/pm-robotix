/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */


#include "../../src/Common/LogAppender/ConsoleAppender.hpp"
#include "../../src/Common/LogAppender/FileAppender.hpp"
#include "../../src/Common/LogAppender/Level.hpp"
#include "../../src/Common/LogAppender/LoggerFactory.hpp"
#include "../../src/Common/LogAppender/SvgAppender.hpp"

void logs::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());

	add(logs::Level::ERROR, "", "console");

}
