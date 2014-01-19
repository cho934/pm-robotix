/*!
 * \file
 * \brief Implémentation de la classe MultiDemultiAllPinsTest, tests successifs de tous les multiplexeurs avec les demultiplexeurs.
 */

#include <iostream>
#include "MultiDemultiAllPinsTest.hpp"
#include "RobotInOutFactory.hpp"
#include "IRobotOut.hpp"
#include "IRobotIn.hpp"

using namespace std;
using namespace test;

void MultiDemultiAllPinsTest::run(int, char *[])
{
    std::cout << "IN/OUT : Nécessite de brancher le DM avec le M correspondant." << std::endl;
    std::cout << "Attention à l'inversion des pins 0->7 7->0 sur la carte." << std::endl;
    std::cout << std::endl;
    
    //initialisation de la sortie port // du robot
    pmx::IRobotOut * out = pmx::RobotInOutFactory::instance()->robotOut();
    pmx::IRobotIn * in = pmx::RobotInOutFactory::instance()->robotIn();
    
    std::cout << "   |";
    for (ushort pin = 0 ; pin < 8 ; pin++)
    {
        std::cout << " " << "Pin" << pin << "|";
    }
    std::cout << std::endl;
    
    std::cout << "   |";
    for (ushort pin = 0 ; pin < 8 ; pin++)
    {
        std::cout << " 1 0 |";
    }
    std::cout << std::endl;
    
    for (ushort mu = 0 ; mu < 6 ; mu++)
    {
        std::cout << "m" << mu << " |";
        for (ushort pin = 0 ; pin < 8 ; pin++)
        {
            //test du seuil haut
            out->setValue(mu, pin, true);
            
            bool result = in->getValue(mu, pin);
            if(result)
            {
                std::cout << " \e[1;34my\e[0m" << std::flush;
            }
            else
            {
                std::cout << " \e[1;31mN\e[0m" << std::flush;
            }
            usleep(100000);
            
            //test du seuil bas
            out->setValue(mu, pin, false);
            
            result = in->getValue(mu, pin);
            
            if(!result)
            {
                std::cout << " \e[1;34my\e[0m" << std::flush;
            }
            else
            {
                std::cout << " \e[1;31mN\e[0m" << std::flush;
            }
            usleep(100000);
            std::cout << " |";
        }
        std::cout << std::endl;
        usleep(500000);
    }
}
