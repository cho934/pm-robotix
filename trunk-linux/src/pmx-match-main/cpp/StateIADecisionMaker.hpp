/*!
 * \file
 * \brief Définition de la classe StateIADecisionMaker.
 */

#ifndef PMX_STATEIADECISIONMAKER_HPP
#define	PMX_STATEIADECISIONMAKER_HPP

#include <string>

#include "../../common/c/global.h"
#include "../../common/cpp/AAutomateState.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace pmx
{
    class StateIADecisionMaker : public AAutomateState
    {
    public:

        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::StateIADecisionMaker");
            return instance;
        }

    public:

        StateIADecisionMaker()
        {
        }
        virtual std::string name()
        {
            return "StateIADecisionMaker";
        }
        virtual ~StateIADecisionMaker()
        {
        }

        virtual IAutomateState* execute(Robot& robot, void * data);

        void IASetupTableTest();
        void IASetupHomologation();
        void IASetupMatches();



    };
}

#endif
