#ifndef _MOTOR_SPEED_ORDER
#define _MOTOR_SPEED_ORDER // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "cmotorSpeedCmd.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTOR_SPEED_ORDER_H_
#include "cmotorSpeedCmd.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

void ComputeSpeedCommand( SpeedCommand *out_cmd,
long V0,
long VGoal,
long distMax,
long Accel)
{
	long P1;
	long P2;

	out_cmd->period0 = 0;
	out_cmd->order0 = 0;
	out_cmd->lastOrder = 0;

	out_cmd->phase = SP_PRE_PHASE;

	if(Accel == 0)
	{
		out_cmd->period0 = 0;
		out_cmd->period1 = 0;
		out_cmd->period2 = 0;
		out_cmd->phase = SP_END_PHASE;
	}

	Accel = abs(Accel);
	distMax = abs(distMax);

	out_cmd->V0 = V0;
	out_cmd->VGoal = VGoal;

	//convert acceleration
	if(out_cmd->VGoal - V0 > 0)
	{
		out_cmd->Acceleration = Accel;
	}
	else
	{
		out_cmd->Acceleration = -Accel;
	}

	//convert max distance
	if(out_cmd->VGoal > 0)
	{
		P2 = +distMax;
	}
	else
	{
		P2 = -distMax;
	}

	//compute acceleration duration
	out_cmd->period1 = (out_cmd->VGoal-V0) / out_cmd->Acceleration;

	//compute constant phase duration
	P1 = out_cmd->Acceleration*out_cmd->period1*out_cmd->period1/2+out_cmd->V0*out_cmd->period1;

	if(out_cmd->VGoal != 0)
		out_cmd->period2 = (P2-P1)/out_cmd->VGoal + out_cmd->period1;
	else
		out_cmd->period2 = out_cmd->period1;
}

void ComputeSpeedCommandTime( SpeedCommand *out_cmd,
long V0,
long Time,
long Accel)
{
	out_cmd->order0 = 0;
	out_cmd->lastOrder = 0;

	out_cmd->phase = SP_PRE_PHASE;

	out_cmd->period0 = 0;
	out_cmd->period1 = Time;
	out_cmd->period2 = Time;

	out_cmd->Acceleration = Accel;
	out_cmd->V0 = V0;
	out_cmd->VGoal = V0 + Time * Accel;
}

void ComputeSpeedCommandMaxTime( SpeedCommand *out_cmd,
long V0,
long VGoal,
long Accel,
long Time)
{
	out_cmd->period0 = 0;
	out_cmd->order0 = 0;
	out_cmd->lastOrder = 0;

	out_cmd->phase = SP_PRE_PHASE;

	if(Accel == 0)
	{
		out_cmd->period0 = 0;
		out_cmd->period1 = 0;
		out_cmd->period2 = 0;
		out_cmd->phase = SP_END_PHASE;
	}

	Accel = abs(Accel);
	out_cmd->V0 = V0;
	out_cmd->VGoal = VGoal;

	//convert acceleration
	if(out_cmd->VGoal - V0 > 0)
	{
		out_cmd->Acceleration = Accel;
	}
	else
	{
		out_cmd->Acceleration = -Accel;
	}

	//compute acceleration duration
	out_cmd->period1 = (out_cmd->VGoal-V0) / out_cmd->Acceleration;
	out_cmd->period2 = Time;

	//can we reach VGoal during max time
	if(out_cmd->period1 < Time)
	{
		//all is fine
	}
	else
	{
		out_cmd->period1 = Time;

		//compute speed at the end of traj
		out_cmd->VGoal = Time*out_cmd->Acceleration + V0;
	}
}

void LoadSpeedCommand( SpeedCommand *out_cmd, long lastPos, long periodNb)
{
	//movement begin at next period
	out_cmd->period0 = periodNb;
	out_cmd->period1 += periodNb;
	out_cmd->period2 += periodNb;

	out_cmd->order0 = lastPos;
	out_cmd->lastOrder = lastPos;
}

bool GetSpeedOrder(SpeedCommand *speedCmd, long PeriodN, long *out_order)
{
	bool finished = false;

	switch(speedCmd->phase)
	{
	case SP_PRE_PHASE:
		if(PeriodN >= speedCmd->period0)
		{
			speedCmd->phase = SP_ACCEL_PHASE;
		}
		else
		{
			*out_order = speedCmd->lastOrder + speedCmd->V0;
			break;
		}
		//acceleration phase
	case SP_ACCEL_PHASE:
		if(PeriodN >= speedCmd->period1)
		{
			speedCmd->phase = SP_CONSTANT_PHASE;
		}
		else
		{
			long Tn = PeriodN - speedCmd->period0;

			//For a fixed integration period, DeltaT = 1 period
			//units for acceleration and speed are in ticks/sample² and ticks/sample
			//so we can simplify the formula :
			//Acceleration*DeltaT*(Tx+DeltaT/2.0f) +V0*DeltaT + codo0;
			*out_order = speedCmd->Acceleration*Tn+speedCmd->Acceleration/2 + speedCmd->V0 + speedCmd->lastOrder;
			break;
		}

		//constant speed phase
	case SP_CONSTANT_PHASE:
		if(PeriodN >= speedCmd->period2)
		{
			speedCmd->phase = SP_END_PHASE;
		}
		else
		{
			//Same computation than first phase with acceleration = 0
			*out_order = speedCmd->VGoal + speedCmd->lastOrder;
			break;
		}

	case SP_END_PHASE:
		//We continue at the same speed
		*out_order = speedCmd->VGoal + speedCmd->lastOrder;
		finished = true;
		break;
	};

	speedCmd->lastOrder = *out_order;

	return finished;
}

// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "cmotorSpeedCmd.c")
	//-----------------------------------------------------------------------------------------------------------------------------
	//! @brief     this task tests the functions
	//! @return    none
	//! @author    cho
	//! @note
	//! @todo
	//-----------------------------------------------------------------------------------------------------------------------------
	task main()
	{


	}
#endif // (PROJECT_MAIN_FILE)

// END OF:  TESTS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif//_MOTOR_SPEED_ORDER
