#ifndef PMX_POSITIONMANAGER_H
#define	PMX_POSITIONMANAGER_H

#include "Position.hpp"
#include "Mutex.hpp"
#include "IMotorListener.hpp"

namespace pmx
{
    /*!
     * \brief Gestionnaire calculant la position du robot en fonction de ses
     * déplacements au sol.
     *
     * Cette classe gère un automate à 5 états représenté par le schéma suivant :
     *
     * \image ArchPositionManager.png
     *
     * Les états \c TurnLeft, \c TurnRight et \c GoForward sont des états de calculs
     * et seront représentés dans la classe par des méthodes.
     * Les états seront représentés par deux bouléens : haveLeft_ et haveRight_.
     */
    class PositionManager : public pmx::IMotorListener, public utils::Mutex
    {
    public:
        
        /*!
         * \brief Distance de l'entraxe entre les 2 roues de la base .
         * 
         */
        static const double DISTANCE_ENTRAXE = 313.0; //313.5;

        /*!
         * \brief Distance parcourue par le robot entre deux fronts montants (en millimètre)
         * si le robot avance en ligne droite.
         * FORMULE :  DISTANCE_PER_UP_PULSE = D_stepper / D_roue_bois * D_roue_sol / Nb_impulsions_codeur_stepper
         * (ancien) DISTANCE_PER_UP_PULSE = 19.6 / 72 * 78.1 * PI / 48 = 1.39150
         * DISTANCE_PER_UP_PULSE = 19.6 / 74.4 * 78 * PI / 48 = 1.3448888
         */
        static const double DISTANCE_PER_UP_PULSE = 1.25889;//1.3448888; // correction coupe 2011
        
        /*!
         * \brief Angle de rotation du robot si le robot (en radiant) si le robot effectue une
         * rotation entre deux fronts montants.
         *
         * Formule de calcul : DISTANCE_PER_UP_PULSE / DISTANCE_ENTRAXE
         * (ancien) 0.004438596491 pour 48 pas
         * 0.00420277747 pour 48 pas
         */
        static const double ANGLE_PER_UP_PULSE = 0.00420277747; // = DISTANCE_PER_UP_PULSE / DISTANCE_ENTRAXE;
        
    protected:
        
        /*!
         * \brief Dernière position connue du robot.
         *
         * Attention : cette valeur ne doit pas être déplacée dans la classe
         * Robot car elle correspond à la position calculée par ce manager.
         * Une telle architecture serait une erreur car elle empecherait
         * l'intégration de plusieurs systèmes de positionnement.
         */
        Position position_;
        
    protected:
        
        /*!
         * \brief Constructeur par défaut.
         */
        PositionManager();
        
    public:
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ PositionManager()
        {}
        
        /*!
         * Accesseur retournant la position courante du robot.
         * \return Position courante du robot.
         */
        inline Position& position()
        {
            return position_;
        }

        virtual void onLeftPulse(int value, utils::Chronometer chrono, MotorWay way) =0;
        
        virtual void onRightPulse(int value, utils::Chronometer chrono, MotorWay way) =0;
    };
}

#endif
