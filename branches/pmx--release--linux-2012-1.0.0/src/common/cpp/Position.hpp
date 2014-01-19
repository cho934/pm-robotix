/*!
 * \file
 * \brief Définition de la classe Position.
 */

#ifndef PMX_POSITION_H
#define	PMX_POSITION_H

#include <iostream>
#include "RobotColor.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe \b immuable regroupe les éléments propres au positionnement
     * d'un élément et du robot en particulier.
     *
     * Le positionnement se base sur une coordonnée dans le plan (x, y) et un angle.
     * La coordonnée correspond au positionnement de l'élément et l'angle à son orientation.
     *
     * Les unités de référence sont les suivantes :
     * - les millimètres pour les distances (x et y),
     * - les radians (PI) pour les angles.
     *
     * Les références du plan se basent sur les règles suivantes :
     * - Si l'angle associé à l'élément vaut 0 alors l'élément est parallèle à l'axe X.
     * - Si l'angle associé à l'élément vaut PI/2 alors l'élément est parallèle à l'axe Y.
     */
    class Position
    {
    private:
        
        /*!
         * \brief Position suivant l'axe X.
         * \sa Position x en mm
         */
        double x_;

        /*!
         * \brief Position suivant l'axe Y.
         * \sa Position y en mm
         */
        double y_;

        /*!
         * \brief Angle de référence. Compris dans l'intervalle [-PI,PI].
         * \sa Position angle en radian.
         */
        double angle_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         * \c x, \c y et \c angle valent 0.
         */
        Position();
        
        /*!
         * \brief Constructeur par recopie.
         * \param position Position à copier.
         */
        Position(const Position& position);
        
        /*!
         * \brief Constructeur initialisé.
         * \param x Position suivant l'axe X.
         * \param y Position suivant l'axe Y.
         * \param angle Angle de référence.
         */
        Position(double x, double y, double angle);
        
        /*!
         * \brief Opérateur d'affectation.
         * \param position Position à copier.
         */
        void operator=(const Position& position);
        
        /*!
         * \brief Ajoute une valeur à \c angle. Cette méthode renvoie une nouvelle position.
         * \param angle Valeur ajoutée à \c angle.
         * \return Nouvelle position.
         */
        Position rotate(double angle);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ Position()
        {}

    public:
        
        inline double x() const
        {
            return x_;
        }

        inline void x(double value)
        {
            this->x_ = value;
        }

        inline double y() const
        {
            return y_;
        }

        inline void y(double value, pmx::RobotColor color)
        {
            if(color == pmx::PMXRED)
            {
                this->y_ = value;
            }else
            {
                this->y_ = -value;
            }
        }

        inline double angle() const
        {
            return angle_;
        }

        inline void angle(double value, pmx::RobotColor color)
        {
            if(color == pmx::PMXRED)
            {
                this->angle_ = value;
            }else
            {
                this->angle_ = -value;
            }
        }
    };
}

std::ostream& operator << (std::ostream& os, const pmx::Position position);
#endif
