/*!
 * \file
 * \brief Définition de la classe RobotInSimulate.
 */

#ifndef PMX_ROBOTINOUTSIMULATE_H
#define	PMX_ROBOTINOUTSIMULATE_H

#include "IRobotInOut.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe implémente pmx::IRobotIn pour les systèmes autre
     * que celui embarqué par le robot.
     *
     * Cette méthode implémente les méthodes RobotInSimulate::getImpLeft()
     * et RobotInSimulate::getImpRight() avec une impulsion pour 10ms.
     *
     * \sa pmx::IRobotIn
     * \sa pmx::RobotOutParallelPort
     */
    class RobotInOutSimulate : public IRobotInOut
    {
    private:

        /*!
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotInOutSimulate");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        RobotInOutSimulate();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~RobotInOutSimulate()
        {
        }

       
    };
}

#endif
