/*!
 * \file
 * \brief Définition de la classe HostSerialBus, gestion du bus serial 2 pour APF9328.
 */

#ifndef HOSTSERIALBUS_HPP
#define HOSTSERIALBUS_HPP

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

namespace utils
{

class HostSerialBus
{
private:
	int fileDescriptor_;

public:
	int connect();
	int connect(const char * device);
	void disconnect(void);

	int sendArray(unsigned char *buffer, int len);
	int getArray(unsigned char *buffer, int len);

	int bytesToRead();
	void clear();
};
}

#endif
