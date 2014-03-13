/*!
 * \file
 * \brief Définition de la classe RobotInOutFactory.
 */

#ifndef PMX_ROBOTINOUTFACTORY_H
#define PMX_ROBOTINOUTFACTORY_H

#include "IRobotInOut.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
/*!
 * \brief Fabrique pour les interfaces pmx::IRobotIn et pmx::IRobotOut.
 *
 * L'ordre de sélection de l'implémentation est le suivant:
 * - Carte Armadeus APF9328 (pmx::RobotInApf, pmx::RobotOutApf)
 * - en mode simulation (pmx::RobotInSimulate, pmx::RobotOutSimulate)
 */
class RobotInOutFactory: public utils::Mutex
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref RobotInOutFactory.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger(
				"pmx::RobotInOutFactory");
		return instance;
	}

public:

	/*!
	 * \brief Instance unique de la classe.
	 */
	static RobotInOutFactory * instance();

private:

	/*!
	 * \brief Flux d'entrées/sorties du robot.
	 */
	IRobotInOut * inOut_;

	/*!
	 * \brief Constructeur de la classe.
	 */
	RobotInOutFactory();

public:

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~RobotInOutFactory()
	{
	}

	/*!
	 * \brief Retourne un pointeur vers le flux d'entrée du robot.
	 *
	 * \return Le flux d'entrée du robot.
	 */
	virtual inline IRobotInOut * robotInOut() const
	{
		return inOut_;
	}

};
}

#endif
