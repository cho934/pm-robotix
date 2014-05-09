/*!
 * \file
 * \brief Implementation de la classe ConsoleUnitTestManager.
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "ConsoleUnitTestManager.hpp"

pmx::ConsoleUnitTestManager::ConsoleUnitTestManager()
		: tests_()
{
}

void pmx::ConsoleUnitTestManager::add(pmx::ConsoleUnitTest * test)
{
	this->tests_.push_back(test);
}

void pmx::ConsoleUnitTestManager::run(char *argv0)
{
	//display unit tests
	for (data_type::size_type i = 0; i < tests_.size(); i++)
	{
		std::cout << "  " << i + 1 << ". " << tests_[i]->name() << std::endl;
	}

	std::cout << "Ton choix [0 pour quitter] : " << std::flush;

	int nTest;
	std::cin >> nTest;
	if (nTest <= 99)
		executeTest(nTest, argv0);
	else
		std::cout << "Ton choix est > 99!" << std::endl;
}

void pmx::ConsoleUnitTestManager::run(uint nTest, int argc, char *argv[])
{
	executeTest(nTest, argc, argv);
}

void pmx::ConsoleUnitTestManager::executeTest(uint nTest, int argc, char *argv[])
{
	if (nTest > 0 && nTest <= tests_.size())
	{
		tests_[nTest - 1]->run(argc, argv);
	}
}

void pmx::ConsoleUnitTestManager::executeTest(uint nTest, char * argv0)
{
	char *argv[2];
	argv[0] = "";
	argv[1] = "";
	char st[3]; // nTest <= 99

	//transformation int to char
	sprintf(st, "%d", nTest);

	if (nTest > 0 && nTest <= tests_.size())
	{
		//creation du char *argv[]
		argv[1] = (char *) malloc(strlen(st) + 1);
		argv[0] = argv0;
		//strcpy(argv[0], argv0);
		strcpy(argv[1], st);

		//lancement du run
		tests_[nTest - 1]->run(1, argv);
	}
}
