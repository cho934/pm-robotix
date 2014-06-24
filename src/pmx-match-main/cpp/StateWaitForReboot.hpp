/*!
 * \file
 * \brief Définition de la classe StateWaitForReboot.
 */

#ifndef PMX_STATEWAITFORREBOOT_H
#define	PMX_STATEWAITFORREBOOT_H

#include "AAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    class StateWaitForReboot : public AAutomateState
    {
    private:

        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateWaitForReboot");
            return instance;
        }

    public:

        StateWaitForReboot()
        {
        }

        virtual ~StateWaitForReboot()
        {
        }

        virtual IAutomateState* execute(Robot& robot, void * data);

        virtual std::string name(){
            return "StateWaitForReboot";
        }
    };
}

#endif
