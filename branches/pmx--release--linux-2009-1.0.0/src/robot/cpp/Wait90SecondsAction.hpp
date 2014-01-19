#ifndef PMX_WAIT90SECONDSACTION_HPP
#define	PMX_WAIT90SECONDSACTION_HPP

#include "IAction.hpp"
#include "LoggerFactory.hpp"
#include "Robot.hpp"

namespace pmx
{
    /*!
     * \brief Cette action lance le chronometer du robot.
     */
    class Wait90SecondsAction : public utils::Thread
    {
    private:
        
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Wait90SecondsAction");
            return instance;
        }
        
        /*!
         * \brief Référence vers le robot.
         */
        Robot * robot_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        Wait90SecondsAction(Robot* robot);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ Wait90SecondsAction()
        {}
        
        /*!
         * \brief Execute l'action.
         */
        virtual void execute();
    };
}

#endif
