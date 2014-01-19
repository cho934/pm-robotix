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
    
    add(utils::Level::ERROR, "", "console");
    add(utils::Level::INFO, "test::UnitTestTest", "console");
    add(utils::Level::INFO, "test::LoggerTest", "console");
    add(utils::Level::INFO, "test::MutexTest", "console");
    add(utils::Level::INFO, "test::mutex::Counter", "console");

    add(utils::Level::INFO, "test::TestThread", "console");
    add(utils::Level::INFO, "test::ThreadTest", "console");
    add(utils::Level::INFO, "test::ChronometerTest", "console");

    add(utils::Level::DEBUG, "utils::Thread", "console");
}
