#include "RedCarpetSystem.hpp"

#include <unistd.h>

#include "../../Log/Logger.hpp"
#include "../Action.Driver/AServoDriver.hpp"
#include "Actions.hpp"

using namespace std;

RedCarpetSystem::RedCarpetSystem(Actions & actions) :
		AActionsElement(actions)
{
	servodriver = AServoDriver::create();
	releaseAll();
}

RedCarpetSystem::~RedCarpetSystem()
{
	servodriver->setPosition(LEFT_CARPET, 0);
	servodriver->setPosition(RIGHT_CARPET, 0);
	releaseAll();
}

void RedCarpetSystem::leftDeploy(int debug)
{
	holdLeft();
	servodriver->setPosition(LEFT_CARPET, 0);
	usleep(400000);
	servodriver->setPosition(LEFT_CARPET, 75);
	sleep(1);
	if (!debug)
	{
		servodriver->setPosition(LEFT_CARPET, 0);
		sleep(1);
	}
	releaseLeft();
}

void RedCarpetSystem::rightDeploy(int debug)
{
	holdRight();
	servodriver->setPosition(RIGHT_CARPET, 0);
	usleep(400000);
	servodriver->setPosition(RIGHT_CARPET, 70);
	sleep(1);
	if (!debug)
	{
		servodriver->setPosition(RIGHT_CARPET, 0);
		sleep(1);
	}
	releaseRight();
}

void RedCarpetSystem::releaseLeft()
{
	servodriver->release(LEFT_CARPET);
}
void RedCarpetSystem::releaseRight()
{
	servodriver->release(RIGHT_CARPET);
}

void RedCarpetSystem::holdLeft()
{
	servodriver->hold(LEFT_CARPET);
}
void RedCarpetSystem::holdRight()
{
	servodriver->hold(RIGHT_CARPET);
}

void RedCarpetSystem::releaseAll()
{
	releaseLeft();
	releaseRight();
}
void RedCarpetSystem::holdAll()
{
	holdLeft();
	holdRight();
}
