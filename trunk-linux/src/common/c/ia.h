/*
 * ia.h
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */

#ifndef IA_H_
#define IA_H_

#include <cstdlib>
#include <stdio.h>

void initialize(int color);
void executeNextAction();
void takeNewDecision();

void executeMoveAction(float x, float y, float a);
void executeWaitAction(float time);
void executeSpecificAction(float actionType);
float getPosX();
float getPosY();
float getPosA();
void updateOponentsValues();
float getTimeRemaining();
float getTimeForMove(float X, float Y, float A, float targetX, float targetY, float targetZ);

#endif /* IA_H_ */
