/**
* SpeedManagerv3.h
*
*
*/

#ifndef _PMX_SPEEDMANAGERPOLAR_H__
#define _PMX_SPEEDMANAGERPOLAR_H__

#pragma systemFile

#ifndef _PMX_PID_H__
#include "Pidv3.h"
#endif

#ifndef __TMR_H__
#include "drivers/timer.h"
#endif


// Robot mechanical values
#define WHEEL_DIAMETER 80 //mm
#define DIST_PER_TICK 0.6981317 //1.0*WHEEL_DIAMETER*PI/360.0 //mm
#define ENTRAX 137 //mm
// Asserv period
#define PERIOD_ASSERV 50 //ms
// Speed Motor configuration
#define MOTOR_LEFT motorA
#define MOTOR_RIGHT motorC
#define MAXSPEED 95
//#define MINSPEED 8
#define MIN_POWER 10
//#define MAX_ACC 3
// Nb ticks for stop robot
//#define NB_TICK_TO_STOP_ASSERV 1


// Asserv working values
#define ACT_NONE 0
#define ACT_FORWARD 1
#define ACT_BACKWARD -1
#define ACT_TURN_RIGHT 1
#define ACT_TURN_LEFT -1
static int arrived = false;
static int action = ACT_NONE;
static int actionTurn = ACT_NONE;
static int targetDistance = 0; // Tick
static int targetOrientation = 0; //Tick
static int lastEncoderLeft = 0;
static int lastEncoderRight = 0;
static int lastVitesse = 0;
static int lastOrderLeft = 0;
static int lastOrderRight = 0;
static float acc = 0;
static float maxDeltaOrder = 0;
static int pidCount = 0;

static PIDParams pidRotation;
static PIDParams pidDistance;


// Functions
task timerAsservPolarTask();
void timerAsservPolar();
void moveNxtWithBrake(int distanceMm, float degre, float accMparS2);
void executePID();
int mmToTicks(int mm);
int degToTicks(int deg);
//float convertSpeedToPower(int speedTick); //converti une vitesse (en tick par PERIOD_ASSERV) en puissance moteur.
int convertAccelerationToTick(float accMparM2);

task timerAsservPolarTask()
{
	timerAsservPolar();
}

void timerAsservPolar()
{
	writeDebugStreamLine("Starting asserv.");
	// Create Timer
	int TMRAsservPolar = TMRnewTimer();
	// Configure timerAsserv for PERIOD_ASSERV
	TMRsetup(TMRAsservPolar, PERIOD_ASSERV);
	// Reset and start timer
	TMRreset(TMRAsservPolar);
	while(!arrived)
	{
		// If timerAsserv expires, make a small noise and reset it.
		if (TMRisExpired(TMRAsservPolar))
		{
			//PlayTone(784, 20);
			//PlaySound(soundShortBlip);
			//while(bSoundActive) EndTimeSlice();
			executePID();
			TMRreset(TMRAsservPolar);
		}
		EndTimeSlice();
	}
}

void moveNxtWithBrake(int distanceMm, float degre, float accMparS2)
{
	//reset PID Position
	pidReset(&pidRotation);
	pidReset(&pidDistance);
	//reset asserv
	targetDistance = 0; // Tick
	targetOrientation = 0.0; //Tick
	lastEncoderLeft = 0;
	lastEncoderRight = 0;
	lastVitesse = 0;
	lastOrderLeft = 0;
	lastOrderRight = 0;
	pidCount = 0;
	//reset encoder
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;

	targetDistance = mmToTicks(distanceMm);
	targetOrientation = degToTicks(degre);

	if(targetOrientation < 0){
		actionTurn = ACT_TURN_RIGHT;
		//DEBUG
		writeDebugStreamLine("Turn Left (%d deg = %dticks)", degre, targetOrientation);
		}else if(targetOrientation > 0){
		actionTurn = ACT_TURN_LEFT;
		//DEBUG
		writeDebugStreamLine("Turn Right (%d deg = %dticks)", degre, targetOrientation);
	}
	if(targetDistance < 0){
		action = ACT_BACKWARD;
		//DEBUG
		writeDebugStreamLine("Moving backward (%dmm = %dticks)", distanceMm, targetDistance);
		}else if(targetDistance > 0){
		action = ACT_FORWARD;
		//DEBUG
		writeDebugStreamLine("Moving forward (%dmm = %dticks)", distanceMm, targetDistance);
	}

	acc = convertAccelerationToTick(accMparS2); //TODO a convertir M/s2 => tick
	maxDeltaOrder = (acc * 0.88 * 100.0 / PERIOD_ASSERV); //delta max force moteur par PERIOD_ASSERV

	//LOG
	writeDebugStreamLine("pidCount,deltaAcc,encoderL,encoderR,dist,vit,distO,rotO,OrderL,OrderR");

	StartTask(timerAsservPolarTask, 10);
	while(!arrived)
	{
		wait1Msec(PERIOD_ASSERV);
	}

	//TODO : tuer la task timerAsservStdTask !!
}

