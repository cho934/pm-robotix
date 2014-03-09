/*!
 * \file
 * \brief Implémentation de la classe ApfSpiWithLs7366, utilisation des LS7366 sur les encodeurs.
 */

#include <iostream>

#include "ApfSpiWithLs7366.hpp"
//#include <as_devices/as_spi.h>
#include "Encoder.hpp"

void test::ApfSpiWithLs7366::run(int, char*[])
{
	std::cout << "APF : Use SPI Input on devLightV2 (As_devices)" << std::endl;


	Encoder *LeftEnc = new Encoder('B', 17);


	LeftEnc->initialize(0x02, 0x00); //x4 and 4 bytes


for(int i=0;i<200;i++)
{
	unsigned char status = LeftEnc->readStatus();
	std::cout << "encoder status = " << (int)status << std::endl;


	unsigned long counter = LeftEnc->readCounter();
	std::cout << "encoder counter = " << counter << std::endl;

	usleep(500000);
}

	/*
	int ret=0;
	int fd=0;
	long speed = 0;
	int bits = 0;
	int mode = 0;

	int lsb = 0;

	const  char *aSpidev_name = "/dev/spidev1.1";
	unsigned  char *d = (unsigned char*) aSpidev_name;

	fd =  as_spi_open(d);
	if (fd < 0)
	{
		std::cout << "Error, can't open SPI" << std::endl;
		exit(0);
	}

	speed = as_spi_get_speed(fd);
	std::cout << "spi speed = " << speed << std::endl;

	bits = as_spi_get_bits_per_word(fd);
	std::cout << "spi bits_per_word = " << bits << std::endl;

	mode = as_spi_get_mode(fd);
	std::cout << "spi mode = " << mode << std::endl;

	lsb = as_spi_get_lsb(fd);
	std::cout << "spi lsb = " << mode << std::endl;


	as_spi_close(fd);
*/

	std::cout << "End Of APF-TEST" << std::endl;
}
