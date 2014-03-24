/*------------------------------------------------------------------------------*\
 * This source file is subject to the GPLv3 license that is bundled with this   *
 * package in the file COPYING.                                                 *
 * It is also available through the world-wide-web at this URL:                 *
 * http://www.gnu.org/licenses/gpl-3.0.txt                                      *
 * If you did not receive a copy of the license and are unable to obtain it     *
 * through the world-wide-web, please send an email to                          *
 * siempre.aprendiendo@gmail.com so we can send you a copy immediately.         *
 *                                                                              *
 * @category  Robotics                                                          *
 * @copyright Copyright (c) 2011 Jose Cortes (http://www.siempreaprendiendo.es) *
 * @license   http://www.gnu.org/licenses/gpl-3.0.txt GNU v3 Licence            *
 *                                                                              *
 \*------------------------------------------------------------------------------*/

#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_

#include "SerialPort.hpp"
#include "GpioPort.hpp"
#include "Utils.hpp"
#include "Mutex.hpp"

using namespace MyUtil;

#define Tx_MODE                     		1
#define Rx_MODE                     		0
#define AX12_MAX_SERVOS 			30
#define AX12_BUFFER_SIZE    		32

/** EEPROM AREA **/
#define AX_MODEL_NUMBER_L   		0 //0x00#define AX_MODEL_NUMBER_H 		1 //0x01#define AX_VERSION             			2 //0x02#define AX_ID                       		3 //0x03#define AX_BAUD_RATE             		4 //0x04#define AX_RETURN_DELAY_TIME  	5 //0x05#define AX_CW_ANGLE_LIMIT_L       	6 //0x06#define AX_CW_ANGLE_LIMIT_H      	7 //0x07#define AX_CCW_ANGLE_LIMIT_L     	8 //0x08#define AX_CCW_ANGLE_LIMIT_H   	9 //0x09#define AX_SYSTEM_DATA2         	10 //0x0a#define AX_LIMIT_TEMPERATURE   	11 //0x0b#define AX_DOWN_LIMIT_VOLTAGE  	12 //0x0c#define AX_UP_LIMIT_VOLTAGE       	13 //0x0d#define AX_MAX_TORQUE_L          	14 //0x0e#define AX_MAX_TORQUE_H          	15 //0x0f#define AX_RETURN_LEVEL             16 //0x10#define AX_ALARM_LED                	17
#define AX_ALARM_SHUTDOWN      	18
#define AX_OPERATING_MODE    		19 //0x13#define AX_DOWN_CALIBRATION_L 	20
#define AX_DOWN_CALIBRATION_H  	21
#define AX_UP_CALIBRATION_L       	22
#define AX_UP_CALIBRATION_H      	23
/** RAM AREA **/
#define AX_TORQUE_ENABLE        			24 //0x018#define AX_LED                      				25
#define AX_CW_COMPLIANCE_MARGIN  	26 //0x01a#define AX_CCW_COMPLIANCE_MARGIN  	27
#define AX_CW_COMPLIANCE_SLOPE    	28
#define AX_CCW_COMPLIANCE_SLOPE   	29
#define AX_GOAL_POSITION_L     			30 //0x01e#define AX_GOAL_POSITION_H          		31
#define AX_GOAL_SPEED_L             		32 //0x20#define AX_GOAL_SPEED_H             		33
#define AX_TORQUE_LIMIT_L           		34 //0x22#define AX_TORQUE_LIMIT_H           		35
#define AX_PRESENT_POSITION_L       	36 //0x24#define AX_PRESENT_POSITION_H       	37
#define AX_PRESENT_SPEED_L          		38 //0x26#define AX_PRESENT_SPEED_H          		39
#define AX_PRESENT_LOAD_L           		40 //0x28#define AX_PRESENT_LOAD_H           		41
#define AX_PRESENT_VOLTAGE          		42 //0x2a#define AX_PRESENT_TEMPERATURE      	43 //0x2b#define AX_REGISTERED_INSTRUCTION   	44 //0x2c#define AX_PAUSE_TIME               			45
#define AX_MOVING                   			46
#define AX_LOCK                     				47 //0x2f#define AX_PUNCH_L                  			48 //0x30#define AX_PUNCH_H                  			49 //0x31
/** Status Return Levels **/
#define AX_RETURN_NONE          	0
#define AX_RETURN_READ              1
#define AX_RETURN_ALL               	2

