/*!
 * \file
 * \brief Définition de la classe ConsoleAppender.
 */

#ifndef UTILS_CONSOLEAPPENDER_H
#define	UTILS_CONSOLEAPPENDER_H

#include <string>
#include <iostream>
#include "Logger.hpp"

namespace utils
{
    /*!
     * \brief Implémentation de Appender pour une sortie sur un flux de sortie
     * de type std::ostream.
     *
     * Le constructeur par défaut de cette classe permet de créer un Appender
     * vers la sortie standard.
     */
    class ConsoleAppender : public Appender
    {
    private:
        
        /*!
         * Flux de sortie associé.
         */
        std::ostream * out_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         * L'appender sera associé au flux de sortie standard.
         */
        ConsoleAppender() : out_(& std::cout)
        {}
        
        /*!
         * \brief Constructeur initialisé de la classe.
         * \param out Le flux de sortie associé à cet Appender.
         */
        ConsoleAppender(std::ostream * out) : out_(out)
        {}
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ ConsoleAppender()
        {}
        
        /*!
         * \brief Méthode générique de trace d'un message.
         * \param logger
         *        Logger de référence du message.
         * \param level
         *        Niveau de référence du message.
         * \param message
         *        Message a tracer.
         */
        virtual void inline writeMessage(const utils::Logger & logger, const utils::Level & level, const std::string & message)
        {
            (*this->out_) << logger.name() << " " << level.name() << " " << message << std::endl;
        }
    };
}
#endif
