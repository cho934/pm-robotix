/*!
 * \file
 * \brief Définition de la classe StateAdjustRobotPosition.
 */

#ifndef PMX_STATEADJUSTROBOTPOSITION_HPP
#define	PMX_STATEADJUSTROBOTPOSITION_HPP

#include "AAutomateState.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    class StateAdjustRobotPosition : public AAutomateState
    {
    private:

        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateAdjustRobotPosition");
            return instance;
        }

    public:

        StateAdjustRobotPosition()
        {
        }
        virtual std::string name()
        {
            return "StateAdjustRobotPosition";
        }
        virtual ~StateAdjustRobotPosition()
        {
        }

        virtual IAutomateState* execute(Robot& robot, void * data);
    };
}

#endif	/* PMX_STATEADJUSTROBOTPOSITION_HPP */
