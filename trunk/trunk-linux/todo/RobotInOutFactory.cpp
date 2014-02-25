/*!
 * \file
 * \brief Implémentation de la classe RobotInOutFactory.
 */

#include <istream>
#include "RobotInOutFactory.hpp"
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
}
