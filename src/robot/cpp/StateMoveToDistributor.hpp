#ifndef PMX_STATEMOVETODISTRIBUTOR_HPP
#define	PMX_STATEMOVETODISTRIBUTOR_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class StateMoveToDistributor : public pmx::IAutomateState
        {
        private:
            
            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::StateMoveToDistributor");
                return instance;
            }
            
        public:
            
            StateMoveToDistributor()
            {}
            
            virtual ~ StateMoveToDistributor()
            {}
            
            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif
