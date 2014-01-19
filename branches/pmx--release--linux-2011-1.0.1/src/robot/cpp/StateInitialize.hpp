/*!
 * \file
 * \brief Définition de la classe StateInitialize.
 */

#ifndef PMX_STATEINITIALIZE_HPP
#define	PMX_STATEINITIALIZE_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class StateInitialize : public pmx::IAutomateState
        {
        private:
            
            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::StateInitialize");
                return instance;
            }
            
        public:

            StateInitialize()
            {}
            
            virtual ~ StateInitialize()
            {}
            
            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif
