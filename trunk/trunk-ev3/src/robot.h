#ifndef ROBOT_H_
#define ROBOT_H_

void robot_init();
void robot_dispose();

void robot_startMotorLeft();
void robot_startMotors();

void robot_stopMotorRight();
void robot_stopMotorLeft();
void robot_setMotorRightSpeed(int speed);
void robot_setMotorLeftSpeed(int speed);

long robot_getLeftExternalCounter();
long robot_getRightExternalCounter();

int robot_isButton1Pressed();

#endif
