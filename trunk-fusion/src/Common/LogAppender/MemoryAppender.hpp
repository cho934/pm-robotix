/*!
 * \file
 * \brief Définition de la classe MemoryAppender.
 */

#ifndef LOGS_MEMORYAPPENDER_HPP_
#define	LOGS_MEMORYAPPENDER_HPP_

#include <list>
#include <sstream>
#include <string>

#include "../Thread/Mutex.hpp"
#include "Level.hpp"
#include "Logger.hpp"

namespace logs
{
/*!
 * \brief Implémentation de Appender stockant les messages en mémoire.
 *
 * La méthode flush() permet d'effectuer un affichage des messages sur la
 * sortie standard. Cette méthode est automatiquement appelé lors de la
 * destruction de l'objet.
 */
class MemoryAppender: public Appender, public utils::Mutex
{
protected:

	/*!
	 * \brief Liste des messages enregistrés.
	 */
	std::list<std::string> messages_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	MemoryAppender();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~MemoryAppender();

	/*!
	 * \return Liste des messages enregistrés.
	 */
	inline const std::list<std::string> & messages() const
	{
		return messages_;
	}

	/*!
	 * \brief Méthode générique de trace d'un message. Ajoute le nom du log devant chaque entrée.
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
		this->lock();
		std::ostringstream out;
		out << logger.name() << " " << level.name() << " " << message;
		this->messages_.push_back(out.str());
		this->unlock();
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
	virtual void inline writeMessageOnly(const std::string & message)
	{
		this->lock();
		std::ostringstream out;
		out << message;
		this->messages_.push_back(out.str());
		this->unlock();
	}

	/*!
	 * \brief Cette méthode affiche tous les messages engistrés sur le
	 * flux de sortie standard.
	 */
	virtual void flush();
};
}

#endif
