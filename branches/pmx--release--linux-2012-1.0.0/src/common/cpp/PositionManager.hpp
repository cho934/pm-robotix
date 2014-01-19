/*!
 * \file
 * \brief Définition de la classe PositionManager.
 */

#ifndef PMX_POSITIONMANAGER_H
#define	PMX_POSITIONMANAGER_H

#include "Position.hpp"
#include "Mutex.hpp"
#include "IEncoderListener.hpp"
#include "SvgWriter.hpp"

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
    class PositionManager : public pmx::IEncoderListener, public utils::Mutex
    {
    public:
        
        /*!
         * \brief Distance de l'entraxe entre les 2 roues de motorisation (en mm).
         *
         */
        static const double DISTANCE_ENTRAXE_MOTORWHEEL = 255.0;

        /*!
         * \brief Distance de l'entraxe entre les 2 roues libres (en mm).
         *
         */
        static const double DISTANCE_ENTRAXE_FREEWHEEL = 327.5;

        /*!
         * \brief Distance parcourue par une roue motrice (en mm/pas).
         *
         */
        static const double DISTANCE_PER_MOTOR_PULSE = 0.8639; //théorique : 0.8639 0.893
        
        /*!
         * \brief Distance parcourue par une roue libre (en mm/pas).
         * 
         */
        static const double DISTANCE_PER_FREE_PULSE = 1.2828;

        /*!
         * \brief Angle de rotation (en radiant) si une roue motrice avance d'un pas.
         *
         * Formule de calcul : DISTANCE_PER_MOTOR_PULSE / DISTANCE_ENTRAXE_MOTORWHEEL (255mm)
         */
        static const double ANGLE_PER_MOTOR_PULSE = 0.003387842137; //0.003374609375 0.00350196

        /*!
         * \brief Angle de rotation (en radiant) si une roue libre avance d'un pas.
         *
         * Formule de calcul : DISTANCE_PER_FREE_PULSE / DISTANCE_ENTRAXE_FREEWHEEL (327.5mm)         */
        static const double ANGLE_PER_FREE_PULSE = 0.003916998474;


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

        virtual void onLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono) =0;
        
        virtual void onRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono) =0;

        virtual void compute(utils::SvgPositionColor color, bool force) =0;

        virtual void changeFrequency(int freq) =0;

        virtual void addAction() =0;

        virtual void reset() =0;
    };
}

#endif
