#include "RobotInOutFactory.hpp"
#include "RobotInOutParallelPort.hpp"
#include "RobotInLogger.hpp"
#include "RobotOutLogger.hpp"

pmx::RobotInOutFactory * pmx::RobotInOutFactory::instance()
{
    static pmx::RobotInOutFactory * instance = new pmx::RobotInOutFactory();
    return instance;
}

pmx::RobotInOutFactory::RobotInOutFactory() : in_(NULL), out_(NULL)
{
    int result = ioperm(pmx::RobotInOutParallelPort::DATA_ADDR, 3, 1);
    if (result == 0)
    {
        pmx::RobotInOutParallelPort * parallel = new pmx::RobotInOutParallelPort();
        in_ = parallel;
        out_ = parallel;
    }
    else
    {
        in_ = new pmx::RobotInLogger();
        out_ = new pmx::RobotOutLogger();
    }
}
