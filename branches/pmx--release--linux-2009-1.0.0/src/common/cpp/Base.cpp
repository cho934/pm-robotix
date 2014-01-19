/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include "Base.hpp"
#include "Robot.hpp"
#include "Motor.hpp"
#include "OdometryPositionManager.hpp"
#include <cmath>

pmx::Base::Base(pmx::Robot & robot): ARobotElement(robot),
        motorLeft_(robot, LEFT, FORWARD, 2.82, -18, utils::PID(1, 0, 0)),
        motorRight_(robot, RIGHT, FORWARD, 3.6, -80, utils::PID(1, 0, 0)),
        positionManager_( new pmx::OdometryPositionManager()),
        positionCorrectionEnabled_(false), x_(0), y_(0), arrived_(false)
{
    robot.addListener(positionManager_);
}

void
pmx::Base::initialize(const std::string&, utils::Configuration& configuration)
{
    this->motorLeft_.initialize("motorLeft", configuration);
    this->motorRight_.initialize("motorRight", configuration);
}

void
pmx::Base::defineMotorSpeed(double speedLeft, double speedRight)
{
    if (speedLeft > 0.0)
    {
        if (this->motorLeft().way() == pmx::BACK)
        {
            this->motorLeft().applyWay(pmx::FORWARD);
        }
        this->motorLeft().orderSpeed(speedLeft);
    }
    else
    {
        if (this->motorLeft().way() == pmx::FORWARD)
        {
            this->motorLeft().applyWay(pmx::BACK);
        }
        this->motorLeft().orderSpeed(-speedLeft);
    }
    if (speedRight > 0.0)
    {
        if (this->motorRight().way() == pmx::BACK)
        {
            this->motorRight().applyWay(pmx::FORWARD);
        }
        this->motorRight().orderSpeed(speedRight);
    }
    else
    {
        if (this->motorRight().way() == pmx::FORWARD)
        {
            this->motorRight().applyWay(pmx::BACK);
        }
        this->motorRight().orderSpeed(-speedRight);
    }
}

void
pmx::Base::goForward(double speed)
{
    this->defineMotorSpeed(speed, speed);
}

void
pmx::Base::movexy(double x, double y)
{
    
    this->x_ = x;
    this->y_ = y;
    
    
    //calcul du trapèze de trajectoires en position
    const Position & position = this->robot().base().positionManager().position(); 
    // Calcul du vecteur v reliant le point actuel (position) au point de destination.
    // vx et vy sont les coordonnées de ce vecteur, vd sa longueur.
    double vx = this->x_ - position.x();
    double vy = this->y_ - position.y();
    double vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5);
    this->vdInitial(vd);
    
    this->b(SPEED_MIN - (GRADIENT_ACC * this->vdInitial_));

    //2. calcul de l'intersection des 2 droites
    this->xIntersect((this->b_ - SPEED_MIN) / (GRADIENT - GRADIENT_ACC));
    this->yIntersect(GRADIENT * this->xIntersect_ + SPEED_MIN);

    logger().debug() << "vx: " << vx 
            << " vy:" << vy 
            << " vd:" << vd 
            << " vdinit:" << this->vdInitial_
            << " xIntersect: " << this->xIntersect_ 
            << " yIntersect: " << this->yIntersect_
            << utils::end;
    /*
    //Application du sens de marche en fonction du vecteur
    if (vx < 0 || vy < 0)
    {
        //application du sens de marche
        logger().debug() << "application du sens de marche:BACK" << utils::end;
        this->motorLeft_.applyWay(pmx::BACK);
        this->motorRight_.applyWay(pmx::BACK);
    }else
    {
        //application du sens de marche
        logger().debug() << "application du sens de marche:FORWARD" << utils::end;
        this->motorLeft_.applyWay(pmx::FORWARD);
        this->motorRight_.applyWay(pmx::FORWARD);
    }
    */
    //active la correction en position dans le speedmanager
    positionCorrectionEnabled(true);
    
    //attente de l'arrivée en position => voir suite prog d'appel
    
}

void
pmx::Base::turnLeft(double speed)
{
    this->defineMotorSpeed(-speed, speed);
}

void
pmx::Base::turnRight(double speed)
{
    this->defineMotorSpeed(speed, -speed);
}

void
pmx::Base::stop()
{
    this->motorLeft().stop();
    this->motorRight().stop();
}
