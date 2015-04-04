#ifndef ROBOT_HPP_
#define ROBOT_HPP_





#ifdef __cplusplus
extern "C" {
#endif

//long call_EncoderControl_getLeftEncoder(struct EncoderControl* p);





extern long long timeOffset;
extern int lPower;
extern int rPower;
extern int running;






long currentTimeInMillis();

void robot_init();

/*
void robot_stopMotorRight();
void robot_stopMotorLeft();
void robot_waitStart();
int robot_isButton1Pressed();
int robot_isButtonPressed(int button);
*/
int robot_getLeftPower();
int robot_getRightPower();

void robot_setMotorRightSpeed(int speed);
void robot_setMotorLeftSpeed(int speed);

long robot_getLeftExternalCounter();
long robot_getRightExternalCounter();

long robot_getLeftInternalCounter();
long robot_getRightInternalCounter();

void robot_resetEncoders();


int robot_isRunning();
int robot_isEmergencyPressed();

int robot_isDetectingObstacle();
void robot_displayText(int line, char* text);
void robot_setLedStatus(int status);


void robot_initPID();
void robot_initPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd);
void robot_initPID_LR(float Ap, float Ai, float Ad, float Dp, float Di, float Dd);

#ifdef __cplusplus
}
#endif

#endif
