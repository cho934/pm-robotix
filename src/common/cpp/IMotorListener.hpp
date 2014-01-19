/*!
 * \file
 * \brief Définition de l'interface IMotorListener.
 */

#ifndef PMX_IMOTOR_LISTENER_HPP
#define PMX_IMOTOR_LISTENER_HPP

#include "MotorWay.hpp"
#include "Chronometer.hpp"

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
    class IMotorListener //!\todo a renommer
    {
    public:
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le moteur gauche.
         * \param value Le nombre de front montant du codeur gauche.
         * \param chrono Donne le temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         * \param way Le sens d'avance.
         */
        virtual void onLeftPulse(int value, utils::Chronometer chrono, pmx::MotorWay way) = 0;
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le moteur gauche.
         * \param value Le nombre de front montant du codeur droit.
         * \param chrono Donne le temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         * \param way Le sens d'avance.
         */
        virtual void onRightPulse(int value, utils::Chronometer chrono, pmx::MotorWay way) = 0;
        
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
