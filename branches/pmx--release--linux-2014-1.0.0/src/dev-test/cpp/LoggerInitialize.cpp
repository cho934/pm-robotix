/*!
 * \file
 * \brief Ce fichier contient la configuration du système de Log pour le programme robot-test.
 */

#include "../../common/cpp/LoggerFactory.hpp"
#include "DevUnitTestAppender.hpp"

void
utils::LoggerFactory::initialize() {
	    // Ne pas modifier la configuration de base des logs
	    // Elle est nécessaire pour le bon fonctionnement des tests unitaires
	    // -------------------------------------------------
	    this->add("console", new utils::DevUnitTestAppender());
	    this->add(utils::Level::ERROR, "", "console");
	    this->add(utils::Level::INFO, "", "console");
	    // -------------------------------------------------

	    //this->add(utils::Level::DEBUG, "test::ThreadTest", "console");
	    this->add(utils::Level::DEBUG, "test::IaTest", "console");

}
