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

	executeTest(nTest, argv0);
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
	else
	{
		std::cout << "N° doit être compris entre 1 et " << tests_.size() << std::endl;
	}
}

void pmx::ConsoleUnitTestManager::executeTest(uint nTest, char * argv0)
{
	if (nTest > 0 && nTest <= tests_.size())
	{
		char **argv = (char**) malloc(2 * sizeof(char*));
		argv[0] = argv0;

		argv[1] = (char *) calloc(1, 12);
		sprintf(argv[1], "%d", nTest);

		//lancement du run
		tests_[nTest - 1]->run(1, argv);
	}
	else
	{
		std::cout << "N° doit être compris entre 1 et " << tests_.size() << std::endl;
	}
}
