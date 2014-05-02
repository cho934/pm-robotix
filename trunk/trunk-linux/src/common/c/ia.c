/*
 * ia.c
 *
 * Provides interface methods between the robot and the artificial intelligence.
 * All of these methods have to be adapted to each robot.
 *
 * Test ia
 *
 * Robot must only use these methods
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */
#include "ia.h"
#include "iaBrain.h"
#include "iaActionManager.h"
#include "iaLogger.h"

// ------------------------
// -- ROBOT -> IA --
// ------------------------

static iaActionListElement* currentActionsPile = NULL;

/**
 * Initializes robot. To call at the beginning, before launch
 */
void iaInitialize(int color) {
	iaLogDebug("iaInitialize");
	iaBrainInitialise(color, currentActionsPile);
}

/**
 * Execute next action, relelases hand after execution
 */
void iaExecuteNextAction() {
	iaLogDebug("iaExecuteNextAction");
	iaAction* action = iaActionManagerGetNextAction(currentActionsPile);
	currentActionsPile = iaActionManagerPop(currentActionsPile);
	if (action == NULL) {
		iaLogDebug("no next action, taking new decision");
		iaTakeNewDecision();
		action = iaActionManagerGetNextAction(currentActionsPile);
		currentActionsPile = iaActionManagerPop(currentActionsPile);
	}
	if (action != NULL) {
		if (action->type == iaActionTypeWait) {
			iaExecuteWaitAction(action->param1);
		} else if (action->type == iaActionTypeMoveToCoord) {
			iaExecuteMoveAction(action->param1, action->param2, action->param3);
		} else if (action->type == iaActionTypeAction) {
			if (iaExecuteSpecificAction((int)(action->param1)) == 1) {
				iaBrainDecisionFinished();
			}
		}
		iaActionManagerClearAction(action);
		currentActionsPile = iaActionManagerPop(currentActionsPile);
		if (currentActionsPile == NULL) {
			iaTakeNewDecision();
		}
	}

}

/**
 * Ask for new actions pile demending on new position
 */
void iaTakeNewDecision() {
	iaLogDebug("iaTakeNewDecision");
	iaActionManagerEmpty(currentActionsPile);
	currentActionsPile = iaBrainComputeNewDecision();
}



void iaDetectOponent(float posX, float posY) {
	iaLogDebug("iaDetectOponent");

}

// ------------------------
// -- IA -> ROBOT --
// ------------------------

/**
 * Move to X, Y, A position
 */
void iaExecuteMoveAction(float x, float y, float a) {
	iaLogDebug("iaExecuteMoveAction");

}

/**
 * Wait for *time* ms
 */
void iaExecuteWaitAction(float time) {
	iaLogDebug("iaExecuteWaitAction");

}

/**
 * Execute the action designed by actionType:
 */
int iaExecuteSpecificAction(int actionType) {
	iaLogDebug("iaExecuteSpecificAction");
	// Return 0 if failed, 1 otherwise
	switch (actionType) {
		case 1:
			return iaLaunchSpear();
			break;
		default:
			break;
	}
}

int iaLaunchSpear() {
	iaLogDebug("iaLaunchSpear");
	// Se mettre en position
	// Envoyer la balle vers le mammouth
	// Eventuellement reculer pour se dégager
	return 0;
}

/**
 * current X position, regarding 0,0 the blue corner
 */
float iaGetPosX() {
	return 0;
}

/**
 * current Y position, regarding 0,0 the blue corner
 */
float iaGetPosY() {
	return 0;
}


/**
 * Current position Alpha, regarding to blue position
 */
float iaGetPosA() {
	return 0;
}


/**
 * Remaining time in secs
 */
float iaGetTimeRemaining() {
	iaLogDebug("iaGetTimeRemaining");
	return 0;
}

/**
 * This method returns the time needed for getting to a position X, Y, A
 * This must be the approximate (and optimal) time took by the robot
 *   to execute the action, move from X, Y, A, to targetX, targetY, targetA
 */
float iaGetTimeForMove(float X, float Y, float A, float targetX, float targetY, float targetA) {
	iaLogDebug("iaGetTimeForMove");
	printf("%f %f %f --> %f %f %f", X, Y, A, targetX, targetY, targetA);
	return 0;
}
