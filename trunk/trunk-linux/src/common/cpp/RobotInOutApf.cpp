/*!
 * \file
 * \brief Implémentation de la classe pmx::RobotInOutApf
 */

#include <string>
#include <cstdlib>
#include <stdio.h>
#include <linux/ppdev.h>

#include "RobotInOutApf.hpp"


using namespace std;

#define GPIORDDIRECTION	_IOR(PP_IOCTL, 0xF0, int)
#define GPIOWRDIRECTION	_IOW(PP_IOCTL, 0xF1, int)
#define GPIORDDATA	_IOR(PP_IOCTL, 0xF2, int)
#define GPIOWRDATA	_IOW(PP_IOCTL, 0xF3, int)
#define GPIORDMODE	_IOR(PP_IOCTL, 0xF4, int)
#define GPIOWRMODE	_IOW(PP_IOCTL, 0xF5, int)


pmx::RobotInOutApf::RobotInOutApf() : IRobotInOut(), utils::Mutex()
{


}

