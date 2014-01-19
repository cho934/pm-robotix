/*!
 * \file
 * \brief Implémentation de la classe StateDecisionMaker.
 */

#include "StateDecisionMaker.hpp"

pmx::IAutomateState*
pmx::StateDecisionMaker::execute(pmx::Robot & robot, void * data)
{
    logger().info() << "start" << utils::end;
    int maxInterest = 0;
    AStrategy* maxStrategy = NULL;
    
    // Affiche le nombre de stratégies
    int nb;
    if (logger().isActive(utils::Level::DEBUG))
    {
        if (nb != (int) this->strategies_.size())//si changement de nombre
        {
            logger().debug() << "Number of actions=" << this->strategies_.size() << utils::end;
            nb = this->strategies_.size();
        }
    }

    utils::PointerList <AStrategy *>::iterator i = this->strategies_.begin();

    while (i != this->strategies_.end())
    {
        AStrategy * strategy = *i;
        int interest = strategy->computeInterest(robot, data);

        if (interest > maxInterest)
        {
            maxStrategy = strategy;
            maxInterest = interest;
        }
        i++;
    }
    logger().debug() << "maxInterest=" << maxInterest << utils::end;
    if (maxInterest <= 0)
        return NULL;
    else
        return maxStrategy;
}
