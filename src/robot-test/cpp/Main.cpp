/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * sur le robot.
 */

#include <cstdlib>
#include "RobotTestManager.hpp"
#include "ImpulsionsTest.hpp"
#include "OutAllPinsTest.hpp"
#include "OutPinsTest.hpp"
#include "InPinsTest.hpp"
#include "MultiDemultiAllPinsTest.hpp"
#include "RobotMoveTest.hpp"
#include "RobotFindPidTest.hpp"
#include "RobotFindPidPositionTest.hpp"
#include "ContactTest.hpp"
#include "DistanceSensorTest.hpp"
#include "RobotMoveByIncrementTest.hpp"
#include "RobotMoveByPositionTest.hpp"
#include "RobotMoveByXYTest.hpp"
#include "ApfOutTest.hpp"
#include "ApfOutDacTest.hpp"
#include "ApfInAdcTest.hpp"
#include "ApfInTest.hpp"
#include "ApfInModeTest.hpp"
#include "Md25Test.hpp"
#include "LedIndicatorTest.hpp"
#include "ApfInXenomaiTest.hpp"
#include "ServoTest.hpp"
#include "ServoAdjustmentTest.hpp"
#include "RobotMoveToPawnTest.hpp"
#include "RobotNoPidTest.hpp"

//#include "ColumnElementLeverTest.hpp"
//#include "ServoMotorsTest.hpp"
//#include "StepperTest.hpp"

/*!
 * \brief Méthode principale pour le lancement des tests sur le robot.
 *
 * \param argc
 *        Nombre d'arguments.
 * \param argv
 *        Arguments du programme (argv[0] est le nom de l'application).
 * \return Code de retour du programme.
 */
int main(int argc, char** argv)
{
    pmx::RobotTestManager manager;

    manager.add(new test::ApfOutTest());
    manager.add(new test::ApfOutDacTest());
    manager.add(new test::ApfInAdcTest());
    manager.add(new test::ApfInTest());
    manager.add(new test::ApfInModeTest());
    manager.add(new test::ApfInXenomaiTest());
    manager.add(new test::Md25Test());
    manager.add(new test::OutPinsTest());
    manager.add(new test::InPinsTest());
    manager.add(new test::OutAllPinsTest());
    manager.add(new test::MultiDemultiAllPinsTest());
    manager.add(new test::ContactTest());
    manager.add(new test::ImpulsionsTest());
    manager.add(new test::LedIndicatorTest());
    manager.add(new test::RobotMoveByIncrementTest());
    manager.add(new test::RobotFindPidTest());
    manager.add(new test::RobotFindPidPositionTest());
    manager.add(new test::RobotMoveTest());
    manager.add(new test::RobotMoveByPositionTest());
    manager.add(new test::RobotMoveByXYTest());
    manager.add(new test::DistanceSensorTest());
    manager.add(new test::ServoTest());
    manager.add(new test::ServoAdjustmentTest());
    manager.add(new test::RobotMoveToPawnTest());
    manager.add(new test::RobotNoPidTest());



    if (argc == 1)
    {
        manager.run();
    }
    else
    {
        manager.run(atoi(argv[1]), argc, argv);
    }
}
