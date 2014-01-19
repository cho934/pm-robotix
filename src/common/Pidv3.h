/**
 * Pidv3.h
 *
 *
 */

#ifndef _PMX_PID_H__
#define _PMX_PID_H__

#pragma systemFile


typedef struct
{
  float kp;
  float ki;
  float kd;
  float errSum;
  float lastError;
  int lastInput;
  int max;
  int min;

} PIDParams;

// Functions
void pidReset(PIDParams* obj);
float pidCompute(PIDParams* obj, int error);
float pidComputeOptimized(PIDParams* obj, int input, int error);
void setPidValues(PIDParams* obj, float Kp, float Ki, float Kd);
void setPidOutputLimits(PIDParams* obj, int Max, int Min);
float getP(PIDParams* obj);

void setPidOutputLimits(PIDParams* obj, int Max, int Min) //TODO ajouter le Sens de marche
{
	if(obj == NULL)
    return;
  obj->min = Min;
  obj->max = Max;
}

void setPidValues(PIDParams* obj, float Kp, float Ki, float Kd)
{
	if(obj == NULL)
    return;
  obj->kp = Kp;
  obj->ki = Ki;
  obj->kd = Kd;
}

float getP(PIDParams* obj)
{
  if(obj == NULL)
    return -1;
  return obj->kp;
}

void pidReset(PIDParams* obj)
{
	obj->errSum = 0.0;
	obj->lastError = 0.0;
	obj->lastInput = 0.0;
}

float pidCompute(PIDParams* obj, int error)
{
	float P, I, D, res;

	// Preparing PID working values
	obj->errSum += error; //somme des erreurs depuis le début
	obj->lastError = error;

	// Computing PID values
	P = error * obj->kp;	 // Proportionnel
	I = obj->errSum * obj->ki; // Intégrale
	D = (error - obj->lastError) * obj->kd;	 // Dérivée

	res = P + I + D; // Le résultat est la somme des 3 composantes calculé

	return res;
}

float pidComputeOptimized(PIDParams* obj, int input, int error)
{
	float P, I, D, res;

	// Preparing PID working values
	obj->errSum += error; //somme des erreurs depuis le début
	int dInput = (input - obj->lastInput);

	// Computing PID values
	P = error * obj->kp;	 // Proportionnel
	I = obj->errSum * obj->ki; // Intégrale
	D = (dInput) * obj->kd;	 // Dérivée

	res = P + I + D; // Le résultat est la somme des 3 composantes calculé
	obj->lastInput = input;
	return res;
}

float pidComputeRcva(PIDParams* obj, float ecart, float vitesse)
{
	//http://www.rcva.fr/index.php?option=com_content&view=article&id=27&Itemid=42&limitstart=8
	/*
	commande = ecart * GAIN_PROPORTIONNEL_DISTANCE
	commande_distance = commande – GAIN_DERIVE_DISTANCE*vitesse
	commande_roue_D= commande_distance
	commande_roue_G= commande_distance
	*/
	float commande = ecart * obj->kp;
	float commande_distance = commande - obj->ki * vitesse; //utilise kd et non ki

	return commande_distance;
}

#endif
