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

void iaInitialize(int color);
void iaExecuteNextAction();
void iaTakeNewDecision();

void iaExecuteMoveAction(float x, float y, float a);
void iaExecuteWaitAction(float time);
int iaExecuteSpecificAction(int actionType);
float iaGetPosX();
float iaGetPosY();
float iaGetPosA();
void iaUpdateOponentsValues();
float iaGetTimeRemaining();
float iaGetTimeForMove(float X, float Y, float A, float targetX, float targetY, float targetA);

// Specific actions
int iaLaunchSpear();

#endif /* IA_H_ */
