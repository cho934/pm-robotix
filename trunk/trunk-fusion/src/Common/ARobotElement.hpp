/*!
 * \file
 * \brief Définition de la classe ARobotElement.
 */

#ifndef COMMON_AROBOTELEMENT_HPP_
#define COMMON_AROBOTELEMENT_HPP_

namespace pmx
{
    // Prédéclaration de la classe Robot.
    /*!
     * \todo Trouver une méthode plus "standardisé" pour la résolution des noms.
     */
    class Robot;

    /*!
     * \brief Classe abstraite définissant la notion d'élément du robot.
     *
     * Chaque élément du robot possède un lien vers l'objet \ref Robot, quelque
     * soit son niveau dans la hiérarchie. Ceci permet à chaque élément
     * d'accéder simplement au manager et donc de pouvoir ajouter de nouvelles
     * actions.
     */
    class ARobotElement
    {
    private:
        /*!
         * \brief Référence à l'objet Robot.
         */
        pmx::Robot & robot_;

    protected:

        /*!
         * \brief Constructeur de la classe.
         * \param robot Référence à l'objet Robot associé.
         *
         * Ce constructeur est \c protected pour éviter toute instantiation
         * de la classe abstraite.
         */
        ARobotElement(pmx::Robot & robot) : robot_(robot)
        {
        }

    public:

        /*!
         * \brief Retourne une référence sur le robot associé.
         */
        inline pmx::Robot & robot()
        {
            return robot_;
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ARobotElement()
        {
        }
    };
}

#endif
