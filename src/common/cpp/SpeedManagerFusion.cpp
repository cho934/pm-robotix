/*!
 * \file
 * \brief Implementation de la classe SpeedManagerFusion.
 */

#include "Macro.hpp"
#include "Robot.hpp"
#include "Base.hpp"
#include "SpeedManagerFusion.hpp"
#include <cmath>
#include <iostream>

pmx::SpeedManagerFusion::SpeedManagerFusion(pmx::Base * base, const utils::PID & pidL, const utils::PID & pidR) :
        base_(base),
        nbPulsesLeft_(0), nbPulsesRight_(0), lastNbPulsesLeft_(0), lastNbPulsesRight_(0),
        timerSMF_(PERIOD_PID, this), pidLeft_(pidL), pidRight_(pidR), ActiveSMF_(false)
{
    //initialisation du fichier de log
    if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG))
    {
        utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug()
                << ";motor;orderTick;RealTick;PIDMotorCode;PIDerror;TimeSpan;speedReal;PIDPosDistanceTotale;PIDPosError;PIDPosOrderTick;tempOrderTick1;vd;vx;vy;va;DiffAngle;VectCorrMode;VectCorrOrderTick;x;y;angle;" << utils::end;
    }
}

void
pmx::SpeedManagerFusion::initialize(const std::string& prefix, utils::Configuration& )
{
    logger().debug() << "initialize: " << prefix << utils::end;
}

int toctoc=0; //! \todo a supprimer apres correction de la methode vecteurCorrectionEnabled

void pmx::SpeedManagerFusion::onTimer(utils::Chronometer chrono)
{
    toctoc++;
    if(this->ActiveSMF_) //si activation
    {
        Motor & motorLeft = this->base_->motorLeft();
        Motor & motorRight = this->base_->motorRight();

        int errorLeft = 0.0;
        int motorCodeLeft = 0;

        int errorRight = 0.0;
        int motorCodeRight = 0;
        int timeSpanReal = 0;

        int orderTickDbuLeft = motorLeft.orderTick(); //log
        int orderTickDbuRight = motorRight.orderTick(); //log

        if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG))
        {
            timeSpanReal = chrono.getElapsedTimeInMicroSec();
        }

        //distance parcourue depuis le dernier calcul en tick
        int distanceLeft = nbPulsesLeft_ - lastNbPulsesLeft_;
        int distanceRight = nbPulsesRight_ - lastNbPulsesRight_;
