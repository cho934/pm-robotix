/*!
 * \file
 * \brief Implémentation de la classe ApfInAdcTest, utilisation des ADC de la carte DevLightV2.
 */

#include <iostream>
#include <string>
#include "ApfInAdcTest.hpp"
#include <stdio.h>
#include <math.h>
#include <as_devices/as_max1027.h>
#include <unistd.h>




void test::ApfInAdcTest::run(int argc, char *argv[])
{
    std::cout << "APFIN : Use ADC Input on devLightV2 (As_devices)" << std::endl;
    int ret, value, channel, model, temp_read, value_converted;
    struct as_max1027_device *max1027_dev;
    AS_max1027_mode mode = AS_MAX1027_SLOW;

    if (argc < 4)
    {
        std::cout << "USAGE: PMX_TEST " << argv[1] << " [channel:0-6] [model:30,80,150] " << std::endl;
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
        //demande du port
        std::cout << "[model:30,80,150] : " << std::flush;
        std::cin >> model;
    }

    //ouverture ADC
    max1027_dev = as_max1027_open(MAX1027_SPI_NUM, mode);
    if (max1027_dev == NULL)
    {
        std::cout << "Error, can't open max1027. Is max1027 modprobed ?" << std::endl;
        
    }
    //std::cout << "opened" << std::endl;

    ret = as_max1027_set_averaging(max1027_dev, 32);
    if (ret < 0)
    {
        printf("Error, can't set averaging\n");
    }    

    ret = as_max1027_get_value_milliVolt(max1027_dev, channel, &value);
    if (ret < 0) {
        printf("Error reading \n");
    }

    switch (model)
    {
    case 30: //SR short range, aka GP2D120 (4-30cm)
        value_converted = 93620.1 * pow(value, -0.949);
        break;
    case 80: //MR medium range, aka GP2D12 (10-80cm)
        value_converted = 845000 * pow(value, -1.15);
        break;
    case 150: //LR long range, aka GP2Y0A02YK (20-150cm)
        value_converted = 1353000 * pow(value, -1.112);
        break;
    }



    ret = as_max1027_read_temperature_mC(max1027_dev, &temp_read);
    if (ret < 0) {
        printf("Error reading temperature\n");
    }

    std::cout << "channel:" << channel << " mV:" << value << " temp_read:" << temp_read << " mm:" << value_converted << std::endl;

    //fermeture ADC
    ret = as_max1027_close(max1027_dev);
    if (ret < 0) {
        std::cout << "Error on closing max5821_dev" << std::endl;

    }
    //std::cout << "closed" << std::endl;
}
