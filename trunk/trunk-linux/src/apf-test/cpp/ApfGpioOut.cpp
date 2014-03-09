/*!
 * \file
 * \brief Implémentation de la classe ApfGpioOut, Clignotement d'une sortie (ou pad) de la carte DevLightV2.
 */

#include <iostream>
#include <cstring>
//#include <cstdlib>
//#include <cstdio>
//#include <fcntl.h>
//#include <sys/ioctl.h>
#include <linux/ppdev.h>

#include <as_devices/as_gpio.h>

#include "ApfGpioOut.hpp"

void test::ApfGpioOut::run(int argc, char *argv[])
{
	using std::string;
	string str;
    int count = 4; //par defaut
    int delay = 1000000; //par defaut
    int32_t ret;
	char port_letter = 'D';
	int pin_num = 31;
    struct as_gpio_device *gpio_dev;

    std::cout << "APF : Blink GPIO out on devLightV2 (with ioctl) :" << std::endl;

    if(argc < 3)
    {
        std::cout << "USAGE: APF_TEST " << argv[1] <<" [GPIO_PORT:A B C D] [GPIO_PIN:0...31] [count:4 times (default)] [delay:100000us (default)]" << std::endl;
    }
    if(argc > 2)
    {
    	port_letter = *argv[2];
        //std::cout << "LED_GPIO_PORT: " << *argv[2] << std::endl;
    }else
    {
        //demande du port
        std::cout << "[LED_GPIO_PORT:A B C D] : " << std::flush;
        std::cin >> str;
        // créer le buffer port_letter pour copier la chaîne
        size_t size = str.size() + 1;
        strncpy( &port_letter, str.c_str(), size );
    }
    if(argc > 3)
    {
    	pin_num = atoi(argv[3]);
    }
    else
    {
        //demande de la pin
        std::cout << "[LED_PIN:0->31]: " << std::flush;
        std::cin >> pin_num;
    }
    if(argc > 4)
    {
        count = atoi(argv[4]);
    }
    if(argc > 5)
    {
        delay = atoi(argv[5]);
    }

    std::cout << "Toggling LED " << port_letter << pin_num << " " << count << " times" << " delai:" << delay << "us"  << std::endl;


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
	std::cout << "End Of APF-TEST" << std::endl;
}
