/*!
 * \file
 * \brief Définition de la classe ConsoleAppender.
 */

#ifndef UTILS_CONSOLEAPPENDER_H
#define	UTILS_CONSOLEAPPENDER_H

#include <string>
#include <iostream>
#include "MemoryAppender.hpp"
#include "Thread.hpp"
#include "LedIndicator.hpp"

namespace utils
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
    class ConsoleAppender : public MemoryAppender, public Thread
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
        ConsoleAppender() : out_(& std::cout)
        {
        }

        /*!
         * \brief Constructeur initialisé de la classe.
         * \param out Le flux de sortie associé à cet Appender.
         */
        ConsoleAppender(std::ostream * out) : out_(out)
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
        virtual void inline writeMessage(const utils::Logger & logger, const utils::Level & level, const std::string & message)
        {
            if (this->state() == utils::CREATED)
            {
                //std::cout << "Thread ConsoleAppender Start." << std::endl;
                bool ret = this->start();

                //affichage LEDINDICATOR
                if(ret == false)
                {
                    pmx::LedIndicator::instance().setOn(1);
                }else
                {
                    pmx::LedIndicator::instance().setOff(1);
                }
            }

            utils::MemoryAppender::writeMessage(logger, level, message);
        }

        virtual void execute();

        virtual void flush();
    };
}

#endif
