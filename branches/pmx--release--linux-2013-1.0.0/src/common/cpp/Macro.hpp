/*!
 * \file
 * \brief Définition des macros du projet.
 */

#ifndef PMX_MACRO_HPP
#define PMX_MACRO_HPP

/*!
 * \brief Type de données : unsigned int.
 */
typedef unsigned int uint;

/*!
 * \brief Type de données : unsigned short.
 */
typedef unsigned short ushort;

/*!
 * \brief Type de données : unsigned long.
 */
typedef unsigned long ulong;

namespace pmx
{

    /*!
     * \brief Enumération des libellés des actions de la barre de leds.
     */
    enum LedBarActionName
    {
        /*!
         * \brief Libellé de l'action permettant d'allumer/eteindre une led.
         */
        LEDBARSET,
        
        /*!
         * \brief Libellé de l'action permettant un clignotement à la "K2000".
         */
        LEDBARK2MIL,

        /*!
         * \brief Libellé de l'action permettant un reset de toute la barre de led.
         */
        LEDBARRESET,

        /*!
         * \brief Libellé de l'action permettant d'allumer toutes les leds.
         */
        LEDBARFLASH,

        /*!
         * \brief Libellé de l'action permettant d'allumer les leds par rapport à une valeur hexa.
         */
        LEDBARFLASHVALUE,

        /*!
         * \brief Libellé de l'action permettant un clignotement de la barre de led.
         */
        LEDBARBLINK,

        /*!
         * \brief Libellé de l'action permettant un clignotement d'un pin de la barre de led.
         */
        LEDBARBLINKPIN,

        /*!
         * \brief Libellé de l'action permettant un clignotement alternatif sur 2 valeurs définies de la barre de led.
         */
        LEDBARALTERNATE

    };

    /*!
     * \brief Enumération des libellés des actions de la pince.
     */
    enum ClampActionName
    {
        OPENWIDE, OPENMEDIUM, OPENLITTLE, CLOSE, KEEPCLOSE
    };

     /*!
     * \brief Enumération des libellés des actions des SERVOMOTEURS.
     */
    enum ServoMotorObjectActionName
    {
        SERVOTURNMIN, SERVOTURNMED, SERVOTURNMAX
    };

    /*!
     * \brief Enumération des localisations des SERVOMOTOR utilisés.
     */
    enum ServoLocation
    {
        CLAMPLEFT, CLAMPRIGHT, BALLOONINFLATE
    };

    /*!
     * \brief Enumération du mode de programmation.
     */
    enum RobotMode
    {
        ROBOTMATCHES, ROBOTHOMOLOGATION
    };

}
#endif
