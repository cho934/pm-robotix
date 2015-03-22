/*!
 * \file
 * \brief Définition de la classe ConsoleAppender.
 */

#ifndef LOGS_CONSOLEAPPENDER_HPP_
#define	LOGS_CONSOLEAPPENDER_HPP_

#include <iostream>
#include <sstream>
#include <string>

#include "../LogAppender/Level.hpp"
#include "../LogAppender/Logger.hpp"
#include "../LogAppender/MemoryAppender.hpp"
#include "../Thread/Thread.hpp"

namespace logs
{
/*!
 * \brief Implémentation de Appender pour une écriture des traces
 * sur un flux de sortie de type std::ostream.
 *
 * Cette implémentation se base sur un thread secondaire pour l'écriture
 * dans le fichier des informations.
 *
 * Le constructeur par défaut de cette classe permet de créer un Appender
 * vers la sortie standard.
 */
class ConsoleAppender: public MemoryAppender, public utils::Thread
{
private:

	/*!
	 * Flux de sortie associé.
	 */
	std::ostream * out_;

	void printData();

public:

	/*!
	 * \brief Constructeur par défaut.
	 * L'appender sera associé au flux de sortie standard.
	 */
	ConsoleAppender()
			: out_(&std::cout)
	{
	}

	/*!
	 * \brief Constructeur initialisé de la classe.
	 * \param out Le flux de sortie associé à cet Appender.
	 */
	ConsoleAppender(std::ostream * out)
			: out_(out)
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ConsoleAppender()
	{
	}

	/*!
	 * \brief Méthode générique de trace d'un message.
	 * \param logger
	 *        Logger de référence du message.
	 * \param level
	 *        Niveau de référence du message.
	 * \param message
	 *        Message à tracer.
	 */
	virtual void inline writeMessage(const logs::Logger & logger, const logs::Level & level,
			const std::string & message)
	{
		if (this->state() == utils::CREATED)
		{
			//printf(" Thread ConsoleAppender start \n");
			std::ostringstream msg;
			msg << "ConsoleAppender created by " << logger.name() << " " << level.name();
			this->start(msg.str());
		}

		logs::MemoryAppender::writeMessage(logger, level, message);
	}

	virtual void execute();

	virtual void flush();
};
}

#endif
