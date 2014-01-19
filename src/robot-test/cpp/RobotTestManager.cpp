/*!
 * \file
 * \brief Implementation de la classe RobotTestManager.
 */

#include "RobotTestManager.hpp"
#include <iostream>
#include <sstream>

pmx::RobotTestManager::RobotTestManager() : tests_()
{}

void pmx::RobotTestManager::add(pmx::RobotTest * test)
{
    this->tests_.push_back(test);
}

void pmx::RobotTestManager::run()
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

void pmx::RobotTestManager::run(uint nTest, int argc, char *argv[])
{
    executeTest(nTest, argc, argv);
}

void pmx::RobotTestManager::executeTest(uint nTest, int argc, char *argv[])
{
    if (nTest > 0 && nTest <= tests_.size())
    {
        tests_[nTest - 1]->run(argc, argv);
    }
}

void pmx::RobotTestManager::executeTest(uint nTest)
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
