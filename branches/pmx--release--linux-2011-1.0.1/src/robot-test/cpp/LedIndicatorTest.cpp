/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include <iostream>
#include "LedIndicatorTest.hpp"
#include "LedIndicator.hpp"

void test::LedIndicatorTest::run(int, char *[])
{
    std::cout << "LedIndicatorTest - Blink LedIndicator board" << std::endl;
    int timeout = 10*1000;//en us
    while (true)
    {
        for (int i = 0; i < 8; i++)
        {
            logger().info() << i << " on" << utils::end;
            pmx::LedIndicator::instance().setOn(i);
            usleep(timeout);
        }
        
        for (int i = 0; i < 8; i++)
        {
            logger().info() << i << " off" << utils::end;
            pmx::LedIndicator::instance().setOff(i);
            usleep(timeout);
        }
        std::cout << "Appuyer sur ENTREE" << std::endl;
        getchar();
    }
}

