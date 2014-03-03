/*!
 * \file
 * \brief Implémentation de la classe ApfSpiWithLs7366, utilisation des LS7366 sur les encodeurs.
 */

#include <iostream>

#include "ApfSpiWithLs7366.hpp"



void test::ApfSpiWithLs7366::run(int, char*[])
{
	std::cout << "APF : Use SPI Input on devLightV2 (As_devices)" << std::endl;

	int ret=0;
	int fd=0;
	long speed = 0;
	const  char *aSpidev_name = "/dev/spidev1.1";
	unsigned  char *d = (unsigned char*) aSpidev_name;

	fd =  as_spi_open(d);
	if (fd < 0)
	{
		std::cout << "Error, can't open SPI" << std::endl;
		exit(0);
	}

	speed = as_spi_get_speed(fd);
	std::cout << "spi speed : " << speed << std::endl;


	as_spi_close(fd);


	std::cout << "End Of APF-TEST" << std::endl;
}
