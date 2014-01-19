/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include "Base.hpp"
#include "Robot.hpp"
#include "Motor.hpp"
#include "OdometryPositionManager.hpp"
#include "SvgWriter.hpp"
#include <cmath>
#include <string>

pmx::Base::Base(pmx::Robot & robot) : ARobotElement(robot),
motorLeft_(robot, LEFT, FORWARD, 0, 0),
motorRight_(robot, RIGHT, FORWARD, 0, 0),
positionManager_(new pmx::OdometryPositionManager()),
speedManager_(new pmx::SpeedManagerFusion(this, utils::PID(1, 0, 0), utils::PID(1, 0, 0))),
flags_(0),
xDestination_(0.0), yDestination_(0.0),
arrived_(false),
xOffset_(0),
yOffset_(0)
{
    logger().debug() << " addListener positionManager_" << utils::end;
    robot.addListener(positionManager_); //ajout de l'odometrie
    logger().debug() << " addListener speedManager_" << utils::end;
    robot.addListener(speedManager_);
}

void
pmx::Base::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "initialize: " << prefix << utils::end;

    double pLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-P");
    double iLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-I");
    double dLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-D");
    this->pidSpeedInitialize(pmx::LEFT, pLeftSpeedForw, iLeftSpeedForw, dLeftSpeedForw);

    double pLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-P");
    double iLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-I");
    double dLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-D");
    this->pidSpeedBackInitialize(pmx::LEFT, pLeftSpeedBack, iLeftSpeedBack, dLeftSpeedBack);

    double pLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-P");
    double iLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-I");
    double dLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-D");
    this->pidPositionInitialize(pmx::LEFT, pLeftPos, iLeftPos, dLeftPos);


    double pRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-P");
    double iRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-I");
    double dRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-D");
    this->pidSpeedInitialize(pmx::RIGHT, pRightSpeedForw, iRightSpeedForw, dRightSpeedForw);

    double pRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-P");
    double iRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-I");
    double dRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-D");
    this->pidSpeedBackInitialize(pmx::RIGHT, pRightSpeedBack, iRightSpeedBack, dRightSpeedBack);

    double pRightPos = configuration.getDouble(prefix + "-RightPos" + "-P");
    double iRightPos = configuration.getDouble(prefix + "-RightPos" + "-I");
    double dRightPos = configuration.getDouble(prefix + "-RightPos" + "-D");
    this->pidPositionInitialize(pmx::RIGHT, pRightPos, iRightPos, dRightPos);

    logger().debug() << "with: "
            << " pLeftSpeedForw:" << pLeftSpeedForw
            << " iLeftSpeedForw:" << iLeftSpeedForw
            << " dLeftSpeedForw:" << dLeftSpeedForw
            << prefix << utils::end;

}

void
pmx::Base::pidSpeedInitialize(MotorLocation location, double VkP, double VkI, double VkD)
{
    this->pidSpeedEnabled(true);
    this->speedManager_->initializeSpeedControler(location, utils::PID(VkP, VkI, VkD));
}

void
pmx::Base::pidSpeedBackInitialize(MotorLocation location, double VkP, double VkI, double VkD)
{
    this->pidSpeedEnabled(true);
    this->speedManager_->initializeSpeedBackControler(location, utils::PID(VkP, VkI, VkD));
}

void
pmx::Base::pidPositionInitialize(MotorLocation location, double PkP, double PkI, double PkD)
{
    this->pidPositionEnabled(true);
    this->speedManager_->initializePositionControler(location, utils::PID(PkP, PkI, PkD));
}

void
pmx::Base::pidSpeedStart()
{
    this->speedManager_->startTimer();
}

void
pmx::Base::pidSpeedActivate()
{
    //this->speedManager_->resetTimer(); //todo a confirmer si necessaire
    this->speedManager_->activateSMF();
}

void
pmx::Base::pidSpeedDesactivate()
{
    this->speedManager_->desactivateSMF();
}

/*
 * deprecated
 */
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
    }else
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
    }else
    {
        if (this->motorRight().way() == pmx::FORWARD)
        {
            this->motorRight().applyWay(pmx::BACK);
        }
        this->motorRight().orderSpeed(-speedRight);
    }
}

/*
 * deprecated
 */
void
pmx::Base::goForward(double speed)
{
    this->defineMotorSpeed(speed, speed);
}

