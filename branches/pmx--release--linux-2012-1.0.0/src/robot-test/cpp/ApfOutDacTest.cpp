/*!
 * \file
 * \brief Implémentation de la classe ApfOutDacTest, utilisation du DAC de la carte DevLightV2.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <as_devices/as_max5821.h>
#include <unistd.h>
#include "ApfOutDacTest.hpp"

void test::ApfOutDacTest::run(int, char*[])
{
    struct as_max5821_device *max5821_dev;
    int ret;

    std::cout << "APF : Use DAC [A] & [B] Output on devLightV2 (As_devices):" << std::endl;

    max5821_dev = as_max5821_open(0, 0x38);
    if (max5821_dev == NULL)
    {
        logger().error() << "Error, can't open max5821" << utils::end;
        exit(0);
    }

    //powerup et ouverture du DAC
    ret = as_max5821_power(max5821_dev, 'a', MAX5821_POWER_UP);
    if (ret < 0)
    {
        logger().error() << "Error, can't DAC[A] power up" << utils::end;
        exit(0);
    }
    ret = as_max5821_power(max5821_dev, 'b', MAX5821_POWER_UP);
    if (ret < 0)
    {
        logger().error() << "Error, can't DAC[B] power up" << utils::end;
        exit(0);
    }

    //incrémentation du code moteur
    for(int i = 0; i < 1024 ; i++)
    {
        logger().info() << "setValues AB [" << i << "]" << utils::end;

        ret = as_max5821_set_one_value(max5821_dev, 'a', i);
        if (ret < 0)
        {
            logger().error() << "Error, can't select value" << utils::end;
            exit(0);
        }
        ret = as_max5821_set_one_value(max5821_dev, 'b', i);
        if (ret < 0)
        {
            logger().error() << "Error, can't select value" << utils::end;
            exit(0);
        }
        
        usleep(50000);
    }
    //remise à 0
    as_max5821_set_one_value(max5821_dev, 'a', 0);
    as_max5821_set_one_value(max5821_dev, 'b', 0);

    //fermeture du DAC
    ret = as_max5821_close(max5821_dev);
    if (ret < 0) {
        logger().error() << "Error on closing max5821_dev" << utils::end;
    }
}
