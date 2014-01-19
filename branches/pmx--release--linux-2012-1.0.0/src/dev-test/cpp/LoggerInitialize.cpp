/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "LoggerFactory.hpp"
#include "UnitTestAppender.hpp"

void
utils::LoggerFactory::initialize()
{
    // Ne pas modifier la configuration de base des logs
    // Elle est nécessaire pour le bon fonctionnement des tests unitaires
    // -------------------------------------------------
    this->add("console", new utils::UnitTestAppender());
    this->add(utils::Level::ERROR, "", "console");
    this->add(utils::Level::INFO, "test", "console");
    // -------------------------------------------------

    //this->add(utils::Level::DEBUG, "test::BaseTest", "console");

}
