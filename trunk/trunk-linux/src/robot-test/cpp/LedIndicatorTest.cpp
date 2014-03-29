/*!
 * \file
 * \brief Implémentation de la classe LedIndicatorTest.
 */

#include <iostream>
#include <cstdio>
#include "LedIndicatorTest.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/LedIndicator.hpp"

void robottest::LedIndicatorTest::run(int, char *[])
{
    std::cout << "LedIndicatorTest - Blink LedIndicator board" << std::endl;
  //  int timeout = 20*1000;//en us


    pmx::Robot robot;

    pmx::LedIndicator::instance().reset();



}

