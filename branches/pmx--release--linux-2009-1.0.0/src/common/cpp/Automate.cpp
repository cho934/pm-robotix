#include "Automate.hpp"

pmx::Automate::Automate() : current_(NULL)
{
}

void
pmx::Automate::run(pmx::Robot& robot, pmx::IAutomateState* first)
{
    IAutomateState* state = first;
    while(state != NULL)
    {
        this->current(state);
        state = this->current()->execute(robot);
    }
}
