/*!
 * \file
 * \brief Définition de la classe StateAdjustRobotPosition.
 */

#ifndef PMX_STATEADJUSTROBOTPOSITION_HPP
#define	PMX_STATEADJUSTROBOTPOSITION_HPP

#include "IAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    namespace automate
    {
        class StateAdjustRobotPosition : public pmx::IAutomateState
        {
        private:

            static inline const utils::Logger & logger()
            {
                static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::automate::StateAdjustRobotPosition");
                return instance;
            }

        public:

            StateAdjustRobotPosition()
            {}

            virtual ~ StateAdjustRobotPosition()
            {}

            virtual IAutomateState* execute(Robot& robot);
        };
    }
}

#endif	/* PMX_STATEADJUSTROBOTPOSITION_HPP */