void executePID()
{
	int encoderLeft = nMotorEncoder[MOTOR_LEFT];
	int encoderRight = nMotorEncoder[MOTOR_RIGHT];
	int deltaLeft = encoderLeft - lastEncoderLeft;
	int deltaRight = encoderRight - lastEncoderRight;

	// ============
	// = DISTANCE =
	// ============
	/*
	Sans terme intégral et avec contrôle dérivé de la sortie
	distance = (roue_d + roue_g) /2
	vitesse= (vitesse_roue_d + vitesse_roue_g)/2
	ecart = consigne_distance - distance
	*/
	float distance = (encoderLeft + encoderRight) / 2.0;
	float vitesse = (deltaLeft + deltaRight) / 2.0;
	float ecart = (float)targetDistance - distance;
	float distanceOrder = 0.0;
	distanceOrder = pidComputeRcva(&pidDistance, ecart, vitesse);

	float deltaAccReal = vitesse - lastVitesse; //en tick par PERIOD_ASSERV
	//int pos_phase_dec = targetDistance / 2;


	// ============
	// = ROTATION =
	// ============
	/*
	orientation = roue_D – roue_G
	vitesse_orientation=vitesse_roue_D – vitesse_roue_G
	ecart = consigne_orientation - orientation
	*/
	float orientation = encoderRight - encoderLeft;
	float vitesseOrientation = deltaRight - deltaLeft;
	float ecartOrientation = targetOrientation - orientation;
	float rotationOrder = pidComputeRcva(&pidRotation, ecartOrientation, vitesseOrientation);

	// ==================
	// = EXECUTE ORDERS =
	// ==================
	float orderLeft = distanceOrder - rotationOrder;
	float orderRight = distanceOrder + rotationOrder;


	float dl = orderLeft - lastOrderLeft;
	float dr = orderRight - lastOrderRight;



	// Limit Acceleration during movement

	//writeDebugStreamLine("dl dr :%f, %f,", dl, dr);
	//if (action == ACT_FORWARD && deltaAccReal > acc) //avec turn ou pas
	//{
	//	dl = dl / (deltaAccReal / acc);
	//	dr = dr / (deltaAccReal / acc);
	//}
	//if (action == ACT_BACKWARD && deltaAccReal < -acc) //avec turn ou pas
	//{
	//	dl = dl / (deltaAccReal / -acc);
	//	dr = dr / (deltaAccReal / -acc);
	//}
	//writeDebugStreamLine("apres dl dr :%f, %f,", dl, dr);

	if(action == ACT_FORWARD || actionTurn == ACT_TURN_RIGHT)//avance ou tourner a droite
	{
		if (dl > maxDeltaOrder) { dl = maxDeltaOrder; }
	}
	if(action == ACT_FORWARD || actionTurn == ACT_TURN_LEFT)//avance ou tourner a gauche
	{
		if (dr > maxDeltaOrder) { dr = maxDeltaOrder; }
	}
	if(action == ACT_BACKWARD || actionTurn == ACT_TURN_LEFT)//recule ou tourner a gauche
	{
		if (dl < -maxDeltaOrder) {	dl = -maxDeltaOrder; }
	}
	if(action == ACT_BACKWARD || actionTurn == ACT_TURN_RIGHT)//recule ou tourner a droite
	{
		if (dr < -maxDeltaOrder) {	dr = -maxDeltaOrder; }
	}

	orderLeft = lastOrderLeft + dl;
	orderRight = lastOrderRight + dr;

	// Limit Speed
	float limit = 0.0;
	//if(action == ACT_FORWARD || action == ACT_BACKWARD)
	//{
	//	limit = action * (25.0 + (40.0 / 700.0 * ecart));
	//	if (limit > MAXSPEED) { limit = MAXSPEED; }
	//	if (limit < -MAXSPEED) { limit = -MAXSPEED; }
	//	//coef = ecart * 0.6 / 500.0;
	//	//if (ecart > 1000.0) { coef = 1; }
	//	//if (ecart < 150.0) { coef = 0.25; }
	//}else
	//{
	//	//coef = ecartOrientation * 0.27 / 500.0;
	//	//if (ecartOrientation > 1000.0) { coef = 1; }
	//	//if (ecartOrientation < 150.0) { coef = 0.15; }
	//}
	//writeDebugStreamLine("ecart:%f, limit:%f,", ecart, limit);

	limit = MAXSPEED;
	//float limit = MAXSPEED * coef;
	if(orderLeft > limit) { orderLeft = limit; }
	if(orderLeft < -limit) { orderLeft = -limit; }
	if(orderRight > limit) { orderRight = limit; }
	if(orderRight < -limit) { orderRight = -limit; }




	//Apply Motors
	motor[MOTOR_LEFT] = orderLeft;
	motor[MOTOR_RIGHT] = orderRight;

	//log
	writeDebugStreamLine("%d,%.2f,%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", pidCount, deltaAccReal, encoderLeft, encoderRight, distance, vitesse, distanceOrder, rotationOrder, orderLeft, orderRight);

	lastEncoderLeft = encoderLeft;
	lastEncoderRight = encoderRight;
	lastVitesse = vitesse;
	lastOrderLeft = orderLeft;
	lastOrderRight = orderRight;
	pidCount ++;
}

int mmToTicks(int mm)
{
	return (int)(1.0*mm/(DIST_PER_TICK));
}

int degToTicks(int deg)
{
	return mmToTicks((1.0*deg/360.0)*(2.0*PI*ENTRAX));
}

//float convertSpeedToPower(int speedTick)
//{
//	float power = (speedTick * 0.88) - 2.0; //COEFF pour 100ms de PERIOD_ASSERV
//	if (power < MIN_POWER){power = MIN_POWER;}
//	return power;
//}

int convertAccelerationToTick(float accMparM2)
{
	return accMparM2;
}

#endif
