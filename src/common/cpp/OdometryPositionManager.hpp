#ifndef PMX_ODOMETRYPOSITIONMANAGER_HPP
#define	PMX_ODOMETRYPOSITIONMANAGER_HPP

#include "PositionManager.hpp"
#include "LoggerFactory.hpp"

namespace pmx
{
    class OdometryPositionManager : public pmx::PositionManager
    {
    private:
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe pour faire un rapport csv.
         * \return Le logger au format csv de cette classe.
         */
        static inline const utils::Logger & csv()
        {
            static const utils::Logger & csv_ = utils::LoggerFactory::logger("pmx::OdometryPositionManager::csv");
            return csv_;
        }
        
        /**
         * \brief Cette méthode retourne le logger associé à cette classe pour faire un rapport svg.
         * \return Le logger au format svg de cette classe.
         */
        static inline const utils::Logger & svg()
        {
            static const utils::Logger & svg_ = utils::LoggerFactory::logger("pmx::OdometryPositionManager::svg");
            return svg_;
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
        
        virtual void onLeftPulse(bool value, int time, int nbTests, MotorWay way);
        
        virtual void onRightPulse(bool value, int time, int nbTests, MotorWay way);
        
    private:
        
        /*!
         * \brief Computes the current position of the robot.
         */
        void compute();
    };
}

#endif
