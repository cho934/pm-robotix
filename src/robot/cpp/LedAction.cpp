#include "LedAction.hpp"

pmx::LedAction::LedAction() : stopped(false)
{}

bool
pmx::LedAction::execute(pmx::IRobotOut * out)
{
    if (stopped)
    {
        out->setValues(pmx::IRobotOut::DM3, 0);
    }
    else
    {
        out->setValues(pmx::IRobotOut::DM3, 255);
    }
    return !stopped;
}