void
pmx::Base::reset()
{
    this->arrived(false);
    //reset des PID vitesse et position
    this->speedManager_->reset();
    this->motorLeft_.resetMotor();
    this->motorRight_.resetMotor();

    //this->xDestination_ = 0;
    //this->yDestination_ = 0;
    this->vdInitial_ = 0.0;
    this->b_ = 0.0;
    this->xIntersect_ = 0.0;
    this->yIntersect_ = 0.0;

    this->pawnFound(false);

    const Position & position = this->robot().position();
    this->xOffset(position.x());
    this->yOffset(position.y());
    this->angleOffset(position.angle());
    logger().debug() << "reset xOffset:" << this->xOffset() << " yOffset:" << this->yOffset() << " angleOffset:" << this->angleOffset() << utils::end;
}

/*
 * \brief Permet d'avancer d'une distance d dans la direction du robot à une coordonnée x,y. y ne doit pas être trop éloigné du 0.
 * \param d abscisse en tick à atteindre sur le repere de base. Peut être négatif pour donner le sens de l'ordre d'avance.
 * \param y ordonnée en tick à atteindre sur le repere de base.
 */

void
pmx::Base::moveD(int d, int y)
{
    logger().debug() << "moveD" << utils::end;

    this->printPosition("moveD start");
    //reset des variables
    this->reset();

    //Dans le cas d'un y different de zero, calcul de la distance de l'hypothenuse.
    double vd = std::abs(d);
    if (y != 0)
    {
        double vx = std::abs(d);
        double vy = y;
        vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5);
    }

    this->vdInitial_ = vd; //en tick

    //Application du sens de marche en fonction de la demande
    if (d < 0)
    {
        this->orderWay(pmx::BBACK);
        //application du sens de marche
        //logger().debug() << "application du sens de marche:BACK" << utils::end;
        this->motorLeft_.applyWay(pmx::BACK);
        this->motorRight_.applyWay(pmx::BACK);
    }else
    {
        this->orderWay(pmx::BFORWARD);
        //application du sens de marche
        //logger().debug() << "application du sens de marche:FORWARD" << utils::end;
        this->motorLeft_.applyWay(pmx::FORWARD);
        this->motorRight_.applyWay(pmx::FORWARD);
    }
    //laisse le temps aux relais de sens de marche de se positionner.
    while (!this->motorLeft_.wayApplied() || !this->motorRight_.wayApplied())
    {
        usleep(5000);
    }

    logger().debug() << "vd(tick):" << vd << utils::end;
    this->robot().firePulseEnabled(true); //prise en compte des impulsions des codeurs.
    //valeur de distance D à atteindre
    this->motorLeft_.orderPositionTick(std::abs(vd));
    this->motorRight_.orderPositionTick(std::abs(vd));
    this->printPosition("moveD end");

    this->pidSpeedActivate(); //start le timer de gestion PID
}

void
pmx::Base::printPosition(std::string log)
{
    logger().info() << "x y angle : " << this->robot().position().x() << " "
            << this->robot().position().y()
            << " " << (this->robot().position().angle() * 180) / M_PI
            << " (" << log << ")"
            << utils::end;
}

/*
 * \brief Permet d'avancer à une coordonnée x,y sur le repere du terrain avec une détection de pion.
 * \param x abscisse à atteindre sur le repere general en mm.
 * \param y ordonnée à atteindre sur le repere general en mm.
 * \param way consigne de sens de marche.
 * \teta NULL pas d'angle, sinon angle en radian
 * \param detectPawn
 * \param offset en mm.
 */
