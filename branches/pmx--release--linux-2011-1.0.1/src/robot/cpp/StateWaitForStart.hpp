#ifndef PMX_STATEWAITFORSTART_HPP
#define	PMX_STATEWAITFORSTART_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class StateWaitForStart : public pmx::IAutomateState
        {
        private:
            
            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::StateWaitForStart");
                return instance;
            }
            
        public:

            StateWaitForStart()
            {}
            
            virtual ~ StateWaitForStart()
            {}
            
            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif
