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
}

RedCarpetSystem::~RedCarpetSystem()
{
	servodriver->setPosition(1, 0);
}

void RedCarpetSystem::leftDeploy()
{
	holdLeft();
	servodriver->setPosition(1, 60);
	sleep(1);
	servodriver->setPosition(1, 0);
	sleep(1);
	releaseLeft();
}

void RedCarpetSystem::rightDeploy()
{
	holdRight();
	servodriver->setPosition(8, 60);
	sleep(1);
	servodriver->setPosition(8, 0);
	sleep(1);
	releaseRight();
}

void RedCarpetSystem::releaseLeft()
{
	servodriver->release(1);
}
void RedCarpetSystem::releaseRight()
{
	servodriver->release(8);
}

void RedCarpetSystem::holdLeft()
{
	servodriver->hold(1);
}
void RedCarpetSystem::holdRight()
{
	servodriver->hold(8);
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