void
pmx::Base::movexy_Dpawn(int xDest, int yDest, BaseWay way, double teta, int detectPawn, int offset)
{
    
    this->orderWay(way); //application de la consigne de sens de marche
    this->xDestination_ = xDest;
    if (this->robot().myColor() == pmx::RED && yDest > 0)
    {
        this->yDestination_ = -yDest; //RED
    }else
    {
        this->yDestination_ = yDest; //BLUE
    }
    logger().debug() << "xDest yDest : " << this->xDestination_ << " " << this->yDestination_ << utils::end;

    //vecteur de destination par rapport à la position actuelle
    const Position & position = this->robot().position();
    double diffAngle = 0.0;
    double anglePos = position.angle(); //compris entre -PI et PI
    double vx = (this->xDestination() - position.x()); //en mm.
    double vy = (this->yDestination() - position.y()); //en mm.
    double vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5); //en mm, tjs positif.
    double va = std::acos(vx / vd); //compris entre 0 et PI

    if (vy < 0)
    {
        logger().debug() << "movexyDpawn vy < 0 => va = -va !!" << utils::end;
        va = -va; //va compris entre 0 et PI ou entre 0 et -PI
    }
    //inversement de PI dans le cas de la marche arrière :
    if (this->orderWay() == pmx::BBACK)
    {
        vd = -vd; //donne le sens pour le moveD
        if (anglePos > 0)
        {
            logger().debug() << "cas back anglePos > 0" << utils::end;
            anglePos = anglePos - M_PI;
        }else if (anglePos <= 0)
        {
            logger().debug() << "cas back anglePos <= 0" << utils::end;
            anglePos = anglePos + M_PI;
        }
    }
    diffAngle = anglePos - va;
    logger().debug() << "movexyDpawn vx:" << vx << " vy:" << vy << " vd:" << vd << utils::end;
    logger().debug() << "movexyDpawn diffAngle:" << (diffAngle * 180) / M_PI << " anglePos:" << (anglePos * 180) / M_PI << " va:" << (va * 180) / M_PI<< utils::end;
    //pas de vecteur de correction pour tourner sur soi-meme
    bool vect = this->vecteurCorrectionEnabled();
    this->vecteurCorrectionEnabled(false);

    //on garde diffangle dans les valeurs entre -pi et pi
    if (diffAngle > M_PI)
    {
        diffAngle = diffAngle - M_2_PI;
    }else if (diffAngle < -M_PI)
    {
        diffAngle = diffAngle + M_2_PI;
    }

    this->reset(); //reset des valeurs

    //lancement de listener
    int distmin = 250;
    int distPawnLeft;
    int distPawnRight;
    
    if (diffAngle > 0 ) //donne le signe pour tourner à droite ou a gauche
    {
        //turn right  
        this->turnRight(diffAngle);
        logger().debug() << "movexyDpawn BeforeTurnRight pos x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI << utils::end;

    }else if (diffAngle < 0)
    {
        //turn left  
        this->turnLeft(diffAngle);
        logger().debug() << "movexyDpawn BeforeTurnLeft pos  x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI << utils::end;
    }
    if(detectPawn == 1)
    {
        this->robot().pawnLeftIrSensor().active(true); //activation des calculs
        this->robot().pawnRightIrSensor().active(true); //activation des calculs
    }
    if (diffAngle != 0)
    {
        while (this->arrived() == false) //boucle d'attente d'arrivée
        {
            if(detectPawn == 1)
            {            
                //on teste les GP2
                distPawnLeft = this->robot().pawnLeftIrSensor().distanceMm();
                distPawnRight = this->robot().pawnRightIrSensor().distanceMm();

                if(distPawnLeft<distmin && distPawnRight<distmin)
                {
                    logger().info() << "movexyDpawn pawn found : distPawnLeft: " << distPawnLeft << "  distPawnRight: " << distPawnRight << utils::end;

                    //on passe en mode : pion détecté
                    this->robot().pawnRightIrSensor().active(false);
                    this->robot().pawnLeftIrSensor().active(false);
                    this->robot().opponentIrSensor().active(false);
                    //this->motorLeft().stop();
                    //this->motorRight().stop();
                    this->pawnFound_ = true;
                    this->arrived(true);
                }
            }
            usleep(10000);
        }
        this->robot().firePulseEnabled(false);
    }
 
    if(!this->pawnFound_) //si pion non detecté lors de la rotation
    {
        this->stop();
        logger().debug() << "movexyDpawn  AfterTurn x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() * 180) / M_PI << utils::end;
        this->vecteurCorrectionEnabled(vect);

        //avancer droit jusqu'au point
        logger().debug() <<"movexyDpawn vd :" << vd << " offset :" << offset << "(vd-offset= " << vd - offset << "mm, vx: " << vx << ", vy: " << vy << utils::end;
        
        this->moveD((vd - offset) / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0); //en tick
        if(detectPawn == 1)
        {
            this->robot().pawnLeftIrSensor().active(true); //activation des calculs
            this->robot().pawnRightIrSensor().active(true); //activation des calculs
        }
        this->robot().opponentIrSensor().active(true);

        while (this->arrived() == false) //boucle d'attente d'arrivée
        {
            if (this->robot().opponentIrSensor().distanceMm() < 450) //test GP2150
            {
                logger().info() << "!!!! collision !!!! " << this->robot().opponentIrSensor().distanceMm() << "mm" << utils::end;
                this->stop();

                //!\todo aller dans un etat
                sleep(1);
                continue;
            }

            if(detectPawn == 1)
            {
                //on teste les GP2
                distPawnLeft = this->robot().pawnLeftIrSensor().distanceMm();
                distPawnRight = this->robot().pawnRightIrSensor().distanceMm();

                if(distPawnLeft<distmin || distPawnRight<distmin)
                {
                    logger().info() << "distPawnLeft: " << distPawnLeft << "  distPawnRight: " << distPawnRight << utils::end;
                    this->robot().pawnRightIrSensor().active(false);
                    this->robot().pawnLeftIrSensor().active(false);
                    this->robot().opponentIrSensor().active(false);
                    //on passe en mode : pion détecté
                    //this->motorLeft().stop();
                    //this->motorRight().stop();
                    this->pawnFound_ = true;
                    this->arrived(true);
                }
            }
            usleep(10000);
        }
        this->robot().firePulseEnabled(false);
        this->stop();

        //!\todo tourner de teta

    }
}


