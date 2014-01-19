/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * sur le robot.
 */

#include "RobotTestManager.hpp"
#include "ImpulsionsTest.hpp"
#include "OutPinsTest.hpp"
#include "MultiDemultiAllPinsTest.hpp"
#include "RobotMoveTest.hpp"
#include "ContactTest.hpp"
#include "DistanceDetectorTest.hpp"
#include "RobotMoveByIncrementTest.hpp"
#include "ServoMotorsTest.hpp"
#include "StepperTest.hpp"
#include "MovePositionTest.hpp"
#include "RobotMoveByPositionTest.hpp"
#include "ColumnElementLeverTest.hpp"

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
    
    manager.add(new test::MultiDemultiAllPinsTest());
    manager.add(new test::ImpulsionsTest());
    manager.add(new test::OutPinsTest());
    manager.add(new test::RobotMoveTest());
    manager.add(new test::ContactTest());
    manager.add(new test::DistanceDetectorTest());
    manager.add(new test::RobotMoveByIncrementTest());
    manager.add(new test::ServoMotorsTest());
    manager.add(new test::StepperTest());
    manager.add(new test::MovePositionTest());
    manager.add(new test::RobotMoveByPositionTest());
    manager.add(new test::ColumnElementLeverTest());

    if (argc == 1)
    {
        manager.run();
    }
    else
    {
        manager.run(atoi(argv[1]), argc, argv);
    }
}
