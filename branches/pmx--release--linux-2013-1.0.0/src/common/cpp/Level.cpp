/*!
 * \file
 * \brief Implémentation de la classe Level.
 */

#include "Level.hpp"

utils::Level utils::Level::DEBUG(5, "DEBUG");

utils::Level utils::Level::INFO(10, "INFO");

utils::Level utils::Level::WARN(15, "WARN");

utils::Level utils::Level::ERROR(20, "ERROR");

utils::Level utils::Level::ALL(0, "ALL");

utils::Level utils::Level::NONE(100, "NONE");
