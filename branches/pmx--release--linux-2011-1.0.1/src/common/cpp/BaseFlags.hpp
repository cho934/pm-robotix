/*!
 * \file
 * \brief Définition de l'énumération BaseFlags.
 */

#ifndef PMX_BASEFLAGS_HPP
#define	PMX_BASEFLAGS_HPP

namespace pmx
{
    /*!
     * \brief Définie les flags s'appliquant à la classe \ref pmx::Base.
     */
    enum BaseFlags
    {
        /*!
         * \brief Indique que la trajectoire est corrigée par le système.
         */
        AUTO_CORRECT = 0x01,

        /*!
         * \brief Indique que le PID en position est actif.
         */
        PID_POSITION = 0x02,

        /*!
         * \brief Indique que le PID sur la vitesse est actif.
         */
        PID_SPEED = 0x04,
    };
}

#endif
