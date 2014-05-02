/*
 * iaActionManager.c
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */
#include "iaActionManager.h"
#include "iaLogger.h"


iaActionListElement* iaActionManagerAddActionAtEnd(iaAction* actionToAdd, iaActionListElement* pile) {
	printf("iaActionManagerAddActionAtEnd\n");
	if (actionToAdd) {
		/* Creating List element */
		iaActionListElement* newElement = (iaActionListElement*)malloc(sizeof(iaActionListElement));

		/* filling the new ActionListElement */
		newElement->action = actionToAdd;
		newElement->next = NULL;

		return iaActionManagerAddActionsAtEnd(newElement, pile);
	} else {
		printf("action to add null\n");
		return pile;
	}
}

iaActionListElement* iaActionManagerAddActionsAtEnd(iaActionListElement* actionsToAdd, iaActionListElement* pile) {
	printf("iaActionManagerAddActionsAtEnd\n");
	if (actionsToAdd) {
		if(pile) {
			iaActionManagerDisplayActionsPile(pile);
			/* Find the last element of the list */
			iaActionListElement* temp=pile;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			/* Add the new one */
			temp->next = actionsToAdd;
			return pile;
		} else {
			/* If no list exist, just return the new one */
			printf("current pile is null\n");
			return actionsToAdd;
		}
	} else {
		printf("action to add is null\n");
		return pile;
	}
}

iaAction* iaActionManagerGetNextAction(iaActionListElement* pile) {
	printf("iaActionManagerGetNextAction\n");
	if(pile) {
		return pile->action;
	} else {
		/* If no list exist, just return the new one */
		return NULL;
	}
}

iaActionListElement* iaActionManagerPop(iaActionListElement* pile) {
	printf("iaActionManagerPop\n");
	if(pile) {
		iaActionListElement* newPile = pile->next;
		free(pile);
		return newPile;
	} else {
		/* If no list exist, just return the new one */
		return NULL;
	}
}

iaActionListElement* iaActionManagerEmpty(iaActionListElement* pile) {
	printf("iaActionManagerEmpty\n");
	while(pile) {
		/* If no list exist, just return the new one */
		pile = iaActionManagerPop(pile);
	}
	return pile;
}

iaAction* iaActionManagerGenerateNewAction(int type, float param1, float param2, float param3) {
	iaAction* action = (iaAction*)malloc(sizeof(iaAction));
	action->type = type;
	action->param1 = param1;
	action->param2 = param2;
	action->param3 = param3;
	return action;
}

void iaActionManagerClearAction(iaAction* action) {
	free(action);
}


void iaActionManagerDisplayActionsPile(iaActionListElement* pile) {
	iaLogDebug("- Current decisions pile:");
	iaActionListElement* currentActionsPileToDisplay = pile;
	iaLogDebug("A");
	while (currentActionsPileToDisplay) {
		iaLogDebug("B");
		iaAction* action = currentActionsPileToDisplay->action;
		iaLogDebug("C");
		printf("    Action: %i [%f, %f, %f]\n", action->type, action->param1, action->param2, action->param3);
		iaLogDebug("D");
		currentActionsPileToDisplay = currentActionsPileToDisplay->next;
		iaLogDebug("E");
	}
}
