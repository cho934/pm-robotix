/*!
 * \file
 * \brief Définition de la classe RobotOutSimulate.
 */

#ifndef PMX_ROBOTOUTSIMULATE_H
#define	PMX_ROBOTOUTSIMULATE_H

#include "IRobotOut.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe implémente pmx::IRobotOut pour les systèmes autre
     * que celui embarqué par le robot.
     *
     * Au lieu d'exploiter un port de transfert, cette classe renvoie les
     * informations sur la sortie standard.
     *
     * \sa pmx::IRobotOut
     * \sa pmx::RobotOutParallelPort
     */
    class RobotOutSimulate : public IRobotOut
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotOutSimulate.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotOutSimulate");
            return instance;
        }
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        RobotOutSimulate();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ RobotOutSimulate()
        {}
        
        virtual void setValue(ushort demultiplexor, ushort pin, bool state);
        
        virtual void setValues(ushort demultiplexor, int value);
    };
}

#endif
