/*!
 * \file
 * \brief Définition de la classe OdometryPositionManager.
 */

#ifndef PMX_ODOMETRYPOSITIONMANAGER_HPP
#define	PMX_ODOMETRYPOSITIONMANAGER_HPP

#include "PositionManager.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe permet de gérer le positionnement du robot via les codeurs.
     */
    class OdometryPositionManager : public pmx::PositionManager
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger nommé csv associé à la classe \ref OdometryPositionManager.
         */
        static inline const utils::Logger & csv()
        {
            static const utils::Logger & csv_ = utils::LoggerFactory::logger("pmx::OdometryPositionManager::csv");
            return csv_;
        }
        
    private:
        
        /*!
         * \brief Nombre absolu d'impulsion depuis le dernier traitement.
         * \sa ::compute()
         */
        int count_;
        
        /*!
         * \brief Nombre d'impulsion sur la roue gauche depuis le dernier traitement.
         */
        int countLeft_;
        
        /*!
         * \brief Nombre d'impulsion sur la roue droite depuis le dernier traitement.
         */
        int countRight_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        OdometryPositionManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ OdometryPositionManager()
        {}
        
        virtual void onLeftPulse(int value, utils::Chronometer chrono, MotorWay way);
        
        virtual void onRightPulse(int value, utils::Chronometer chrono, MotorWay way);
        
    private:
        
        /*!
         * \brief Computes the current position of the robot.
         */
        void compute();
    };
}

#endif
