/*!
 * \file
 * \brief Définition de la classe StateWaitForStart.
 */

#ifndef STATEWAITFORSTART_HPP
#define	STATEWAITFORSTART_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AAutomateState.hpp"

/*!
 * \brief Implémente l'attente du commencement du jeu - goupille manuelle.
 */
class StateWaitForStart: public AAutomateState
{
private:

	/*!
	 * La trace associée à la classe StateWaitForStart.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("StateWaitForStart");
		return instance;
	}

public:

	/*!
	 * Constructeur de la classe.
	 */
	StateWaitForStart()
	{
	}
	virtual std::string name()
	{
		return "StateWaitForStart";
	}
	/*!
	 * Destructeur de la classe.
	 */
	virtual ~StateWaitForStart()
	{
	}

	/*!
	 * \brief Attend le lancement du jeu.
	 *
	 * Cette méthode doit être bloquante pour le processus et ne retourner
	 * un résultat qu'une fois l'une de ses transitions actives.
	 *
	 * \param robot
	 *        Le robot à manipuler.
	 * \param data
	 *        Les données associées à l'execution de l'automate.
	 * \return L'état suivant ou \c NULL si la fin de l'automate est atteinte.
	 */
	virtual IAutomateState* execute(Robot& robot, void * data);
};

#endif
