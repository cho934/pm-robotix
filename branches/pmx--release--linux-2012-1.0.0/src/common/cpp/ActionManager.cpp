/*!
 * \file
 * \brief Implémentation de la classe ActionManager.
 */

#include <iostream>
#include "ActionManager.hpp"
#include "RobotInOutFactory.hpp"

pmx::ActionManager::ActionManager() : stop_(false)
{
}

void
pmx::ActionManager::execute()
{
    logger().info("ActionManager is started");
    debugThread("ActionManager");
    pmx::IRobotOut * out = pmx::RobotInOutFactory::instance()->robotOut();

    while (!stop_)
    {

        lock();
        if (actions_.size() > 0)
        {
            IAction * action = actions_.front();
            if (action == NULL)
            {
                logger().debug("ActionManager NULL action");
            }
            actions_.pop_front();
            unlock();
            bool persist = action->execute(out);
            lock();
            if (persist)
            {
                actions_.push_back(action);
            }

        }

        unlock();
        // Comme il n'y a pas d'action, le processus attend avant de
        // relancer la boucle d'execution
        usleep(5000);

    }


    logger().info("ActionManager is stopped");
}

void
pmx::ActionManager::debug()
{
    lock();
    logger().info() << "Defined actions" << utils::end;
    utils::PointerList <pmx::IAction *>::iterator i = actions_.begin();
    while (i != actions_.end())
    {
        pmx::IAction * action = *i;
        logger().info() << " - " << action->info() << utils::end;
        i++;
    }
    unlock();
    logger().info() << "End of defined actions" << utils::end;
}
