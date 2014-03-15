/*!
 * \file
 * \brief Implémentation de la classe ApfI2cWithMd25, concernant l'utilisation des servomoteurs AX12.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "ApfUartWithAX12.hpp"

#include "SerialPort.hpp"
#include "Dynamixel.hpp"

#include <fcntl.h>
#include <errno.h>
#include <termios.h>

void test::ApfUartWithAX12::run(int, char*[])
{
	std::cout << "APF : Use UART2 and AX-12" << std::endl;

	int error = 0;
	int idAX12 = 7;

	SerialPort serialPort;
	Dynamixel dynamixel;

	if (serialPort.connect("//dev//ttySMX1") != 0)
	{
		dynamixel.sendTossModeCommand(&serialPort);

		for (int i = 0; i < 20000; i++)
		{

			int pos = dynamixel.getPosition(&serialPort, idAX12);
			printf("\nPosition <%i> under 250 or over 1023\n", pos);
		}
/*
		if (pos > 250 && pos < 1023)
			dynamixel.setPosition(&serialPort, idAX12, pos - 100);
		else
			printf("\nPosition <%i> under 250 or over 1023\n", pos);
*/
		serialPort.disconnect();
	}
	else
	{
		printf("\nCan't open serial port");
		error = -1;
	}

	/*
	 int fd;
	 // Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
	 fd = open("/dev/ttySMX1", O_RDWR | O_NOCTTY | O_NDELAY);
	 if (fd == -1) {
	 //perror("open_port: Unable to open /dev/ttyAMA0 - ");
	 //return(-1);
	 std::cout << "Error, open_port: Unable to open /dev/ttySMX1 -" << std::endl;
	 exit(1);
	 }

	 std::cout << "open ok " << std::endl;
	 // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
	 fcntl(fd, F_SETFL, 0);

	 // Write to the port
	 int n = write(fd,"Hello Peripheral\n",255);
	 if (n < 0) {
	 //perror("Write failed - ");
	 //return -1;
	 std::cout << "Error, Write failed -" << std::endl;
	 exit(1);
	 }
	 std::cout << "write ok " << std::endl;

	 // Read up to 255 characters from the port if they are there
	 char buf[256];
	 n = read(fd, (void*)buf, 255);
	 if (n < 0) {
	 //perror("Read failed - ");
	 //return -1;
	 std::cout << "Error, Read failed -" << std::endl;
	 exit(1);
	 } else if (n == 0) printf("No data on port\n");
	 else {
	 buf[n] = '\0';
	 printf("%i bytes read : %s", n, buf);
	 }

	 // Don't forget to clean up
	 close(fd);
	 //return 0;
	 */

	std::cout << "End Of APF-TEST" << std::endl;
}

