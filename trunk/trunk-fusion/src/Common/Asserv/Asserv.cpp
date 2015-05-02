#include "Asserv.hpp"

#include "../../Log/Logger.hpp"

void Asserv::start()
{

	logger().debug("Asserv is started");
}

void Asserv::stop()
{
//TODO ramener motor et encoder sur asserv
	logger().debug("Asserv is stopped");
}
