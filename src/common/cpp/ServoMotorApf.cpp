/*!
 * \file
 * \brief Implémentation de la classe ServoMotorApf.
 */

#include <fcntl.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include "ServoMotorApf.hpp"

pmx::ServoMotorApf::ServoMotorApf()
{
}

void
pmx::ServoMotorApf::setServoEnable(int servoID, int value)
{
    char operationFileName[1024];
    char data[16];
    int file;
    int ret;

    this->lock();

    sprintf(operationFileName, "%s%s%d/%s", SERVO_DRIVER_SYSFS_BASE, SERVO_DRIVER_SERVO_FILE, servoID, SERVO_DRIVER_SERVO_ENABLE_FILE);
    file = open(operationFileName, O_WRONLY);
    if (file == -1)
    {
        fprintf(stderr, "MotionServer setServoEnable: failed to open %s", operationFileName);

    }
    /* Keep the value */
    servoEnableBuffer[servoID] = value; //todo configuration file parser
    sprintf(data, "%d", value);
    ret = write(file, data, strlen(data));
    if (ret == -1)
    {
        fprintf(stderr, "MotionServer setServoEnable: failed to write in %s", operationFileName);

    }
    close(file);
    this->unlock();
}

void
pmx::ServoMotorApf::setServoOffset(int servoID, int value)
{
    printf("setServoOffset\n");
    char operationFileName[1024];
    char data[16];
    int file;
    int ret;

    this->lock();

    sprintf(operationFileName, "%s%s%d/%s", SERVO_DRIVER_SYSFS_BASE, SERVO_DRIVER_SERVO_FILE, servoID, SERVO_DRIVER_SERVO_OFFSET_FILE);
    file = open(operationFileName, O_WRONLY);
    if (file == -1)
    {
        fprintf(stderr, "MotionServer setServoOffset: failed to open %s", operationFileName);

    }
    /* Keep the value */
    servoOffsetBuffer[servoID] = value;
    sprintf(data, "%d", value);
    ret = write(file, data, strlen(data));
    if (ret == -1)
    {
        fprintf(stderr, "MotionServer setServoOffset: failed to write in %s", operationFileName);

    }
    close(file);

    this->unlock();
}

void
pmx::ServoMotorApf::setServoPosition(int servoID, int value)
{
    char operationFileName[1024];
    char data[16];
    int file;
    int ret;

    this->lock();

    sprintf(operationFileName, "%s%s%d/%s", SERVO_DRIVER_SYSFS_BASE, SERVO_DRIVER_SERVO_FILE, servoID, SERVO_DRIVER_SERVO_POSITION_FILE);
    file = open(operationFileName, O_WRONLY);
    if (file == -1)
    {
        fprintf(stderr, "MotionServer setServoPosition: failed to open %s", operationFileName);

    }
    /* Keep the value */
    servoPositionBuffer[servoID] = value;
    sprintf(data, "%d", value);
    ret = write(file, data, strlen(data));
    if (ret == -1)
    {
        fprintf(stderr, "MotionServer setServoPosition: failed to write in %s", operationFileName);

    }
    close(file);

    this->unlock();
}

int
pmx::ServoMotorApf::getServoPosition(int servoID)
{
    return servoPositionBuffer[servoID];
}

int
pmx::ServoMotorApf::getServoCurrentPosition(int )
{
    //cat /sys/class/servo/servo0/current_position

    unsigned int intValue = 0;


    this->lock();

    std::ifstream file( "/sys/class/servo/servo0/current_position" );
    if ( file ) // ce test échoue si le fichier n'est pas ouvert
    {
        /*
        std::string ligne; // variable contenant chaque ligne lue

        // cette boucle s'arrête dès qu'une erreur de lecture survient
        while ( std::getline( file, ligne ) )
        {
            // afficher la ligne à l'écran
            std::cout << ligne << std::endl;
        }*/

        std::stringstream buffer; // variable contenant l'intégralité du fichier
        // copier l'intégralité du fichier dans le buffer
        buffer << file.rdbuf();
        // nous n'avons plus besoin du fichier !
        file.close();
        // manipulations du buffer...
        std::cout << "Taille du buffer : " << buffer.str().size() << '\n';


        //conversion
        buffer >> intValue;

        this->unlock();

    }

    return intValue;
}

