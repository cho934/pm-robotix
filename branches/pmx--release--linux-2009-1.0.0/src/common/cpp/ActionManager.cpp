/*!
 * \file
 * \brief Implémentation de la classe ActionManager.
 */

#include <iostream>
#include "ActionManager.hpp"
#include "RobotInOutFactory.hpp"

pmx::ActionManager::ActionManager(): stop_(false)
{}

void
pmx::ActionManager::execute()
{
    logger().info("ActionManager is started");
    pmx::IRobotOut * out = pmx::RobotInOutFactory::instance()->robotOut();
    
    while (!stop_)
    {
        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "Number of actions : " << actions_.size() << utils::end;
        }
        if (actions_.size() > 0)
        {
            utils::PointerList <IAction *>::iterator i = actions_.begin();
            while (i != actions_.end())
            {
                IAction * action = *i;
                bool persist = action->execute(out);
                
                if (!persist)
                {
                    utils::PointerList <IAction *>::iterator old = i;
                    i++;
                    
                    delete action;
                    actions_.erase(old);
                }
                else
                {
                    i++;
                }
                this->yield();
            }
        }
        this->yield();
    }
    
    logger().info("ActionManager is stopping");
    
    if (actions_.size() > 0)
    {
        if(logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "Number of end actions : " << actions_.size() << utils::end;
        }
        utils::PointerList <IAction *>::iterator i = actions_.begin();
        while (i != actions_.end())
        {
            IAction * action = *i;
            action->execute(out);
            
            utils::PointerList <IAction *>::iterator old = i;
            i++;
            
            delete action;
            actions_.erase(old);
        }
    }
    
    logger().info("ActionManager is stopped");
}

void
pmx::ActionManager::debug()
{
    logger().info() << "Defined actions" << utils::end;
    utils::PointerList <pmx::IAction *>::iterator i = actions_.begin();
    while (i != actions_.end())
    {
        pmx::IAction * action = *i;
        logger().info() << " - " << action->info() << utils::end;
        i++;
    }
    logger().info() << "End of defined actions" << utils::end;
}
