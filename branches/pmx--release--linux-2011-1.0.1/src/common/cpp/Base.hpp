/*!
 * \file
 * \brief Définition de la classe Base.
 */


#ifndef PMX_BASE_HPP
#define PMX_BASE_HPP

#include "Macro.hpp"
#include "Motor.hpp"
#include "ARobotElement.hpp"
#include "PositionManager.hpp"
#include "IInitialized.hpp"
#include "SpeedManagerFusion.hpp"
#include "Position.hpp"
#include "BaseWay.hpp"
#include "BaseFlags.hpp"

namespace pmx
{
    /*!
     * \brief Cette classe représente la base roulante du robot.
     *
     * L'objectif de cette classe est de regrouper l'ensemble des méthodes liées
     * au déplacement du robot.
     */
    class Base: public ARobotElement, public IInitialized
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref Base.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::Base");
            return instance;
        }
        
        /*!
         * \brief Moteur gauche du robot.
         */
        pmx::Motor motorLeft_;
        
        /*!
         * \brief Moteur droit du robot.
         */
        pmx::Motor motorRight_;
        
        /*!
         * \brief Objet assurant le calcul de la position du robot en fonction
         * des déplacements de sa base sur le terrain.
         */
        pmx::PositionManager * positionManager_;

        /*!
         * \brief Objet assurant les calculs de PID vitesse et position.
         */
        pmx::SpeedManagerFusion * speedManager_;
        
        /*!
         * \brief Flags de configuration actifs sur la base.
         * \sa BaseFlags
         */
        int flags_;

        /*!
         * \brief Coordonnée à atteindre (en mm).
         */
        int xDestination_;
        
        /*!
         * \brief Coordonnée à atteindre (en mm).
         */
        
        int yDestination_;

        /*!
         * \brief Statut d'arrivée à la position.
         */        
        bool arrived_;

        /*!
         * \brief Distance à parcourir (en tick).
         */
        double vdInitial_;

        /*!
         * \brief Ordonnée à l'origine de la rampe de décélération.
         * \deprecated
         */
        double b_;

        /*!
         * \brief Abscisse de intersection de la trajectoire en position. (cad des
         * 2 rampes de d'accélération et de décélération.
         * \deprecated
         */
        double xIntersect_;

        /*!
         * \brief Ordonnée de intersection de la trajectoire en position (cad des
         * 2 rampes de d'accélération et de décélération.
         * \deprecated
         */
        double yIntersect_;

        /*!
         * \brief abcisse de changement de repère position (en tick).
         */
        double xOffset_;

        /*!
         * \brief ordonnée de changement de repère position (en tick).
         */
        double yOffset_;

        /*!
         * \brief angle de changement de repère position (en radian).
         */
        double angleOffset_;

        BaseWay orderWay_;

        /*!
         * \brief Statut si un palet est détecté en roulant.
         */
        bool pawnFound_;

             
    public:
        /*!
         * \brief Coefficient d'accélération et de décélération. C'est en fait la
         * différence de tick nécessaire entre 2 appels de Timer du pid.
         * Est utilisé si pidPositionEnabled est \c true.
         */
        static const int A_MAX = 2;

        /*!
         * \brief Distance du point d'arret à partir duquel on peut s'arrêter en mm.
         * Est utilisé si trajectoryGenerationEnabled est \c true.
         * \deprecated
         */
        static const double EPSILON = 2.0; //\!todo faire une demi cercle de fin
        
        /*!
         * \brief Coefficient de décélération.
         * Est utilisé si trajectoryGenerationEnabled est \c true.
         * \deprecated
         */
        static const double GRADIENT = 0.5;

        /*!
         * \brief coefficient d'accélération.
         * Est utilisé si trajectoryGenerationEnabled est \c true.
         * \deprecated
         */
        static const double GRADIENT_ACC = -0.5;
        
        /*!
         * \brief Vitesse minimum (en tick) permettant de faire avancer le robot "en petite vitesse".
         */
        static const int SPEED_MIN = 15;
        
        /*!
         * \brief Vitesse maximum  (en tick) appliquée au robot.
         */
        static const int SPEED_MAX = 30;
        
        /*!
         * \brief Constructeur de la classe.
         * \param robot
         *        Référence vers le robot associé à cette base roulante.
         */
        Base(pmx::Robot & robot);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ Base()
        {}
        
        /*!
         * \brief Retourne une référence vers l'objet \ref Motor associé au
         * moteur gauche.
         */
        inline pmx::Motor & motorLeft()
        {
            return motorLeft_;
        }
        
        /*!
         * \brief Retourne une référence vers l'objet \ref Motor associé au
         * moteur droit.
         */
        inline pmx::Motor & motorRight()
        {
            return motorRight_;
        }
        
        /*!
         * \brief Retourne la gestionnaire de position (odométrie) associé à la
         * base du robot.
         */
        inline PositionManager & positionManager()
        {
            return *positionManager_;
        }

        inline bool vecteurCorrectionEnabled() const
        {
            return this->flags_ & AUTO_CORRECT;
        }

        inline void vecteurCorrectionEnabled(bool vecteurCorrectionEnabled)
        {
            if (vecteurCorrectionEnabled)
            {
                this->flags_ = this->flags_ | AUTO_CORRECT;
            }
            else
            {
                this->flags_ = this->flags_ & ~AUTO_CORRECT;
            }
        }

        inline bool pidPositionEnabled() const
        {
            return this->flags_ & PID_POSITION;
        }

        inline void pidPositionEnabled(bool pidPositionEnabled)
        {
            if (pidPositionEnabled)
            {
                this->flags_ |= PID_POSITION;
            }
            else
            {
                this->flags_ &= ~PID_POSITION;
            }
        }

        inline bool pidSpeedEnabled() const
        {
            return this->flags_ & PID_SPEED;
        }

        inline void pidSpeedEnabled(bool pidSpeedEnabled)
        {
            if (pidSpeedEnabled)
            {
                this->flags_ |= PID_SPEED;
            }
            else
            {
                this->flags_ &= ~PID_SPEED;
            }
        }

        inline int xDestination() const
        {
            return this->xDestination_;
        }

        inline void xDestination(int x)
        {
            this->xDestination_ = x;
        }

        inline int yDestination() const
        {
            return this->yDestination_;
        }
        
        inline void yDestination(int y)
        {
            this->yDestination_ = y;
        }
        
        inline bool arrived() const
        {
            return arrived_;
        }
        
        inline void arrived(bool arrived)
        {
            this->arrived_ = arrived;
        }
        
        inline double vdInitial() const
        {
            return this->vdInitial_;
        }
        
        inline void vdInitial(double vdInitial)
        {
            this->vdInitial_ = vdInitial;
        }
        
        inline double b() const
        {
            return this->b_;
        }
        
        inline void b(double b)
        {
            this->b_ = b;
        }
        
        inline double xIntersect() const
        {
            return this->xIntersect_;
        }
        
        inline void xIntersect(double xIntersect)
        {
            this->xIntersect_ = xIntersect;
        }
        
        inline double yIntersect() const
        {
            return this->yIntersect_;
        }
        
        inline void yIntersect(double yIntersect)
        {
            this->yIntersect_ = yIntersect;
        }

        inline double xOffset() const
        {
            return this->xOffset_;
        }

        inline void xOffset(double x)
        {
            this->xOffset_ = x;
        }

        inline double yOffset() const
        {
            return this->yOffset_;
        }

        inline void yOffset(double y)
        {
            this->yOffset_ = y;
        }

        inline double angleOffset() const
        {
            return this->angleOffset_;
        }

        inline void angleOffset(double angle)
        {
            this->angleOffset_ = angle;
        }

        inline BaseWay orderWay() const
        {
            return this->orderWay_;
        }

        inline void orderWay(BaseWay orderWay)
        {
            this->orderWay_ = orderWay;
        }

        inline bool pawnFound() const
        {
            return this->pawnFound_;
        }

        inline void pawnFound(bool pawnFound)
        {
            this->pawnFound_ = pawnFound;
        }

        /*!
         * \brief Configure les coefficients de pid en vitesse sur un moteur pour l'avance.
         *
         */
        void pidSpeedInitialize(MotorLocation location, double VkP, double VkI, double VkD);

        /*!
         * \brief Configure les coefficients de pid en vitesse sur un moteur pour el recul.
         *
         */
        void pidSpeedBackInitialize(MotorLocation location, double VkP, double VkI, double VkD);

        void pidSpeedActivate();

        void pidSpeedStart();

        void pidSpeedDesactivate();

        /*!
         * \brief Reset des variables pour effectuer une nouvelle avance du robot.
         */
        void reset();

        /*!
         * \brief Confire pid en vitesse et position sur un moteur.
         *
         */
        void pidPositionInitialize(MotorLocation location, double PkP, double PkI, double PkD);

        /*!
         * \brief Cette méthode définit les vitesses souhaitées pour les deux moteurs
         *        de la base roulante.
         *
         * Les vitesses fournies à cette méthode peuvent être négatives.
         *
         * Pour stopper le robot, utilisez la méthode \c stop().
         *
         * \param speedLeft
         *        Vitesse du moteur gauche.
         * \param speedRight
         *        Vitesse du moteur droit.
         *
         * \todo deprecated
         */
        void defineMotorSpeed(double speedLeft, double speedRight);
        
        /*!
         * \brief Donne l'ordre à la base roulante d'avancer à une vitesse donnée.
         * Cette méthode équivaut à appeler \c defineMotorSpeed(speed,speed).
         *
         * \param speed
         *        Vitesse appliquée aux moteurs de la base roulante.
         */
        void goForward(double speed);
        
        /*!
         * \brief Donne l'ordre à la base roulante de tourner à gauche.
         * Cette méthode équivaut à appeler \c defineMotorSpeed(-speed,speed).
         *
         * \param angle
         *        angle de rotation du robot (compris entre 0 et 2PI).
         */
        void turnLeft(double angle);
        
        /*!
         * \brief Donne l'ordre à la base roulante de tourner à droite.
         * Cette méthode équivaut à appeler \c defineMotorSpeed(speed,-speed).
         *
         * \param angle
         *        angle de rotation du robot(compris entre 0 et 2PI).
         */
        void turnRight(double angle);
        
        /*!
         * \brief Arret de la base.
         */
        void stop();
        
        /*!
         * \brief (deprecated)Donne l'ordre à la base roulante d'avancer à une position donnée.
         *
         * \param x
         *        abscisse de destination (en tick).
         * \param y
         *        ordonnée de destination (en tick).
         * \param way
         *        ordre d'avance.
         * \param teta
         *        angle final.
         * \param detectPawn
         *        permet de détecter un pion.
         * \param offset de dépose de pion en mm.
         *        permet de limiter la distance d'avance.
         */
        void movexy_Dpawn(int x, int y, BaseWay way, double teta, int detectPawn, int offset);

        
        /*!
         * \brief (deprecated)Donne l'ordre à la base roulante d'avancer à une position donnée.
         *
         * \param x
         *        abscisse de destination (en tick).
         * \param y
         *        ordonnée de destination (en tick).
         * \param way
         *        ordre d'avance.
         */
        void movexy(int x, int y, BaseWay way);

        /*!
         * \brief Donne l'ordre à la base roulante d'avancer en ligne droite sur une distance donnée.
         *
         * \param d
         *        distance de destination.
         * \param y
         *        decalage d'ordonnée sur le repere de la base.
         */
        void moveD(int d, int y);


        void printPosition(std::string log);

        /*!
         * \brief Configuration par fichier de conf.
         */
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
}

#endif
