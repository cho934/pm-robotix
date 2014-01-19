/*!
 * \file
 * \brief Définition de la classe RobotInOutFactory.
 */

#ifndef PMX_ROBOTINOUTFACTORY_H
#define	PMX_ROBOTINOUTFACTORY_H

#include "IRobotIn.hpp"
#include "IRobotOut.hpp"
#include "Mutex.hpp"
#include "LoggerFactory.hpp"
#include "ServoMotorApf.hpp"

namespace pmx
{
    /*!
     * \brief Fabrique pour les interfaces pmx::IRobotIn et pmx::IRobotOut.
     *
     * L'ordre de sélection de l'implémentation est le suivant:
     * - processeur Apf (pmx::RobotInApf, pmx::RobotOutApf)
     * - port parallèle (pmx::RobotInOutParallelPort)
     * - simulation (pmx::RobotInSimulate, pmx::RobotOutSimulate)
     */
    class RobotInOutFactory : public utils::Mutex
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref RobotInOutFactory.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::RobotInOutFactory");
            return instance;
        }

    public:

        /*!
         * \brief Instance unique de la classe.
         */
        static RobotInOutFactory * instance();

        //todo cc rajouter un flag pour savoir si bloquant ou non bloquant.

    private:

        /*!
         * \brief Flux d'entrée du robot.
         */
        IRobotIn * in_;

        /*!
         * \brief Flux de sortie du robot.
         */
        IRobotOut * out_;

        /*!
         * \brief Flux de sortie du robot concernant les servomoteurs par FPGA.
         */
        ServoMotorApf * outServoMotor_;

        /*!
         * \brief Flag indiquant si le système d'entrée utilise une lecture blocante.
         */
        bool blockingRead_;

        /*!
         * \brief Constructeur de la classe.
         */
        RobotInOutFactory();

    public:

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~RobotInOutFactory()
        {
        }

        /*!
         * \brief Retourne un pointeur vers le flux d'entrée du robot.
         *
         * \return Le flux d'entrée du robot.
         */
        virtual inline IRobotIn * robotIn() const
        {
            return in_;
        }

        /*!
         * \brief Retourne un pointeur vers le flux de sortie du robot.
         *
         * \return Le flux de sortie du robot.
         */
        virtual inline IRobotOut * robotOut() const
        {
            return out_;
        }

        /*!
         * \brief Retourne un pointeur vers le flux de sortie du robot.
         *
         * \return Le flux de sortie du robot.
         */
        virtual inline ServoMotorApf * outServoMotor() const
        {
            return outServoMotor_;
        }

        /*!
         * \brief Retourne le flag indiquant si la lecture est bloquance ou non.
         * \return \c true si la lecture est en mode bloquante.
         */
        virtual inline bool blockingRead() const
        {
            return this->blockingRead_;
        }

    private:

        /*!
         * \brief Définie si la lecture est bloquante ou non.
         * \param value La valeur du flag indiquant si la lecture est bloquante.
         */
        virtual inline void blockingRead(bool value)
        {
            this->blockingRead_ = value;
        }
    };
}

#endif
