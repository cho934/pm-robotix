/*!
 * \file
 * \brief Implémentation de la classe Elevator (Ascenceur).
 */

#include <stdlib.h>
#include "Md25.hpp"

uint8_t TCS3414values[4]; // [Clear,Red,Green,Blue]
float TCS3414medium[4]; // [Clear,Red,Green,Blue]
float TCS3414mediate[4]; // [Clear,Red,Green,Blue]
float ColorTemperature = 0;

// SET the integration time here. Higher times allow for higher values with better precicion.
int integrationtime = 12; //12 == 12ms, 100 = 100ms, 400 = 400ms. Other values are note accepted
int loopdelay = integrationtime; //loop delay depends on the integration time

bool debug = false; //change to true if you want to see the various debug serial output bits
bool percentageEnabled = false; //enable/disable the percentage mode
bool compensateEnabled = false; //enable/disable color compensation of the sensor sensitivity per color


int utils::Md25::getSoftwareVersion(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_SOFTWAREVER_REG, &val);
    return val;
}

float utils::Md25::getBatteryVolts(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_VOLTAGE_REG, &val);
    return (float) val / 10.0;
}

int utils::Md25::getAccelerationRate() {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_ACCELRATE_REG, &val);
    return val;
}

int utils::Md25::getMotor1Speed(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_SPEED1_REG, &val);
    return val;
}

int utils::Md25::getMotor2Speed(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_SPEED2_REG, &val);
    return val;
}

int utils::Md25::getMotor1Current(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_CURRENT1_REG, &val);
    return val;
}

int utils::Md25::getMotor2Current(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_CURRENT2_REG, &val);
    return val;
}

int utils::Md25::getMode(void) {
    uint8_t val;
    readRegisterbyte(MD25_i2cAddress_, MD25_MODE_REG, &val);
    return val;
}

int utils::Md25::getNbErrors(void) {
    return errorCount_;
}

int utils::Md25::getEncoder(long *pvalue, uint8_t MD25Register) {
    uint8_t encoder2;
    uint8_t encoder5;
    uint8_t encoder4;
    uint8_t encoder3;

    int err = readRegisterbyte(MD25_i2cAddress_, MD25Register, &encoder2);
    err += readRegisterbyte(MD25_i2cAddress_, MD25Register + 1, &encoder3);
    err += readRegisterbyte(MD25_i2cAddress_, MD25Register + 2, &encoder4);
    err += readRegisterbyte(MD25_i2cAddress_, MD25Register + 3, &encoder5);

    *pvalue = (encoder2 << 24) + (encoder3 << 16) + (encoder4 << 8) + encoder5;

    logger().debug() << "MD25:getEncoder: " << MD25Register << " " << encoder5
            << " " << encoder4
            << " " << encoder3
            << " " << *pvalue
            << utils::end;
    
    return err;
}

long utils::Md25::ensureGetEncoder(long last, uint8_t MD25Register) {
    long value = 0;
    int err = getEncoder(&value, MD25Register);
    if (err < 0 || value > last + 100) //filtrage par rapport à l'ancienne valeur
    {
        value = 0;
        int err2 = getEncoder(&value, MD25Register);
        if (err2 < 0 || value > last + 100) //filtrage par rapport à l'ancienne valeur
        {
            return last;
        }else {
            return value;
        }
    }else {
        return value;
    }
    return last;
}

void utils::Md25::setMode(uint8_t mode) {
    writeRegisterbyte(MD25_i2cAddress_, MD25_MODE_REG, mode);
    current_mode_ = mode;
}

void utils::Md25::setAccelerationRate(uint8_t rate) {
    writeRegisterbyte(MD25_i2cAddress_, MD25_ACCELRATE_REG, rate);
}

void utils::Md25::setCommand(uint8_t command) {
    writeRegisterbyte(MD25_i2cAddress_, MD25_CMD_REG, command);
}

void utils::Md25::setSpeedRegisters(uint8_t speed_1, uint8_t speed_2) {
    ensureSetSpeed(speed_1, MD25_SPEED1_REG);
    ensureSetSpeed(speed_2, MD25_SPEED2_REG);

}

