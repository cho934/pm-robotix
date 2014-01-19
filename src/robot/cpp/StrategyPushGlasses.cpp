
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
    logger().info() << "move 450,950" << utils::end;
    robot.goTo(450.0, 950.0, pmx::BFORWARD, true);



    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    //reculer
    logger().info() << "move 500,position().y()=" << robot.position().y() << utils::end;
    robot.goTo(500.0, robot.position().y_abs(), pmx::BBACK, false);


    logger().info() << "move 1550,950" << utils::end;
    robot.goTo(1500.0, 950.0, pmx::BFORWARD, true);
    //baisser le levier
    logger().info() << "baisser le levier" << utils::end;
    robot.servoLevier().turnMin(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    logger().info() << "move 1800,950" << utils::end;
    robot.goTo(1800.0, 950.0, pmx::BFORWARD, true);
    logger().info() << "move 1650,1200" << utils::end;
    robot.goTo(1650.0, 1200.0, pmx::BFORWARD, true);
    logger().info() << "move 410,1200" << utils::end;
    robot.goTo(410.0, 1200.0, pmx::BFORWARD, true);


    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);
    //sleep(1);
    //robot.servoLevier().stop(true);
    logger().info() << "move 500,position().y()="<< robot.position().y() << utils::end;
    robot.goTo(500.0, robot.position().y_abs(), pmx::BBACK, false);


    robot.goTo(1500.0, 1200.0, pmx::BFORWARD, true);
    //baisser le levier
    logger().info() << "baisser le levier" << utils::end;
    robot.servoLevier().turnMin(false);

    robot.goTo(2100.0, 1200.0, pmx::BFORWARD, true);
    robot.goTo(2100.0, 1450.0, pmx::BFORWARD, true);
    robot.goTo(410.0, 1450.0, pmx::BFORWARD, true);

    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);

/*
    logger().info() << "move 1000,600" << utils::end;
    robot.goTo(1000.0, 600.0, pmx::BFORWARD, true);
    logger().info() << "move 1320,750" << utils::end;
    robot.goToTeta(1320.0, 750.0, (98.6 * M_PI) / 180.0, pmx::BFORWARD, true);
    logger().info() << "baisser le levier" << utils::end;
    robot.servoLevier().turnMin(false);
    logger().info() << "move 800,1550" << utils::end;
    robot.goTo(800.0, 1550.0, pmx::BFORWARD, true);
    logger().info() << "move 450,1550" << utils::end;
    robot.goTo(450.0, 1550.0, pmx::BFORWARD, true);
    //lever le levier
    logger().info() << "lever le levier" << utils::end;
    robot.servoLevier().turnMax(false);
    logger().info() << "move 450,1550" << utils::end;
    robot.goTo(600.0, 1550.0, pmx::BBACK, false);
*/


    sleep(10);


 



    pmx::Data* sharedData = (pmx::Data*) data;
    sharedData->isEmpty(false);

    //Prog de decision
    result = this->getState("decisionMaker");

    return result;
}
