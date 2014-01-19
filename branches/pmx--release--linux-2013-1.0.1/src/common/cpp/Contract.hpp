/*!
 * \file
 * \brief Définition de la classe Contract.
 */

#ifndef UTILS_CONTRACT_HPP
#define UTILS_CONTRACT_HPP

#include <string>
#include "Exception.hpp"

namespace utils
{

    /*!
     * \brief Exception lancée si un contrat n'est pas respectée par une méthode
     * ou sont appelant.
     */
    class ContractException : public Exception
    {
    public:

        ContractException(const std::string & message) : Exception(message)
        {
        }

        virtual ~ContractException() throw ()
        {
        }
    };

    /*!
     * \brief Permet de valider les paramètres d'une méthode ou son résultat
     * pour confirmer que son 'contrat' est respecté.
     */
    class Contract
    {
    public:
        /*!
         * \brief Vérifie qu'une valeur est bien différente de \c NULL.
         * \param value La valeur a tester.
         * \param message Le message utilisé en cas d'erreur.
         * 
         * Cette méthode lance une exception si le paramètre value vaut \c NULL.
         */
        static void isNotNull(void * value, const std::string& message);
    };
}

#endif
