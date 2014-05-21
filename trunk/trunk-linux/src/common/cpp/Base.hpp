/*!
 * \file
 * \brief Définition de la classe Base.
 */

#ifndef PMX_BASE_HPP
#define PMX_BASE_HPP

#include <string>

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

	void begin(int lResolution, int rResolution, float dist, int startAsserv);

	void printPosition();

	void launchAndEndAfterCmd(RobotCommand* cmd);

	void move(int mm);

	void movexyteta(int forward, float x, float y, float thetaInDegree);

	void findPidAD(float degrees, int mm, int sec);
	void setupPID_AD(float Ap, float Ai, float Ad, float Dp, float Di, float Dd);

	void MoveLineSpeedAcc(int mm, float VMax, float Accel, float Decel);
};
}

#endif
