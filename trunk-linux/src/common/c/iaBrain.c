/*
 * iaBrain.c
 *
 *  Created on: 20 Apr 2014
 *      Author: pmx
 */
#include "iaBrain.h"
#include "ia.h"
#include "iaActionManager.h"
#include "iaLogger.h"


// -----------------
// Initialisation
// -----------------

static iaDecision* iaDecisions = NULL;
static int numberOfDecisions = 0;
int colorBlue = 0;

static float coefTime = 1;
static float coefReward = 1;
static float coefRisk = 0;

static iaDecision iaBrainCurrentDecision;

void iaBrainInitialise(int color, iaActionListElement* currentActionsPile) {
	// Initialize decisions list
	iaBrainAddSpearsDecisions(color);
	iaBrainAddFireDecisions(color);
	iaBrainAddFunnyActionDecisions(color);
	iaBrainAddSherriesDecisions(color);
	iaBrainAddStoreSherriesDecisions(color);
	// Display pile
	iaBrainDisplayDecisionsPile();
	// take first decision
	currentActionsPile = iaBrainComputeNewDecision();
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
	mammothRed->idSpecificAction = 1.0;

	iaDecision* mammothBlue = iaBrainAddDecision();
	mammothBlue->active = 1;
	mammothBlue->reward = 10;
	mammothBlue->startPointX = 250.0;
	mammothBlue->startPointY = 50.0;
	mammothBlue->startPointA = 90.0;
	mammothBlue->risk = 1.0;
	mammothBlue->actionsTime = 10.0;
	mammothBlue->idSpecificAction = 1.0;

}

void iaBrainAddFireDecisions(int color) {

	iaDecision* mammothRed = iaBrainAddDecision();
	mammothRed->active = 1;
	mammothRed->reward = 10;
	mammothRed->startPointX = 150.0;
	mammothRed->startPointY = 150.0;
	mammothRed->startPointA = 90.0;
	mammothRed->risk = 1.0;
	mammothRed->actionsTime = 10.0;
	mammothRed->idSpecificAction = 1.0;

	iaDecision* mammothBlue = iaBrainAddDecision();
	mammothBlue->active = 1;
	mammothBlue->reward = 10;
	mammothBlue->startPointX = 250.0;
	mammothBlue->startPointY = 50.0;
	mammothBlue->startPointA = 90.0;
	mammothBlue->risk = 1.0;
	mammothBlue->actionsTime = 10.0;
	mammothBlue->idSpecificAction = 1.0;

}

void iaBrainAddFunnyActionDecisions(int color) {

}

void iaBrainAddSherriesDecisions(int color) {

}

void iaBrainAddStoreSherriesDecisions(int color) {

}


iaDecision* iaBrainAddDecision() {
	numberOfDecisions++;
	if (iaDecisions == NULL) {
		iaDecisions = (iaDecision*)malloc(numberOfDecisions*sizeof(iaDecision));
	} else {
		iaDecisions = (iaDecision*)realloc(iaDecisions, numberOfDecisions*sizeof(iaDecision));
	}
	return &iaDecisions[numberOfDecisions-1];
}

// ----------------
// Main usage
// ----------------

// Used by the interface to manually compute a new action, or by the IA if action pile is empty
iaActionListElement* iaBrainComputeNewDecision(){
	iaLogDebug("New Decision:");
	iaActionListElement* currentActionsPile;
	float optimalValue = -1;
	int optimalIndex = -1;
	for(int index = 0; index < numberOfDecisions; index++) {
		printf("  decision[%i]", index);
		if(iaDecisions[index].active > 0) {
			printf("\n");
			float computedValue = iaBrainValueOfDecision(&iaDecisions[index]);
			printf(" Value=%f\n", computedValue);
			if(computedValue > optimalValue) {
				optimalValue = computedValue;
				optimalIndex = index;
			}
		} else {
			printf(" inactive\n");
		}
	}
	if (optimalIndex > -1) {
		printf("Decision took: %i\n", optimalIndex);
		iaBrainCurrentDecision = iaDecisions[optimalIndex];
		//Move to coordinates, compute move
		//TODO To optimize !!!
		iaAction* moveAction = iaActionManagerGenerateNewAction(
				iaActionTypeMoveToCoord,
				iaBrainCurrentDecision.startPointX,
				iaBrainCurrentDecision.startPointY,
				iaBrainCurrentDecision.startPointA
				);
		printf("A\n");
		iaActionManagerAddActionAtEnd(moveAction, currentActionsPile);
		printf("B\n");
		iaAction* specificAction = iaActionManagerGenerateNewAction(
						iaActionTypeAction,
						iaBrainCurrentDecision.idSpecificAction,
						0.0,
						0.0
						);
		printf("C\n");
		iaActionManagerAddActionAtEnd(specificAction, currentActionsPile);
		printf("D\n");
		//Add pile for actions
		//iaActionManagerAddActionsAtEnd(iaDecisions[optimalIndex].actionsList, currentActionsPile);
	} else {
		iaLogDebug("No decision left !");
	}
}

void iaBrainDisplayDecisionsPile() {
	for(int index = 0; index < numberOfDecisions; index++) {
		iaDecision decision = iaDecisions[index];
		printf("Decision[%i] active=%i, specificAction=%i, X=%f Y=%f A=%f\n",
				index, decision.active, decision.idSpecificAction,
				decision.startPointX, decision.startPointY, decision.startPointA);
	}
}

void iaBrainDecisionFinished() {
	if (iaBrainCurrentDecision.active == 1) {
		iaBrainCurrentDecision.active = 0;
	}
}

float iaBrainValueOfDecision(iaDecision* decision) {
	if (decision == NULL) {
		return 0;
	} else {
		int rewardValue = decision->reward;
		float timeForOptimal = decision->actionsTime + iaBrainComputeMoveDecision(iaGetPosX(), iaGetPosY(), iaGetPosA(), decision->startPointX, decision->startPointY, decision->startPointA);
		float riskEvaluation = decision->risk;
		return coefReward*rewardValue - (coefTime*timeForOptimal + coefRisk*riskEvaluation);
	}
}

float iaBrainComputeMoveDecision(float originX, float originY, float originA, float targetX, float targetY, float targetA) {
	// TODO compute path
	float timeForOptimal = iaGetTimeForMove(originX, originY, originA, targetX, targetY, targetA);
	return timeForOptimal;
}
