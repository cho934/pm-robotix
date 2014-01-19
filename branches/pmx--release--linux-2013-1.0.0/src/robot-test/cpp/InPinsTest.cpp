/*!
 * \file
 * \brief Implémentation de la classe InPinsTest.
 */

#include <iostream>
#include <cstdlib>
#include "InPinsTest.hpp"
#include "RobotInOutFactory.hpp"
#include "IRobotIn.hpp"

void test::InPinsTest::run(int argc, char *argv[])
{
    std::cout << "IN : Test getValue via multiplexage" << std::endl;
    bool inValue, inValuePast;
    std::string inPin, inMu;
    long i = 0;

    pmx::IRobotIn * in = pmx::RobotInOutFactory::instance()->robotIn();

    if(argc < 3)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] <<" [MU:0...5] [PIN:0...7]" << std::endl;
    }
    if(argc > 2)
    {
        inMu = argv[2];
    }
    else
    {
        //demande du port
        std::cout << "[IN_M:0->5] : " << std::flush;
        std::cin >> inMu;
    }
    if(argc > 3)
    {
        inPin = argv[3];
    }
    else
    {
        //demande de la pin
        std::cout << "[IN_PIN:0->7]: " << std::flush;
        std::cin >> inPin;
    }

    while(1)
    {
        inValue = in->getValue(atoi(inMu.c_str()), atoi(inPin.c_str()));
        if(inValuePast != inValue)
        {
            std::cout << i << " MU:" << atoi(inMu.c_str()) << " Pin:" << atoi(inPin.c_str()) << " Value:" << inValue << std::endl;
            i++;
        }
        inValuePast = inValue;
    }
}
