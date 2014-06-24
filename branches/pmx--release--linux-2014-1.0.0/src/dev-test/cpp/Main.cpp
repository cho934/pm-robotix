/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * unitaires sur le code.
 */

#include <iostream>

#include "ActionManagerTest.hpp"

#include "LoggerTest.hpp"
#include "ConfigurationTest.hpp"
#include "ThreadTest.hpp"

#include "MutexTest.hpp"
#include "PositionTest.hpp"
#include "PidTest.hpp"

#include "ChronometerTest.hpp"
#include "PointerListTest.hpp"

#include "DevUnitTestTest.hpp"
#include "DevUnitTestSuite.hpp"

#include "IaTest.hpp"

using namespace std;
using namespace test;

/*!
 * \brief Méthode principale pour le lancement des tests unitaires.
 *
 * \return Code de retour du programme. Toujours égal à \c 0.
 */
int main()
{
	utils::DevUnitTestSuite suite;

	// tests unitaires stratégiques

	suite.addTest(new IaTest());
	//suite.addTest(new LoggerTest());
	/*suite.addTest(new UnitTestTest());

	 // tests unitaires pour le namespace utils
	 suite.addTest(new ConfigurationTest());
	 suite.addTest(new MutexTest());
	 suite.addTest(new ThreadTest());
	 suite.addTest(new PointerListTest());

	 // tests unitaires normaux
	 suite.addTest(new ChronometerTest());
	 suite.addTest(new PidTest());
	 suite.addTest(new PositionTest());
	 suite.addTest(new ActionManagerTest());*/

	/*//TODO add tests
	 suite.addTest(new ARobotElementTest());
	 suite.addTest(new AAutomateStateTest());
	 suite.addTest(new AutomateTest());
	 suite.addTest(new BaseTest());
	 */

	suite.run();
}
