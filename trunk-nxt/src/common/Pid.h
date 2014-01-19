/**
 * Pid.h
 *
 *
 */

#ifndef _PMX_PID_H__
#define _PMX_PID_H__

#pragma systemFile



float ASSERV_KP = 0.2; //TODO const
float ASSERV_KD = 0.0; //TODO const
float ASSERV_KI = 0.0; //TODO const

// PID working values
float errSum_ = 0.0;
float lastError_ = 0.0;


// Functions
void PidReset();
float PidCompute(int error);



void PidReset()
{
	errSum_ = 0.0;
	lastError_ = 0.0;
}

float PidCompute(int error)
{
	float P, I, D;

	// Preparing PID working values
	errSum_ += error; //somme des erreurs depuis le début
	float errDif = error - lastError_;
	lastError_ = error;

	// Computing PID values
	P = error * ASSERV_KP;	 // Proportionnel
	I = errSum_ * ASSERV_KI; // Intégrale
	D = (error - lastError_) * ASSERV_KD;	 // Dérivée

	return P + I + D; // Le résultat est la somme des 3 composantes calculé
}

#endif
