/*
 * iaBrain.c
 *
 *  Created on: 20 Apr 2014
 *      Author: pmx
 */
#include "iaBrain.h"
#include "ia.h"
#include  "iaActionManager.h"


// -----------------
// Initialisation
// -----------------

static iaDecision* iaDecisions;
static int numberOfDecisions = 0;
int colorBlue = 0;

static float coefTime = 1;
static float coefReward = 1;
static float coefRisk = 0;



void iaBrainInitialise(int color, iaActionListElement* currentActionsPile) {
	// Initialize decisions list
	iaBrainAddSpearsDecisions(color);
	iaBrainAddFireDecisions(color);
	iaBrainAddFunnyActionDecisions(color);
	iaBrainAddSherriesDecisions(color);
	iaBrainAddStoreSherriesDecisions(color);
	// take first decision
	iaBrainComputeNewDecision(currentActionsPile);
}

void iaBrainAddSpearsDecisions(int color) {

	iaDecision* mammothRed = iaBrainAddDecision();
	mammothRed->active = 1;
	mammothRed->reward = 10;
	mammothRed->startPointX = 150.0;
	mammothRed->startPointY = 150.0;
	mammothRed->startPointA = 90.0;
	mammothRed->risk = 1.0;
	mammothRed->actionsTime = 10.0;

	iaDecision* mammothBlue = iaBrainAddDecision();
	mammothBlue->active = 1;
	mammothBlue->reward = 10;
	mammothBlue->startPointX = 250.0;
	mammothBlue->startPointY = 50.0;
	mammothBlue->startPointA = 90.0;
	mammothBlue->risk = 1.0;
	mammothBlue->actionsTime = 10.0;
}

void iaBrainAddFireDecisions(int color) {

}

void iaBrainAddFunnyActionDecisions(int color) {

}

void iaBrainAddSherriesDecisions(int color) {

}

void iaBrainAddStoreSherriesDecisions(int color) {

}


iaDecision* iaBrainAddDecision() {
	numberOfDecisions++;
	iaDecisions = (iaDecision*)malloc(numberOfDecisions*sizeof(iaDecision));
	return &iaDecisions[numberOfDecisions-1];
}

// ----------------
// Main usage
// ----------------

// Used by the interface to manually compute a new action, or by the IA if action pile is empty
void iaBrainComputeNewDecision(iaActionListElement* currentActionsPile){
	iaActionManagerEmpty(currentActionsPile);
	float optimalValue = 0;
	int optimalIndex = -1;
	for(int index = 0; index < numberOfDecisions; index++) {
		float computedValue = valueOfDecision(&iaDecisions[index]);
		if(computedValue > optimalValue) {
			optimalValue = computedValue;
			optimalIndex = index;
		}
	}
	if (optimalIndex > -1) {
		//Move to coordinates, compute move
		iaAction* moveAction = iaActionManagerGenerateNewAction(
				iaActionTypeMoveToCoord,
				iaDecisions[optimalIndex].startPointX,
				iaDecisions[optimalIndex].startPointY,
				iaDecisions[optimalIndex].startPointA
				);
		iaActionManagerAddActionAtEnd(moveAction, currentActionsPile);
		//Add pile for actions
		iaActionManagerAddActionsAtEnd(iaDecisions[optimalIndex].actionsList, currentActionsPile);
	}
}

float valueOfDecision(iaDecision* decision) {
	if (decision == NULL) {
		return 0;
	} else {
		int rewardValue = decision->reward;
		float timeForOptimal = decision->actionsTime + getTimeForMove(getPosX(), getPosY(), getPosA(), decision->startPointX, decision->startPointY, decision->startPointA);
		//TODO risk value
		float riskEvaluation = decision->risk;
		return coefReward*rewardValue - (coefTime*timeForOptimal + coefRisk*riskEvaluation);
	}
}