//printf("distanceLeft:%d distanceRight%d nbPulsesLeft_%d lastNbPulsesLeft_%d nbPulsesRight_%d lastNbPulsesRight_%d\n", distanceLeft, distanceRight,nbPulsesLeft_,lastNbPulsesLeft_,nbPulsesRight_,lastNbPulsesRight_);
        int tickLeftPidP = 0;
        int tickRightPidP = 0;
        int distanceTotalRight = 0;
        int distanceTotalLeft = 0;
        double errorLeftP = 0.0;
        double errorRightP = 0.0;

        int tempOrderTick1 = 0;
        int tempOrderTickLeft3 = 0;
        int tempOrderTickRight3 = 0;

        double vx = 0.0, vy = 0.0, vd = 0.0, va = 0.0, diffAngle = 0.0;

        int xPosBase = 0;
        int yPosBase = 0;
        double anglePos = 0;

        if (this->base_->vecteurCorrectionEnabled() == true) //!\TODO vecteurCorrectionEnabled a revoir
        {
            const Position & position = this->base_->robot().position();
            //translation du repere global sur le repere de la base:
            xPosBase = position.x() - this->base_->xOffset();
            yPosBase = position.y() - this->base_->yOffset();
            //anglePos = position.angle() + this->base_->angleOffset();
            anglePos = position.angle();
            
            logger().debug() << "VecCor1 -  xDest:" << this->base_->xDestination() << " yDest:" << this->base_->yDestination() << " xPosBase:" << xPosBase << " yPosBase:" << yPosBase << " anglePos:" << anglePos << utils::end;

            //calcul du nouveau vecteur destination (en tick) vx, vy, vd, va dans le repere de la base:
            vx = (this->base_->xDestination() - position.x()) ; //en mm.
            vy = (this->base_->yDestination() - position.y()) ; //en mm.
            vd = std::pow(std::pow(vx, 2) + std::pow(vy, 2), 0.5); //en mm, tjs positif.

            // Calcul de l'angle de v par rapport à l'origine (tjs positif)
            va = std::acos(vx/vd); //compris entre 0 et PI
            if(vy < 0)
            {
                va = -va; //va compris entre 0 et PI ou entre 0 et -PI
            }

            logger().debug() << "va: " << va << utils::end;

            //inversement de PI dans le cas de la marche arrière :
            if(this->base_->orderWay() == pmx::BBACK)
            {
                if(anglePos > 0)
                {
                    logger().debug() << "cas back anglePos > 0" << utils::end;
                    anglePos = anglePos - M_PI;
                }else if(anglePos <= 0)
                {
                    logger().debug() << "cas back anglePos <= 0" << utils::end;
                    anglePos = anglePos + M_PI;
                }
            }
            diffAngle = anglePos - va;

            logger().debug() << "VecCor2 -  vx:" << vx << " vy:" << vy << " vd:" << vd << " va:" << va << " diffAngle:" << diffAngle << utils::end;
        }

        //trajectoire en position (trapeze de vitesse par pid position).
        if (this->base_->pidPositionEnabled())
        {
            if (motorLeft.orderPositionTick() != 0)
            {
                //printf("pidPositionEnabled\n");

                //distance linéaire parcourue par la roue depuis le début du comptage en tick.
                distanceTotalLeft = std::abs(nbPulsesLeft_);
                //Régulation de la position (via le PID)
                errorLeftP = motorLeft.orderPositionTick() - distanceTotalLeft;
                tickLeftPidP = this->pidLeftP_.ComputePID(errorLeftP);

                //Écrêtage de l'accélération
                if((tickLeftPidP - motorLeft.oldOrderTick()) - this->base_->A_MAX > 0)
                {
                    tickLeftPidP = motorLeft.oldOrderTick() + this->base_->A_MAX ;
                }
                if((tickLeftPidP - motorLeft.oldOrderTick()) + this->base_->A_MAX < 0)
                {
                    tickLeftPidP = motorLeft.oldOrderTick() - this->base_->A_MAX;
                }
                //Écrêtage de la vitesse
                if(tickLeftPidP > this->base_->SPEED_MAX)
                {
                    tickLeftPidP=this->base_->SPEED_MAX;
                }
                if(tickLeftPidP < this->base_->SPEED_MIN)
                {
                    tickLeftPidP = this->base_->SPEED_MIN;
                }
                if(errorLeftP < 0)
                {
                    tickLeftPidP = 0;
                }
                motorLeft.orderTick(tickLeftPidP);
            }

            if (motorRight.orderPositionTick() != 0)
            {
                //distance linéaire parcourue par la roue droite depuis le début du comptage en tick.
                distanceTotalRight = std::abs(nbPulsesRight_);
                //Régulation de la position (via le PID)
                errorRightP = motorRight.orderPositionTick() - distanceTotalRight;
                tickRightPidP = this->pidRightP_.ComputePID(errorRightP);

                //Écrêtage de l'accélération
                if((tickRightPidP - motorRight.oldOrderTick()) - this->base_->A_MAX > 0)
                {
                    tickRightPidP = motorRight.oldOrderTick() + this->base_->A_MAX ;
                }
                if((tickRightPidP - motorRight.oldOrderTick()) + this->base_->A_MAX < 0)
                {
                    tickRightPidP = motorRight.oldOrderTick() - this->base_->A_MAX;
                }
                //Écrêtage de la vitesse
                if(tickRightPidP > this->base_->SPEED_MAX)
                {
                    tickRightPidP = this->base_->SPEED_MAX;
                }
                if(tickRightPidP < this->base_->SPEED_MIN)
                {
                    tickRightPidP = this->base_->SPEED_MIN;
                }
                if(errorRightP < 0)
                {
                    tickRightPidP = 0;
                }
                motorRight.orderTick(tickRightPidP);
            }
            logger().debug() << "PIDPos - TickLEFT: " << tickLeftPidP << " TickRIGHT: " << tickRightPidP << "  errorLeftP: " << errorLeftP << "  errorRightP: " << errorRightP << "  distanceTotalLeft: " << distanceTotalLeft << "  distanceTotalRight: " << distanceTotalRight << utils::end;

            //arrivée à destination dès qu'on a une valeur negative a tester
            if(errorLeftP <= 2 && errorRightP <= 2) //arret
            {
                logger().debug() << "errorLeftP <= 2 & errorRightP <= 2" << utils::end;
                this->base_->arrived(true);
                this->reset();
                distanceTotalLeft = 0;
                distanceTotalRight = 0; 
                distanceLeft=0;
                distanceRight=0;
                this->ActiveSMF_ = false;
            }
            if(errorLeftP <= 2) //arret
            {
                logger().debug() << "errorLeftP <= 2" << utils::end;
                motorLeft.applyMotorCode(0);
                motorLeft.orderTick(0);
                motorLeft.orderPositionTick(0);
                motorLeft.oldOrderTick(0);
                errorLeftP = 0;
                errorLeft = 0;
                this->lastNbPulsesLeft_ = 0;
                this->pidLeft_.reset();
                this->pidLeftP_.reset();
                this->pidLeftBack_.reset();
                this->nbPulsesLeft_ = 0;
                distanceTotalLeft = 0;
                distanceLeft=0;
                
            }
            if(errorRightP <= 2) //arret
            {
                logger().debug() << "errorRightP <= 2" << utils::end;
                motorRight.applyMotorCode(0);
                motorRight.orderTick(0);
                motorRight.orderPositionTick(0);
                motorRight.oldOrderTick(0);
                errorRightP = 0;
                errorRight = 0;
                this->lastNbPulsesRight_ = 0;
                this->pidRight_.reset();
                this->pidRightP_.reset();
                this->pidRightBack_.reset();
                this->nbPulsesRight_ = 0;
                distanceTotalRight = 0;
                distanceRight=0;
            }
//printf("2-distanceLeft:%d distanceRight%d \n", distanceLeft, distanceRight);
        }    

        //CORRECTION PID si pid activé sur les moteurs
        if (this->base_->pidSpeedEnabled())
        {
            //printf("\n pidSpeedEnabled %d %d\n", motorLeft.orderTick(), this->base_->orderWay());

            if (motorLeft.orderTick() > 0)
            {
                //Régulation de la vitesse (via le PID)
                errorLeft = motorLeft.orderTick() - std::abs(distanceLeft);
             
                if (this->base_->orderWay() == pmx::BFORWARD)
                {
                    motorCodeLeft = this->pidLeft_.ComputePID(errorLeft);
                }else
                {
                    motorCodeLeft = this->pidLeftBack_.ComputePID(errorLeft);
                }

                //saturation de la puissance appliquee aux moteurs : motorCode
                if (motorCodeLeft < 0)
                {
                    motorCodeLeft = 0;
                }
                else if(motorCodeLeft > 1023)
                {
                    motorCodeLeft = 1023;
                }

            }

            if (motorRight.orderTick() > 0)
            {
                //Régulation de la vitesse (via le PID)
                errorRight = motorRight.orderTick() - std::abs(distanceRight);

                if (this->base_->orderWay() == pmx::BFORWARD)
                {
                    motorCodeRight = this->pidRight_.ComputePID(errorRight); 
                }else
                {
                    motorCodeRight = this->pidRightBack_.ComputePID(errorRight); 
                }
                //saturation de la puissance appliquee aux moteurs : motorCode
                if (motorCodeRight < 0)
                {
                    motorCodeRight = 0;
                }
                else if(motorCodeRight > 1023)
                {
                    motorCodeRight = 1023;
                }
            }

        }else
        {
            //auto stop si pas de correction PID
printf("!!SpeedManagerFusion : auto stop si pas de correction PID!!");
            this->timerSMF_.stopTimer();
        }

        //CORRECTION DE LA POSITION par rapport au vecteur d'arrivée.
        tempOrderTickLeft3 = motorCodeLeft;//!\todo tempOrderTickLeft3 a renommer
        tempOrderTickRight3 = motorCodeRight;
        int corrcode = 0;
        double pourcentL = 1.0, pourcentR = 1.0;

        if (this->base_->vecteurCorrectionEnabled() == true ) //todo a confirmer : && toctoc % 50 == 20
        {
            //printf("\nvecteurCorrectionEnabled\n");

            double ecart = 0.01;
            double coeff = 5;

            if (vd > 5) //pas de correction en rampe descendante : vd > 100
            {


                
                //!\todo vecteurCorrectionEnabled : prendre en compte l'avance en arrière et le recul en avant. vérifier les signes de diffangles dans tous les sens.




                if ((diffAngle > ecart && this->base_->orderWay() == pmx::BFORWARD) || (diffAngle < -ecart && this->base_->orderWay() == pmx::BBACK)) //variation sur la droite
                {
                    pourcentL = 1 + (std::abs(diffAngle) * coeff ); //todo ajouter vd/vd_initial
                    pourcentR = 1 - (std::abs(diffAngle) * coeff );

                    corrcode = 100;

                }else if ((diffAngle < -ecart && this->base_->orderWay() == pmx::BFORWARD) || (diffAngle > ecart && this->base_->orderWay() == pmx::BBACK)) //variation sur la gauche
                {
                    pourcentL = 1 - (std::abs(diffAngle) * coeff );
                    pourcentR = 1 + (std::abs(diffAngle) * coeff );

                    corrcode = 200;

                }
                tempOrderTickLeft3 = round(pourcentL * tempOrderTickLeft3);
                tempOrderTickRight3 = round(pourcentR * tempOrderTickRight3);

                //saturation en vitesse minimum d'avance
                if (tempOrderTickLeft3 < 100)
                {
                    tempOrderTickLeft3 = 100;
                }
                if (tempOrderTickRight3 < 100)
                {
                    tempOrderTickRight3 = 100;
                }
            }
            
            logger().debug() << "VecCor3: " << corrcode << " motorCodeLeft: " << tempOrderTickLeft3 << " motorCodeRight: " << tempOrderTickRight3 << "  [diffA: " << diffAngle << "]  %L %R : " << pourcentL << " " << pourcentR << utils::end;
            
            //arrivée à destination (dépassement de la droite perpendiculaire à la trajectoire d'arrivée.
            //!\todo vecteurCorrectionEnabled : et la verticale et le retour arrière ??
            /*
            if(vx<0)//si retour dans les negatifs
            {
                vfin=-vx;
            }else
            {
                vfin=vx;
            }
            if (vfin <= 1)
            {
                logger().debug() << "VecCor - Arrived (vx <= 1) " << utils::end;

                this->base_->arrived(true);
                this->base_->motorLeft().applyMotorCode(0);
                this->base_->motorRight().applyMotorCode(0);
                this->base_->stop();
                this->ActiveSMF_ = false;
            }*/
        }
        //Application de la nouvelle vitesse avec correction en position par vecteur d'approche.
        motorLeft.applyMotorCode(tempOrderTickLeft3);
        motorRight.applyMotorCode(tempOrderTickRight3);

        if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG))
        {
            utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug() << ";"
                    << "LEFT" << ";"
                    << orderTickDbuLeft << ";"
                    << distanceLeft << ";"
                    << motorCodeLeft << ";"
                    << errorLeft << ";"
                    << timeSpanReal  << ";"
                    << distanceLeft * pmx::PositionManager::DISTANCE_PER_UP_PULSE * 1000000 / timeSpanReal << ";"
                    << distanceTotalLeft << ";"
                    << errorLeftP << ";"
                    << tickLeftPidP << ";"
                    << tempOrderTick1 << ";"
                    << vd << ";"
                    << vx << ";"
                    << vy << ";"
                    << va << ";"
                    << diffAngle << ";"
                    << corrcode << ";"
                    << tempOrderTickLeft3 << ";"
                    << xPosBase << ";"
                    << yPosBase << ";"
                    << anglePos << ";"
                    << utils::end;

            utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug() << ";"
                    << "RIGHT" << ";"
                    << orderTickDbuRight << ";"
                    << distanceRight << ";"
                    << motorCodeRight << ";"
                    << errorRight << ";"
                    << timeSpanReal  << ";"
                    << distanceRight * pmx::PositionManager::DISTANCE_PER_UP_PULSE * 1000000 / timeSpanReal << ";"
                    << distanceTotalRight << ";"
                    << errorRightP << ";"
                    << tickRightPidP << ";"
                    << tempOrderTick1 << ";" 
                    << vd << ";"
                    << vx << ";"
                    << vy << ";"
                    << va << ";"
                    << diffAngle << ";"
                    << corrcode << ";"
                    << tempOrderTickRight3 << ";"
                    << xPosBase << ";"
                    << yPosBase << ";"
                    << anglePos << ";"
                    << utils::end;
        }
        motorLeft.oldOrderTick(motorLeft.orderTick());
        motorRight.oldOrderTick(motorRight.orderTick());

        lastNbPulsesLeft_ = nbPulsesLeft_;
        lastNbPulsesRight_ = nbPulsesRight_;
        
    }
}
