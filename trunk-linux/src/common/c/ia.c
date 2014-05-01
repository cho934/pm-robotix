/*
 * ia.c
 *
 * Provides interface methods between the robot and the artificial intelligence.
 * All of these methods have to be adapted to each robot.
 *
 * Robot must only use these methods
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */
#include "ia.h"
#include "iaBrain.h"
#include "iaActionManager.h"

// ------------------------
// -- ROBOT -> IA --
// ------------------------

static iaActionListElement* currentActionsPile;

/**
 * Initializes robot. To call at the beginning, before launch
 */
void initialize(int color) {
	iaBrainInitialise(color, currentActionsPile);
}

/**
 * Execute next action, relelases hand after execution
 */
void executeNextAction() {
	iaAction* action = iaActionManagerGetNextAction(currentActionsPile);
	if (action == NULL) {
		takeNewDecision();
		action = iaActionManagerGetNextAction(currentActionsPile);
	}
	if (action != NULL) {
		if (action->type == iaActionTypeWait) {
			executeWaitAction(action->param1);
		} else if (action->type == iaActionTypeMoveToCoord) {
			executeMoveAction(action->param1, action->param2, action->param3);
		} else if (action->type == iaActionTypeAction) {
			executeSpecificAction(action->param1);
		}
		iaActionManagerClearAction(action);
		currentActionsPile = iaActionManagerPop(currentActionsPile);
		if (currentActionsPile == NULL) {
			takeNewDecision();
		}
	}

}

/**
 * Ask for new actions pile demending on new position
 */
void takeNewDecision() {
	iaBrainComputeNewDecision(currentActionsPile);
}

void detectOponent(float posX, float posY) {

}

// ------------------------
// -- IA -> ROBOT --
// ------------------------

/**
 * Move to X, Y, A position
 */
void executeMoveAction(float x, float y, float a) {

}

/**
 * Wait for *time* ms
 */
void executeWaitAction(float time) {

}

/**
 * Execute the action designed by actionType:
 */
void executeSpecificAction(float actionType) {

}

/**
 * current X position, regarding 0,0 the blue corner
 */
float getPosX() {
	return 0;
}

/**
 * current Y position, regarding 0,0 the blue corner
 */
float getPosY() {
	return 0;
}


/**
 * Current position Alpha, regarding to blue position
 */
float getPosA() {
	return 0;
}


/**
 * Remaining time in secs
 */
float getTimeRemaining() {
	return 0;
}

/**
 * This method returns the time needed for getting to a position X, Y, A
 * This must be the approximate (and optimal) time took by the robot
 *   to execute the action, move from X, Y, A, to targetX, targetY, targetA
 */
float getTimeForMove(float X, float Y, float A, float targetX, float targetY, float targetZ) {
	return 0;
}
