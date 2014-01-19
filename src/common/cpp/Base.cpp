/*!
 * \file
 * \brief Implémentation de la classe Base.
 */

#include <cmath>
#include <string>
#include "Base.hpp"
#include "Robot.hpp"
#include "MotorWithMd25.hpp"
#include "OdometryPositionManager.hpp"
#include "SvgWriter.hpp"

pmx::Base::Base(pmx::Robot & robot) : ARobotElement(robot),
motorLeft_(robot, pmx::MLEFT),
motorRight_(robot, pmx::MRIGHT),
positionManager_(new pmx::OdometryPositionManager(robot, pmx::ENCODERMOTOR)),
speedManager_(new pmx::SpeedManagerFusion(this, utils::PID(1, 0, 0), utils::PID(1, 0, 0), utils::PID(1, 0, 0))),
flags_(0),
xDestination_(0.0), yDestination_(0.0),
arrived_(false), arrivedDestination_(false),
xOffset_(0),
yOffset_(0),
flashBallWheel_(robot, pmx::MRED, pmx::FORWARD, 0, 0)
{
}

void
pmx::Base::startListener()
{
    logger().debug() << " addListener OdometryPositionManager" << utils::end;
    this->robot().addListener(positionManager_); //ajout de l'odometrie
    logger().debug() << " addListener speedManagerFusion" << utils::end;
    this->robot().addListener(speedManager_);
}

void
pmx::Base::initialize(const std::string& prefix, utils::Configuration& configuration)
{
    logger().debug() << "initialize: " << prefix << utils::end;

    //MRED
    double pRedSpeedForw = configuration.getDouble(prefix + "-RedSpeedForw" + "-P");
    double iRedSpeedForw = configuration.getDouble(prefix + "-RedSpeedForw" + "-I");
    double dRedSpeedForw = configuration.getDouble(prefix + "-RedSpeedForw" + "-D");
    this->pidSpeedInitialize(pmx::MRED, pRedSpeedForw, iRedSpeedForw, dRedSpeedForw);

    //MLEFT
    double pLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-P");
    double iLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-I");
    double dLeftSpeedForw = configuration.getDouble(prefix + "-LeftSpeedForw" + "-D");
    this->pidSpeedInitialize(pmx::MLEFT, pLeftSpeedForw, iLeftSpeedForw, dLeftSpeedForw);
    double pLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-P");
    double iLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-I");
    double dLeftSpeedBack = configuration.getDouble(prefix + "-LeftSpeedBack" + "-D");
    this->pidSpeedBackInitialize(pmx::MLEFT, pLeftSpeedBack, iLeftSpeedBack, dLeftSpeedBack);
    double pLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-P");
    double iLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-I");
    double dLeftPos = configuration.getDouble(prefix + "-LeftPos" + "-D");
    this->pidPositionInitialize(pmx::MLEFT, pLeftPos, iLeftPos, dLeftPos);

    //MRIGHT
    double pRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-P");
    double iRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-I");
    double dRightSpeedForw = configuration.getDouble(prefix + "-RightSpeedForw" + "-D");
    this->pidSpeedInitialize(pmx::MRIGHT, pRightSpeedForw, iRightSpeedForw, dRightSpeedForw);
    double pRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-P");
    double iRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-I");
    double dRightSpeedBack = configuration.getDouble(prefix + "-RightSpeedBack" + "-D");
    this->pidSpeedBackInitialize(pmx::MRIGHT, pRightSpeedBack, iRightSpeedBack, dRightSpeedBack);
    double pRightPos = configuration.getDouble(prefix + "-RightPos" + "-P");
    double iRightPos = configuration.getDouble(prefix + "-RightPos" + "-I");
    double dRightPos = configuration.getDouble(prefix + "-RightPos" + "-D");
    this->pidPositionInitialize(pmx::MRIGHT, pRightPos, iRightPos, dRightPos);

    logger().debug() << "initialize with: "
            << " pLeftSpeedForw:" << pRedSpeedForw
            << " iLeftSpeedForw:" << iRedSpeedForw
            << " dLeftSpeedForw:" << dRedSpeedForw
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
pmx::Base::pidSpeedStop()
{
    this->speedManager_->stopTimer();
}

void
pmx::Base::pidSpeedActivate()
{
    //this->speedManager_->resetTimer(); //!\ todo a confirmer si necessaire
    this->speedManager_->activateSMF(); //!\todo fusionner avec desactivateSMF avec true/false
}

void
pmx::Base::pidSpeedDesactivate()
{
    this->speedManager_->desactivateSMF();
}

void
pmx::Base::pidSpeedMotorRedYellowActivate(bool enable)
{
    this->speedManager_->activateSMFMotorRedYellow(enable);
}

void
pmx::Base::reset()
{
    this->arrived(false);
    //reset des PID vitesse et position
    this->speedManager_->reset();
    this->motorLeft_.resetMotor();
    this->motorRight_.resetMotor();

    this->vdInitial_ = 0.0;
    this->b_ = 0.0;
    this->xIntersect_ = 0.0;
    this->yIntersect_ = 0.0;

    this->positionManager().reset();


    const Position & position = this->robot().position();
    this->xOffset(position.x());
    this->yOffset(position.y());
    this->angleOffset(position.angle());
    logger().debug() << "reset xOffset:" << this->xOffset() << " yOffset:" << this->yOffset() << " angleOffset:" << this->angleOffset() << utils::end;
}

void
pmx::Base::moveD(int d, int yGap) //d est signé
{
    //logger().debug() << "moveD" << utils::end;

    this->printPosition("moveD start");
    //reset des variables
    this->reset();

    //Dans le cas d'un y different de zero, calcul de la distance de l'hypothenuse.
    double vd =std::abs((double)d);
    if (yGap != 0)
    {
        double vx = std::abs((double)d);
        double vy = yGap;
        vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5);
    }

    this->vdInitial_ = vd; //en tick

    //Application du sens de marche en fonction de la demande //todo utile ?
    if (d < 0)
    {
        this->orderWay(pmx::BBACK);
    }else
    {
        this->orderWay(pmx::BFORWARD);
    }

    logger().debug() << "moveD: vd(tick):" << vd << utils::end; //valeur de distance D à atteindre
    this->robot().firePulseEnabled(true); //prise en compte des impulsions des codeurs.

    this->positionManager().changeFrequency(this->ODO_FREQ_MAX);

    this->motorLeft_.orderPositionTick(vd); //valeur tjs positive
    this->motorRight_.orderPositionTick(vd); //valeur tjs positive

    this->pidSpeedActivate(); //start le timer de gestion PID
}