void utils::Md25::ensureSetSpeed(uint8_t speed, uint8_t reg) {
    int err = setSpeedReg(speed, reg);
    if (err != 0) {
        logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (1) : err=" << err << utils::end;
        int err2 = setSpeedReg(speed, reg);
        if (err2 != 0) {
            logger().info() << "setSpeed1Reg, value=" << speed << " not applied, write again (2) : err=" << err2 << utils::end;
        }
    }
}

int utils::Md25::setSpeedReg(uint8_t speed, uint8_t reg) {
    uint8_t read;

    writeRegisterbyte(MD25_i2cAddress_, reg, speed);
    
    readRegisterbyte(MD25_i2cAddress_, reg, &read);
    //if (current_mode_ == MD25_MODE_1 || current_mode_ == MD25_MODE_3) {
        //if (speed >= 0) {
            if (speed == read) {
                return 0;
            }else {
                logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read << utils::end;
                return read;
            }
        //}else {
        //    if ((speed + 256) == read) //decalage de 256 par rapport à la lecture.
        //    {
        //        return 0;
        //    }else {
        //        logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read << utils::end;
        //        return read;
        //    }
        //}
    //}else {
    //    if (speed == read) {
    //        return 0;
    //    }else {
    //        logger().error() << "setSpeedReg" << (int) reg << " : write / read :" << (int) speed << " / " << (int) read << utils::end;
    //        return read;
    //    }
    //}
}

int utils::Md25::stopMotor(uint8_t reg) {
    int ret;
    switch (current_mode_)
    {
        case MD25_MODE_0:
        case MD25_MODE_2:
            ret = writeRegisterbyte(MD25_i2cAddress_, reg, 128);
            break;
        case MD25_MODE_1:
        case MD25_MODE_3:
            ret = writeRegisterbyte(MD25_i2cAddress_, reg, 0);
            break;
    }
    return ret;
}

