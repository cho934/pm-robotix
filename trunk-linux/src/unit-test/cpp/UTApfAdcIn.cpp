/*!
 * \file
 * \brief Implémentation de la classe UTApfAdcIn, utilisation des ADC de la carte DevLightV2.
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

#include <as_devices/as_max1027.h>
#include <as_devices/as_adc.h>
#include "UTApfAdcIn.hpp"


void test::UTApfAdcIn::run(int argc, char *argv[])
{
    std::cout << "APF : Use ADC Input on devLightV2 (As_devices)" << std::endl;
    int ret, channel, model ;
    long value, value_converted;
    //int temp_read;
    struct as_adc_device *max1027_dev;
    float vRef = 2500;


    if (argc < 4)
    {
        std::cout << "USAGE: UNIT_TEST " << argv[1] << " [channel:0-6] [model:30,80,150]" << std::endl;
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

    //ouverture ADC
    max1027_dev = as_adc_open(AS_MAX1027_NAME, channel, vRef);
    if (max1027_dev < 0)
    {
        std::cout << "Error, can't open max1027. Is max1027 modprobed ?" << std::endl;

    }


/*
    ret = as_max1027_set_averaging(max1027_dev, 32);
    if (ret < 0)
    {
        printf("Error, can't set averaging\n");
    }    */


    value = as_adc_get_value_in_millivolts(max1027_dev, channel);
    if (value < 0) {
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


/*
    ret = as_max1027_read_temperature_mC(max1027_dev, &temp_read);
    if (ret < 0) {
        printf("Error reading temperature\n");
    }
*/
    //std::cout << "channel:" << channel << " mV:" << value << " temp_read:" << temp_read << " mm:" << value_converted << std::endl;
    std::cout << "channel:" << channel << " mV:" << value  << " mm:" << value_converted << std::endl;

    //fermeture ADC
    ret = as_adc_close(max1027_dev);
    if (ret < 0) {
        std::cout << "Error on closing max5821_dev" << std::endl;
    }
}
