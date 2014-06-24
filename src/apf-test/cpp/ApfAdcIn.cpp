/*!
 * \file
 * \brief Implémentation de la classe ApfAdcIn, utilisation des ADC de la carte DevLightV2.
 */

#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>

#include <cstdlib>
#include <unistd.h>


#include <as_devices/as_max1027_3_3.h>
#include "ApfAdcIn.hpp"

void test::ApfAdcIn::run(int argc, char *argv[])
{
	std::cout << "APF : Use ADC Input on devLightV2 (As_devices)" << std::endl;

	int model = 0;
	long ret;
	int value;
	int temperature = 0;
	int temp_read=0;
	struct as_max1027_device *max1027_dev;
	int channel = 0;
	AS_max1027_mode mode= AS_MAX1027_SLOW;


	if (argc < 4)
	{
		std::cout << "USAGE: APF_TEST " << argv[1]
				<< " [channel:0-6] [model:30,80,150]" << std::endl;
	}
	if (argc > 2)
	{
		channel = atoi(argv[2]);
	}
	else
	{
		//demande du port
		std::cout << "[channel:0-6] : " << std::flush;
		std::cin >> channel;
	}
	if (argc > 3)
	{
		model = atoi(argv[3]);
	}
	else
	{
		//demande du model
		std::cout << "[model:30,80,150] : " << std::flush;
		std::cin >> model;
	}


	    max1027_dev = as_max1027_open(MAX1027_SPI_NUM, mode);
	    if (max1027_dev == NULL)
	    {
	        printf("Error, can't open max1027. Is max1027 modprobed ?\n");
	        exit(1);
	    }

	    ret = as_max1027_read_temperature_mC(max1027_dev, &temp_read);
		if (ret < 0) {
			printf("Error reading temperature\n");
			exit(1);
		}
		temperature = temp_read;
		printf("Temperature read in miliC : %d\n", temperature);


		ret = as_max1027_set_averaging_3_3(max1027_dev, 32);
		if (ret < 0)
		{
		   printf("Error, can't set averaging\n");
		   exit(1);
		}


		ret = as_max1027_get_value_milliVolt(max1027_dev,
		                                                             channel,&value);
		if (ret < 0) {
			printf("Error reading \n");
			exit(1);
		}
		printf("Channel %d value read = %d ; cm = %d\n", channel, value, iRConvert2cm(value, model));


	    ret = as_max1027_close(max1027_dev);
		if (ret < 0) {
		   printf("Error on closing max1027\n");
		   exit(1);
		}


	std::cout << "End Of APF-TEST" << std::endl;
}


int test::ApfAdcIn::iRConvert2cm(int value, int model)
{
	switch (model)
	{
	case 30: //SR short range, aka GP2D120 (4-30cm)
		return 93620.1 * pow(value, -0.949);
		break;
	case 80: //MR medium range, aka GP2D12 (10-80cm)
		return 845000 * pow(value, -1.15);
		break;
	case 150: //LR long range, aka GP2Y0A02YK (20-150cm)
		return 1353000 * pow(value, -1.112);
		break;
	}
	return 0;
}
