#include <iostream>

#include "../Action.Driver/ALedDriver.hpp"

using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//test Actions
	//LedBar ledbar(2); //TODO pb 2=>EV3 8=>ARM...?
	//ledbar.blinkPin(3, 100, 10000);

	char aPortChar;
	int aPinNum;
	int aGpioNum = 10;

	for (aGpioNum=0; aGpioNum<200; aGpioNum++)
	{
		aPortChar = (aGpioNum / 32) + 'A';
		aPinNum = aGpioNum - (aPortChar - 'A')*32;

		//printf("aPortChar=%c, aPinNum=%d,",aPortChar, aPinNum);
		cout << "aGpioNum=" << aGpioNum <<" => aPortChar=" << aPortChar  << " aPinNum =" << aPinNum << endl;
	}
	//Drivers
	ALedDriver* leddriver;
	leddriver = ALedDriver::create();
	leddriver->set(0, 3);

	//TODO Tests
	//Unit Tests ?
	//Actions Tests ?
	//IA Tests ?
	//Asserv Tests ?

	return 0;
}
