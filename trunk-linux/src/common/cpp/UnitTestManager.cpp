/*!
 * \file
 * \brief Implementation de la classe RobotTestManager.
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "UnitTestManager.hpp"

pmx::UnitTestManager::UnitTestManager() : tests_()
{}

void pmx::UnitTestManager::add(pmx::UnitTest * test)
{
    this->tests_.push_back(test);
}

void pmx::UnitTestManager::run()
{
    for(data_type::size_type i = 0 ; i < tests_.size() ; i++)
    {
        std::cout << "  " << i + 1 << ". " << tests_[i]->name() << std::endl;
    }
    
    std::cout << "Ton choix [0 pour quitter] : " << std::flush;
    
    int nTest;
    std::cin >> nTest;
    
    executeTest(nTest);
}

void pmx::UnitTestManager::run(uint nTest, int argc, char *argv[])
{
    executeTest(nTest, argc, argv);
}

void pmx::UnitTestManager::executeTest(uint nTest, int argc, char *argv[])
{
    if (nTest > 0 && nTest <= tests_.size())
    {
        tests_[nTest - 1]->run(argc, argv);
    }
}

void pmx::UnitTestManager::executeTest(uint nTest)
{
    char *argv[1];
    char st[2];
    char *cTest;
    //transformation int to char
    sprintf(st, "%d", nTest);
    cTest = st;
    
    if (nTest > 0 && nTest <= tests_.size())
    {
        //creation du char *argv[]
        argv[0] =(char *) malloc( strlen(cTest) + 1 );
        strcpy(argv[0], cTest);
        
        //lancement du run
        tests_[nTest - 1]->run(1, argv);
    }
}