/*
 * \brief Permet d'avancer à une coordonnée x,y sur le repere du terrain.
 * \param x abscisse à atteindre sur le repere general en mm.
 * \param y ordonnée à atteindre sur le repere general en mm.
 * \param way consigne de sens de marche.
 */
void
pmx::Base::movexy(int xDest, int yDest, BaseWay way)
{
    //logger().debug() << "movexy" << utils::end;

    this->orderWay(way); //application de la consigne de sens de marche
    this->xDestination_ = xDest;
    if (this->robot().myColor() == pmx::RED && yDest > 0)
    {
        this->yDestination_ = -yDest; //RED
    }else
    {
        this->yDestination_ = yDest; //BLUE
    }

    //vecteur de destination par rapport à la position actuelle
    const Position & position = this->robot().position();
    double diffAngle = 0.0;
    double anglePos = position.angle(); //compris entre -PI et PI
    double vx = (this->xDestination() - position.x()); //en mm.
    double vy = (this->yDestination() - position.y()); //en mm.
    double vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5); //en mm, tjs positif.
    double va = std::acos(vx / vd); //compris entre 0 et PI
    if (vy < 0) //
    {
        logger().debug() << "vy < 0 => va = -va !!" << utils::end;
        va = -va; //va compris entre 0 et PI ou entre 0 et -PI
    }
    //inversement de PI dans le cas de la marche arrière :
    if (this->orderWay() == pmx::BBACK)
    {
        vd = -vd; //donne le sens pour le moveD
        if (anglePos > 0)
        {
            logger().debug() << "cas back anglePos > 0" << utils::end;
            anglePos = anglePos - M_PI;
        }else if (anglePos <= 0)
        {
            logger().debug() << "cas back anglePos <= 0" << utils::end;
            anglePos = anglePos + M_PI;
        }
    }
    diffAngle = anglePos - va;
    logger().debug() << "vx:" << vx << " vy:" << vy << " vd:" << vd << utils::end;
    logger().debug() << "diffAngle:" << diffAngle << " anglePos:" << anglePos << " va:" << va << utils::end;
    //pas de vecteur de correction pour tourner sur soi-meme
    bool vect = this->vecteurCorrectionEnabled();
    this->vecteurCorrectionEnabled(false);

    //on garde diffangle dans les valeurs entre -pi et pi
    if (diffAngle > M_PI)
    {
        diffAngle = diffAngle - 2 * M_PI;
    }else if (diffAngle < -M_PI)
    {
        diffAngle = diffAngle + M_2_PI;
    }

    this->reset(); //reset des valeurs

    if (diffAngle > 0) //donne le signe pour tourner à droite ou a gauche
    {
        //turn right
        this->turnRight(diffAngle);
        logger().debug() << "BeforeTurnRight x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() * 180) / M_PI << utils::end;

    }else if (diffAngle < 0)
    {
        //turn left  
        this->turnLeft(diffAngle);
        logger().debug() << "BeforeTurnLeft  x: " << position.x() << " y: " << position.y()  << " deg: " << (position.angle() * 180) / M_PI << utils::end;
    }
    if (diffAngle != 0)
    {
        while (this->arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(1000);
        }
        this->robot().firePulseEnabled(false);
    }

    this->stop();
    logger().debug() << " AfterTurn x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI << utils::end;
    this->vecteurCorrectionEnabled(vect);

    //avancer droit jusqu'au point
    this->moveD(vd / pmx::PositionManager::DISTANCE_PER_UP_PULSE, 0); //en tick
    while (this->arrived() == false) //boucle d'attente d'arrivée
    {
        usleep(1000);
    }
    this->robot().firePulseEnabled(false);
    
    this->stop();



    //!\todo tourner de teta




}

