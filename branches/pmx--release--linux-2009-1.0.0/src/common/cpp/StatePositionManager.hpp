#ifndef PMX_STATEPOSITIONMANAGER_H
#define	PMX_STATEPOSITIONMANAGER_H

#include "PositionManager.hpp"

namespace pmx
{
    class StatePositionManager : public pmx::PositionManager
    {
    private:
        
        static Position computeForward(const Position& position, double distance);
        
    private:
        
        /*!
         * \c true Si une impulsion a été reçue à gauche.
         */
        bool haveLeft_;
        
        /*!
         * \c true Si une impulsion a été reçue à droite.
         */
        bool haveRight_;
        
    public:
        
        /*!
         * \brief Constructeur par défaut.
         */
        StatePositionManager();
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ StatePositionManager()
        {}
        
        virtual void onLeftPulse(bool value, int time, int nbTests);
        
        virtual void onRightPulse(bool value, int time, int nbTests);
        
    private:
        
        /*!
         * Trace les informations de positions sur le logger \c pmx::StatePositionManager::csv en debug.
         */
        void log();
        
        /*!
         * Modifie la position du robot pour une tenir compte d'une rotation à gauche.
         */
        void turnLeft();
        
        /*!
         * Modifie la position du robot pour une tenir compte d'une rotation à droite.
         */
        void turnRight();
        
        /*!
         * Modifie la position du robot pour une tenir compte d'un mouvement vers l'avant.
         * Cette méthode modifie l'état de l'automate et le fait revenir à son état initial.
         */
        void goForward();
    };
}

#endif	/* PMX_STATEPOSITIONMANAGER_H */

