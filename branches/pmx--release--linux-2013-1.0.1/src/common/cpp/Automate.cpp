/*!
 * \file
 * \brief Implémentation de la classe Automate.
 */

#include "Automate.hpp"

pmx::Automate::Automate() : current_(NULL) {
}

void
pmx::Automate::run(pmx::Robot& robot, pmx::IAutomateState* first, void* data) {
    if (first == NULL) {
        logger().error() << "ERROR: Automate::run called with a NULL state"
                << utils::end;
    }
    IAutomateState* state = first;

    while (state != NULL) {
        this->current(state);

        if (this->current() != NULL) {
            logger().debug() << "1.Current state : name=" << state->name()
                    << utils::end;

            state = this->current()->execute(robot, data);
            if (state != NULL) {
                logger().debug() << "2.Current state : name=" << state->name() << " done."
                        << utils::end;
            }
        }
    }
}
