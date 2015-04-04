/*!
 * \file
 * \brief Définition de la classe Base.
 */

#ifndef BASE_HPP_
#define BASE_HPP_

#include "../AsservIa/path_manager.h"
//#include "../AsservIa/robot_trajectory.h"

/*!
 * \brief Cette classe représente la base roulante du robot.
 *
 * L'objectif de cette classe est de regrouper l'ensemble des méthodes liées
 * au déplacement du robot.
 */
class Base
{
private:


	/*!
	 * \brief Constructeur de la classe.
	 */
	Base();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~Base()
	{
	}

	void begin(int lResolution, int rResolution, float dist, int startAsserv, int useExtEncoders);

	void printPosition();

	TRAJ_STATE launchAndEndAfterCmd(RobotCommand* cmd);

	void collisionOccured(int front);

	int getMatchColor();
	void setMatchColor(int color);

	void assistedHandling();

	TRAJ_STATE move(int mm);

	TRAJ_STATE movexyteta(int forward, float x, float y, float thetaInDegree);

	void findPidAD(float degrees, int mm, int sec);

	void findPidLR(int posLmm, int posRmm, int sec);
	void setupPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd);
	void setupPID_LR(float Ap, float Ai, float Ad, float Dp, float Di, float Dd);

	void LineSpeedAcc(int mm, float VMax, float Accel, float Decel);
	void RotateSpeedAcc(int degrees, float VMax, float Accel, float Decel);

	void SpeedControlLR(float spLeft, int distLeftmm,
	float accLeft, float spRight, int distRightmm, float accRight);
	void ArcRotate(int degrees, float radius);
};


#endif
