/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * unitaires sur le code.
 */

#include "UnitTestSuite.hpp"

#include "ThreadTest.hpp"
#include "LoggerTest.hpp"
#include "UnitTestTest.hpp"
#include "MutexTest.hpp"
#include "PositionTest.hpp"
#include "PidTest.hpp"
#include "ConfigurationTest.hpp"
#include "ChronometerTest.hpp"

#include <iostream>

using namespace std;
using namespace test;

/*!
 * \brief Méthode principale pour le lancement des tests unitaires.
 *
 * \return Code de retour du programme. Toujours égal à \c 0.
 */
int main()
{
    utils::UnitTestSuite suite;

    //tests unitaires
    suite.addTest(new LoggerTest());
    suite.addTest(new UnitTestTest());
    suite.addTest(new MutexTest());     
    suite.addTest(new PositionTest());
    suite.addTest(new PidTest());
    suite.addTest(new ConfigurationTest());

    //tests de methode CPP
    suite.addTest(new ChronometerTest());
    suite.addTest(new ThreadTest());

    suite.run();
}
