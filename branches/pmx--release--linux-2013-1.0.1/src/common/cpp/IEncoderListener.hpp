/*!
 * \file
 * \brief Définition de l'interface IEncoderListener.
 */

#ifndef PMX_IENCODER_LISTENER_HPP
#define PMX_IENCODER_LISTENER_HPP

#include "MotorWay.hpp"
#include "Chronometer.hpp"

namespace pmx
{
    /*!
     * \brief Cette interface représente le listener d'un codeur incremental
     * associé à la classe SensorManager.
     *
     * Les instances de cette classe sont 'averties' des modifications d'état
     * sur les capteurs du robot grace aux méthodes 'onXXX()' et peuvent traiter
     * l'information en conséquence.
     */
    class IEncoderListener
    {
    public:
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le codeur gauche.
         * \param motorEncoderValue Le nombre de front montant du codeur gauche.
         * \param freeEncoderValue Le nombre de front montant du codeur gauche indépendant.
         * \param chrono Donne le temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         */
        virtual void onLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono) = 0;
        
        /*!
         * \brief Cette méthode est appelée lorsque qu'une impulsion est reçue
         * sur le codeur droit.
         * \param motorEncoderValue Le nombre de front montant du codeur droit attaché au moteur.
         * \param freeEncoderValue Le nombre de front montant du codeur droit indépendant.
         * \param chrono Donne le temps de référence en microsecondes. Représente le temps
         *        écoulé entre le lancement du robot et l'impulsion.
         *        Les intervalles doivent donc être calculé en fonction de la
         *        périodes à observer.
         * \param way Le sens d'avance.
         */
        virtual void onRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono) = 0;
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ IEncoderListener()
        {}
        
    protected:
        
        /*!
         * \brief Constructeur de la classe.
         *
         * Le constructeur de cette classe est protégée pour éviter son
         * instanciation et rendre obligatoire sa surcharge.
         */
        IEncoderListener()
        {}
    };
};

#endif
