/*!
 * \file
 * \brief Implémentation de la classe ApfInTest, Test d'une entrée par interruption "blocking read" de la carte DevLightV2.
 * 
 */

#include <iostream>
#include <fstream>
#include "ApfInTest.hpp"

std::string test::ApfInTest::INPUT_PORT_PATH = "/dev/gpio/P";
std::string test::ApfInTest::INPUT_PORT_PATH2 = "/proc/driver/gpio/port";

void test::ApfInTest::run(int argc, char *argv[])
{
    int fd_input, retval = 0, iomask = 0x00;
    unsigned short c = 0;

    // The gpio port (A, B, C or D)
    std::string inGpioPort;
    std::string inPin;

    std::cout << "APFIN  : Blocking read interruption on devLightV2 pad (with fstream) :" << std::endl;

    if (argc < 3)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [GPIO_PORT:A B C D] [GPIO_PIN:0...31]" << std::endl;
    }
    if (argc > 2)
    {
        inGpioPort = argv[2];
    }
    else
    {
        //demande du port
        std::cout << "[IN_GPIO_PORT:A B C D] : " << std::flush;
        std::cin >> inGpioPort;
    }
    if (argc > 3)
    {
        inPin = argv[3];
    }
    else
    {
        //demande de la pin
        std::cout << "[IN_PIN:0->31]: " << std::flush;
        std::cin >> inPin;
    }

    std::string filePort;
    filePort = INPUT_PORT_PATH.append(inGpioPort).append(inPin);

    logger().info() << "Blocking read by fstream :" << filePort << utils::end;

    //Open GPIO device for communication
    fd_input = open(filePort.c_str(), O_RDONLY);
    if (fd_input < 0)
    {
        printf("Open Failed : %s\n", filePort.c_str());
        exit(EXIT_FAILURE);
    }
    logger().debug() << "fd_input opened" << utils::end;


    logger().info() << "WARNING : Are you sure the pin mode/dir/irq are configured ?" << utils::end;
    //ex: pour la pin DE=PD18:
    //cat /proc/driver/gpio/portDmode | sed "s/[0-1]\([0-1]\{31\}\)$/1\1/" > /proc/driver/gpio/portDmode
    //cat /proc/driver/gpio/portDdir | sed "s/[0-1]\([0-1]\{31\}\)$/0\1/" > /proc/driver/gpio/portDdir
    //cat /proc/driver/gpio/portDirq | sed "s/[0-1]\([0-1]\{31\}\)$/1\1/" > /proc/driver/gpio/portDirq

    //cat /proc/driver/gpio/portAmode | sed "s/[0-1]\([0-1]\{4\}\)$/1\1/" > /proc/driver/gpio/portAmode
    //cat /proc/driver/gpio/portAdir | sed "s/[0-1]\([0-1]\{4\}\)$/0\1/" > /proc/driver/gpio/portAdir
    //cat /proc/driver/gpio/portAirq | sed "s/[0-1]\([0-1]\{4\}\)$/1\1/" > /proc/driver/gpio/portAirq

    //Set this process as owner of device file
    retval = fcntl(fd_input, F_SETOWN, getpid());
    if (retval < 0)
    {
        printf("F_SETOWN fails for%s\n", filePort.c_str());
        exit(EXIT_FAILURE);
    }

    std::string filePort2;
    filePort2 = INPUT_PORT_PATH2.append(inGpioPort);

    logger().debug() << "while" << utils::end;
    int nb = 0;
    std::fstream io;
    std::string value;

    while (1)
    {
        //detection front montant/descendant
        int nbbytes = read(fd_input, &c, 1); 

        io.open(filePort2.c_str(), std::fstream::in);

        io >> value;

        logger().info() << filePort << " : " << nb << " " << nbbytes << " " << c << " " << iomask << utils::end;
        //logger().info() << "    " << value << " - " << value[31-atoi(inPin.c_str())] << utils::end;
        logger().info() << "    " << value << " - IMPGD:" << value[6] << " - IMPDD:" << value[5] << utils::end;

        iomask ^= 1; //(iomask == 0x00)?0x01:0x00;
        nb++;
        io.close();
    }

    close(fd_input);
}
