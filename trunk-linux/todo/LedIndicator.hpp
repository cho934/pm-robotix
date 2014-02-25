/*!
 * \file
 * \brief Définition de la classe LedIndicator.
 *
 * Définition des positions de LED au démarrage :
 * 0 : thread File Appender started => allumée
 * 1 : thread Console Appender started => allumée
 * 2 : thread actionManager_ started => allumée
 * 3 : thread sensorManager_ started => allumée
 * 4 : all interruptions started => allumée
 * 5 : initialize DAC MAX5821 ok => allumée
 * 6 : initialize DAC MAX1027 ok => allumée
 * 7 : /
 */

#ifndef PMX_LEDINDICATOR_HPP
#define PMX_LEDINDICATOR_HPP

#include <string>
//#include <iostream>
#include <as_devices/as_gpio.h>
#include "Mutex.hpp"
#include "Macro.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe permet d'interagir avec la série de 8 leds.
     *
     * Cette classe est implémentée comme un singleton afin de pouvoir être
     * utilisée à tout endroit du programme sans difficulté, en contrepartie
     * les sorties pour les leds doivent être dédiées.
     */
    class LedIndicator : utils::Mutex
    {
    public:

        /*!
         * \brief Cette méthode statique retourne l'instance unique de la classe
         * LedIndicator.
         * \return L'instance unique de la classe.
         *
         */
        static LedIndicator & instance()
        {
            static LedIndicator instance;
            return instance;
        }

        struct as_gpio_device *paths[8];

    private:

        /*!
         * \brief Constructeur par défaut.
         */
        LedIndicator()
        {
            paths[0] = as_gpio_open('D', 7);
            paths[1] = as_gpio_open('D', 8);
            paths[2] = as_gpio_open('D', 9);
            paths[3] = as_gpio_open('D', 10);
            paths[4] = as_gpio_open('D', 11);
            paths[5] = as_gpio_open('D', 12);
            paths[6] = as_gpio_open('D', 13);
            paths[7] = as_gpio_open('D', 14);
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~LedIndicator()
        {
            as_gpio_close(paths[0]);
            as_gpio_close(paths[1]);
            as_gpio_close(paths[2]);
            as_gpio_close(paths[3]);
            as_gpio_close(paths[4]);
            as_gpio_close(paths[5]);
            as_gpio_close(paths[6]);
            as_gpio_close(paths[7]);
        }

    public:

        /*!
         * \brief Change le statut d'une led.
         * \param position La position de la led (de 0 à 7).
         * \param status Le statut de la led.
         */
        void set(int position, int status);

        /*!
         * \brief Active une led spécifique.
         * \param position La position de la led (de 0 à 7).
         */
        inline void setOn(int position)
        {
            this->set(position, 1);
        }

        /*!
         * \brief Désactive une led spécifique.
         * \param position La position de la led (de 0 à 7).
         */
        inline void setOff(int position)
        {
            this->set(position, 0);
        }

        /*!
         * \brief Désactive toutes les leds.
         */
        void reset();

        /*!
         * \brief Allume toutes les leds.
         */
        void flash();

        /*!
         * \brief Allume les leds définit par hexValue, max = 0xFF.
         */
        void flashValue(uint hexValue);

        /*!
         * \brief Clignote toutes les leds nb fois.
         */
        void blink(uint nb, uint timeus);

        /*!
         * \brief Clignote une led nb foispendant timeus.
         */
        void blinkPin(int position, uint nb, uint timeus);

        /*!
         * \brief Clignote toutes les leds nb fois sur les 2 valeurs hex val1 et val2.
         */
        void alternate(uint nb, uint timeus, uint val1, uint val2);
    };
}

#endif
