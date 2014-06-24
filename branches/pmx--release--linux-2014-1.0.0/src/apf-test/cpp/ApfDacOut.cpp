/*!
 * \file
 * \brief Implémentation de la classe ApfOutDacTest, utilisation du DAC de la carte DevLightV2.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "ApfDacOut.hpp"

#include <as_devices/as_max5821.h>
#include <as_devices/as_dac.h>

void test::ApfDacOut::run(int, char*[])
{

	struct as_dac_device *max5821_dev;
	float vRef = 2500;
	int ret;

	std::cout << "APF : Use DAC [A] & [B] Output on devLightV2 (As_devices):" << std::endl;

	//max5821_dev = as_max5821_open(0, 0x38);
	max5821_dev = as_dac_open(AS_MAX5821_TYPE, 0, 0x38, vRef);

	if (max5821_dev == NULL)
	{
		logger().error() << "Error, can't open max5821" << utils::end;
		exit(0);
	}

	//powerup et ouverture du DAC
	ret = as_dac_max5821_power(max5821_dev, 'A', MAX5821_POWER_UP);
	if (ret < 0)
	{
		logger().error() << "Error, can't DAC[A] power up" << utils::end;
		exit(0);
	}
	ret = as_dac_max5821_power(max5821_dev, 'B', MAX5821_POWER_UP);
	if (ret < 0)
	{
		logger().error() << "Error, can't DAC[B] power up" << utils::end;
		exit(0);
	}

	//incrémentation du code moteur
	for (int i = 0; i < 1024; i++)
	{
		logger().info() << "setValues AB [" << i << "]" << utils::end;

		ret = as_dac_set_value_in_millivolts(max5821_dev, 0, i);
		if (ret < 0)
		{
			logger().error() << "Error, can't select value" << utils::end;
			exit(0);
		}
		ret = as_dac_set_value_in_millivolts(max5821_dev, 1, i);
		if (ret < 0)
		{
			logger().error() << "Error, can't select value" << utils::end;
			exit(0);
		}

		/*
		 ret = as_dac_set_value_max5821(max5821_dev, 'A', i);
		 if (ret < 0)
		 {
		 logger().error() << "Error, can't select value" << utils::end;
		 exit(0);
		 }
		 ret = as_dac_set_value_max5821(max5821_dev, 'B', i);
		 if (ret < 0)
		 {
		 logger().error() << "Error, can't select value" << utils::end;
		 exit(0);
		 }*/

		usleep(50000);
	}
	//remise à 0
	as_dac_set_value_max5821(max5821_dev, 'A', 0);
	as_dac_set_value_max5821(max5821_dev, 'B', 0);

	//fermeture du DAC
	ret = as_dac_close(max5821_dev);
	if (ret < 0)
	{
		logger().error() << "Error on closing max5821_dev" << utils::end;
	}
}


