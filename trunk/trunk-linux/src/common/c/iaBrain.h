/*
 * iaBrain.h
 *
 *  Created on: 20 Apr 2014
 *      Author: pmx
 */

#ifndef IABRAIN_H_
#define IABRAIN_H_

#include <cstdlib>
#include <stdio.h>

#include "iaActionManager.h"

typedef struct iaDecision iaDecision;
struct iaDecision {
    float startPointX;
    float startPointY;
    float startPointA;
    int active;
    iaActionListElement* actionsList;
    float actionsTime;
    float risk;
    int reward;
};

// Initialisation
void iaBrainInitialise(int color, iaActionListElement* currentActionsPile);
void iaBrainAddSpearsDecisions(int color);
void iaBrainAddFireDecisions(int color);
void iaBrainAddFunnyActionDecisions(int color);
void iaBrainAddSherriesDecisions(int color);
void iaBrainAddStoreSherriesDecisions(int color);
iaDecision* iaBrainAddDecision();

// Main
void iaBrainComputeNewDecision(iaActionListElement* currentActionsPile);
float valueOfDecision(iaDecision* decision);


#endif /* IABRAIN_H_ */
