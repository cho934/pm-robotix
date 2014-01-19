/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactory.hpp"
#include "ConsoleAppender.hpp"
#include "MemoryAppender.hpp"

void
utils::LoggerFactory::initialize()
{
    add("console", new utils::ConsoleAppender());
    add("memory", new utils::MemoryAppender());
    
    add(utils::Level::INFO, "", "console");
    add(utils::Level::DEBUG, "test", "console");
    add(utils::Level::DEBUG, "utils::Thread", "console");
    
    add(utils::Level::DEBUG, "test::VisualValidation", "memory");
}
