/*!
 * \file
 * \brief Définition de la classe Wait90SecondsAction.
 */

#ifndef WAIT90SECONDSACTION_HPP
#define	WAIT90SECONDSACTION_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "../../Thread/Thread.hpp"

class Robot;

/*!
 * \brief Cette action lance le chronometer du robot.
 */
class Wait90SecondsAction: public utils::Thread // , public AAutomateState
{
private:

	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Wait90SecondsAction");
		return instance;
	}

	/*!
	 * \brief Référence vers le robot.
	 */
	Robot & robot_;

	void * data_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	Wait90SecondsAction(Robot& robot, void *data);

	virtual std::string name()
	{
		return "Wait90SecondsAction";
	}
	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ Wait90SecondsAction()
	{
	}

	/*!
	 * \brief Execute l'action.
	 */
	virtual void execute();
};

#endif