int utils::Md25::stopMotors(void) {
    int res1 = stopMotor(MD25_SPEED1_REG);
    //if (res1 == 0)
        //logger().debug() << "stopMotor1:ok" << utils::end;
    int tmp = 0;
    while (res1 < 0) //try 5 times
    {
        logger().error() << "apply stopMotor1: error" << utils::end;
        res1 = stopMotor(MD25_SPEED1_REG);
        //if (res1 == 0)
        //    logger().debug() << "stopMotor1:ok" << utils::end;
        tmp++;
        if (tmp > 5) {
            logger().error() << "stopMotor1: error > 5" << utils::end;
            return -3;
        }
    }

    int res2 = stopMotor(MD25_SPEED2_REG);
    //if (res2 == 0)
    //    logger().debug() << "stopMotor2:ok" << utils::end;
    tmp = 0;
    while (res2 < 0) //try 5 times
    {
        logger().error() << "apply stopMotor2: error" << utils::end;
        res2 = stopMotor(MD25_SPEED2_REG);
        //if (res2 == 0)
            //logger().debug() << "stopMotor2:ok" << utils::end;
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
    usleep(100000);
}

void utils::Md25::setI2Cslave(void) {
    int result = 0;

    lock();
    result = as_i2c_set_slave(fd_, MD25_i2cAddress_);
    usleep(5000); //fréq i2c à 100kHz : attente de l'application complète de la trame
    unlock();
    if (result < 0) {
        logger().error() << "setI2Cslave: Can't set i2c bus num n°" << MD25_i2cAddress_ << "!" << utils::end;
    }

    lock();
    result = as_i2c_set_slave(fd_, groveColorSensor_i2cAddress_);
    usleep(5000); //fréq i2c à 100kHz : attente de l'application complète de la trame
    unlock();
    if (result < 0) {
        logger().error() << "setI2Cslave: Can't set i2c bus num n°" << groveColorSensor_i2cAddress_ << "!" << utils::end;
    }
}

/*
 * Private Methods
 */

int utils::Md25::readRegisterbyte(uint8_t adr, uint8_t reg, uint8_t* data) {
    lock();
    int ret = as_i2c_read_reg(fd_, adr, reg, data, 1); //return 0 on success, -1 on write error (\e reg byte), -2 on read error.
    if (ret < 0) {
        errorCount_++;
        if (ret == -1)
            logger().error() << "as_i2c_read_reg_byte: reg " << (int) reg << " WRITE error!" << utils::end;
        if (ret == -2)
            logger().error() << "as_i2c_read_reg_byte: reg " << (int) reg << " READ error!" << utils::end;
    }else {
        errorCount_ = 0;
    }
    unlock();
    return ret;
}

int utils::Md25::writeRegisterbyte(uint8_t adr, uint8_t reg, uint8_t value) {
    //logger().error() << "as_i2c_write_reg_byte: adr=" << (int) adr << utils::end;
    lock();
    int result = as_i2c_write_reg_byte(fd_, adr, reg, value);
    
    if (result < 0) {
        errorCount_++;
        logger().error() << "as_i2c_write_reg_byte: reg=" << (int) reg << " val=" << (int) value << " !" << utils::end;
    }else {
        errorCount_ = 0;
    }
    //usleep(1000); //fréq i2c à 100kHz : attente de l'application complète de la trame

    unlock();
    return result;
}

void utils::Md25::CMD(int delayTime){

    if(percentageEnabled){
        logger().info() << "TSC3414 Percentage mode ON"  << utils::end;
      }else{
        logger().info() << "TSC3414 Percentage mode OFF"  << utils::end;
      }

    if(compensateEnabled){
        logger().info() << "TSC3414 Color compensation mode ON"  << utils::end;
      }else{
        logger().info() << "TSC3414 Color compensation mode OFF"  << utils::end;
      }

    usleep(delayTime * 1000);


  /*Serial.println("=========== Command list ===========");
  Serial.println("\'                                  \'");
  Serial.println("  ? == Show this command list");
  Serial.println("");
  Serial.println("  p == pause for 5 seconds (stackable)");
  Serial.println("");
  Serial.println("  1 == Enable Percentage mode");
  Serial.println("  0 == Disable Percentage mode");
  Serial.print("  Percentage mode is currently: ");
  if(percentageEnabled){
    Serial.println("ON");
  }else{
    Serial.println("OFF");
  }
  Serial.println("");
  Serial.println("  c == Enable Color compensation mode");
  Serial.println("  n == Disable Color compensation mode");
  Serial.print("  Color compensation mode is currently: ");
  if(compensateEnabled){
    Serial.println("ON");
  }else{
    Serial.println("OFF");
  }
  Serial.println("\'                                  \'");
  Serial.println("====================================");
  delay(delayTime);*/
}

/*
 * ======================================================
 * Serial command-line interface functions - optional
 * ======================================================
*/
void utils::Md25::getSerialCommands(){


  /*if(Serial.available() > 0){
    int receive_command = Serial.read();
    if(receive_command == 49){//49 == 1
      Serial.println("Percentage enabled, max value (100%) set to current medium");
      percentageEnabled = true;//enables/disables percentage mode.
      for(int o = 0; o < 4; o++){
        TCS3414medium[o] = TCS3414mediate[o];
      }
    }else if(receive_command == 48){//48 == 0
      Serial.println("Percentage disabled");
      percentageEnabled = false;//enables/disables percentage mode.
    }else if(receive_command == 63){//63 == ?
      CMD(2000);
    }else if(receive_command == 112){//112 == p
      Serial.println("pausing for 5 seconds (stackable)...");
      delay(5000);
      getSerialCommands();
    }else if(receive_command == 99){//99 == c
      Serial.println("Color compensation enabled");
      compensateEnabled = true;
    }else if(receive_command == 110){//110 == n
      Serial.println("Color compensation disabled");
      compensateEnabled = false;
    }else{
      Serial.print("The command entered ( ");
      Serial.print(receive_command);
      Serial.println(" ) was NOT found in the command list");
    }
  }*/
}

/*** Gets the blue sensor value and returns an unsigned int ***/
uint8_t utils::Md25::TSC3414Blue(){

    uint8_t blueLow = 0;
    uint8_t blueHigh = 0;
    int ret = 0;
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x94, &blueLow); //read Clear register
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x95, &blueHigh); //read Clear register

    logger().info() << "blueLow: " << (int) blueLow << " \tblueHigh: " << (int) blueHigh
          << utils::end;
    blueHigh = (blueHigh * 256) + blueLow;

    return blueHigh;
  /*unsigned int blueLow = 0;
  unsigned int blueHigh = 0;
  Wire.beginTransmission(0x39); //0011 1001 //+0 for write
  Wire.write(0xB4); //1011 0100 //read Blue register
  Wire.endTransmission();

  Wire.beginTransmission(0x39); //Request information
  Wire.requestFrom(0x39,2); //0011 1001 //+1 for read
  blueLow = Wire.read();
  blueHigh = Wire.read();
  Wire.endTransmission();

  if(debug){
    Serial.print("blueH:  ");
    Serial.print(blueHigh);
    Serial.print("  blueL:  ");
    Serial.print(blueLow);
  }

  blueHigh = (blueHigh * 256) + blueLow;

  if(debug){
    Serial.print("  blueF:  ");
    Serial.println(blueHigh);
  }
  return blueHigh;*/
}

