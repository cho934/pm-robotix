#ifndef ROBOT_H_
#define ROBOT_H_

extern long long timeOffset;
extern int lPower;
extern int rPower;
extern int running;

long currentTimeInMillis();

void robot_init();
void robot_dispose();

void robot_startMotorLeft();
void robot_startMotors();

void robot_stopMotorRight();
void robot_stopMotorLeft();
int robot_getLeftPower();
int robot_getRightPower();

void robot_setMotorRightSpeed(int speed);
void robot_setMotorLeftSpeed(int speed);

long robot_getLeftExternalCounter();
long robot_getRightExternalCounter();

long robot_getLeftInternalCounter();
long robot_getRightInternalCounter();

int robot_isButton1Pressed();

int robot_isRunning();
int robot_isEmergencyPressed();

void robot_waitStart();

int robot_isDetectingObstacle();
void robot_displayText(int line, char* text);
void robot_setLedStatus(int status);

int robot_isButtonPressed(int button);
void robot_initPID();


#endif
