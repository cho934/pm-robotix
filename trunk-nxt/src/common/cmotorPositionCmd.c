#pragma config(Sensor, S4,     HTANG_LEFT,     sensorI2CCustom)
#pragma config(Sensor, S1,     HTANG_RIGHT,    sensorI2CCustom)
#pragma config(Motor,  motorC,          MOTOR_LEFT,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorA,          MOTOR_RIGHT,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(NXT)

#ifndef _MOTOR_POSITION_ORDER
#define _MOTOR_POSITION_ORDER // prevent multiple compilations

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: ROBOTC PROJECT MAIN FILE DECLARATION
#ifndef PROJECT_MAIN_FILE
#define PROJECT_MAIN_FILE "cmotorPositionCmd.c" //!< enable compilation of task main() and various debug and test functions of this file
#endif
// END OF:  ROBOTC PROJECT MAIN FILE DECLARATION
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: HEADERS
#ifndef _MOTOR_POSITION_ORDER_H_
#include "cmotorPositionCmd.h"
#endif
// END OF:  HEADERS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: GLOBAL INSTANCES
// END OF:  GLOBAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: EXTERNAL SOURCES
#ifndef _MOTOR
#include "cmotor.c"
#endif
// END OF:  EXTERNAL SOURCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: LOCAL INSTANCES
// END OF:  LOCAL INSTANCES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: CODES

void ComputePositionCommand(PositionCommand *out_cmd, long dist, long VMax, long Accel, long Decel)
{
	#if(LEVEL_MOTORPOSCMD <= DEBUG)
	writeDebugStreamLine("cmotorPosCmd.c : ComputePosCmd: dist=%d, VMax=%d, Accel=%d, Decel=%d", dist, VMax, Accel, Decel);
	#endif
	out_cmd->period0 = 0;
	out_cmd->order0 = 0;
	out_cmd->lastOrder = 0;
	out_cmd->phase = TR_PRE_PHASE;
	out_cmd->order3 = out_cmd->order0 + dist;

	Accel = abs(Accel);
	Decel = abs(Decel);
	VMax = abs(VMax);

	//avoid erroneous case
	if(dist == 0 || VMax == 0 || Accel == 0 || Decel == 0)
	{
		#if(LEVEL_MOTORPOSCMD <= DEBUG)
		writeDebugStreamLine("cmotorPosCmd.c : ComputePosCmd: dist == 0 || VMax == 0 || Accel == 0 || Decel == 0 !!!!");
		#endif
		out_cmd->T01 = 0;
		out_cmd->T12 = 0;
		out_cmd->T23 = 0;
		out_cmd->phase = TR_END_PHASE;

		return;
	}

	//convert all acceleration
	if(dist > 0)
	{
		out_cmd->Acceleration = Accel;
		out_cmd->Deceleration = Decel;

		//convert maximum speed
		out_cmd->VMax = VMax;
	}
	else
	{
		out_cmd->Acceleration = -Accel;
		out_cmd->Deceleration = -Decel;

		//convert maximum speed
		out_cmd->VMax = -VMax;
	}

	//compute acceleration / deceleration phases duration
	out_cmd->T01 = out_cmd->VMax/out_cmd->Acceleration;
	out_cmd->T23 = out_cmd->VMax/out_cmd->Deceleration;

	//test if the maximum speed is possible for this distance and acceleration
	//fabs
	if(abs(out_cmd->order0 + (out_cmd->Acceleration*out_cmd->T01*out_cmd->T01/2.0) + (out_cmd->VMax*out_cmd->T23) - (out_cmd->Deceleration*out_cmd->T23*out_cmd->T23/2.0)) > abs(out_cmd->order3))
	{
		//case 1 : maximum speed isn't reachable
		#if(LEVEL_MOTORPOSCMD <= DEBUG)
		writeDebugStreamLine("cmotorPosCmd.c : ComputePosCmd: case 1 : maximum speed isn't reachable");
		#endif
		long order02b;
		out_cmd->T23 = round(sqrt((out_cmd->order3-out_cmd->order0) / ((out_cmd->Deceleration/(2.0*out_cmd->Acceleration)+0.5)*out_cmd->Deceleration))); //sqrtf
		out_cmd->VMax = out_cmd->T23*out_cmd->Deceleration;

		order02b = out_cmd->order3-((out_cmd->VMax*out_cmd->T23)-(out_cmd->T23*out_cmd->T23*out_cmd->Deceleration/2))-out_cmd->order0;
		out_cmd->T01 = round(sqrt(2*order02b/out_cmd->Acceleration)); //sqrtf

		out_cmd->T12 = 0;
	}
	else
	{
		//case 2 : maximum speed is reachable
		#if(LEVEL_MOTORPOSCMD <= DEBUG)
		writeDebugStreamLine("cmotorPosCmd.c : ComputePosCmd: case 1 : maximum speed is reachable");
		#endif
		long order1,order2,order23b,delta;

		order1 = out_cmd->Acceleration * out_cmd->T01*out_cmd->T01/2 + out_cmd->order0;
		order2 = out_cmd->order3 - (out_cmd->Deceleration * out_cmd->T23*out_cmd->T23/2);

		//try to avoid numerical error
		out_cmd->T12 = abs((order2 - order1) / out_cmd->VMax);

		//recalculate deceleration time
		//knowing integer value for speed and time
		//=> reduce numerical error

		//(goal position) - (position after int constant phase)
		order23b = out_cmd->order3-(out_cmd->T12*out_cmd->VMax)-order1;
		delta = out_cmd->VMax*out_cmd->VMax - 2*out_cmd->Deceleration*order23b;

		if(delta > 0)
		{
			if(dist>0)
				out_cmd->T23 = abs((-out_cmd->VMax + sqrt(delta))/out_cmd->Deceleration); //sqrtf
			else
				out_cmd->T23 = abs((-out_cmd->VMax - sqrt(delta))/out_cmd->Deceleration); //sqrtf
		}
	}

	#if(LEVEL_MOTORPOSCMD <= INFO)
	writeDebugStreamLine("cmotorPosCmd.c : ComputePosCmd : period0=%d ,T01=%d, T12=%d, T23=%d", out_cmd->period0, out_cmd->T01, out_cmd->T12, out_cmd->T23);
	#endif
}

