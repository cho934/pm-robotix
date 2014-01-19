/*!
 * \file
 * \brief Définition de l'interface IMotorListener.
 */

#ifndef PMX_IMOTOR_LISTENER_HPP
#define PMX_IMOTOR_LISTENER_HPP

#include "MotorWay.hpp"

namespace pmx
{
    /*!
     * \brief Cette interface représente le listener associé à la classe
     * SensorManager.
     *
     * Les instances de cette classe sont 'averties' des modifications d'état
     * sur les capteurs du robot grace aux méthode 'onXXX()' et peuvent traiter
     * l'information en conséquence.
     */
    class IMotorListener
    {
    public:
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le moteur gauche.
         * \param value La valeur de la pulsation. Vaut \c true pour un front
         *        montant ou \c false pour un front descendant.
         * \param time Temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         * \param nbTests Nombre de tests réalisés depuis le dernier appel.
         */
        virtual void onLeftPulse(bool value, int time, int nbTests, pmx::MotorWay way) =0;
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le moteur gauche.
         * \param value La valeur de la pulsation. Vaut \c true pour un front
         *        montant ou \c false pour un front descendant.
         * \param time Temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         * \param nbTests Nombre de tests réalisés depuis le dernier appel.
         */
        virtual void onRightPulse(bool value, int time, int nbTests, pmx::MotorWay way) =0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IMotorListener()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         *
         * Le constructeur de cette classe est protégée pour éviter son
         * instanciation et rendre obligatoire sa surcharge.
         */
        IMotorListener()
        {}
    };
};

#endif
