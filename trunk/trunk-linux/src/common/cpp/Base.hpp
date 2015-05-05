/*!
 * \file
 * \brief Définition de la classe Base.
 */

#ifndef PMX_BASE_HPP
#define PMX_BASE_HPP

#include <string>

#include "../c/path_manager.h"
#include "../c/robot_trajectory.h"
#include "ARobotElement.hpp"
#include "IInitialized.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
/*!
 * \brief Cette classe représente la base roulante du robot.
 *
 * L'objectif de cette classe est de regrouper l'ensemble des méthodes liées
 * au déplacement du robot.
 */
class Base: public ARobotElement, public IInitialized
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Base.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Base");
		return instance;
	}

public:
	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Base.
	 */
	static inline const utils::Logger & mlogger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("motion.c");
		return instance;
	}

	/*!
	 * \brief Constructeur de la classe.
	 * \param robot
	 *        Référence vers le robot associé à cette base roulante.
	 */
	Base(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~Base()
	{
	}

	/*!
	 * \brief Configuration par fichier de conf.
	 */
	virtual void initialize(const std::string& prefix, utils::Configuration& configuration);

	void begin(int lResolution, int rResolution, float dist, int startAsserv, int useExtEncoders);

	void stop();

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
}

#endif
