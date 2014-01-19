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
    protected:
        
        /*!
         * \brief Distance de l'entraxe entre les 2 roues de la base (en millimètre).
         * 
         */
        static const double DISTANCE_ENTRAXE = 313.5;

        /*!
         * \brief Distance parcourue par le robot entre deux fronts montants (en millimètre)
         * si le robot avance en ligne droite.
         * \todo Regrouper cette constante et celle présente dans la classe SpeedManager.
         * FORMULE :  DISTANCE_PER_UP_PULSE = D_stepper / D_roue_bois * D_roue_sol / Nb_impulsions_codeur_stepper
         * DISTANCE_PER_UP_PULSE = 19.5 / 72.2 * 78.1*PI / 100 = 0.662671541798 (50 => 1.325343)
         */
        static const double DISTANCE_PER_UP_PULSE = 1.325343;
        
        /*!
         * \brief Angle de rotation du robot si le robot (en radiant) si le robot effectue une
         * rotation entre deux fronts montants.
         *
         * Formule de calcul : DISTANCE_PER_UP_PULSE / DISTANCE_ENTRAXE
         * 0.002113784822 pour 100 ; 0.00422757pour 50
         */
        static const double ANGLE_PER_UP_PULSE = 0.00422757; // DISTANCE_PER_UP_PULSE / DISTANCE_ENTRAXE;
        
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
        inline const Position& position() const
        {
            return position_;
        }
        
        virtual void onLeftPulse(bool value, int time, int nbTests, MotorWay way) =0;
        
        virtual void onRightPulse(bool value, int time, int nbTests, MotorWay way) =0;
    };
}

#endif
