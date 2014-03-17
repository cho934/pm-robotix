/*!
 * \file
 * \brief Implémentation de la classe ApfGpioOut, Clignotement d'une sortie (ou pad) de la carte DevLightV2.
 */

#include <iostream>
#include <cstring>
#include <linux/ppdev.h>

#include "../../common/cpp/Exception.hpp"
#include "GpioPort.hpp"

#include "ApfGpioOut.hpp"

void test::ApfGpioOut::run(int argc, char *argv[])
{
	using std::string;
	string str;
	int count = 4; //par defaut
	int delay = 1000000; //par defaut

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
				<< " [GPIO1_PORT:A B C D] [GPIO1_PIN:0...31] [GPIO2_PORT:A B C D] [GPIO2_PIN:0...31] [count:4 times (default)] [delay:100000us (default)]"
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
		count = atoi(argv[6]);
	}
	if (argc > 7)
	{
		delay = atoi(argv[7]);
	}

	std::cout << "Toggling LED " << port_letter << pin_num << " "
			<< port_letter2 << pin_num2 << " " << count << " times" << " delai:"
			<< delay << "us" << std::endl;

	try
	{
		utils::GpioPort* gpio1 = new utils::GpioPort(port_letter, pin_num);
		utils::GpioPort* gpio2 = new utils::GpioPort(port_letter2, pin_num2);
		std::cout << "created " << std::endl;

		//gpio1.open(port_letter, pin_num);
		//gpio2.open(port_letter2, pin_num2);
		//gpio1.open('B', 17);
		//gpio2.open('B', 17);
		std::cout << "opened " << std::endl;

		gpio1->setDirection(1);
		gpio2->setDirection(1);
		std::cout << "setDirection " << std::endl;

		gpio1->setValue(0);
		gpio2->setValue(0);
		std::cout << "setValue " << std::endl;

		for (int i = 0; i < count; i++)
		{
			//std::cout << "ON " << std::flush;
			gpio1->setValue(1);
			usleep(delay);
			gpio2->setValue(0);

			usleep(delay);
			//std::cout << "OFF " << std::flush;
			gpio1->setValue(0);
			usleep(delay);
			gpio2->setValue(1);

			usleep(delay);

		}
	} catch (utils::Exception* exception)
	{
		std::cout << "Exception: " << exception->what() << std::endl;

	}

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
