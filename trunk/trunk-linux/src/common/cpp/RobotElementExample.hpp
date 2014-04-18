/*!
 * \file
 * \brief Définition de la classe RobotElementExample.
 */

#ifndef PMX_ROBOTELEMENTEXAMPLE_HPP
#define PMX_ROBOTELEMENTEXAMPLE_HPP

#include "ARobotElement.hpp"
#include "LoggerFactory.hpp"


namespace pmx
{
/*!
 * \brief Implementation for RobotElementExample.
 */
class RobotElementExample: public ARobotElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref RobotElementExample.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotElementExample");
		return instance;
	}

	bool connected_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	RobotElementExample(pmx::Robot & robot);

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~RobotElementExample()
	{
	}

	bool isConnected()
	{
		return connected_;
	}

private:

};
}

#endif
