/*!
 * \file
 * \brief Implémentation de la classe ApfI2cTest, utilisation I²C de la carte DevLightV2.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "GroveColorTest.hpp"
#include "Chronometer.hpp"
#include "PositionManager.hpp"

void test::GroveColorTest::run(int argc, char *argv[])
{

    std::cout << "test::GroveColorTest: Start" << std::endl;

    if (argc < 6)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " " << std::endl;
    }

    //init setup TCS3414
    utils::Md25::instance().CMD(0);
    utils::Md25::instance().TCS3414Start(100,2000);

    while(1)
    {
        utils::Md25::instance().TCS3414Loop();

        usleep(300000); //todo a mettre en parametre avec le time d'execution
        
    }

    logger().info() << "End Of GroveColorTest"  << utils::end;

}