void LoadPositionCommand (PositionCommand *out_cmd, MOTOR *motor, long periodNb)
{
	out_cmd->period0 = periodNb;

	out_cmd->lastOrder = motor->lastPos;
	out_cmd->order0 = motor->lastPos;
	out_cmd->order3 += motor->lastPos;

	#if(LEVEL_MOTORPOSCMD <= INFO)
	writeDebugStreamLine("cmotorPosCmd.c : LoadPositionCommand : period0=%d ,lastOrder=%d, order0=%d, order3=%d", out_cmd->period0, out_cmd->lastOrder, out_cmd->order0, out_cmd->order3);
	#endif
}

/*
// 3 phases trapezoidal trajectory (acceleration - constant speed - deceleration)
//    T1 --- T2
//   /        \
//  T0         T3
*/
bool GetPositionOrder(PositionCommand *posCmd, long Tn, long *out_Order)
{
	bool finished = false;

	switch(posCmd->phase)
	{
	case TR_PRE_PHASE:
		#if(LEVEL_MOTORPOSCMD <= INFO)
		writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_PRE_PHASE");
		#endif
		if(Tn >= posCmd->period0)
		{
			posCmd->phase = TR_ACCEL_PHASE;
		}
		else
		{
			*out_Order = posCmd->order0;
			break;
		}

		//acceleration phase
	case TR_ACCEL_PHASE:
		#if(LEVEL_MOTORPOSCMD <= INFO)
		writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_ACCEL_PHASE");
		#endif
		Tn -= posCmd->period0;

		if(Tn >= posCmd->T01)
		{
			#if(LEVEL_MOTORPOSCMD <= DEBUG)
			writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : Tn >= posCmd->T01");
			#endif
			Tn += posCmd->period0;
			posCmd->period0 += posCmd->T01;
			posCmd->phase = TR_CONSTANT_PHASE;
		}
		else
		{
			//For a fixed integration period, DeltaT = 1 period
			//units for acceleration and speed are in ticks/sample� and ticks/sample
			//so we can simplify the formula :
			//Acceleration*DeltaT*(Tx+DeltaT/2.0f) +V0*DeltaT + codo0;
			*out_Order = posCmd->Acceleration*Tn + posCmd->Acceleration/2 + posCmd->lastOrder;
			break;
		}

		//constant speed phase
	case TR_CONSTANT_PHASE:
		#if(LEVEL_MOTORPOSCMD <= INFO)
		writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_CONSTANT_PHASE");
		#endif
		Tn -= posCmd->period0;

		if(Tn >= posCmd->T12)
		{
			Tn += posCmd->period0;
			posCmd->period0 += posCmd->T12;
			posCmd->phase = TR_DECEL_PHASE;
		}
		else
		{
			//Same computation than first phase with acceleration = 0
			*out_Order = posCmd->VMax + posCmd->lastOrder;
			break;
		}

		//deceleration phase
	case TR_DECEL_PHASE:
		#if(LEVEL_MOTORPOSCMD <= INFO)
		writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_DECEL_PHASE Tn=%d", Tn);
		#endif
		Tn -= posCmd->period0;

		if(Tn >= posCmd->T23) //TODO CCH Patch +10
		{
			#if(LEVEL_MOTORPOSCMD <= INFO)
			writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_DECEL_PHASE : Tn >= posCmd->T23!! Tn=%d", Tn);
			#endif
			posCmd->phase = TR_END_PHASE;
		}
		else
		{
			//Same computation than acceleration
			*out_Order = -posCmd->Deceleration*Tn - posCmd->Deceleration/2 + posCmd->VMax + posCmd->lastOrder;
			break;
		}

	case TR_END_PHASE:
		#if(LEVEL_MOTORPOSCMD <= INFO)
		writeDebugStreamLine("cmotorPosCmd.c : GetPositionOrder : TR_END_PHASE");
		#endif
		*out_Order = posCmd->order3;
		finished = true;
		break;
	};

	posCmd->lastOrder = *out_Order;
	return finished;
}


// END OF:  CODES
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// SECTION: TESTS

#if(PROJECT_MAIN_FILE == "cmotorPositionCmd.c")
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

#endif//_MOTOR_POSITION_ORDER
