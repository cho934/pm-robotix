
/*!
 * \file
 * \brief Implémentation de la classe StatInit.
 */

#include "StateInit.hpp"

using namespace pmx;

pmx::IAutomateState*
test::StateInit::execute(pmx::Robot & , void * ) {


    logger().info() << "start StateInit" << utils::end;

    IAutomateState* result = NULL;

    //Prog de decision
    result = this->getState("decisionMaker");

    return result;
}
