
/*!
 * \file
 * \brief Implémentation de la classe StrategyOne.
 */

#include "StrategyOne.hpp"
#include "Robot.hpp"
#include "StateData.hpp"
#include "Contract.hpp"

using namespace pmx;

int
test::StrategyOne::computeInterest(const pmx::Robot &, void * data) {
    utils::Contract::isNotNull(data, "pmx::StrategyOne::computeInterest - data is null");

    pmx::StateData* sharedData = (pmx::StateData*) data;
    if (sharedData->isEmpty() == false) {
        return -1;
    }else {
        return 3;
    }
}

pmx::IAutomateState*
test::StrategyOne::execute(Robot& , void * data)
{
    logger().info() << "start" << utils::end;

    pmx::StateData* sharedData = (pmx::StateData*) data;
    sharedData->isEmpty(false);

    IAutomateState* result = NULL;

    //Prog de decision
    result = this->getState("decisionMaker");

    return result;
}