void
pmx::Base::printPosition(std::string log)
{
    logger().info() << "printPosition: x y angle : " << this->robot().position().x() << " "
            << this->robot().position().y()
            << " " << (this->robot().position().angle() * 180.0) / M_PI
            << " (" << log << ")"
            << utils::end;
}

bool
pmx::Base::movexyTeta(double xDest, double yDest, BaseWay way, double teta, bool opponentDetection)
{

    logger().debug() << "xDest yDest : " << this->xDestination_ << " " << this->yDestination_ << utils::end;

    bool opponentDetected = movexy(xDest, yDest, way, opponentDetection);
    if(opponentDetected == true)
    {
        return opponentDetected;
    }

    const Position & position = this->robot().position();

    //opponentDetected = this->checkOpponent();
    //if (!opponentDetected)
    //{
        logger().debug() << "movexyTeta:  turnTeta " << utils::end;
        this->turnTeta(teta);
        while (this->arrived() == false) //boucle d'attente d'arrivée
        {
            usleep(1000);
        }
    //}else{
    //    logger().debug() << "movexyTeta: opponentDetected: NO turnTeta " << utils::end;
    //}


    this->stop();

    this->robot().firePulseEnabled(false);

    logger().debug() << "movexyTeta:  AfterTurn x: " << position.x() << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI << utils::end;
    
    //Mise à jour de la position
    this->positionManager().compute(utils::SVG_POS_END, true);

    return false;
}

