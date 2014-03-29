/*!
 * \file
 * \brief Définition de la classe Base.
 */


#ifndef PMX_BASE_HPP
#define PMX_BASE_HPP

#include "Macro.hpp"
#include "ARobotElement.hpp"
#include "IInitialized.hpp"
#include "Position.hpp"
#include "BaseWay.hpp"
#include "BaseFlags.hpp"
#include "MotorLocation.hpp"
/*
#include "PositionManager.hpp"
#include "Motor.hpp"
#include "SpeedManagerFusion.hpp"
#include "MotorWithMd25.hpp"*/

namespace pmx
{
    /*!
     * \brief Cette classe représente la base roulante du robot.
     *
     * L'objectif de cette classe est de regrouper l'ensemble des méthodes liées
     * au déplacement du robot.
     */
    class Base : public ARobotElement, public IInitialized
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
        //pmx::MotorWithMd25 motorLeft_;

        /*!
         * \brief Moteur droit du robot.
         */
        //pmx::MotorWithMd25 motorRight_;

        /*!
         * \brief Objet assurant le calcul de la position du robot en fonction
         * des déplacements de sa base sur le terrain.
         */
        //pmx::PositionManager * positionManager_;

        /*!
         * \brief Objet assurant les calculs de PID vitesse et position.
         */
        //pmx::SpeedManagerFusion * speedManager_;

        /*!
         * \brief Flags de configuration actifs sur la base.
         * \sa BaseFlags
         */
        int flags_;

        /*!
         * \brief Coordonnée x à atteindre (en mm).
         */
        double xDestination_;

        /*!
         * \brief Coordonnée y à atteindre (en mm).
         */
        double yDestination_;

        /*!
         * \brief Coordonnée d'angle à atteindre (en radian).
         */
        double angleDestination_;

        /*!
         * \brief Statut d'arrivée à la position.
         */
        bool arrived_;

        /*!
         * \brief Statut d'arrivée à la position.
         */
        bool arrivedDestination_;

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
         * \brief Abcisse de changement de repère position (en tick).
         */
        double xOffset_;

        /*!
         * \brief Ordonnée de changement de repère position (en tick).
         */
        double yOffset_;

        /*!
         * \brief Angle de changement de repère position (en radian).
         */
        double angleOffset_;

        /*!
         * \brief Sens de direction de la base.
         */
        BaseWay orderWay_;


    public:
        /*!
         * \brief Coefficient d'accélération et de décélération. C'est en fait la
         * différence de tick nécessaire entre 2 appels de Timer du pid.
         * Est utilisé si pidPositionEnabled est \c true.
         * 
         * Ancien parametres : pour A_MAX=2 => base-RightPos-P : 0.12 base-RightPos-I : 0.00001 base-RightPos-D : 0.4
         */
        static const int A_MAX = 4;

        /*!
         * \brief Coefficient d'accélération.
         * Est utilisé si rampPositionEnabled est \c true.
         */
        static const float RAMP_ACC = 0.1; //0.3 0.2

        /*!
         * \brief Coefficient de décélération.
         * Est utilisé si rampPositionEnabled est \c true.
         */
        static const float RAMP_DEC = 0.07; //0.07 0.1

        /*!
         * \brief Vitesse minimum (en tick par PERIOD_TIMER) permettant de faire
         * avancer le robot "en petite vitesse".
         */
        static const int SPEED_MIN = 6; //50ms 6

        /*!
         * \brief Vitesse maximum (en tick par PERIOD_TIMER) appliquée au robot
         * lors de l'asservissement.
         *
         * Pour 100ms : La vitesse du robot est de 90cm/s et donc 100 tick (un tick=0,86mm=100impulsions=100ms).
         * Pour 50ms :
         */
        static const int SPEED_MAX = 70; //50ms 35

        static const int ODO_FREQ_MAX = 10;
        
        static const int ODO_FREQ_MIN = 3;

