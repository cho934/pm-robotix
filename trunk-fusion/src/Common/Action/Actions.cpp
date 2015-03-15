#include "Actions.hpp"

#include <unistd.h>

#include "../LogAppender/Logger.hpp"

void Actions::start()
{
	//start action manager
	actionManager_.start("ActionManager");

	logger().debug("Actions is started");
}

void Actions::stop()
{
	this->stopDevices();
	this->stopManagers();

	logger().debug("Actions is stopped");
}

void Actions::stopDevices()
{
	//this->ledBar().stop(true);
}

void Actions::stopManagers()
{
	actionManager_.stop();

	usleep(5000);//TODO  créer une Attente de la fin de l'actionManager à la place du usleep
}
