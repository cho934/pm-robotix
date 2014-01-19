/*!
 * \file
 * \brief Implémentation de la classe PositionManager.
 */

#include "PositionManager.hpp"

pmx::PositionManager::PositionManager()
: IEncoderListener(), Mutex(), position_()
{}