/*** Gets the green sensor value and returns an unsigned int ***/
uint8_t utils::Md25::TSC3414Green(){

    uint8_t greenLow = 0;
    uint8_t greenHigh = 0;
    int ret = 0;
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x90, &greenLow); //read Clear register
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x91, &greenHigh); //read Clear register

    logger().info() << "greenLow: " << (int) greenLow << " \tgreenHigh: " << (int) greenHigh
          << utils::end;
    greenHigh = (greenHigh * 256) + greenLow;

    return greenHigh;
  /*unsigned int greenLow = 0;
  unsigned int greenHigh = 0;
  Wire.beginTransmission(0x39); //0011 1001 //+0 for write
  Wire.write(0xB0); //1011 0000 //read Green register
  Wire.endTransmission();

  Wire.beginTransmission(0x39); //Request information
  Wire.requestFrom(0x39,2); //0011 1001 //+1 for read
  greenLow = Wire.read();
  greenHigh = Wire.read();
  Wire.endTransmission();

  if(debug){
    Serial.print("greenH: ");
    Serial.print(greenHigh);
    Serial.print("  greenL: ");
    Serial.print(greenLow);
  }

  greenHigh = (greenHigh * 256) + greenLow;

  if(debug){
    Serial.print("  greenF: ");
    Serial.println(greenHigh);
  }
  return greenHigh;*/
}

/*** Gets the red sensor value and returns an unsigned int ***/
uint8_t utils::Md25::TSC3414Red(){

    uint8_t redLow = 0;
    uint8_t redHigh = 0;
    int ret = 0;
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x92, &redLow); //read Clear register
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x93, &redHigh); //read Clear register

    logger().info() << "redLow: " << (int) redLow << " \tredHigh: " << (int) redHigh
          << utils::end;
    redHigh = (redHigh * 256) + redLow;

    return redHigh;
  /*unsigned int redLow = 0;
  unsigned int redHigh = 0;
  Wire.beginTransmission(0x39); //0011 1001 //+0 for write
  Wire.write(0xB2); //1011 0010 //read Red register
  Wire.endTransmission();

  Wire.beginTransmission(0x39); //Request information
  Wire.requestFrom(0x39,2); //0011 1001 //+1 for read
  redLow = Wire.read();
  redHigh = Wire.read();
  Wire.endTransmission();

  if(debug){
    Serial.print("redH:   ");
    Serial.print(redHigh);
    Serial.print("  redL:   ");
    Serial.print(redLow);
  }

  redHigh = (redHigh * 256) + redLow;

  if(debug){
    Serial.print("  redF:   ");
    Serial.println(redHigh);
  }
  return redHigh;*/
}

