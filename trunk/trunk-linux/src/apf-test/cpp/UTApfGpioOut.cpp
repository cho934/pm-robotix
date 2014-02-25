/*!
 * \file
 * \brief Implémentation de la classe UTApfGpioOut, Clignotement d'une sortie (ou pad) de la carte DevLightV2.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/ppdev.h>

#include "UTApfGpioOut.hpp"

void test::UTApfGpioOut::run(int argc, char *argv[])
{
    using std::string;
    char *ledGpioPort;
    char *filePort;
    string str;
    int ledPin;
    int fd;
    int portval;
    int count = 4; //par defaut
    int delay = 1000000; //par defaut
    
    std::cout << "APF : Blink GPIO out on devLightV2 (with ioctl) :" << std::endl;

    if(argc < 3)
    {
        std::cout << "USAGE: UNIT_TEST " << argv[1] <<" [GPIO_PORT:A B C D] [GPIO_PIN:0...31] [count:4 times (default)] [delay:100000us (default)]" << std::endl;
    }
    if(argc > 2)
    {
        ledGpioPort = argv[2];
        //std::cout << "LED_GPIO_PORT: " << *argv[2] << std::endl;
    }else
    {
        //demande du port
        std::cout << "[LED_GPIO_PORT:A B C D] : " << std::flush;
        std::cin >> str;
        // créer le buffer ledGpioPort pour copier la chaîne
        size_t size = str.size() + 1;
        ledGpioPort = new char[ size ];
        // copier la chaîne dans le char*
        strncpy( ledGpioPort, str.c_str(), size );
    }
    if(argc > 3)
    {
        ledPin = atoi(argv[3]);
    }
    else
    {
        //demande de la pin
        std::cout << "[LED_PIN:0->31]: " << std::flush;
        std::cin >> ledPin;
    }
    if(argc > 4)
    {
        count = atoi(argv[4]);
    }
    if(argc > 5)
    {
        delay = atoi(argv[5]);
    }
    logger().info() << "Toggling LED " << LED_GPIO_PORT_PATH << ledGpioPort << ledPin << " " << count << " times" << " delai:" << delay << "us" << utils::end;

    filePort = (char *)malloc((strlen(LED_GPIO_PORT_PATH) + strlen(ledGpioPort) + 1)
                         *sizeof(char));
    strcpy(filePort, LED_GPIO_PORT_PATH);
    strcat(filePort, ledGpioPort);
    logger().info() << "Opening " << filePort << utils::end;
    if ((fd = open(filePort, O_RDWR)) < 0)
    {
        perror("Error Opening filePort");
        exit(1);
    }

    /* Set LED PIN as GPIO; read/modify/write */
    ioctl(fd, GPIORDMODE, &portval);
    portval |= (1 << ledPin);
    ioctl(fd, GPIOWRMODE, &portval);

    /* Set LED GPIO as output; read/modify/write */
    ioctl(fd, GPIORDDIRECTION, &portval);
    portval |= (1 << ledPin);
    ioctl(fd, GPIOWRDIRECTION, &portval);

    /* Blink the LED */
    for (int i = 0; i < count; i++)
    {
        logger().debug() << "Led OFF" << utils::end; /* pin <- 0 */
        ioctl(fd, GPIORDDATA, &portval);
        portval &= ~(1 << ledPin);
        ioctl(fd, GPIOWRDATA, &portval);

        usleep(delay);

        logger().debug() << "Led ON" << utils::end; /* pin <- 1 */
        ioctl(fd, GPIORDDATA, &portval);
        portval |= (1 << ledPin);
        ioctl(fd, GPIOWRDATA, &portval);

        usleep(delay);
    }

    close(fd);

}
