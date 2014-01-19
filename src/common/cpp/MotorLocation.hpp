/*!
 * \file
 * \brief Définition de l'énumération MotorLocation.
 * \todo deplacer dans macro.hpp
 */

#ifndef PMX_MOTOR_LOCATION_H
#define	PMX_MOTOR_LOCATION_H

namespace pmx
{
    /*!
     * \brief Enumération des positions des moteurs.
     * LEFT/RIGHT pour la motorisation principale,
     * RED/YELLOW pour les moteurs GEARBOX.
     */
    enum MotorLocation
    { MLEFT, MRIGHT, MRED, MYELLOW };
}

#endif
