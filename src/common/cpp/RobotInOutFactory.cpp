/*!
 * \file
 * \brief Implémentation de la classe RobotInOutFactory.
 */

#include <istream>
#include "RobotInOutFactory.hpp"
#include "RobotInOutParallelPort.hpp"
#include "RobotInSimulate.hpp"
#include "RobotOutSimulate.hpp"
#include "RobotInOutApf.hpp"
#include "ServoMotorApf.hpp"

pmx::RobotInOutFactory * pmx::RobotInOutFactory::instance() //singleton
{
    static pmx::RobotInOutFactory * instance = new pmx::RobotInOutFactory();
    return instance;
}

pmx::RobotInOutFactory::RobotInOutFactory() : in_(NULL), out_(NULL), outServoMotor_(NULL)
{
    logger().debug("pmx::RobotInOutFactory::RobotInOutFactory()");

    if (access("/etc/machine", F_OK) == 0)
    {
        logger().info("Use of the Apf in/out");
        this->blockingRead(true);
        pmx::RobotInOutApf * apf = new pmx::RobotInOutApf();
        in_ = apf;
        out_ = apf;

        pmx::ServoMotorApf * servo = new pmx::ServoMotorApf();
        outServoMotor_ = servo;

    }
    else //! \todo ce n'est plus d'actualité
    {
        int result = ioperm(pmx::RobotInOutParallelPort::DATA_ADDR, 3, 1);
        if (result == 0)
        {
            logger().info("Use of the parallel port for in/out");
            pmx::RobotInOutParallelPort * parallel = new pmx::RobotInOutParallelPort();
            in_ = parallel;
            out_ = parallel;
        }
        else
        {
            logger().info("Use of simulated in/out");
            in_ = new pmx::RobotInSimulate();
            out_ = new pmx::RobotOutSimulate();
        }
    }
}
