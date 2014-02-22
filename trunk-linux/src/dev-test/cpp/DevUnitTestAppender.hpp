/*!
 * \file
 * \brief Définition de la classe DevUnitTestAppender.
 */

#ifndef UTILS_DEVUNITTESTAPPENDER_HPP
#define UTILS_DEVUNITTESTAPPENDER_HPP

#include "../../common/cpp/MemoryAppender.hpp"

namespace utils
{
    /*!
     * \brief Implémente un appender spécifique à l'execution et au suivi des
     * tests unitaires.
     */
    class DevUnitTestAppender : public MemoryAppender
    {
    private:

        /*!
         * \brief The current indentation level.
         */
        int indent_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        DevUnitTestAppender();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~DevUnitTestAppender();

        /*!
         * \brief Méthode générique de trace d'un message.
         * \param logger
         *        Logger de référence du message.
         * \param level
         *        Niveau de référence du message.
         * \param message
         *        Message à tracer.
         */
        virtual void writeMessage(const utils::Logger & logger, const utils::Level & level, const std::string & message);

        /*!
         * \brief Augmente l'indentation de la trace.
         */
        void increaseIndent();

        /*!
         * \brief Diminue l'indentation de la trace.
         */
        void decreaseIndent();

        /*!
         * \brief Indique qu'un message d'erreur doit avoir été enregistré.
         * 
         * Si le message d'erreur est trouvé, celui-ci est supprimé des messages enregistré.
         * 
         * \param message
         *        Le texte du message enregistré (incluant le logger et le niveau).
         * \return \c true uniquement si le message a été trouvé.
         */
        bool expectedError(const std::string & message);

        /*!
         * \brief Supprime tous les message enregistrés.
         */
        void cleanMessages();
    };
}

#endif
