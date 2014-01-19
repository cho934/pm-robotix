/*!
 * \file
 * \brief Définition de la classe ServoMotorApf (sur n positions).
 * Permet de gérer les R/C servos (Remote control servo moteur) via FPGA.
 * 
 */

#ifndef PMX_SERVOMOTORAPF_HPP
#define	PMX_SERVOMOTORAPF_HPP

#include "LoggerFactory.hpp"

#define SERVO_DRIVER_SYSFS_BASE "/sys/class/servo/"
#define SERVO_DRIVER_SERVO_FILE "servo"
#define SERVO_DRIVER_SERVO_POSITION_FILE "desired_position"
#define SERVO_DRIVER_SERVO_ENABLE_FILE "enable"
#define SERVO_DRIVER_SERVO_OFFSET_FILE "offset"
#define SERVO_DRIVER_SERVO_MIN_FILE "lower_boundary"
#define SERVO_DRIVER_SERVO_MAX_FILE "upper_boundary"

namespace pmx
{
    /*!
     * \brief Cette classe représente l'un des servomoteurs fonctionnant sur 
     * n positions du robot et utilisant le "motion system" du FPGA.
     *
     */
    class ServoMotorApf
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorApf.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::ServoMotorApf");
            return instance;
        }

        int servoEnableBuffer[];

        int servoMinBuffer[];

        int servoMaxBuffer[];

        int servoOffsetBuffer[];

        int servoPositionBuffer[];

    public:

        /*!
         * \brief Cette méthode statique retourne l'instance unique de la classe.
         *
         * \return L'instance unique de la classe.
         */
        /*static ServoMotorApf & instance()
        {
            static ServoMotorApf instance; //singleton

            return instance;
        }*/

        /*!
         * \brief Constructeur de la classe.
         */
        ServoMotorApf();

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ServoMotorApf()
        {
        }

        /*!
         * \brief Permet d'activer un servomoteur ou non (freewheeling).
         * \param servoID : identifiant du servomoteur.
         * \param value : prend la valeur 0 ou 1.
         */
        virtual void setServoEnable(int servoID, int value);

        /*!
         * \brief Mets à jour la valeur d'offset du servo associé.
         */
        virtual void setServoOffset(int, int);

        /*!
         * \brief Positionne le servo à la valeur de position demandée.
         */
        virtual void setServoPosition(int, int);

        /*!
         * \brief indique la valeur de la position qui a été demandée.
         */
        virtual int getServoPosition(int servoID);

        /*!
         * \brief indique la valeur courante de la position du servo.
         */
        virtual int getServoCurrentPosition(int servoID);

    };
};

#endif
