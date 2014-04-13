/*!
 * \file
 * \brief Implémentation de la classe ApfUartWithAX12, concernant l'utilisation des servomoteurs AX12.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "ApfUartWithAX12.hpp"
#include "../../common/cpp/ServoMotorDxlConstant.hpp"


void test::ApfUartWithAX12::run(int, char*[])
{
	//add param ID Loop
	std::cout << "APF : Use UART2 and AX-12" << std::endl;

	int idAX12 = 7;

	Dynamixel dynamixel;

	long temp = 0;
	int data = 0;
	int volt = 0;
	int pos = 0;
	int v2 = 0;
	for (int i = 0; i < 20000; i++)
	{
		volt = 0;
		temp = 0;
		//int v2 = rand() % 100 + 1;     // v2 in the range 1 to 100 //2147483647
		v2 = (rand() % 600) + 200;     // v2 in the range 200 to 800


		dynamixel.setCommand(idAX12, AX_LED, 1, 1);

		//DxlSetAxLedOn(idAX12);
		data = DxlGetAxLed(idAX12);
		std::cout << "Led=" << data << std::endl;

		std::cout << "Go Position=" << v2 << std::endl;
		DxlSetPos(idAX12, v2);

		usleep(2000000);

		DxlSetAxLedOff(idAX12);
		data = DxlGetAxLed(idAX12);
		std::cout << "Led=" << data << std::endl;

		volt = DxlGetVoltage(idAX12);
		std::cout << "volt=" << volt << std::endl;

		temp = DxlGetTemperature(idAX12);
		std::cout << "temp=" << temp << std::endl;

		data = DxlGetBaud(idAX12);
		std::cout << "baud=" << reinterpret_cast<void*>(data) << std::endl;

		data = DxlGetReturnDelay(idAX12);
		std::cout << "delay=" << reinterpret_cast<void*>(data) << std::endl;

		data = DxlGetEnableTorque(idAX12);
		std::cout << "enable torque=" << reinterpret_cast<void*>(data) << std::endl;

		data = DxlGetMaxTorqueLimit(idAX12);
		std::cout << "max torque limit=" << reinterpret_cast<void*>(data) << std::endl;

		data = DxlGetMaxTorque(idAX12);
		std::cout << "max torque=" << reinterpret_cast<void*>(data) << std::endl;

		pos = DxlGetPos(idAX12);
		std::cout << "Last Position=" << pos << std::endl;

		usleep(2000000);
		std::cout << "------" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "End Of APF-TEST" << std::endl;
}

