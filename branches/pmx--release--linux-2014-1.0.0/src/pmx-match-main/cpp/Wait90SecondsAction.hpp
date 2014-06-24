/*!
 * \file
 * \brief Définition de la classe Wait90SecondsAction.
 */

#ifndef PMX_WAIT90SECONDSACTION_HPP
#define	PMX_WAIT90SECONDSACTION_HPP

//#include <cstdlib>

#include <string>

#include "../../common/cpp/AAutomateState.hpp"
#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/Thread.hpp"

//#include "IAction.hpp"
//#include "Robot.hpp"

namespace pmx
{
class Robot;
} /* namespace pmx */

namespace pmx
{
    /*!
     * \brief Cette action lance le chronometer du robot.
     */
    class Wait90SecondsAction : public utils::Thread// , public AAutomateState
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
        
        void * data_;

    public:
        
        /*!
         * \brief Constructeur de la classe.
         */
        Wait90SecondsAction(Robot* robot,  void *data);

        virtual std::string name()
        {
            return "Wait90SecondsAction";
        }
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
