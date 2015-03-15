#ifndef ACTIONS_HPP_
#define ACTIONS_HPP_

#include "../LogAppender/LoggerFactory.hpp"
#include "ActionManager.hpp"
#include "ARobotElement.hpp"

/*!
 * List of robot actions. It contains all common RobotElement.
 */
class Actions
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedBar.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Actions");
		return instance;
	}

	/*!
	 * \brief Assure la gestion des actions du robot en mode asynchrone.
	 */
	ActionManager actionManager_;

public:

	/*!
	 * \brief Constructor.
	 *
	 * \param nb Number of leds in the LedBar.
	 */
	Actions()
	{
	}

	/*!
	 * \brief Destructor.
	 */
	~Actions()
	{

	}

	/*!
	 * \brief Ajout d'une action.
	 * \param action
	 *        L'action à ajouter.
	 */
	inline void addAction(IAction * action)
	{
		actionManager_.addAction(action);
	}

	/*!
	 * \brief Active les actions.
	 *
	 * Cette méthode lance le thread gérant le ActionManager.
	 */
	void start();

	/*!
	 * \brief Arrete le robot et libère les ressources associés.
	 */
	void stop();

	/*!
	 * \brief Arrete le thread sensorManager et actionManager.
	 */
	void stopManagers();

	/*!
	 * \brief Arrete les composant du robot.
	 */
	void stopDevices();

};

#endif
