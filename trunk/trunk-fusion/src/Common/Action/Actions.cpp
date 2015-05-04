#include "Actions.hpp"

#include <unistd.h>

#include "../../Log/Logger.hpp"

void Actions::start()
{
	//start action manager
	actionManager_.start("ActionManager");

	logger().debug("Actions is started");
}

void Actions::stop()
{
	//this->stopDevices();
	this->stopManagers(); // wait end of tasks in managers

	logger().debug("Actions is stopped");
}

void Actions::stopDevices()
{

}

void Actions::stopManagers()
{
	while (actionManager_.count() > 0) //TODO mettre un timeout !!
	{
		logger().debug() << actionManager_.count() << logs::end;
		usleep(50000);
	}
	actionManager_.stop();

	usleep(5000); //TODO  créer une Attente avec timeout de la fin de l'actionManager à la place du usleep
}
