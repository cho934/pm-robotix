/*
 * iaActionPile.h
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */

#ifndef IAACTIONMANAGER_H_
#define IAACTIONMANAGER_H_

#include <cstdlib>
#include <stdlib.h>

static int iaActionTypeWait = 0; // 1:time(ms), 2:-, 3:-
static int iaActionTypeMoveToCoord = 1; // 1:X, 2:Y, 3:A
static int iaActionTypeAction = 2; // 1:ActionType, 2:-, 3:-

typedef struct iaActionListElement iaActionListElement;
struct iaActionListElement {
	struct iaAction *action;
    struct iaActionListElement *next;
};

typedef struct iaAction iaAction;
struct iaAction {
    int type;
    float param1;
    float param2;
    float param3;
};

iaActionListElement* iaActionManagerAddActionAtEnd(iaAction* actionToAdd, iaActionListElement* pile);
iaActionListElement* iaActionManagerAddActionsAtEnd(iaActionListElement* actionsToAdd, iaActionListElement* pile);
iaAction* iaActionManagerGetNextAction(iaActionListElement* pile);
iaActionListElement* iaActionManagerPop(iaActionListElement* pile);
iaActionListElement* iaActionManagerEmpty(iaActionListElement* pile);
iaAction* iaActionManagerGenerateNewAction(int type, float param1, float param2, float param3);
void iaActionManagerClearAction(iaAction* action);
void iaActionManagerDisplayActionsPile(iaActionListElement* pile);
#endif /* IAACTIONMANAGER_H_ */
