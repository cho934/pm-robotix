/*!
 * \file
 * \brief Implémentation de la classe HstateMoveToPawn (Homologation).
 */

#include "HstateMoveToPawn.hpp"
#include "HstateTakePawn.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::automate::HstateMoveToPawn::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;
    robot.firePulseEnabled(false);

    //open clamp
    robot.clamp().openWidePosition();
    while(!robot.clamp().stateOpened())
    {
        usleep(10000);
    }

    //repositionnement
    robot.position().x(130);
    robot.position().y(200, robot.myColor());
    robot.position().angle(0, robot.myColor());


    //creation des listeners
    robot.pawnLeftIrSensor().getObjectDistance();//active le listener:
    robot.pawnRightIrSensor().getObjectDistance();//active le listener:
    robot.opponentIrSensor().getObjectDistance();//active le listener:

    
    this->logger().info() << "Move 700, y()" << utils::end;
    robot.base().movexy_Dpawn(700, robot.position().y(), pmx::BFORWARD, NULL, 0, 0);
    while(!robot.base().arrived())
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);

    this->logger().info() << "Move 800, 700" << utils::end;
    robot.base().movexy_Dpawn(800, 700, pmx::BFORWARD, NULL, 1, 0);
    while(!robot.base().arrived())
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);
    if (robot.base().pawnFound())//take pawn si pawn detecte
    {
        return new pmx::automate::HstateTakePawn();
    }

    this->logger().info() << "Move 800, 1400" << utils::end;
    robot.base().movexy_Dpawn(800,1400, pmx::BFORWARD, NULL, 1, 0);
    while(!robot.base().arrived())
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);
    if (robot.base().pawnFound())//take pawn si pawn detecte
    {
        return new pmx::automate::HstateTakePawn();
    }

    // 2eme ligne
    this->logger().info() << "Move 800, 1400" << utils::end;
    robot.base().movexy_Dpawn(1150,1400, pmx::BFORWARD, NULL, 1, 0);
    while(!robot.base().arrived())
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);
    if (robot.base().pawnFound())//take pawn si pawn detecte
    {
        return new pmx::automate::HstateTakePawn();
    }

    this->logger().info() << "Move 800, 1400" << utils::end;
    robot.base().movexy_Dpawn(1150,700, pmx::BFORWARD, NULL, 1, 0);
    while(!robot.base().arrived())
    {
        usleep(10000);
    }
    robot.firePulseEnabled(false);


    if (robot.base().pawnFound())//take pawn si pawn detecte
    {
        return new pmx::automate::HstateTakePawn();
    }

    return NULL;
}
