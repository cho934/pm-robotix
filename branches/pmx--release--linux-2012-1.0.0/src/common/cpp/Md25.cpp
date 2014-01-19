/*!
 * \file
 * \brief Implémentation de la classe Elevator (Ascenceur).
 */

#include <stdlib.h>
#include "Md25.hpp"

int utils::Md25::getSoftwareVersion(void) {
    uint8_t val;
    readRegisterbyte(MD25_SOFTWAREVER_REG, &val);
    return val;
}

float utils::Md25::getBatteryVolts(void) {
    uint8_t val;
    readRegisterbyte(MD25_VOLTAGE_REG, &val);
    return (float)val / 10.0;
}

int utils::Md25::getAccelerationRate() {
    uint8_t val;
    readRegisterbyte(MD25_ACCELRATE_REG, &val);
    return val;
}

int utils::Md25::getMotor1Speed(void) {
    uint8_t val;
    readRegisterbyte(MD25_SPEED1_REG, &val);
    return val;
}

int utils::Md25::getMotor2Speed(void) {
    uint8_t val;
    readRegisterbyte(MD25_SPEED2_REG, &val);
    return val;
}

int utils::Md25::getMotor1Current(void) {
    uint8_t val;
    readRegisterbyte(MD25_CURRENT1_REG, &val);
    return val;
}

int utils::Md25::getMotor2Current(void) {
    uint8_t val;
    readRegisterbyte(MD25_CURRENT2_REG, &val);
    return val;
}

int utils::Md25::getMode(void) {
    uint8_t val;
    readRegisterbyte(MD25_MODE_REG, &val);
    return val;
}

int utils::Md25::getNbErrors(void) {
    return errorCount_;
}

int utils::Md25::getEncoder(long *pvalue, int MD25Register) {
    uint8_t encoder2;
    uint8_t encoder5;
    uint8_t encoder4;
    uint8_t encoder3;

    int err = readRegisterbyte(MD25Register, &encoder2);
    err += readRegisterbyte(MD25Register+1, &encoder3);
    err += readRegisterbyte(MD25Register+2, &encoder4);
    err += readRegisterbyte(MD25Register+3, &encoder5);

    *pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;

    logger().debug() << "MD25:getEncoder: " << MD25Register << " " << encoder5
            << " " << encoder4
            << " " << encoder3
            << " " << *pvalue
            << utils::end;

    return err;
}

long utils::Md25::ensureGetEncoder(long last, int MD25Register)
{
    long value = 0;
    int err = getEncoder(&value, MD25Register);
    if (err < 0 | (value > last + 100)) //filtrage par rapport à l'ancienne valeur
    {
        value = 0;
        int err2 = getEncoder(&value, MD25Register);
        if (err2 < 0 | (value > last + 100)) //filtrage par rapport à l'ancienne valeur
        {
            return last;
        }else
        {
            return value;
        }
    }else
    {
        return value;
    }
    return last;
}

void utils::Md25::setMode(uint8_t mode) {
    writeRegisterbyte(MD25_MODE_REG, mode);
    current_mode_ = mode;
}

void utils::Md25::setAccelerationRate(uint8_t rate) {
    writeRegisterbyte(MD25_ACCELRATE_REG, rate);
}

void utils::Md25::setCommand(uint8_t command) {
    writeRegisterbyte(MD25_CMD_REG, command);
}

void utils::Md25::setSpeedRegisters(int speed_1, int speed_2) {
    ensureSetSpeed(speed_1, MD25_SPEED1_REG);
    ensureSetSpeed(speed_2, MD25_SPEED2_REG);

}

void utils::Md25::ensureSetSpeed(int speed, int reg) {
    int err = setSpeedReg(speed, reg);
    if (err != 0)
    {
        logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (1) : err=" << err << utils::end;
        int err2 = setSpeedReg(speed, reg);
        if (err2 != 0)
        {
            logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (2) : err=" << err2 << utils::end;
        }
    }
}

int utils::Md25::setSpeedReg(int speed, int reg) {
    writeRegisterbyte(reg, (uint8_t) speed);
    uint8_t read;
    readRegisterbyte(reg, &read);
    if (current_mode_ == MD25_MODE_1 || current_mode_ == MD25_MODE_3) {
        if (speed >= 0) {
            if (speed == read) {
                return 0;
            }else {
                logger().error() << "setSpeedReg" << reg << " : write / read :" << speed << " / " << read << utils::end;
                return read;
            }
        }else {
            if ((speed + 256) == read) //decalage de 256 par rapport à la lecture.
            {
                return 0;
            }else {
                logger().error() << "setSpeedReg" << reg << " : write / read :" << speed << " / " << read << utils::end;
                return read;
            }
        }
    }else {
        if (speed == read) {
            return 0;
        }else {
            logger().error() << "setSpeedReg" << reg << " : write / read :" << speed << " / " << read << utils::end;
            return read;
        }
    }
}

