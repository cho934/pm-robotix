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
         * \brief Manager assurant le calcul de la position du robot en fonction
         * des déplacements de sa base sur le terrain.
         */
        pmx::PositionManager * positionManager_;
        
        /*!
         * \brief \c true si la vitesse doit être corrigée en fonction de la position.
         *
         * Si cette propriété vaut \c false, le speed manager ne fera que tracer les informations de vitesse.
         */
        bool positionCorrectionEnabled_;
        
        /*!
         * \brief Coordonnée à atteindre (abscisse).
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
        
        double vdInitial_;
        
        double b_;
        
        double xIntersect_;
        
        double yIntersect_;
        
        
    public:
        /*!
         * \brief Distance du point d'arret à partir duquel on peut s'arrêter en mm.
         */
        static const double EPSILON = 6.0;
        
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
        static const double SPEED_MIN = 45.0;
        
        /*!
         * \brief Vitesse maximum appliquée au robot.
         */
        static const double SPEED_MAX = 250.0;
        
        
        
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
         * \brief Cette méthode retourne une référence vers l'objet Motor
         * de manipulation du moteur gauche.
         */
        inline pmx::Motor & motorLeft()
        {
            return motorLeft_;
        }
        
        /*!
         * \brief Cette méthode retourne une référence vers l'objet Motor
         * de manipulation du moteur droit.
         */
        inline pmx::Motor & motorRight()
        {
            return motorRight_;
        }
        
        /*!
         * \brief Cette méthode retourne la gestionnaire de position associé à la base
         * du robot.
         */
        inline const PositionManager & positionManager() const
        {
            return *positionManager_;
        }
        
        inline bool positionCorrectionEnabled() const
        {
            return this->positionCorrectionEnabled_;
        }
        
        inline void positionCorrectionEnabled(bool positionCorrectionEnabled)
        {
            this->positionCorrectionEnabled_ = positionCorrectionEnabled;
        }
        
        inline double x() const
        {
            return this->x_;
        }
        
        inline void x(double x)
        {
            this->x_ = x;
        }
        
        inline double y() const
        {
            return this->y_;
        }
        
        inline void y(double y)
        {
            this->y_ = y;
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
        
        
        /*
         * TODO deprecated
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
         * \param speed
         *        Vitesse appliquée aux moteurs.
         */
        void turnLeft(double speed);
        
        /*!
         * \brief Donne l'ordre à la base roulante de tourner à droite.
         * Cette méthode équivaut à appeler \c defineMotorSpeed(speed,-speed).
         *
         * \param speed
         *        Vitesse appliquée aux moteurs.
         */
        void turnRight(double speed);
        
        /*!
         * \brief Arret de la base.
         */
        void stop();
        
        /*!
         * \brief Donne l'ordre à la base roulante d'avancer à une position donnée.
         *
         * \param x
         *        abscisse de destination.
         * \param y
         *        ordonnée de destination.
         */
        void movexy(double x, double y);
        
        virtual void initialize(const std::string& prefix, utils::Configuration& configuration);
    };
}

#endif
