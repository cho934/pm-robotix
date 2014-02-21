/*!
 * \file
 * \brief Définition de la classe FileAppender.
 */

#ifndef UTILS_FILEAPPENDER_H
#define	UTILS_FILEAPPENDER_H

#include <string>
#include <fstream>
#include "MemoryAppender.hpp"
#include "Thread.hpp"

namespace utils
{
    /*!
     * \brief Implémentation de Appender pour une sortie sur fichier.
     *
     * Cette implémentation se base sur un thread secondaire pour l'écriture
     * dans le fichier des informations.
     */
    class FileAppender : public MemoryAppender, public Thread
    {
    private:

        /*!
         * Flux de sortie associé.
         */
        std::ofstream ofs_;

        void printData();

    public:

        /*!
         * \brief Constructeur initialisé de la classe.
         * \param filename Le nom du fichier associé à cet Appender.
         */
        FileAppender(const std::string & filename) : ofs_(filename.c_str())
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~FileAppender();

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
                //std::cout << "Thread FileAppender Start." << std::endl;
                printf(" Thread ConsoleAppender Start. \n");
                this->start();
            }

            utils::MemoryAppender::writeMessage(logger, level, message);
        }

        virtual void execute();

        virtual void flush();
    };
}

#endif