int utils::Md25::stopMotor(int reg) {
    int ret;
    switch (current_mode_)
    {
        case MD25_MODE_0:
        case MD25_MODE_2:
            ret = writeRegisterbyte(reg, 128);
            break;
        case MD25_MODE_1:
        case MD25_MODE_3:
            ret = writeRegisterbyte(reg, 0);
            break;
    }
    return ret;
}

int utils::Md25::stopMotors(void) {
    int res1 = stopMotor(MD25_SPEED1_REG);
    if (res1 == 0)
        logger().debug() << "stopMotor1:ok" << utils::end;
    int tmp = 0;
    while (res1 < 0) //try 5 times
    {
        logger().error() << "apply stopMotor1: error" << utils::end;
        res1 = stopMotor(MD25_SPEED1_REG);
        if (res1 == 0)
            logger().debug() << "stopMotor1:ok" << utils::end;
        tmp++;
        if (tmp > 5) {
            logger().error() << "stopMotor1: error > 5" << utils::end;
            return -3;
        }
    }

    int res2 = stopMotor(MD25_SPEED2_REG);
    if (res2 == 0)
        logger().debug() << "stopMotor2:ok" << utils::end;
    tmp = 0;
    while (res2 < 0) //try 5 times
    {
        logger().error() << "apply stopMotor2: error" << utils::end;
        res2 = stopMotor(MD25_SPEED2_REG);
        if (res2 == 0)
            logger().debug() << "stopMotor2:ok" << utils::end;
        tmp++;
        if (tmp > 5) {
            logger().error() << "stopMotor2: error > 5" << utils::end;
            return -3;
        }
    }
    return 0;
}

void utils::Md25::changeAddress(uint8_t) //newAddress
{
    //TODO
    /*
     static byte command[] = { cmdReg, 0x0A };
     command[1] = 0x0A;
     sendWireCommand(command, 2);
     delay(6);
     command[1] = 0xAA;
     sendWireCommand(command, 2);
     delay(6);
     command[1] = 0xA5;
     sendWireCommand(command, 2);
     delay(6);
     command[1] = newAddress;
     sendWireCommand(command, 2);
     delay(6);*/
}

void utils::Md25::closeI2C(void) {
    lock();
    int result = as_i2c_close(fd_);
    unlock();
    if (result < 0) {
        logger().error() << "closeI2C: Can't close i2c bus num n°" << MD25_I2C_BUS << "!" << utils::end;
    }
}

void utils::Md25::openI2C(void) {
    lock();
    fd_ = as_i2c_open(MD25_I2C_BUS);
    unlock();
    if (fd_ < 0) {
        logger().error() << "openI2C: Can't open I2C port n°" << MD25_I2C_BUS << "!" << utils::end;
    }else {
        logger().debug() << "openI2C: Open I2C port n°" << MD25_I2C_BUS << " successful!" << utils::end;
    }
}

void utils::Md25::setI2Cslave(void) {
    lock();
    int result = as_i2c_set_slave(fd_, MD25_i2cAddress_);
    usleep(100); //fréq i2c à 100kHz : attente de l'application complète de la trame
    unlock();
    if (result < 0) {
        logger().error() << "setI2Cslave: Can't set i2c bus num n°" << MD25_i2cAddress_ << "!" << utils::end;
    }
}

/*
 * Private Methods
 */

int utils::Md25::readRegisterbyte(uint8_t reg, uint8_t* data) {
    lock();
    int ret = as_i2c_read_reg(fd_, MD25_i2cAddress_, reg, data, 1); //return 0 on success, -1 on write error (\e reg byte), -2 on read error.
    if (ret < 0) {
        errorCount_++;
        if (ret == -1)
            logger().error() << "as_i2c_read_reg_byte: reg " << reg << " WRITE error!" << utils::end;
        if (ret == -2)
            logger().error() << "as_i2c_read_reg_byte: reg " << reg << " READ error!" << utils::end;
    }else {
        errorCount_ = 0;
    }
    unlock();
    return ret;
}

int utils::Md25::writeRegisterbyte(uint8_t reg, uint8_t value) {
    lock();
    int result = as_i2c_write_reg_byte(fd_, MD25_i2cAddress_, reg, value);
    usleep(400); //fréq i2c à 100kHz : attente de l'application complète de la trame
    
    if (result < 0) {
        errorCount_++;
        logger().error() << "as_i2c_write_reg_byte: reg=" << (int) reg << " val=" << (int) value << " !" << utils::end;
    }else {
        errorCount_ = 0;
    }
    unlock();
    return result;
}
