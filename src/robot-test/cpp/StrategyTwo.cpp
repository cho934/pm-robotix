/*!
 * \file
 * \brief Implémentation de la classe StrategyTwo.
 */

#include "StrategyTwo.hpp"
#include "Robot.hpp"
#include "StateData.hpp"
#include "Contract.hpp"

using namespace pmx;

int
test::StrategyTwo::computeInterest(const pmx::Robot &, void * data) {
    //utils::Contract::isNotNull(data, "pmx::PushBottleStrategy::computeInterest - data is null");

    pmx::StateData* sharedData = (pmx::StateData*) data;
    if (sharedData->isEmpty() == true) {
        return -1;
    }else {
        return 2;
    }
}

pmx::IAutomateState*
test::StrategyTwo::execute(Robot&, void * ) {
    logger().info() << "start" << utils::end;
    
    IAutomateState* result = NULL;

    //Prog de decision
    //result = this->getState("decisionMaker");

    return result;
}
