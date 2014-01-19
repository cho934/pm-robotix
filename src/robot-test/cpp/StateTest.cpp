/*!
 * \file
 * \brief Implémentation de la classe StateTest.
 */

#include "StateTest.hpp"
#include "Automate.hpp"
#include "Robot.hpp"
#include "LoggerFactory.hpp"

#include "StateDecisionMaker.hpp"
#include "StateInit.hpp"
#include "StrategyOne.hpp"
#include "StrategyTwo.hpp"
#include "StateData.hpp"


using namespace pmx;

void test::StateTest::run(int, char **) //(int argc, char *argv[])
{
    std::cout << "test::StateTest: Start" << std::endl;


    //test de l'architecture d'un programme

    Robot robot;
    robot.firePulseEnabled(false); //pour ne pas prendre en compte les impulsions des codeurs.


    logger().info() << "Start of PMX, the robot..." << utils::end;
    robot.start();

    robot.base().pidSpeedDesactivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID

    //le decisionmaker
    pmx::StateDecisionMaker* decisionMaker = new pmx::StateDecisionMaker();

    //les Etats automate pour ce programme
    IAutomateState* stateInit = new StateInit();

    //les stratégies
    AStrategy* strategyOne = new StrategyOne(decisionMaker);
    AStrategy* strategyTwo = new StrategyTwo(decisionMaker);

    //Liste des liens entre les états:
    stateInit->addState("decisionMaker", decisionMaker);
    stateInit->addState("tryAgain", stateInit);

    decisionMaker->addStrategy(strategyOne);
    decisionMaker->addStrategy(strategyTwo);

    // Create the data used to run the automate
    StateData *data = new StateData();
    data->isEmpty(true);


    // Start the automate and wait for its return
    Automate *automate = new Automate();
    automate->run(robot, stateInit, data);


    robot.stop();
    logger().info() << "End-Of-PMX" << utils::end;
}

