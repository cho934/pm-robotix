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

	add(utils::Level::INFO, "test::UTApfGpioOut", "console");
	add(utils::Level::INFO, "test::UTApfGpioIn", "console");
	add(utils::Level::INFO, "test::UTApfDacOut", "console");
	add(utils::Level::INFO, "test::UTApfAdcIn", "console");


}
