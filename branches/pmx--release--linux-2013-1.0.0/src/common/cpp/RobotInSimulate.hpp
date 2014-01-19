/*!
 * \file
 * \brief Définition de la classe RobotInSimulate.
 */

#ifndef PMX_ROBOTINSIMULATE_H
#define	PMX_ROBOTINSIMULATE_H

#include "IRobotIn.hpp"
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
    class RobotInSimulate : public IRobotIn
    {
    private:

        /*!
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotInSimulate");
            return instance;
        }

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        RobotInSimulate();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~RobotInSimulate()
        {
        }

        virtual int getValue(ushort multiplexor, ushort pin);

        virtual int getValues(ushort multiplexor);

        virtual bool getImpRight();

        virtual bool getImpLeft();

        virtual bool getImpLeftWay();

        virtual bool getImpRightWay();

       
    };
}

#endif
