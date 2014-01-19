/*!
 * \file
 * \brief Définition de la classe RobotOutLogger.
 */

#include "IRobotOut.hpp"
#include "LoggerFactory.hpp"

#ifndef PMX_ROBOTOUTLOGGER_H
#define	PMX_ROBOTOUTLOGGER_H

namespace pmx
{
    /*!
     * \brief Cette classe implémente pmx::RobotOut pour les systèmes autre
     * que celui embarqué par le robot.
     *
     * Au lieu d'exploiter un port de transfert, cette classe renvoie les
     * informations sur la sortie standard.
     *
     * \sa pmx::RobotOut
     * \sa pmx::RobotOutParallelPort
     * \todo Exploiter un logger et pas la sortie standard
     */
    class RobotOutLogger : public IRobotOut
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotOutLogger");
            return instance;
        }
        
    public:
        
        /**
         * \brief Constructeur par défaut.
         */
        RobotOutLogger();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ RobotOutLogger()
        {}
        
        virtual void setValue(ushort demultiplexor, ushort pin, bool state);
        
        virtual void setValues(ushort demultiplexor, ushort value);
    };
}

#endif
