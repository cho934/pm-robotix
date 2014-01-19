#include "LedAction.hpp"

pmx::LedAction::LedAction() : stopped(false)
{}

bool
pmx::LedAction::execute(pmx::IRobotOut * out)
{
    if (stopped)
    {
        out->setValues(pmx::IRobotOut::DM0, 0);
    }
    else
    {
        out->setValues(pmx::IRobotOut::DM0, 255);
    }
    return !stopped;
}
