/*!
 * \file
 * \brief Implementation de la classe ConsoleManager.
 */

#include "ConsoleManager.hpp"

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "ConsoleKeyInput.hpp"

using namespace std;

ConsoleManager::ConsoleManager() :
		tests_()
{
}

void ConsoleManager::add(FunctionalTest * test)
{
	this->tests_.push_back(test);
}

void ConsoleManager::displayMenuFunctionalTestsAndRun(char *argv0)
{
	char cInput;
	int lindex = 0;
	std::string color = "\033[7;32m";
	std::string default_console = "\033[0m";

	std::string tab[tests_.size() + 1];
	clearScreen();
	setPrintPos(1, 1);
	//display unit tests
	for (data_type::size_type i = 0; i < tests_.size(); i++)
	{
		std::cout << std::flush;
		if (lindex == (int) i)
			std::cout << color << std::flush;
		else
			std::cout << default_console << std::flush;

		std::cout << "  " << i + 1 << ". " << tests_[i]->name() << std::endl;
		ostringstream out;
		out << "  " << i + 1 << ". " << tests_[i]->name();
		tab[i + 1] = out.str();
	}

	do
	{
		cInput = mygetch();
		switch (cInput)
		{
			case 65:
			//printf("Up arrow key!\n");
			if (lindex > 0)
			{
				setPrintPos(lindex + 1, 1);
				std::cout << default_console << tab[lindex + 1] << "  " << std::flush;
				lindex--;
				setPrintPos(lindex + 1, 1);
				std::cout << color << "> " << tab[lindex + 1] << std::flush;
			}
			break;
			case 66:
			if (lindex < (int) tests_.size() - 1)
			{
				//printf("Down arrow key!\n");
				setPrintPos(lindex + 1, 1);
				std::cout << default_console << tab[lindex + 1] << "  " << std::flush;
				lindex++;
				setPrintPos(lindex + 1, 1);
				std::cout << color << "> " << tab[lindex + 1] << std::flush;
			}
			break;
			/*
			 case 67:
			 printf("Right arrow key!\n");
			 break;
			 case 68:
			 printf("Left arrow key!\n");
			 break;*/
			case 10:
			//printf("Enter key!\n");
			break;
			case 127:
			//printf("BACK key!\n");
			cout << default_console << endl;
			exit(0);
			break;
		}

		usleep(1000);
	} while (cInput != 10);

	cout << default_console << flush;
	clearScreen();

	executeTest(lindex + 1, argv0);
}

string ConsoleManager::displayMenuFirstArgu()
{
	string select;
	char cInput;
	std::string color = "\033[7;32m";
	std::string default_console = "\033[0m";

	//Request input parameters
	clearScreen();
	setPrintPos(3, 1);
	cout << "  (M)ATCHES" << flush;
	setPrintPos(5, 1);
	cout << "  (T)ESTS" << flush;

	do
	{
		cInput = mygetch();
		switch (cInput)
		{
		case 65:
			//printf("Up arrow key!\n");
			setPrintPos(3, 1);
			cout << color << "> (M)ATCHES" << flush;
			setPrintPos(5, 1);
			cout << default_console << "  (T)ESTS  " << flush;
			select[0] = 'M';
			break;
		case 66:
			//printf("Down arrow key!\n");
			setPrintPos(3, 1);
			cout << default_console << "  (M)ATCHES" << flush;
			setPrintPos(5, 1);
			cout << color << "> (T)ESTS  " << flush;
			select[0] = 'T';
			break;
			/*case 67:
			 printf("Right arrow key!\n");
			 break;
			 case 68:
			 printf("Left arrow key!\n");
			 break;*/
		case 10:
			//printf("Enter key!\n");
			break;
		case 127:
			//printf("BACK key!\n");
			cout << default_console << endl;
			exit(0);
			break;
		}
		usleep(1000);
	} while (cInput != 10);
	cout << default_console << endl;
	clearScreen();
	return select;
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

		std::cout << "Launch test n°" << nTest << " / " << tests_.size() << std::endl;
		//launch the test
		tests_[nTest - 1]->run(1, argv);
	}
	else
	{
		std::cout << "The N° must be between 0 and " << tests_.size() << std::endl;
	}
}