bool
pmx::Base::movexy(double xDest, double yDest, BaseWay way, bool opponentDetection)
{
    logger().debug() << "movexy" << utils::end;
    

    this->xDestination_ = xDest;
    if (this->robot().myColor() == pmx::PMXRED && yDest > 0)
    {
        logger().debug() << "movexy --RED" << utils::end;
        this->yDestination_ = yDest; //RED
    }else
    {
        logger().debug() << "movexy --BLUE" << utils::end;
        this->yDestination_ = -yDest; //BLUE or defaut NOCOLOR
    }
    logger().debug() << "movexy: xDest yDest : " << this->xDestination_ << " " << this->yDestination_ << utils::end;

    const Position & position = this->robot().position();

    double vxDest = 0.0, vyDest = 0.0, vdDest = 0.0, vaDest = 0.0;
    double *v = new double[4];
    computeDestinationVector(v, this->xDestination(), this->yDestination(), position.x(), position.y());
    vxDest = v[0];
    vyDest = v[1];
    vdDest = v[2];
    vaDest = v[3];
    delete[] v;

    //init du repere de base
    this->xOffset_ = position.x() * cos(vaDest) + position.y() * sin(vaDest);
    this->yOffset_ = -position.x() * sin(vaDest) + position.y() * cos(vaDest);
    this->angleOffset_ = vaDest;

    if(way == pmx::BBACK)
    {
        if (vaDest > 0.0)
        {
            vaDest-=M_PI;
        }else if (vaDest <= 0.0)
        {
            vaDest+=M_PI;
        }
    }

    bool opponentDetected = false;
    //opponentDetected = this->checkOpponent();
    //if (!opponentDetected)
    //{
        if (vaDest != 0.0)
        {
            logger().debug() << "movexy:  turnTeta " << utils::end;
            this->turnTeta(vaDest); //vise le point de destination
            while (this->arrived() == false) //boucle d'attente d'arrivée
            {
                usleep(1000);
            }
            this->stop();

            this->robot().firePulseEnabled(false);

            logger().debug() << "movexy:  After turnTeta x: " << position.x()
                    << " y: " << position.y()
                    << " deg: " << (position.angle() *180) / M_PI
                    << utils::end;
        }else
        {
            logger().debug() << "movexy:  PAS DE turnTeta " << utils::end;
        }
    //}else
    //{
    //     logger().debug() << "movexy: opponentDetected: NO turnTeta " << utils::end;
    //}

    //avancer droit jusqu'au point
    if (vdDest > 5)
    {
        if(way == pmx::BBACK)
        {
            vdDest = -vdDest;
        }

        if (opponentDetection == true)
        {
            //this->robot().irSensorsGroup().startTimer();
            opponentDetected = this->checkOpponent();
        }

        if (!opponentDetected)
        {
            logger().debug() << "movexy:  moveD " << utils::end;
            this->moveD(vdDest / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE, 0); //en tick
        }
        else
        {
            logger().debug() << "movexy:  opponentDetected: NO moveD " << utils::end;
        }
        logger().debug() << "movexy:  before while " << utils::end;
        while (this->arrived() == false) //boucle d'attente d'arrivée
        {
            if (opponentDetection == true)
            {
                //logger().debug() << "b48" << utils::end;
         //       logger().debug() << "movexy:  opponentDetected before checkOpponent() "<< opponentDetected << utils::end;
                opponentDetected = this->checkOpponent();
                //logger().debug() << "movexy:  opponentDetected before Test ==="<< opponentDetected << utils::end;
                if (opponentDetected == true)
                {
                    logger().debug() << "movexy:  opponentDetected 1 " << utils::end;
                    //lance une confirmation
                    //this->robot().opponentIrSensorLeft().changeFrequency(10);
                    //this->robot().opponentIrSensorRight().changeFrequency(10);
                    //this->robot().opponentIrSensorCenter().changeFrequency(10);
                    //usleep(40000);
/*                    bool opponentDetectedConfirmation = this->checkOpponent();

                    if(opponentDetectedConfirmation)
                    {
                        logger().info() << "movexy:  opponentDetected 2 confirm " << utils::end;
                        //this->robot().opponentIrSensorLeft().changeFrequency(pmx::IrSensor::PERIOD_IR);
                        //this->robot().opponentIrSensorRight().changeFrequency(pmx::IrSensor::PERIOD_IR);
                        //this->robot().opponentIrSensorCenter().changeFrequency(pmx::IrSensor::PERIOD_IR);
                        //this->robot().base().stop();

                        return opponentDetectedConfirmation;
                    }   */
                    return opponentDetected;

                }
            }
//logger().debug() << "b49" << utils::end;
            usleep(1000);
        }
//logger().debug() << "b50" << utils::end;
        this->stop();
        /*if (opponentDetection == true)
        {
            this->robot().irSensorsGroup().stopTimer();
        }*/
    }
    this->robot().firePulseEnabled(false);

    logger().debug() << "movexy:  After moveD x: " << position.x()
                << " y: " << position.y()
                << " deg: " << (position.angle() *180) / M_PI
                << utils::end;

    logger().debug() << "b51" << utils::end;

    //Mise à jour de la position
    this->positionManager().compute(utils::SVG_POS_RED, true);
    
    if (!opponentDetected)
    {
        this->arrivedDestination(true);
    }

    logger().debug() << "b52" << utils::end;

    return false;
}


