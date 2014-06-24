/*!
 * \file
 * \brief Définition de l'interface IInitialized.
 */

#ifndef PMX_IINITIALIZED_HPP
#define PMX_IINITIALIZED_HPP

#include <string>
#include "Configuration.hpp"

namespace pmx
{
    /*!
     * \brief Représente la capacité d'initialiser ou de réinitialiser une instance en
     *        fonction d'une configuration donnée.
     */
    class IInitialized
    {
    public:
        
        /*!
         * \brief Initialise l'instance en fonction des informations de la configuration.
         *
         * \param prefix
         *        Prefixe utilisé devant toutes les variables de l'instance.
         * \param configuration
         *        La configuration contenant les infos d'initialisation de l'instance.
         */
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration) = 0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IInitialized()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         */
        IInitialized()
        {}
    };
};

#endif
