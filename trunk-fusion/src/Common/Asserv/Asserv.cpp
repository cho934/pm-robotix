#include "Asserv.hpp"

#include <unistd.h>

#include "../LogAppender/Logger.hpp"

void Asserv::start()
{

	logger().debug("Asserv is started");
}

void Asserv::stop()
{

	logger().debug("Asserv is stopped");
}