bool
pmx::Base::checkOpponent()
{   
    bool opponentDetectedL = false;
    bool opponentDetectedC = false;

    bool opponentDetectedR = false;

    bool opponentDetected = false;

    //TODO PRENDRE EN COMPTE LA DIRECTION DU ROBOT



    if (this->robot().irSensorsGroup().irLeft().distanceMm() < 270 ) //test GP2150
    {
        logger().debug() << "checkOpponent !!!! collision LEFT !!!! " << this->robot().irSensorsGroup().irLeft().distanceMm() << "mm" << utils::end;
        opponentDetectedL = true;
    }

    if (this->robot().irSensorsGroup().irRight().distanceMm() < 270 ) //test GP2150
    {
        logger().debug() << "checkOpponent !!!! collision RIGHT !!!! " << this->robot().irSensorsGroup().irRight().distanceMm() << "mm" << utils::end;
        opponentDetectedR = true;
    }

    if (this->robot().irSensorsGroup().irCenter().distanceMm() < 250 ) //test GP2150
    {
        logger().debug() << "checkOpponent !!!! collision CENTER !!!! " << this->robot().irSensorsGroup().irCenter().distanceMm() << "mm" << utils::end;
        opponentDetectedC = true;
    }

    if (opponentDetectedL || opponentDetectedR || opponentDetectedC )
    {
        opponentDetected = ensureOpponent(this->robot().irSensorsGroup().irLeft().distanceMm(),
                this->robot().irSensorsGroup().irCenter().distanceMm(),
                this->robot().irSensorsGroup().irRight().distanceMm());
        if (opponentDetected)
        {
            logger().debug() << "---- ensureOpponent OK" << utils::end;
            //this->motorLeft().applyMotorCode(pmx::Base::SPEED_MIN);
            //this->motorRight().applyMotorCode(pmx::Base::SPEED_MIN);

            //this->stop();
        }else
        {
            logger().debug() << "---- ensureOpponent NOK" << utils::end;
        }
    }

    return opponentDetected;
}