/** Instruction Set **/
#define AX_PING                     		1
#define AX_READ_DATA                	2
#define AX_WRITE_DATA               	3
#define AX_REG_WRITE                	4
#define AX_ACTION                   		5
#define AX_RESET                    		6
#define AX_SYNC_WRITE               	131

/** Error Levels **/
#define ERR_NONE                    	0
#define ERR_VOLTAGE                 	1
#define ERR_ANGLE_LIMIT             	2
#define ERR_OVERHEATING         	4
#define ERR_RANGE                   	8
#define ERR_CHECKSUM                16
#define ERR_OVERLOAD                	32
#define ERR_INSTRUCTION             64

/** AX-S1 **/
/*
 #define AX_LEFT_IR_DATA             26
 #define AX_CENTER_IR_DATA           27
 #define AX_RIGHT_IR_DATA            28
 #define AX_LEFT_LUMINOSITY          29
 #define AX_CENTER_LUMINOSITY        30
 #define AX_RIGHT_LUMINOSITY         31
 #define AX_OBSTACLE_DETECTION       32
 #define AX_BUZZER_INDEX             40
 */

#define DxlGetTemperature(id) (dynamixel.getCommand(id, AX_PRESENT_TEMPERATURE, 1))
#define DxlGetVoltage(id) (dynamixel.getCommand(id, AX_PRESENT_VOLTAGE, 1))
#define DxlGetPos(id) (dynamixel.getCommand(id, AX_PRESENT_POSITION_L, 2))
#define DxlGetBaud(id) (dynamixel.getCommand(id, AX_BAUD_RATE, 1))
#define DxlGetMaxTorqueLimit(id) (dynamixel.getCommand(id, AX_TORQUE_LIMIT_L, 2))
#define DxlGetMaxTorque(id) (dynamixel.getCommand(id, AX_MAX_TORQUE_L, 2))
#define DxlGetEnableTorque(id) (dynamixel.getCommand(id, AX_TORQUE_ENABLE, 1))
#define DxlGetReturnDelay(id) (dynamixel.getCommand(id, AX_RETURN_DELAY_TIME, 1))
#define DxlGetAcMoving(id) (dynamixel.getCommand(id, AX_MOVING, 1))
#define DxlGetAxLed(id) (dynamixel.getCommand(id, AX_LED, 1))


#define DxlSetPos(id, pos) (dynamixel.setCommand(id, AX_GOAL_POSITION_L, pos, 2))
#define DxlSetAxLedOn(id) (dynamixel.setCommand(id, AX_LED, 1, 1))
#define DxlSetAxLedOff(id) (dynamixel.setCommand(id, AX_LED, 0, 1))

class Dynamixel: public utils::Mutex
{

private:
	utils::GpioPort gpio_;
	SerialPort serial_;

	//static const int waitTimeForResponseUs=600;
	static const int BufferSize = 1024;

	byte buffer[BufferSize];
	byte bufferIn[BufferSize];

	int createReadDataBuffer(int id, int regstart, int readLength);
	int createWriteDataBuffer(int id, int regstart, int data, int numberOfParameters);
	//int createWriteDataBuffer1Byte(int id, int regstart, short data);
	//int createWriteDataBuffer2bytes(int id, int regstart, short data);

	void setTX();
	void setRX();

	void cleanBuffers();

public:
	Dynamixel();
	~Dynamixel();

	void setCommand(int idAX12, int regstart, int data, int nb2Write);
	long getCommand(int idAX12, int regstart, int readLength);

	void logBf(byte *buffer, int n);
};

#endif
