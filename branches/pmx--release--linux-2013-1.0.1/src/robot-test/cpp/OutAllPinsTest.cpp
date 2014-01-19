/*!
 * \file
 * \brief Implémentation de la classe OutAllPinsTest, teste des démultiplexeurs (pour les sorties).
 */

#include <iostream>
#include "OutAllPinsTest.hpp"
#include "RobotInOutFactory.hpp"
#include "IRobotOut.hpp"

void test::OutAllPinsTest::drawLine(int dm, int nPin, bool state)
{
    std::cout << "dm" << dm << " ";
    
    for (int i=0 ; i<8 ; i++)
    {
        if (i == nPin)
        {
            std::cout << " \e[1;04;34m"<< state <<"\e[0m ";
        }
        else
        {
            std::cout << " 0 ";
        }
    }
    std::cout << std::flush;
}

void test::OutAllPinsTest::run(int, char *[])
{
    std::cout << "OUT : Pour chaque DM, applique un 1 puis un 0 à chaque pin par ordre croissant puis décroissant." << std::endl;

    //initialisation de la sortie port // du robot
    pmx::IRobotOut * out = pmx::RobotInOutFactory::instance()->robotOut();
    
    std::cout << "   ";
    for (int pin = 0 ; pin < 8 ; pin++)
    {
        std::cout << " pin" << pin;
    }
    std::cout << std::endl;
    
    //test de tous les pin de tous les DM
    for (int dm = 0 ; dm < 8 ; dm++)
    {
        logger().debug() << "DM:" << dm << utils::end;
        out->setValues(dm, 0x00);
        //incrémentation du mot sur le DM
        for (int pin = 0 ; pin < 8 ; pin++)
        {
            logger().debug() << "DM:" << dm << " PIN:" << pin << utils::end;
            for (int state = 1 ; state >= 0 ; state--)
            {
                drawLine(dm, pin, state);
                out->setValue(dm, pin, state);
                usleep(100000);
                std::cout << "\r" << std::flush;
            }
        }
        
        //décrémentation du mot sur le DM
        for (int pin = 7 ; pin >= 0 ; pin--)
        {
            logger().debug() << "DM:" << dm << " PIN:" << pin << utils::end;
            for (int state = 1 ; state >= 0 ; state--)
            {
                drawLine(dm, pin, state);
                out->setValue(dm, pin, state);
                usleep(100000);
                std::cout << "\r" << std::flush;
            }
        }
        
        drawLine(dm, 9, false);
        std::cout << std::endl;
    }
}