bool
pmx::Base::ensureOpponent(double distIrLeft, double distIrCenter, double distIrRight)
{

    const Position & position = this->robot().position();
    double angleIrRight = 40.0;
    double angleIrLeft = 40.0;
    //conversion distance reelle (decalage de centre + conversion inclinaison)
    double sens=-1.0;
    if (this->robot().myColor() ==pmx::PMXRED)
        sens=1.0;

    //calcul de la position de l'adversaire
    //calcul des points détection
    double oxCenter=0.0, oyCenter=0.0;  //détecteur central
    oxCenter=position.x() + (distIrCenter * std::cos(position.angle()));
    oyCenter=position.y() + sens*(distIrCenter * std::sin(position.angle()));

    logger().debug() << "ensureOpponent: "
            <<" position=("<<position.x()<<","<<position.y()<<")"
            <<" angle=="<<position.angle()
            <<" IrCentre=("<<distIrCenter<<"), sens="<<sens
            << utils::end;
    double oxLeft=0.0, oyLeft=0.0;
    oxLeft=position.x() + 120.0 + (distIrLeft * std::cos(angleIrLeft) * std::cos(position.angle()));
    oyLeft=position.y() - (sens*130.0) + (distIrLeft * std::cos(angleIrLeft) * std::sin(position.angle()));

    double oxRight=0.0, oyRight=0.0;
    oxRight=position.x() + 120 + (distIrRight * std::cos(angleIrRight) * std::cos(position.angle()));
    oyRight=position.y() + (sens*130.0) + (distIrRight * std::cos(angleIrRight) * std::sin(position.angle()));

    //tous les cas
    logger().debug() << "ensureOpponent: "
            <<" centre=("<<oxCenter<<","<<oyCenter<<")"
            <<" left=("<<oxLeft<<","<<oyLeft<<")"
            <<" right=("<<oxRight<<","<<oyRight<<")"
            << utils::end;
    //depassement de terrain //todo prendre en compte les bordures
    if(oxCenter <= 0)
        return false;
    if(oxCenter >= 3000)
        return false;
    if (this->robot().myColor() ==pmx::PMXRED)
    {
        if(oyCenter <= 0)
            return false; //c'est pas l'adversaire
        if(oyCenter >= 2000)
            return false; //c'est pas l'adversaire
    }else
    {
        if(oyCenter >= 0)
            return false;  //c'est pas l'adversaire
        if(oyCenter <= -2000)
            return false; //c'est pas l'adversaire
    }
    //todo autres capteurs
     logger().debug() << "ensureOpponent: détection dans le terrain" << utils::end;
     bool object=true;
     /*
    //objet cdrom de la mer
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxCenter,oyCenter,1000.0,500.0,8.0);
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxLeft,oyLeft,1000.0,500.0,8.0);
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxRight,oyRight,1000.0,500.0,8.0);
    //objet totem de notre camp
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxCenter,oyCenter,1100.0,1000.0,302.0);
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxLeft,oyLeft,1100.0,1000.0,302.0);
    object = object || this->isInAForm(pmx::PMXCIRCLE,oxRight,oyRight,1100.0,1000.0,302.0);
    */
    logger().debug() << "ensureOpponent: object="<<object << utils::end;
    return object;  //true c'est bien l'adversaire
    //return true;
}

bool
pmx::Base::isInAForm(ObjectForm form, double oxCentre, double oyCentre, double xFormCentre, double yFormCentre, double length)
{

    if (form==pmx::PMXSQUARE)
    {
        if (oxCentre>xFormCentre-length && oxCentre<xFormCentre+length && oyCentre>yFormCentre-length && oyCentre<yFormCentre+length)
        {
            return true;
        }
    }
    else
    {
        if (std::pow(std::pow(xFormCentre-oxCentre,2.0)+std::pow(yFormCentre-oyCentre,2.0),0.5)<=length)
        {
            return true;
        }
    }
    return false;
}

double 
pmx::Base::computeAngleToGo(double teta) //!\TODO fusionner avec computeAngleToGo2
{
    const Position & position = this->robot().position();
    double diffAngle = 0.0;
    double anglePos = position.angle(); //compris entre -PI et PI

    diffAngle = teta - anglePos;

    logger().debug() << "ComputeAngleToGo diffAngle:" << (diffAngle * 180.0) / M_PI
            << " anglePos:" << (anglePos * 180.0) / M_PI << " teta:" << (teta * 180.0) / M_PI
            << utils::end;

    //on garde diffangle dans les valeurs entre -pi et pi
    if (diffAngle >= M_PI)
    {
        diffAngle = diffAngle - (M_PI * 2.0);
    }else if (diffAngle <= -M_PI)
    {
        diffAngle = diffAngle + (M_PI * 2.0);
    }
    return diffAngle;
}

double
pmx::Base::computeAngleToGo2(double teta, double anglePos)
{
    double diffAngle = 0.0;
    diffAngle = teta - anglePos;

    logger().debug() << "ComputeAngleToGo2 diffAngle:" << (diffAngle * 180.0) / M_PI
            << "° anglePos:" << (anglePos * 180.0) / M_PI << "° teta:" << (teta * 180.0) / M_PI << "°"
            << utils::end;

    //on garde diffangle dans les valeurs entre -pi et pi
    if (diffAngle >= M_PI)
    {
        diffAngle = diffAngle - (M_PI * 2.0);
    }else if (diffAngle <= -M_PI)
    {
        diffAngle = diffAngle + (M_PI * 2.0);
    }
    return diffAngle;
}

