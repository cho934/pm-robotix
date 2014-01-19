
/*!
 * \file
 * \brief Implémentation de la classe StrategyPushGlasses.
 */

#include "StrategyPushGlasses.hpp"
#include "Robot.hpp"
#include "Contract.hpp"
#include "Data.hpp"

int
pmx::StrategyPushGlasses::computeInterest(const pmx::Robot &, void * data) {
    utils::Contract::isNotNull(data, "pmx::StrategyPushGlasses::computeInterest - data is null");

    pmx::Data* sharedData = (pmx::Data*) data;
    if (sharedData->isEmpty() == false) {
        return -1;
    }else {
        return 3;
    }

}

pmx::IAutomateState*
pmx::StrategyPushGlasses::execute(Robot& robot , void * data)
{
    logger().info() << "start" << utils::end;

    IAutomateState* result = NULL;

    robot.firePulseEnabled(false);
    robot.base().pidSpeedEnabled(false);
    robot.base().pidPositionEnabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    robot.base().rampPositionEnabled(false);

    //avancer pour pousser les verres

    logger().info() << "move 1000,600" << utils::end;
    robot.goTo(1000.0, 600.0, pmx::BFORWARD, true);
    logger().info() << "move 1500,950" << utils::end;
    robot.goToTeta(1500.0, 950.0, (145.0 * M_PI) / 180.0, pmx::BFORWARD, true);
    //baisser le levier
    logger().info() << "baisser le levier" << utils::end;
    robot.servoLevier().turnMin(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    logger().info() << "move 500,950" << utils::end;
    robot.goTo(450.0, 950.0, pmx::BFORWARD, true);



    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    //reculer
    logger().info() << "move 600,950" << utils::end;
    robot.goTo(600.0, 950.0, pmx::BBACK, true);


    logger().info() << "move 1550,950" << utils::end;
    robot.goTo(1500.0, 950.0, pmx::BFORWARD, true);
    //baisser le levier
    logger().info() << "baisser le levier" << utils::end;
    robot.servoLevier().turnMin(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    logger().info() << "move 2150,950" << utils::end;
    robot.goTo(2100.0, 950.0, pmx::BFORWARD, true);
    logger().info() << "move 2000,1200" << utils::end;
    robot.goTo(2000.0, 1200.0, pmx::BFORWARD, true);
    logger().info() << "move 2000,1200" << utils::end;
    robot.goTo(2000.0, 1200.0, pmx::BFORWARD, true);
    logger().info() << "move 500,1200" << utils::end;
    robot.goTo(450.0, 1200.0, pmx::BFORWARD, true);


    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);
    //sleep(1);
    //robot.servoLevier().stop(true);


    robot.goTo(1500.0, 1500.0, pmx::BFORWARD, true);

    robot.goTo(400.0, 1400.0, pmx::BFORWARD, true);

    sleep(90);



    pmx::Data* sharedData = (pmx::Data*) data;
    sharedData->isEmpty(false);

    //Prog de decision
    result = this->getState("decisionMaker");

    return result;
}
