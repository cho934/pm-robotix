/*!
 * \file
 * \brief Implementation de la classe ConsoleManager.
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "ConsoleManager.hpp"

ConsoleManager::ConsoleManager()
		: tests_()
{
}

void ConsoleManager::add(FunctionalTest * test)
{
	this->tests_.push_back(test);
}

void ConsoleManager::run(char *argv0)
{
	//display unit tests
	for (data_type::size_type i = 0; i < tests_.size(); i++)
	{
		std::cout << "  " << i + 1 << ". " << tests_[i]->name() << std::endl;
	}

	std::cout << "Your choice [0 = quit] : " << std::flush;

	int nTest;
	std::cin >> nTest;

	executeTest(nTest, argv0);
}

void ConsoleManager::run(uint nTest, int argc, char *argv[])
{
	executeTest(nTest, argc, argv);
}

void ConsoleManager::executeTest(uint nTest, int argc, char *argv[])
{
	if (nTest > 0 && nTest <= tests_.size())
	{
		tests_[nTest - 1]->run(argc, argv);
	}
	else
	{
		std::cout << "The N° must be between 0 and " << tests_.size() << std::endl;
	}
}

void ConsoleManager::executeTest(uint nTest, char * argv0)
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
		std::cout << "The N° must be between 0 and " << tests_.size() << std::endl;
	}
}