void
pmx::Base::computeDestinationVector(double *v, double xDest, double yDest, double xPos, double yPos)
{
    //vecteur de destination par rapport à la position actuelle (vx, vy, vd, va)
    v[0] = (xDest - xPos); //en mm.
    v[1] = (yDest - yPos); //en mm.
    v[2] = std::pow(std::pow(v[0], 2) + std::pow(v[1], 2), 0.5); //en mm, tjs positif.
    v[3] = std::acos(v[0] / v[2]); //compris entre 0 et PI

    if (v[1] < 0) // signe sur va
    {
        //logger().debug() << "movexy: vy < 0 => va = -va !!" << utils::end;
        v[3] = -v[3]; //va compris entre 0 et PI ou entre 0 et -PI
    }

    logger().debug() << "ComputeDestinationVector vx:" << v[0] << " vy:" << v[1] << " vd:" << v[2] << " va:" << v[3] << utils::end;
}

void
pmx::Base::turnTeta(double tetaDest)
{
    //calcul l'angle nécessaire pour tourner
    double diffAngle = computeAngleToGo(tetaDest);
    
    const Position & position = this->robot().position();
    
    this->angleDestination_ = tetaDest;

    logger().debug() << "turnTeta:" << (diffAngle * 180.0) / M_PI
            << utils::end;

    this->positionManager().changeFrequency(this->ODO_FREQ_MAX);

    if (diffAngle < 0.0) //donne le signe pour tourner à droite ou a gauche
    {
        //turn right
        this->turn(pmx::BTURNRIGHT, diffAngle);
        logger().debug() << "turnTeta: BeforeTurnRight pos x: " << position.x() 
                << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI
                << utils::end;

    }else if (diffAngle > 0.0)
    {
        //turn left
        this->turn(pmx::BTURNLEFT, diffAngle);
        logger().debug() << "turnTeta: BeforeTurnLeft pos  x: " << position.x() 
                << " y: " << position.y() << " deg: " << (position.angle() *180) / M_PI
                << utils::end;
    }
}

void
pmx::Base::turn(pmx::BaseWay way, double alpha)
{
    this->printPosition("turn: start");
    
    this->reset(); //reset des variables
    this->orderWay(way);

    //calcul de la distance (en tick) à parcourir sur le périmètre des roues du robot
    int d = std::abs(alpha * (this->positionManager_->DISTANCE_ENTRAXE_MOTORWHEEL / pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE) / 2);

    logger().debug() << "turn " << (way==pmx::BTURNLEFT ? "LEFT" : "RIGHT")
            << ": alpha:" << alpha << " degré:" << (alpha * 180.0) / M_PI
            << " d(perimetre):" << d
            << utils::end;
    
    if (d > 3)
    {
        //Mise à jour de la position
        this->positionManager().compute(utils::SVG_POS_RED, true);
        std::ostringstream log;
        log << "turn:" <<  (way==pmx::BTURNLEFT ? "LEFT" : "RIGHT")
                << (alpha * 180.0) / M_PI << "° x:"<< this->positionManager_->position().x()
                << " y:" << this->positionManager_->position().y();
        utils::SvgWriter::writeText(this->positionManager_->position().x() + 5, this->positionManager_->position().y()-3, log.str());

        this->robot().firePulseEnabled(true); //prise en compte des impulsions des codeurs.

        this->motorLeft_.orderPositionTick(d);
        this->motorRight_.orderPositionTick(d);

        this->pidSpeedActivate(); //start le timer de gestion PID
    }else
    {
        this->arrived(true);
    }
}

/*!
 * \brief Stop le robot et desactive la correction par PID (speedManagerFusion).
 */
void
pmx::Base::stop()
{
    //logger().debug("Stop flashBallWheel");
    this->flashBallWheel().stop();

    this->pidSpeedDesactivate();
    this->motorLeft().stop();
    this->motorRight().stop();
}

void
pmx::Base::arrivedStopReset()
{
    this->stop();
    this->arrived(true);

    this->motorLeft().resetMotor();
    this->motorRight().resetMotor();

    //Mise à jour de la position
    this->positionManager().compute(utils::SVG_POS_BLACK, true);
}