/*
 * \brief Tourne le robot sur lui-meme à gauche.
 * \param alpha compris entre 0 et 2PI
 */
void
pmx::Base::turnLeft(double alpha)
{
    this->printPosition("turnLeft start");
    //logger().debug() << "turnLeft" << utils::end;
    //reset des variables
    this->reset();

    //application du sens de marche
    this->orderWay(pmx::BTURNLEFT);
    this->motorLeft_.applyWay(pmx::BACK);
    this->motorRight_.applyWay(pmx::FORWARD);
    //laisse le temps aux relais de sens de marche de se positionner.
    while (!this->motorLeft_.wayApplied() || !this->motorRight_.wayApplied())
    {
        usleep(10000);
    }
    usleep(200000); //temps de prise en compte du sens de marche par les relais.

    //calcul de la distance (en tick) à parcourir sur le périmètre des roues du robot
    int d = std::abs(alpha * (this->positionManager_->DISTANCE_ENTRAXE / pmx::PositionManager::DISTANCE_PER_UP_PULSE) / 2);

    logger().debug() << "ORDRE turnLeft : alpha:" << alpha << " degré:" << (alpha * 180) / M_PI << " d(perimetre):" << d << utils::end;

    std::ostringstream log;
    log << "LEFT " << d << " " << (alpha * 180) / M_PI;
    utils::SvgWriter::writeText(this->positionManager_->position().x() + 10, this->positionManager_->position().y() + 10, log.str());
    this->robot().firePulseEnabled(true); //prise en compte des impulsions des codeurs.
    this->motorLeft_.orderPositionTick(d);
    this->motorRight_.orderPositionTick(d);

    this->printPosition("turnLeft end");
    this->pidSpeedActivate(); //start le timer de gestion PID
}

/*
 * \brief Tourne le robot sur lui-meme à droite.
 * \param alpha compris entre 0 et 2PI
 */
void
pmx::Base::turnRight(double alpha)
{
    this->printPosition("turnRight start");
    //logger().debug() << "turnRight" << utils::end;
    //reset des variables
    this->reset();

    //application du sens de marche
    this->orderWay(pmx::BTURNRIGHT);
    this->motorLeft_.applyWay(pmx::FORWARD);
    this->motorRight_.applyWay(pmx::BACK);
    //laisse le temps aux relais de sens de marche de se positionner.
    while (!this->motorLeft_.wayApplied() || !this->motorRight_.wayApplied())
    {
        usleep(5000);
    }
    usleep(200000); //temps de prise en compte du sens de marche par les relais.

    //calcul de la distance (en tick) à parcourir sur le périmètre des roues du robot
    int d = alpha * (this->positionManager_->DISTANCE_ENTRAXE / pmx::PositionManager::DISTANCE_PER_UP_PULSE) / 2;

    logger().debug() << "ORDRE turnRight : alpha:" << alpha << " degré:" << (alpha * 180) / M_PI << " d(perimetre):" << d << utils::end;

    std::ostringstream log;
    log << "RIGHT " << (alpha * 180) / M_PI;
    utils::SvgWriter::writeText(this->positionManager_->position().x() + 10, this->positionManager_->position().y() + 10, log.str());
    this->robot().firePulseEnabled(true); //prise en compte des impulsions des codeurs.
    this->motorLeft_.orderPositionTick(std::abs(d));
    this->motorRight_.orderPositionTick(std::abs(d));

    this->printPosition("turnRight end");
    this->pidSpeedActivate(); //start le timer de gestion PID
}

/*
 * \brief Stop le robot et desactive la correction par PID (speedManagerFusion).
 */
void
pmx::Base::stop()
{
    this->motorLeft().stop();
    this->motorRight().stop();
    this->pidSpeedDesactivate();
}