        /*!
         * \brief Constructeur de la classe.
         * \param robot
         *        Référence vers le robot associé à cette base roulante.
         */
        Base(pmx::Robot & robot);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~Base()
        {
            /*delete positionManager_;
            delete speedManager_;*/
        }

        /*!
         * \brief Retourne une référence vers l'objet \ref Motor associé au
         * moteur gauche.
         */
        /*inline pmx::MotorWithMd25 & motorLeft()
        {
            return motorLeft_;
        }
*/
        /*!
         * \brief Retourne une référence vers l'objet \ref Motor associé au
         * moteur droit.
         */
        /*inline pmx::MotorWithMd25 & motorRight()
        {
            return motorRight_;
        }*/


        /*!
         * \brief Retourne la gestionnaire de position (odométrie) associé à la
         * base du robot.
         */
       /* inline PositionManager & positionManager()
        {
            return *positionManager_;
        }*/

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

        inline bool rampPositionEnabled() const
        {
            return this->flags_ & RAMP_POSITION;
        }

        inline void rampPositionEnabled(bool rampPositionEnabled)
        {
            if (rampPositionEnabled)
            {
                this->flags_ |= RAMP_POSITION;
            }
            else
            {
                this->flags_ &= ~RAMP_POSITION;
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

        inline bool modeVecteurCorrectionEnabled() const
        {
            return this->flags_ & MODE_AUTOCORRECT;
        }

        inline void modeVecteurCorrectionEnabled(bool modeVecteurCorrectionEnabled)
        {
            if (modeVecteurCorrectionEnabled)
            {
                this->flags_ = this->flags_ | MODE_AUTOCORRECT;
            }
            else
            {
                this->flags_ = this->flags_ & ~MODE_AUTOCORRECT;
            }
        }

        inline double xDestination() const
        {
            return this->xDestination_;
        }

        inline void xDestination(double x)
        {
            this->xDestination_ = x;
        }

        inline double yDestination() const
        {
            return this->yDestination_;
        }

        inline void yDestination(double y)
        {
            this->yDestination_ = y;
        }

        inline double angleDestination() const
        {
            return this->angleDestination_;
        }

        inline void angleDestination(double angle)
        {
            this->angleDestination_ = angle;
        }

        inline bool arrived() const
        {
            return arrived_;
        }

        inline void arrived(bool arrived)
        {
            this->arrived_ = arrived;
        }

        inline bool arrivedDestination() const
        {
            return arrivedDestination_;
        }

        inline void arrivedDestination(bool arrived)
        {
            this->arrivedDestination_ = arrived;
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

        /*!
         * \brief Permet de rendre actif les calcul du SpeedManager.
         *
         */
        void pidSpeedActivate();

        /*!
         * \brief Permet de laisser actif le SpeedManager mais de ne rien faire (sauf le test I2C).
         *
         */
        void pidSpeedDesactivate();

        /*!
         * \brief Permet d'activer ou non l'asservissement en vitesse des moteur RED/YELLOW.
         *
         */
        void pidSpeedMotorRedYellowActivate(bool enable);

        /*!
         * \brief Demarre le Timer associé au SpeedManager pour activer la fonction onTimer.
         *
         */
        void pidSpeedStart();

        /*!
         * \brief Arrete le Timer associé au SpeedManager, l'execution de la fonction onTimer ne sera plus exécuté.
         *
         */
        void pidSpeedStop();
       
        /*!
         * \brief indique que le mode test pid position afin de ne pas prendre en compte le test d'arret en position.
         *
         */
        inline void pidPositionTest(bool )
        {
            /*this->speedManager_->modeTestPidPos(value);*/
        }

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
         * \deprecated
         */
        void defineMotorSpeed(double speedLeft, double speedRight);

        /*!
         * \brief Donne l'ordre à la base roulante d'avancer à une vitesse donnée.
         * Cette méthode équivaut à appeler \c defineMotorSpeed(speed,speed).
         *
         * \deprecated
         *
         * \param speed
         *        Vitesse appliquée aux moteurs de la base roulante.
         */
        void goForward(double speed);

        /*!
         * \brief Donne l'ordre à la base roulante de tourner à gauche d'un
         * angle défini.
         *
         * \param way
         *        pmx::BTURNLEFT, pmx::BTURNRIGHT
         * \param angle
         *        angle de rotation du robot (compris entre -PI et PI).
         */
        void turn(BaseWay way, double angle);

        /*!
         * \brief Donne l'ordre à la base roulante de tourner à droite.
         *
         * \param angle
         *        angle de rotation du robot(compris entre -PI et PI).
         */
        //void turnRight(double angle);

        /*!
         * \brief Donne l'ordre à la base roulante de tourner d'un angle donné
         * au plus court (droite ou gauche).
         * 
         * \param angle
         *        angle du repere generale (compris entre -PI et PI).
         */
        void turnTeta(double anglePos);
        

        /*!
         * \brief Active les listeners associés à la base (odométrie + SpeedManager).
         *
         * Cette méthode lance les différents threads associés.
         */
        void startListener();


        /*!
         * \brief Arret de la base.
         */
        void stop();

        /*!
         * \brief Arret de la base et reset des valeurs;
         */
        void arrivedStopReset();

        
        /*!
         * \brief Donne l'ordre à la base roulante d'avancer à une position
         * donnée et à un angle donné.
         *
         * \param x
         *        abscisse de destination (en mm).
         * \param y
         *        ordonnée de destination (en mm).
         * \param way
         *        ordre d'avance.
         * \param angle
         *        angle souhaité à l'arrivée (compris entre -PI et PI).
         * \param opponentDetection
         *        moveD avec ou sans détection de l'adversaire.
         *
         * \return opponent detected.
         *
         */
        bool movexyTeta(double x, double y, BaseWay way, double angle, bool opponentDetection);

        /*!
         * \brief Donne l'ordre à la base roulante d'avancer à une position donnée.
         *
         * \param x
         *        abscisse de destination (en mm).
         * \param y
         *        ordonnée de destination (en mm).
         * \param way
         *        ordre d'avance.*
         * \param opponentDetection
         *        moveD avec ou sans détection de l'adversaire.
         *
         * \return opponent detected.
         *
         */
        bool movexy(double x, double y, BaseWay way, bool opponentDetection);
      
        /*!
         * \brief Permet d'avancer d'une distance d dans la direction du robot à
         * une coordonnée x,y. y ne doit pas être trop éloigné du 0.
         *
         * \param d
         *        abscisse en tick à atteindre sur le repere de base. Peut être
         * négatif pour donner le sens de l'ordre d'avance.
         * \param y
         *        ordonnée en tick à atteindre sur le repere de base.
         */
        void moveD(int d, int y);



        bool checkOpponent();

        bool ensureOpponent(double distIrLeft, double distIrCenter, double distIrRight);

        bool isInAForm(ObjectForm form, double oxCentre, double oyCentre, double xFormCentre, double yFormCentre, double length);


        /*!
         * \brief Calcule l'angle par rapport à la position actuelle
         * du robot.
         *
         * \param angle
         *        angle souhaité à l'arrivée (compris entre -PI et PI).
         *
         */
        double computeAngleToGo(double angle);
        double computeAngleToGo2(double angle, double anglePos);

        /*!
         * \brief Calcule le vecteur jusqu'au point de destination.
         *
         * \param v*        Vecteur vx, vy, vd, va à initialiser.
         * \param xDest     abcisse de destination.
         * \param yDest     ordonnée de destination.
         */
        void computeDestinationVector(double *v, double xDest, double yDest, double xPos, double yPos);


        void printPosition(std::string log);

        /*!
         * \brief Configuration par fichier de conf.
         */
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
}

#endif