/*** Gets the clear sensor value and returns an unsigned int ***/
uint8_t utils::Md25::TSC3414Clear(){
  
    uint8_t clearLow = 0;
    uint8_t clearHigh = 0;
    int ret = 0;
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x96, &clearLow); //read Clear register
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x97, &clearHigh); //read Clear register

    logger().info() << "clearH: " << (int) clearLow << "  \tclearL: " << (int) clearHigh
          << utils::end;
    clearHigh = (clearHigh * 256) + clearLow;

    return clearHigh;

    /*unsigned int clearLow = 0;
  unsigned int clearHigh = 0;
  Wire.beginTransmission(0x39); //0011 1001 //+0 for write
  Wire.write(0xB6); //1011 0110 //read Clear register
  Wire.endTransmission();

  Wire.beginTransmission(0x39); //Request information
  Wire.requestFrom(0x39,2); //0011 1001 //+1 for read
  clearLow = Wire.read();
  clearHigh = Wire.read();
  Wire.endTransmission();

  if(debug){
    Serial.print("clearH: ");
    Serial.print(clearHigh);
    Serial.print("  clearL: ");
    Serial.print(clearLow);
  }

  clearHigh = (clearHigh * 256) + clearLow;

  if(debug){
    Serial.print("  clearF: ");
    Serial.println(clearHigh);
  }
  return clearHigh;*/
}

/*
 * ======================================================
 * Sensor read functions - retrieves the RGBW raw sensor values
 * ======================================================
*/
void utils::Md25::TSC3414All(uint8_t allcolors[]){
  uint8_t white = TSC3414Clear();
  uint8_t green = TSC3414Green();
  uint8_t red = TSC3414Red();
  uint8_t blue = TSC3414Blue();

  allcolors[0] = white;
  allcolors[1] = red;
  allcolors[2] = green;
  allcolors[3] = blue;
  //returns all colors;
}

