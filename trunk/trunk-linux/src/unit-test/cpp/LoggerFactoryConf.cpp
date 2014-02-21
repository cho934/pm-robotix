/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactoryConf.hpp"

#include "../../common/cpp/ConsoleAppender.hpp"
#include "../../common/cpp/MemoryAppender.hpp"
#include "../../common/cpp/FileAppender.hpp"
#include "../../common/cpp/SvgAppender.hpp"

void
utils::LoggerFactoryConf::initialize() {
    add("console", new ConsoleAppender());
    add("memory", new MemoryAppender());

    add(utils::Level::ERROR, "", "console");

    //INFO pour les programmes de tests :
    //add(utils::Level::INFO, "test::OutPinsTest", "console");


    //DEBUG
    //add(utils::Level::DEBUG, "pmx::Robot", "console");


}
