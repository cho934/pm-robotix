#ifndef PMX_MOVEMENTACTION_HPP
#define	PMX_MOVEMENTACTION_HPP

#include "IAction.hpp"
#include "Robot.hpp"
#include "Timer.hpp"

namespace pmx
{
    /*!
     * Assure le déplacement du robot vers un point donné.
     */
    class MovementAction : public IAction, utils::ITimerListener
    {
    public:
        
        /*!
         * \brief Période concernant la fréquence d'appel du timer(en millisecondes).
         */
        static const int PERIOD_TIMER = SpeedManager::PERIOD_PID;
        
    private:
        
        /*!
         * \brief Cette méthode retourne le logger associé à cette classe.
         * \return Le logger de cette classe.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::MovementAction");
            return instance;
        }
        
        /*!
         * \brief Distance du point d'arret à partir duquel on peut s'arrêter en mm.
         */
        static const double EPSILON = 20.0;
        
        /*!
         * \brief Multiplicateur de la courbe de vitesse.
         */
        static const double GRADIENT = 0.4;
        
        /*!
         * \brief Multiplicateur de la courbe de vitesse.
         */
        static const double GRADIENT_ACC = -1.0;
        
        /*!
         * \brief Vitesse minimum appliquée au robot.
         */
        static const double SPEED_MIN = 40.0;
        
        /*!
         * \brief Vitesse maximum appliquée au robot.
         */
        static const double SPEED_MAX = 180.0;
        
        /*!
         * \brief Référence vers le robot.
         */
        Robot& robot_;
        
        /*!
         * \brief Coordonnée à atteindre (absisse).
         */
        double x_;
        
        /*!
         * \brief Coordonnée à atteindre (ordonnée).
         */
        double y_;
        
        /*!
         * \brief Statut d'arrivée à la position.
         */
        bool arrived_;
        /*!
         * \brief vd initial.
         */
        double vdInitial_;
        
        double b_;
        
        double xIntersect_;
        
        double yIntersect_;
        
        bool activ_;
        
        /*!
         * \brief Timer associé à cette instance.
         */
        utils::Timer timer_;
        
    public:
        
        /*!
         * \brief Initialise une nouvelle action de déplacement.
         *
         * \param robot
         *        Référence vers le robot à manipuler.
         * \param x
         *        Absisse du point à atteindre.
         * \param y
         *        Ordonnée du point à atteindre.
         */
        MovementAction(Robot& robot, double x, double y);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ MovementAction()
        {}
        
        inline bool arrived() const
        {
            return arrived_;
        }
        
        inline void arrived(bool arrived)
        {
            this->arrived_ = arrived;
        }
        
        inline void vdInitial(double vdInitial)
        {
            this->vdInitial_ = vdInitial;
        }
        
        inline void b(double b)
        {
            this->b_ = b;
        }
        
        inline void xIntersect(double xIntersect)
        {
            this->xIntersect_ = xIntersect;
        }
        
        inline void yIntersect(double yIntersect)
        {
            this->yIntersect_ = yIntersect;
        }
        
        inline bool activ() const
        {
            return activ_;
        }
        
        inline void activ(bool activ)
        {
            this->activ_ = activ;
        }
        
        /*!
         * \brief Valide la position courante du robot et corrige la trajectoire
         * si nécessaire.
         *
         * Cette méthode se base sur les données de position fournies par la base
         * pour valider le déplacement actuel.
         */
        virtual bool execute(IRobotOut * out);
        
        virtual inline std::string info()
        {
            return "MovementAction";
        }

        /*!
         * \brief Méthode appelée en fonction du chronometer, à une fréquence donnée.
         * \param timeSpan
         *        Intervalle de temps depuis le dernier appel de cette méthode (en ms).
         */
        void onTimer(int timeSpan);
    };
}

#endif
