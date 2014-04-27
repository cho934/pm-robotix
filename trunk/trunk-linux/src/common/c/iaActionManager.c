/*
 * iaActionManager.c
 *
 *  Created on: 18 Apr 2014
 *      Author: pmx
 */
#include "iaActionManager.h"

#include <stdlib.h>


iaActionListElement* iaActionManagerAddActionAtEnd(iaAction* actionToAdd, iaActionListElement* pile) {
	if (actionToAdd != NULL) {
		/* Creating List element */
		iaActionListElement* newElement = (iaActionListElement*)malloc(sizeof(iaActionListElement));

		/* filling the new ActionListElement */
		newElement->action = actionToAdd;
		newElement->next = NULL;

		return iaActionManagerAddActionsAtEnd(newElement, pile);
	} else {
		return pile;
	}
}

iaActionListElement* iaActionManagerAddActionsAtEnd(iaActionListElement* actionsToAdd, iaActionListElement* pile) {
	if (actionsToAdd != NULL) {
		if(pile == NULL) {
			/* If no list exist, just return the new one */
			return actionsToAdd;
		} else {
			/* Find the last element of the list */
			iaActionListElement* temp=pile;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			/* Add the new one */
			temp->next = actionsToAdd;
			return pile;
		}
	} else {
		return pile;
	}
}

iaAction* iaActionManagerGetNextAction(iaActionListElement* pile) {
	if(pile == NULL) {
		/* If no list exist, just return the new one */
		return NULL;
	} else {
		return pile->action;
	}
}

iaActionListElement* iaActionManagerPop(iaActionListElement* pile) {
	if(pile == NULL) {
		/* If no list exist, just return the new one */
		return NULL;
	} else {
		iaActionListElement* newPile = pile->next;
		free(pile);
		return newPile;
	}
}

iaActionListElement* iaActionManagerEmpty(iaActionListElement* pile) {
	while(pile != NULL) {
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