/*
 * ======================================================
 * TCS3414 Initialization
 * Turns on the sensor and sets integration time
 * ======================================================
*/
void utils::Md25::TCS3414Start(int delay1,int delay2){

    int ret = 0;
    //slave address: 0011 1001
    //0x80 1000 0000 //write to Control register
    //0x01 0000 0001 //Turn the device on (does not enable ADC yet)
    ret = writeRegisterbyte(groveColorSensor_i2cAddress_, 0x80, 0x01);

    usleep(delay1 * 1000); //14

    // Request confirmation //0011 1001
    uint8_t receivedVal; //0001 (ADC valid) 0001 (Power on)
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x39, &receivedVal);
    
    // Request ID //0011 1001
    uint8_t ID;
    //0x84 1000 0100 //get information from ID register (04h)
    ret = readRegisterbyte(groveColorSensor_i2cAddress_, 0x84, &ID);
    //0001 0000 (first byte == 0001 (TCS: 3413,3414,3415,3416) or 0000 (TCS: 3404).
    logger().debug() << "Part and rev ID: " << (int) ID
          << utils::end;

    if(ID == 1 || ID == 17){ //0000 0001 || 0001 0001
        logger().info() << "TCS3414 is now ON"
          << utils::end;
    }else{
        logger().info() << "TCS3414 is now OFF"
          << utils::end;
    }

    //Write to Timing (integration) register
    if(integrationtime == 12){
        //0000 0000 //set free running INTEG_MODE and integration time to 12ms
        ret = writeRegisterbyte(groveColorSensor_i2cAddress_, 0x81, 0x00);
    }else if(integrationtime == 100){
        //0000 0001 //set free running INTEG_MODE and integration time to 100ms
        ret = writeRegisterbyte(groveColorSensor_i2cAddress_, 0x81, 0x01);
    }else if(integrationtime == 400){
        //0000 0010 //set free running INTEG_MODE and integration time to 400ms
        ret = writeRegisterbyte(groveColorSensor_i2cAddress_, 0x81, 0x02);
    }else{
        logger().info() << "improper integration time has been set!"
          << utils::end;
    }

    //0000 0011 //Enable ADC_EN (needed to allow integration every 100ms)
    ret = writeRegisterbyte(groveColorSensor_i2cAddress_, 0x80, 0x03);


    usleep(delay2 * 1000); //14 //wait for a moment to allow ADC to initialize*/



  /*Wire.beginTransmission(0x39); //slave address: 0011 1001
  Wire.write(0x80); //1000 0000 //write to Control register
  Wire.write(0x01); //0000 0001 //Turn the device on (does not enable ADC yet)
  Wire.endTransmission();

  delay(delay1); //14

  Wire.beginTransmission(0x39); // Request confirmation //0011 1001
  Wire.requestFrom(0x39,1);
  int receivedVal = Wire.read(); //0001 (ADC valid) 0001 (Power on)
  Wire.endTransmission();

  Serial.print("TCS3414 is now "); //Serial.println(receivedVal);
  if(receivedVal == 1 || receivedVal == 17){ //0000 0001 || 0001 0001
    Serial.println("ON");
  }else{
    Serial.println("OFF");
  }

  Wire.beginTransmission(0x39); //slave address: 0011 1001
  Wire.write(0x84); //1000 0100 //get information from ID register (04h)
  Wire.endTransmission();

  Wire.beginTransmission(0x39); // Request ID //0011 1001
  Wire.requestFrom(0x39,1);
  int ID = Wire.read();
  Wire.endTransmission();

  Serial.print("Part and rev ID: ");
  Serial.println(ID, BIN); //0001 0000 (first byte == 0001 (TCS: 3413,3414,3415,3416) or 0000 (TCS: 3404).

  Wire.beginTransmission(0x39); //slave address: 0011 1001
  Wire.write(0x81); //1000 0000 //Write to Timing (integration) register
  if(integrationtime == 12){
    Wire.write(0x00); //0000 0000 //set free running INTEG_MODE and integration time to 12ms
  }else if(integrationtime == 100){
    Wire.write(0x01); //0000 0001 //set free running INTEG_MODE and integration time to 100ms
  }else if(integrationtime == 400){
    Wire.write(0x02); //0000 0010 //set free running INTEG_MODE and integration time to 400ms
  }else{
    Serial.println("improper integration time has been set!");
  }
  Wire.endTransmission();

  Wire.beginTransmission(0x39); //slave address: 0011 1001
  Wire.write(0x80); //1000 0000 //write to Control register
  Wire.write(0x03); //0000 0011 //Enable ADC_EN (needed to allow integration every 100ms)
  Wire.endTransmission();

  delay(delay2); //14 //wait for a moment to allow ADC to initialize*/
}


/*** Keeps a running average of 4 values per color. ***/
void utils::Md25::calculateMedium(float med[], uint8_t value[], float divider){
  for(int i = 0; i < 4; i++){
    med[i] = ( (med[i]*(divider-1.0)) + value[i] ) / divider;
  }
}

/*** calculates percentages for R,G,B channels, if enabled.  ***/
void utils::Md25::makePercentage(uint8_t allcolors[], float allmedium[]){ //makes every color a percentage, 100% is the average of the previous 4 values before this is entered.
  for(int i=0; i<4; i++){
    allcolors[i] = (int)(allcolors[i] / allmedium[i] * 100);
  }
}

//compensateEnabled = false; //enable/disable color compensation of the sensor sensitivity per color
void utils::Md25::colorCompensator(uint8_t allcolors[]){
  allcolors[2] = (int)(allcolors[2]*1.3125);//green
  allcolors[3] = (int)(allcolors[2]*1.5973);//blue
  //look at the graph in the datasheet to find the following percentages
  //blue  52%    (r/b == 1.5973)
  //green 63.28% (r/g == 1.3125)
  //red   83.06%
}

/*** takes the raw values from the sensors and converts them to
     Correlated Color Temperature.  Returns a float with CCT ***/
