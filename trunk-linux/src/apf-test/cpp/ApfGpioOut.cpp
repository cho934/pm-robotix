/*!
 * \file
 * \brief Implémentation de la classe ApfGpioOut, Clignotement d'une sortie (ou pad) de la carte DevLightV2.
 */

#include "ApfGpioOut.hpp"

//#include <linux/ppdev.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "../../common/cpp/Exception.hpp"
#include "GpioPort.hpp"

void test::ApfGpioOut::run(int argc, char *argv[])
{
	using std::string;
	string str;
	int count = 4; //par defaut
	int delay = 1000000; //par defaut
	int io = 0;

	char port_letter = 'D';
	int pin_num = 31;
	char port_letter2 = 'D';
	int pin_num2 = 31;
	//struct as_gpio_device *gpio_dev;

	std::cout << "APF : Blink GPIO out on devLightV2 (with ioctl) :"
			<< std::endl;

	if (argc < 5)
	{
		std::cout << "USAGE: APF_TEST " << argv[1]
				<< " [GPIO1_PORT:A B C D] [GPIO1_PIN:0...31] [GPIO2_PORT:A B C D] [GPIO2_PIN:0...31] [by IOCTL:0 by ASDEVICES:1] [count:4 times (option)] [delay:100000us (option)]"
				<< std::endl;
	}
	if (argc > 2)
	{
		port_letter = *argv[2];
	}
	else
	{
		std::cout << "[LED1 GPIO PORT: A B C D] : " << std::flush;
		std::cin >> str;
		// créer le buffer port_letter pour copier la chaîne
		strncpy(&port_letter, str.c_str(), str.size() + 1);
	}
	if (argc > 3)
	{
		pin_num = atoi(argv[3]);
	}
	else
	{
		std::cout << "[LED1 PIN:0->31]: " << std::flush;
		std::cin >> pin_num;
	}

	if (argc > 4)
	{
		port_letter2 = *argv[4];
	}
	else
	{
		std::cout << "[LED2 GPIO PORT: A B C D] : " << std::flush;
		std::cin >> str;
		// créer le buffer port_letter pour copier la chaîne
		strncpy(&port_letter2, str.c_str(), str.size() + 1);
	}
	if (argc > 5)
	{
		pin_num2 = atoi(argv[5]);
	}
	else
	{
		std::cout << "[LED2 PIN:0->31]: " << std::flush;
		std::cin >> pin_num2;
	}

	if (argc > 6)
	{
		io = atoi(argv[6]);
		std::cout << "io=[" << io << "]"<< std::flush;
	}
	if (argc > 7)
	{
		count = atoi(argv[7]);
	}
	if (argc > 8)
	{
		delay = atoi(argv[8]);
	}

	std::cout << "Toggling LED " << port_letter << pin_num << " "
			<< port_letter2 << pin_num2 << " " << count << " times" << " delai:"
			<< delay << "us" << std::endl;
	bool nok = false;
	try
	{
		utils::GpioPort* gpio1 = new utils::GpioPort();
		utils::GpioPort* gpio2 = new utils::GpioPort();

		if (io == 0) //ASDEVICES
		{
			std::cout << "created " << std::endl;
			gpio1->openAs(port_letter, pin_num);
			gpio2->openAs(port_letter2, pin_num2);
			std::cout << "opened " << std::endl;
			gpio1->setDirectionAs(1);
			gpio2->setDirectionAs(1);
			std::cout << "setDirection " << std::endl;
			gpio1->setValueAs(0);
			gpio2->setValueAs(0);
			std::cout << "setValue as" << std::endl;
			for (int i = 0; i < count; i++)
			{
				//std::cout << "ON " << std::flush;
				gpio1->setValueAs(1);
				//usleep(delay);
				gpio2->setValueAs(0);
				usleep(delay);

				//std::cout << "OFF " << std::flush;
				gpio1->setValueAs(0);
				//usleep(delay);
				gpio2->setValueAs(1);
				usleep(delay);
			}
		}
		else //IOCTL
		{

			std::cout << "created IOCTL" << std::endl;
			gpio1->openIoctl(port_letter, pin_num);
			gpio2->openIoctl(port_letter2, pin_num2);
			std::cout << "opened IOCTL " << std::endl;
			gpio1->setDirIoctl(1);
			gpio2->setDirIoctl(1);
			std::cout << "setDirection IOCTL" << std::endl;
			gpio1->setValueIoctl(0);
			gpio2->setValueIoctl(0);
			std::cout << "setValue IOCTL" << std::endl;
			for (int i = 0; i < count; i++)
			{
				//std::cout << "ON " << std::flush;
				gpio1->setValueIoctl(true);
				//usleep(delay);
				gpio2->setValueIoctl(false);
				usleep(delay);

				//std::cout << "OFF " << std::flush;
				gpio1->setValueIoctl(false);
				//usleep(delay);
				gpio2->setValueIoctl(true);
				usleep(delay);
			}
		}
	} catch (utils::Exception* exception)
	{
		nok = true;
		std::cout << "Exception: " << exception->what() << std::endl;
	}

	//return nok;
	/*

	 gpio_dev = as_gpio_open(port_letter, pin_num);
	 if (gpio_dev == NULL)
	 {
	 printf("Error can't open gpio %c\nHave you run loadgpio.sh ?\n", port_letter);
	 exit(1);
	 }

	 //pin Direction (0:in, 1:out) => OUT
	 ret = as_gpio_set_pin_direction(gpio_dev, 1);
	 if(ret < 0)
	 {
	 printf("Error, can't change direction\n");
	 exit(1);
	 }

	 for (int i = 0; i < count; i++)
	 {
	 std::cout << "OFF " << std::flush;
	 ret = as_gpio_set_pin_value(gpio_dev, 0);
	 if(ret < 0)
	 {
	 printf("Error, can't change pin value\n");
	 exit(1);
	 }
	 usleep(delay);
	 std::cout << "ON " << std::flush;
	 ret = as_gpio_set_pin_value(gpio_dev, 1);
	 if(ret < 0)
	 {
	 printf("Error, can't change pin value\n");
	 exit(1);
	 }
	 usleep(delay);
	 }
	 std::cout << std::endl;
	 ret = as_gpio_close(gpio_dev);
	 if(ret < 0)
	 {
	 printf("Error, can't close gpio\n");
	 exit(1);
	 }

	 */
	std::cout << "End Of APF-TEST" << std::endl;
}
