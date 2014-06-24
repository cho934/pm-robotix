/*!
 * \file
 * \brief Définition de la classe ServoMotorDxlConstant.
 */

#ifndef PMX_SERVOMOTORDXLCONS_HPP

#define PMX_SERVOMOTORDXLCONS_HPP
//
#define Tx_MODE                     		1
#define Rx_MODE                     		0
#define AX12_MAX_SERVOS 			30
#define AX12_BUFFER_SIZE    		32

#define AX_MODEL_NUMBER_L   		0
#define AX_MODEL_NUMBER_H 		1
#define AX_VERSION             			2
#define AX_ID                       		3

#define AX_BAUD_RATE             		4 //0x04

#define AX_RETURN_DELAY_TIME  	5 //0x05
#define AX_CW_ANGLE_LIMIT_L       	6 //0x06
#define AX_CW_ANGLE_LIMIT_H      	7 //0x07
#define AX_CCW_ANGLE_LIMIT_L     	8 //0x08
#define AX_CCW_ANGLE_LIMIT_H   	9 //0x09


#define AX_SYSTEM_DATA2         	10 //0x0a



#define AX_LIMIT_TEMPERATURE   	11 //0x0b
#define AX_DOWN_LIMIT_VOLTAGE  	12 //0x0c
#define AX_UP_LIMIT_VOLTAGE       	13 //0x0d




#define AX_MAX_TORQUE_L          	14 //0x0e
#define AX_MAX_TORQUE_H          	15 //0x0f
#define AX_RETURN_LEVEL             16 //0x10
#define AX_ALARM_LED                	17
#define AX_ALARM_SHUTDOWN      	18



#define AX_OPERATING_MODE    		19 //0x13
#define AX_DOWN_CALIBRATION_L 	20
#define AX_DOWN_CALIBRATION_H  	21



#define AX_UP_CALIBRATION_L       	22
#define AX_UP_CALIBRATION_H      	23

#define AX_TORQUE_ENABLE 					24
#define AX_LED                      				25

#define AX_CW_COMPLIANCE_MARGIN  	26 //0x01a
#define AX_CCW_COMPLIANCE_MARGIN  	27
#define AX_CW_COMPLIANCE_SLOPE    	28
#define AX_CCW_COMPLIANCE_SLOPE   	29
#define AX_GOAL_POSITION_L     			30 //0x01e
#define AX_GOAL_POSITION_H          		31
#define AX_GOAL_SPEED_L             		32 //0x20
#define AX_GOAL_SPEED_H             		33
#define AX_TORQUE_LIMIT_L           		34 //0x22
#define AX_TORQUE_LIMIT_H           		35
#define AX_PRESENT_POSITION_L       	36 //0x24
#define AX_PRESENT_POSITION_H       	37
#define AX_PRESENT_SPEED_L          		38 //0x26
#define AX_PRESENT_SPEED_H          		39
#define AX_PRESENT_LOAD_L           		40 //0x28
#define AX_PRESENT_LOAD_H           		41
#define AX_PRESENT_VOLTAGE          		42 //0x2a
#define AX_PRESENT_TEMP					43 //0x2b
#define AX_REGISTERED_INSTRUCTION   	44 //0x2c
#define AX_PAUSE_TIME               			45
#define AX_MOVING                   			46
#define AX_LOCK                     				47 //0x2f
#define AX_PUNCH_L                  			48 //0x30
#define AX_PUNCH_H                  			49 //0x31
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
//

#endif