float utils::Md25::CCTCalc(uint8_t allcolors[]){
  float TCS3414tristimulus[3]; // [tri X, tri Y, tri Z]
  float TCS3414chromaticityCoordinates[2]; //chromaticity coordinates // [x, y]

  //calculate tristimulus values (chromaticity coordinates)
  //The tristimulus Y value represents the illuminance of our source
  TCS3414tristimulus[0] = (-0.14282 * allcolors[1]) + (1.54924 * allcolors[2]) + (-0.95641 * allcolors[3]); //X
  TCS3414tristimulus[1] = (-0.32466 * allcolors[1]) + (1.57837 * allcolors[2]) + (-0.73191 * allcolors[3]); //Y // = Illuminance
  TCS3414tristimulus[2] = (-0.68202 * allcolors[1]) + (0.77073 * allcolors[2]) + (0.56332 * allcolors[3]); //Z

  float XYZ = TCS3414tristimulus[0] + TCS3414tristimulus[1] + TCS3414tristimulus[2];

  //calculate the chromaticiy coordinates
  TCS3414chromaticityCoordinates[0] = TCS3414tristimulus[0] / XYZ; //x
  TCS3414chromaticityCoordinates[1] = TCS3414tristimulus[1] / XYZ; //y

  float n = (TCS3414chromaticityCoordinates[0] - 0.3320) / (0.1858 - TCS3414chromaticityCoordinates[1]);

  float CCT = ( (449*pow(n,3)) + (3525*pow(n,2)) + (6823.3 * n) + 5520.33 );
/*
  Serial.print("Illuminance: ");
  Serial.print(TCS3414tristimulus[1]);
  Serial.print("\tx: ");
  Serial.print(TCS3414chromaticityCoordinates[0]);
  Serial.print(" \ty: ");
  Serial.print(TCS3414chromaticityCoordinates[1]);
  Serial.print(" \tCCT: ");
  Serial.print(CCT);
  Serial.print("K\t -- \t");*/
  logger().info() << "Illuminance: " << TCS3414tristimulus[1]
          << " \tx: " << TCS3414chromaticityCoordinates[0]
          << " \ty: " << TCS3414chromaticityCoordinates[1]
          << " \tCCT:  " << CCT  << " K"
          << utils::end;

  return CCT;
}

void utils::Md25::TCS3414Loop(){
    //getSerialCommands(); //to be able to receive commands

    //gets the raw values from the sensors and writes it to TCS3414values[]
    TSC3414All(TCS3414values);

    //compensate based on the filter characteristics of the TCS3414
    if(compensateEnabled)
        colorCompensator(TCS3414values);

    //keeps a running average from the last 4 values per color.
    calculateMedium(TCS3414mediate,TCS3414values,4.0);

    //calculates the color temperature, using the algorithm in the TCS3414 datasheet
    ColorTemperature = CCTCalc(TCS3414values);

    //displays percentage values, if enabled.
    if(percentageEnabled){
        makePercentage(TCS3414values, TCS3414medium);
    }
/*
  Serial.print("Clear: ");
  Serial.print(TCS3414values[0]);
  if(percentageEnabled)
    Serial.print("%");
  Serial.print("\tRed: ");
  Serial.print(TCS3414values[1]);
  if(percentageEnabled)
    Serial.print("%");
  Serial.print("  \tGreen: ");
  Serial.print(TCS3414values[2]);
  if(percentageEnabled)
    Serial.print("%");
  Serial.print("\tBlue: ");
  if(percentageEnabled){
    Serial.print(TCS3414values[3]);
    Serial.println("%");
  }else{
    Serial.println(TCS3414values[3]);
  }*/

  logger().info() << "Clear: " << (int) TCS3414values[0]
          << " \tRed: " << (int) TCS3414values[1]
          << " \tGreen: " << (int) TCS3414values[2]
          << " \tBlue:  " << (int) TCS3414values[3]
          << utils::end;
  logger().info() << utils::end;

  //pause
  usleep(loopdelay*1000); //delays by the integration time between measurements


}

