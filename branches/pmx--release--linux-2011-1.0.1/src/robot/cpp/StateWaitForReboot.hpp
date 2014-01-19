/*!
 * \file
 * \brief Définition de la classe StateWaitForReboot.
 */

#ifndef PMX_STATEWAITFORREBOOT_H
#define	PMX_STATEWAITFORREBOOT_H

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class StateWaitForReboot : public pmx::IAutomateState
        {
        private:
            
            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::StateWaitForReboot");
                return instance;
            }
            
        public:
            
            StateWaitForReboot()
            {}
            
            virtual ~ StateWaitForReboot()
            {}
            
            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif
