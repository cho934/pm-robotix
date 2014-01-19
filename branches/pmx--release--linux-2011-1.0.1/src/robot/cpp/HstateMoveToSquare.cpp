/*!
 * \file
 * \brief Implémentation de la classe HstateMoveToSquare.
 */

#include <cmath>
#include "SvgWriter.hpp"
#include "HstateMoveToSquare.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::automate::HstateMoveToSquare::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;

    robot.firePulseEnabled(false);

    this->logger().info() << "move to 800, 1050" << utils::end;
    robot.base().movexy_Dpawn(800, 1050, pmx::BFORWARD, NULL, 0, 0);
    while (robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }
    
    robot.firePulseEnabled(false);

    this->logger().info() << "move to 625, 1225" << utils::end;
    robot.base().movexy_Dpawn(625, 1225, pmx::BFORWARD, NULL, 0, 130);
    while (robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }

    robot.firePulseEnabled(false);

    logger().info() << "Arrived    x: " << robot.position().x() << " y: "
            << robot.position().y() << " angle: " << robot.position().angle()
            << utils::end;

    this->logger().info() << "lacher pion" << utils::end;

    robot.elevator().goLowPosition();
    sleep(1);
    robot.clamp().openWidePosition();
    while(robot.clamp().stateOpened() == 0)
    {
        usleep(10000);
    }

    utils::SvgWriter::writePawn(robot.position().x() + 130*std::cos(robot.position().angle()), robot.position().y() + 130*std::sin(robot.position().angle()));

    this->logger().info() << "reculer" << utils::end;
    robot.firePulseEnabled(true);
    robot.base().moveD(-200 / pmx::PositionManager::DISTANCE_PER_UP_PULSE,0);
    while (robot.base().arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);
    logger().info() << "Arrived    x: " << robot.position().x() << " y: "
            << robot.position().y() << " angle: " << robot.position().angle()
            << utils::end;


    robot.clamp().close();
    sleep(2);
    return NULL;
}
