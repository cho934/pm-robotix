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

pmx::ServoMotorApf::ServoMotorApf() {

    servoEnableBuffer = new int[NbMaxServo];
    servoMinBuffer = new int[NbMaxServo];
    servoMaxBuffer = new int[NbMaxServo];
    servoOffsetBuffer = new int[NbMaxServo];
    servoPositionBuffer = new int[NbMaxServo];
    for (int i = 0; i < NbMaxServo; i++) {
        servoEnableBuffer[i] = 0;
        servoMinBuffer[i] = 0;
        servoMaxBuffer [i] = 0;
        servoOffsetBuffer[i] = 0;
        servoPositionBuffer[i] = 0;
    }
}

char* getFilename(int servoId, std::string type) {
    char* name = new char[1024];
    memset(name, 0, 1024);
    sprintf(name, "%s%s%d/%s", SERVO_DRIVER_SYSFS_BASE, SERVO_DRIVER_SERVO_FILE, servoId, type.c_str());
    return name;
}

void
pmx::ServoMotorApf::setServoEnable(int servoID, int value) {
    if (servoID < 0) {
        logger().error() << "ERROR servoID<0 " << servoID << utils::end;
    }else if (servoID >= NbMaxServo) {
        logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">" << NbMaxServo << utils::end;
    }else {
        this->lock();
        char* operationFileName = getFilename(servoID,SERVO_DRIVER_SERVO_ENABLE_FILE);
        char data[16];

        logger().info() << "setServoEnable  servoID="
                << " value=" << value
                << " operationFileName=" << operationFileName
                << utils::end;



        int file = open(operationFileName, O_WRONLY);
        if (file == -1) {
            logger().error() << "MotionServer setServoEnable: failed to open  " << operationFileName << utils::end;
        }
        /* Keep the value */
        servoEnableBuffer[servoID] = value; //todo configuration file parser
        sprintf(data, "%d", value);
        int ret = write(file, data, strlen(data));
        if (ret == -1) {
            logger().error() << "MotionServer setServoEnable: failed to write in  " << operationFileName << utils::end;
        }
        close(file);
        delete operationFileName;
        this->unlock();
    }
}

void
pmx::ServoMotorApf::setServoOffset(int servoID, int value) {
    if (servoID < 0) {
        logger().error() << "ERROR servoID<0 " << servoID << utils::end;
    }else if (servoID >= NbMaxServo) {
        logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">" << NbMaxServo << utils::end;
    }else {
        this->lock();
        char* operationFileName = getFilename(servoID,SERVO_DRIVER_SERVO_OFFSET_FILE);
        char data[16];





        int file = open(operationFileName, O_WRONLY);
        if (file == -1) {
            logger().error() << "MotionServer setServoOffset: failed to open  " << operationFileName << utils::end;
        }
        /* Keep the value */
        servoOffsetBuffer[servoID] = value;
        sprintf(data, "%d", value);
        int ret = write(file, data, strlen(data));
        if (ret == -1) {
            logger().error() << "MotionServer setServoOffset: failed to write in " << operationFileName << utils::end;
        }
        close(file);
        delete operationFileName;
        this->unlock();
    }
}

void
pmx::ServoMotorApf::setServoPosition(int servoID, int value) {
    if (servoID < 0) {
        logger().error() << "ERROR servoID<0 " << servoID << utils::end;
    }else if (servoID >= NbMaxServo) {
        logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">" << NbMaxServo << utils::end;
    }else {
        this->lock();
        char* operationFileName = getFilename(servoID,SERVO_DRIVER_SERVO_POSITION_FILE);
        char data[16];
        int file;
        int ret;



        file = open(operationFileName, O_WRONLY);
        if (file == -1) {
            logger().error() << "MotionServer setServoPosition: failed to open " << operationFileName << utils::end;
        }else {


            /* Keep the value */
            servoPositionBuffer[servoID] = value;
            sprintf(data, "%d", value);
            ret = write(file, data, strlen(data));
            if (ret == -1) {
                logger().error() << "MotionServer setServoPosition: failed to write in " << operationFileName << utils::end;
            }
            close(file);
        }
        delete operationFileName;
        this->unlock();
    }
}

int
pmx::ServoMotorApf::getServoId(int servoID) {
    int result = -1;
    if (servoID < 0) {
        logger().error() << "ERROR servoID<0 " << servoID << utils::end;
    }else if (servoID >= NbMaxServo) {
        logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">" << NbMaxServo << utils::end;
    }else {
        result = servoPositionBuffer[servoID];
    }
    return result;
}

int
pmx::ServoMotorApf::getServoCurrentPosition(int servoID) {
    //cat /sys/class/servo/servo0/current_position
    int result = -1;
    if (servoID < 0) {
        logger().error() << "ERROR servoID<0 " << servoID << utils::end;
    }else if (servoID >= NbMaxServo) {
        logger().error() << "ERROR servoID>NbMaxServo " << servoID << ">" << NbMaxServo << utils::end;
    }else {
        this->lock();
        char* operationFileName = getFilename(servoID,SERVO_DRIVER_SERVO_CURRENT_POS);
        int intValue = 0;


        std::ifstream file(operationFileName);
        if (file.is_open()) // ce test échoue si le fichier n'est pas ouvert
        {
            if (file.good()) {
                std::string line;
                std::getline(file, line);
                intValue = atoi(line.c_str());
                logger().debug() << "OK getServoCurrentPosition : ok " << utils::end;
            }else {
                logger().error() << "ERROR getServoCurrentPosition : file not good " << utils::end;
            }
            file.close();

        }else {
            logger().error() << "ERROR getServoCurrentPosition : No file found " << utils::end;
        }
        delete operationFileName;
        this->unlock();

        result = intValue;
    }
    return result;
}

