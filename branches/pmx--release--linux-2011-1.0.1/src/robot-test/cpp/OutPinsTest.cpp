/*!
 * \file
 * \brief Implémentation de la classe OutPinsTest.
 */

#include <iostream>
#include "OutPinsTest.hpp"
#include "RobotInOutFactory.hpp"
#include "IRobotOut.hpp"

void test::OutPinsTest::run(int argc, char *argv[])
{
    int pin, dm;
    int count = 4; //par defaut
    int delay = 100000; //par defaut en us

    std::cout << "OUT : Clignote un pin de sortie DM :" << std::endl;

    if(argc < 3)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [DM:0...7] [PIN:0...7] [count:4 times] [delay:100000us]" << std::endl;
    }
    if(argc > 2)
    {
        dm = atoi(argv[2]);
    }else
    {
        //demande du DM
        std::cout << "[DM:0...7]: " << std::flush;
        std::cin >> dm;
    }

    if(argc > 3)
    {
        pin = atoi(argv[3]);
    }
    else
    {
        //demande de la pin
        std::cout << "[PIN:0...7]: " << std::flush;
        std::cin >> pin;
    }
    
    if(argc > 4)
    {
        count = atoi(argv[4]);
    }

    if(argc > 5)
    {
        delay = atoi(argv[5]);
    }

    logger().info() << "Toggling LED DM:" << dm << " pin:" << pin << ", " << count << " times"<< ", with " << delay << "us delay" << utils::end;

    //initialisation de la sortie port // du robot
    pmx::IRobotOut * out = pmx::RobotInOutFactory::instance()->robotOut();
    
    /* Blink the LED */
    for (int i = 0; i < count; i++)
    {
        out->setValue(dm, pin, 1);
        usleep(delay);
        out->setValue(dm, pin, 0);
        usleep(delay);
    }
}
