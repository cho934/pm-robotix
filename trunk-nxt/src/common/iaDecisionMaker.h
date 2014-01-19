#ifndef _IADECISIONMAKER_H_
#define _IADECISIONMAKER_H_ // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DEFINITIONS

typedef enum ACTION_TYPE
{
	ACTION_TYPE_END,
	ACTION_TYPE_MOVE,
	ACTION_TYPE_MOVE_NO_DETECT,
	ACTION_TYPE_TURN,
	ACTION_TYPE_TURN_TO_ANGLE,
	ACTION_TYPE_TURN_AND_MOVE,
	ACTION_TYPE_TURN_AND_MOVE_NO_DETECT,
	ACTION_TYPE_PUSH
} ACTION_TYPE;

typedef struct IAAction
{
	ACTION_TYPE type;
	float value1;
	float value2;
} IAAction;

typedef struct IADecision
{
	bool done;
	float firstPointX;
	float firstPointY;
	float firstPointA;
	int finalActionsSize;
	IAAction finalActions[10];
}IADecision;


// END OF:  DEFINITIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CONSTANTS
/*
// Blue side glasses
float C_A1_X = 900.0;
float C_A1_Y = 950.0;
float C_A2_X = 1250.0;
float C_A2_Y = 950.0;
float C_A3_X = 1050.0;
float C_A3_Y = 1200.0;
float C_A4_X = 1350.0;
float C_A4_Y = 1200.0;
float C_A5_X = 900.0;
float C_A5_Y = 1450.0;
float C_A6_X = 1250.0;
float C_A6_Y = 1450.0;

// Red side glasses
float C_B1_X = 2100.0;
float C_B1_Y = 950.0;
float C_B2_X = 1750.0;
float C_B2_Y = 950.0;
float C_B3_X = 1950.0;
float C_B3_Y = 1200.0;
float C_B4_X = 1650.0;
float C_B4_Y = 1200.0;
float C_B5_X = 2100.0;
float C_B5_Y = 1450.0;
float C_B6_X = 1750.0;
float C_B6_Y = 1450.0;

// Presents
float C_C1_X = 600.0;
float C_C1_Y = 2000.0;
float C_C2_X = 1200.0;
float C_C2_Y = 2000.0;
float C_C3_X = 1800.0;
float C_C3_Y = 2000.0;
float C_C4_X = 2400.0;
float C_C4_Y = 2000.0;

// Hot spots
float C_X1_X = 600.0;
float C_X1_Y = 1700.0;
float C_X2_X = 1500.0;
float C_X2_Y = 1700.0;
float C_X3_X = 2400.0;
float C_X3_Y = 1700.0;
float C_X4_X = 600.0;
float C_X4_Y = 700.0;
float C_X5_X = 1500.0;
float C_X5_Y = 700.0;
float C_X6_X = 1700.0;
float C_X6_Y = 700.0;
*/

float criticalAngleForOponent = 3.0*PI/8;

// END OF:  CONSTANTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: DECLARATIONS

// Init step
void dm_init();
void dm_init_present(int index);
void dm_init_glass(int index);

// Decisions master and tools
void dm_takeDecision(float x1, float y1, float theta1);
//float dm_addMoveTo(float startPosX, float startPosY, float startAngle, float endPosX, float endPosY);

// Match decision
void dm_matchDecide(float x1, float y1, float theta1);
bool dm_isOponentInFirstDirection(float x1, float y1, float theta1, float x2, float y2);
int getCurrentZone(float x1, float y1, float theta1);
int getNextInterrestingZone();

// Test decision
void dm_testDecide(float x1, float y1, float theta1);

// Table test decision
void dm_tableTestDecide(float x1, float y1, float theta1);

// Actions pool management
void dm_actionsNext(ACTION_TYPE* action_type, float* action_value, float* action_turn_value, float* action_move_value, float x1, float y1, float theta1);
void dm_actionsFinishCurrentAction();
void dm_actionsFinishCurrentDecision();
void dm_interruptionOfCurrentDecision(float x1, float y1, float theta1);
void dm_actionsClear();
bool dm_actionsAdd(IAAction action);
bool dm_actionsInsert(IAAction action);

// Maths tools, copied from crobotTrajWrappers
float dm_computeAlphaDelta(float x1, float y1, float theta1, float x2, float y2, float *out_angle, float *out_dist);
float dm_math_atan2f(float y, float x);
// END OF:  DECLARATIONS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif
