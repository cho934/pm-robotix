/*!
 * \file
 * \brief Définition de la classe StateInitialize.
 */

#ifndef PMX_STATEINITIALIZE_HPP
#define	PMX_STATEINITIALIZE_HPP

#include "AAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    class StateInitialize : public AAutomateState
    {
    private:

        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateInitialize");
            return instance;
        }

    public:

        StateInitialize()
        {
        }

        virtual ~StateInitialize()
        {
        }

        virtual std::string name()
        {
            return "StateInitialize";
        }
        virtual IAutomateState* execute(Robot& robot, void * data);
    };
}

#endif
