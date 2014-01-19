/*!
 * \file
 * \brief Implementation de la classe SpeedManagerFusion.
 */


#include <iostream>
#include "Macro.hpp"
#include "Robot.hpp"
#include "Base.hpp"
#include "SpeedManagerFusion.hpp"
#include "SvgWriter.hpp"
#include "Md25.hpp"
#include "LedIndicator.hpp"
#include <stdlib.h>

pmx::SpeedManagerFusion::SpeedManagerFusion(pmx::Base * base,
        const utils::PID & pidL,
        const utils::PID & pidR,
        const utils::PID & pidRed) :
base_(base),
nbTickRed_(0), lastNbTickRed_(0), pidRed_(pidRed),
nbPulsesLeft_(0), nbPulsesRight_(0), lastNbPulsesLeft_(0), lastNbPulsesRight_(0),
timerSMF_(PERIOD_PID, 0, this), pidLeft_(pidL), pidRight_(pidR), ActiveSMF_(false),
rampPhase_(0), distTickRampLeftOld_(3), distTickRampRightOld_(3), yrampLeft_(0), yrampRight_(0),
motorCodePidPosLeftOld_(0), motorCodePidPosRightOld_(0), timeElapsed_(0), testPidPos_(false),
distanceTotalLeft_(0), distanceTotalRight_(0)
 {
    //initialisation du fichier de log
    if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG)) {
        utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug()
                << ";motor;orderTick;RealTick;PIDMotorCode;PIDerror;TimeSpan;speedReal;PIDPosDistanceTotale;PIDPosError;PIDPosOrderTick;x;y;angle;" << utils::end;
    }
}

void pmx::SpeedManagerFusion::onTimerEnd(utils::Chronometer) {
}

void pmx::SpeedManagerFusion::onTimer(utils::Chronometer chrono) {
    //printf("SPM\n");
    if (this->SMFMotorRedYellowEnabled_) //si activation moteur mécanisme RED/YELLOW
    {
        Motor & motorRed = this->base_->flashBallWheel();
        int errorRed = 0;
        int motorCodeRed = 0;
        int distanceRed = nbTickRed_ - lastNbTickRed_; //distance parcourue depuis le dernier calcul en tick

        //Régulation de la vitesse (via le PID)
        errorRed = motorRed.orderTick() - abs(distanceRed);
        motorCodeRed = this->pidRed_.ComputePID(errorRed);

        //saturation de la puissance appliquee aux moteurs : motorCode
        if (motorCodeRed < 0) {
            motorCodeRed = 0;
        }else if (motorCodeRed > 1023) {
            motorCodeRed = 1023;
        }
        motorRed.applyMotorCode(motorCodeRed);
        motorRed.oldOrderTick(motorRed.orderTick());
        logger().info() << "onTimer SMFMotorRedEnabled: "
                << " chrono(us)=" << chrono.getElapsedTimeInMicroSec()
                << " orderTick=" << motorRed.orderTick()
                << " errorRed=" << errorRed
                << " motorCodeRed=" << motorCodeRed
                << " nbTickRed_=" << nbTickRed_
                << " lastNbTickRed_=" << lastNbTickRed_

                << utils::end;

        lastNbTickRed_ = nbTickRed_;

    }

    if (this->ActiveSMF_) //si activation moteur de propulsion //& vecteurMode_==0 //& this->base_->modeVecteurCorrectionEnabled()==false
    {
        timeElapsed_++;

        //Mise à jour de la position
        this->base_->positionManager().compute(utils::SVG_POS_YELLOW, true);

        MotorWithMd25 & motorLeft = this->base_->motorLeft();
        MotorWithMd25 & motorRight = this->base_->motorRight();

        int errorLeft = 0;
        int motorCodeLeft = 0;

        int errorRight = 0;
        int motorCodeRight = 0;
        int timeSpanReal = 0;

        int orderTickLeftDbu = motorLeft.orderTick(); //log
        int orderTickRightDbu = motorRight.orderTick(); //log

        if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG)) {
            timeSpanReal = chrono.getElapsedTimeInMicroSec();
        }

        int distanceLeft = nbPulsesLeft_ - lastNbPulsesLeft_; //distance parcourue depuis le dernier calcul en tick
        int distanceRight = nbPulsesRight_ - lastNbPulsesRight_; //distance parcourue depuis le dernier calcul en tick
        int tickLeftPidP = 0;
        int tickRightPidP = 0;

        //int distTickRampLeft = 0;
        //int distTickRampRight = 0;

        //int distanceTotalLeft = 0; //distance linéaire parcourue par la roue depuis le début de l'execution du OnTimer en tick.
        //int distanceTotalRight = 0; //distance linéaire parcourue par la roue droite depuis le début de l'execution du OnTimer en tick.
        double errorLeftP = 0.0;
        double errorRightP = 0.0;

        int motorCodePidPosLeft = 0;
        int motorCodePidPosRight = 0;

        double xPosBase = 0.0;
        double yPosBase = 0.0;
        double anglePosBase = 0.0;

        //trajectoire en position (trapeze de vitesse par pid position).
        if (this->base_->pidPositionEnabled() == true) {
            if (motorLeft.orderPositionTick() != 0) {
                //printf("pidPositionEnabled\n");
                //logger().debug() << "pidPositionEnabled" << utils::end;

                //distance linéaire totale parcourue par la roue depuis le début
                distanceTotalLeft_ += abs(distanceLeft);
                //Régulation de la position (via le PID)
                errorLeftP = motorLeft.orderPositionTick() - distanceTotalLeft_;
                tickLeftPidP = this->pidLeftP_.ComputePID(errorLeftP);

                //Écrêtage de l'accélération
                //!\TODO ecretage de la deceleration en marche avant !! est-ce utile ? a corriger
                if ((tickLeftPidP - motorLeft.oldOrderTick()) - this->base_->A_MAX > 0) //&& this->base_->orderWay() == pmx::BFORWARD
                {
                    tickLeftPidP = motorLeft.oldOrderTick() + this->base_->A_MAX;
                }
                if ((tickLeftPidP - motorLeft.oldOrderTick()) + this->base_->A_MAX < 0) //&& this->base_->orderWay() == pmx::BBACK
                {
                    tickLeftPidP = motorLeft.oldOrderTick() - this->base_->A_MAX;
                }

                //Saturation minimum à vitesse min sauf en cas de test de PID position
                if (tickLeftPidP >-this->base_->SPEED_MIN && errorLeftP < 0 && testPidPos_ == false) {
                    //logger().debug() << "tickLeftPidP >-this->base_->SPEED_MIN  && errorLeftP < 0 && testPidPos_ == false" << utils::end;
                    tickLeftPidP = -this->base_->SPEED_MIN;
                }
                if (tickLeftPidP < this->base_->SPEED_MIN && errorLeftP > 0 && testPidPos_ == false) {
                    //logger().debug() << "tickLeftPidP < this->base_->SPEED_MIN && errorLeftP > 0 && testPidPos_ == false" << utils::end;
                    tickLeftPidP = this->base_->SPEED_MIN;
                }

                //Écrêtage de la vitesse
                if (tickLeftPidP > this->base_->SPEED_MAX) {
                    tickLeftPidP = this->base_->SPEED_MAX;
                }
                if (tickLeftPidP < -this->base_->SPEED_MAX) {
                    tickLeftPidP = -this->base_->SPEED_MAX;
                }

                motorLeft.orderTick(tickLeftPidP);
            }

            if (motorRight.orderPositionTick() != 0) {
                //distance linéaire parcourue par la roue droite depuis le début du comptage en tick.
                distanceTotalRight_ += abs(distanceRight);
                //Régulation de la position (via le PID)
                errorRightP = motorRight.orderPositionTick() - distanceTotalRight_;
                tickRightPidP = this->pidRightP_.ComputePID(errorRightP);

                //Écrêtage de l'accélération
                if ((tickRightPidP - motorRight.oldOrderTick()) - this->base_->A_MAX > 0) //&& this->base_->orderWay() == pmx::BFORWARD
                {
                    tickRightPidP = motorRight.oldOrderTick() + this->base_->A_MAX;
                }
                if ((tickRightPidP - motorRight.oldOrderTick()) + this->base_->A_MAX < 0) //todo && this->base_->orderWay() == pmx::BBACK
                {
                    tickRightPidP = motorRight.oldOrderTick() - this->base_->A_MAX;
                }

                //Saturation minimum à vitesse min sauf en cas de test de PID position
                if (tickRightPidP >-this->base_->SPEED_MIN && errorRightP < 0 && testPidPos_ == false) {
                    //logger().debug() << "tickRightPidP >-this->base_->SPEED_MIN  && errorRightP < 0 && testPidPos_ == false" << utils::end;
                    tickRightPidP = -this->base_->SPEED_MIN;
                }
                if (tickRightPidP < this->base_->SPEED_MIN && errorRightP > 0 && testPidPos_ == false) {
                    //logger().debug() << "tickRightPidP < this->base_->SPEED_MIN && errorRightP > 0 && testPidPos_ == false" << utils::end;
                    tickRightPidP = this->base_->SPEED_MIN;
                }


                //Écrêtage de la vitesse
                if (tickRightPidP > this->base_->SPEED_MAX) {
                    tickRightPidP = this->base_->SPEED_MAX;
                }
                if (tickRightPidP < -this->base_->SPEED_MAX) {
                    tickRightPidP = -this->base_->SPEED_MAX;
                }

                motorRight.orderTick(tickRightPidP);

            }
            logger().info() << "PIDPos -"
                    << " TimeElapsed: " << timeElapsed_ * PERIOD_PID
                    << " TickLEFT: " << tickLeftPidP
                    << " TickRIGHT: " << tickRightPidP
                    << "  errorLeftP: " << errorLeftP
                    << "  errorRightP: " << errorRightP
                    << "  distTotalLeft: " << distanceTotalLeft_
                    << "  distTotalRight: " << distanceTotalRight_
                    << utils::end;


            //arrivée à destination dès qu'on a une valeur negative a tester
            if (errorLeftP <= 1.0 && errorRightP <= 1.0
                    && this->base_->vecteurCorrectionEnabled() == false
                    && testPidPos_ == false
                    ) //arret
            {
                logger().info() << "ARRET errorLeftP <= 1.0 & errorRightP <= 1.0" << utils::end;
                this->base_->arrived(true);
                this->base_->modeVecteurCorrectionEnabled(false);
                this->reset();
                distanceTotalLeft_ = 0;
                distanceTotalRight_ = 0;
                distanceLeft = 0;
                distanceRight = 0;
                this->ActiveSMF_ = false;
            }

        }
        /*
                if (this->base_->rampPositionEnabled() == true)
                {
                    //printf("rampPositionEnabled\n");
                    logger().debug() << "rampPositionEnabled" << utils::end;

                    //double ecartramp = 0.3;
            
                    if (motorLeft.orderPositionTick() != 0)
                    {
                        //distance linéaire parcourue par la roue depuis le début du comptage en tick.
                        distanceTotalLeft = std::abs(nbPulsesLeft_);
                        //Régulation de la position (via le PID)
                        errorLeftP = motorLeft.orderPositionTick() - distanceTotalLeft;



                        //!\todo A calculer une seule fois

                        //calcul de b, xdec
                        int b = this->base_->SPEED_MIN + (this->base_->RAMP_DEC * motorLeft.orderPositionTick());//ajouter -2 pour saturer plus rapidement à vitesse min
                        int xdec = (b - this->base_->SPEED_MIN) / (this->base_->RAMP_ACC + this->base_->RAMP_DEC);
                
                        //logger().debug() << "LEFT : xdec=" << xdec << " b=" << b << utils::end;


                
             
                        //2 phases principales:
                        if (distanceTotalLeft < xdec)
                        {
                            //phase d'accélération
                            //logger().debug() << "acc" << utils::end;
                            //distTickRampLeft = distanceTotalLeft * this->base_->RAMP_ACC + this->base_->SPEED_MIN; //en distance
                            distTickRampLeft = distTickRampLeftOld_ + this->base_->A_MAX; // en temps
                            distTickRampLeftOld_ = distTickRampLeft;
                            //saturation en vitesse
                            if (distTickRampLeft >= this->base_->SPEED_MAX)
                            {
                                //logger().debug() << "satacc" << utils::end;
                                distTickRampLeft = this->base_->SPEED_MAX;
                            }
                            yrampLeft_ = distTickRampLeft;

                        }else if (distanceTotalLeft >= xdec)
                        {
                            //phase deceleration
                            //logger().debug() << "dec" << utils::end;
                            distTickRampLeft = b - (distanceTotalLeft * this->base_->RAMP_DEC);
                            //saturation en vitesse accmax
                            if(distTickRampLeft > yrampLeft_)
                            {
                                distTickRampLeft = yrampLeft_;
                            }
                            //saturation en vitesse max
                            if (distTickRampLeft >= this->base_->SPEED_MAX)
                            {
                                //logger().debug() << "satdec" << utils::end;
                                distTickRampLeft = this->base_->SPEED_MAX;

                            }else if (distTickRampLeft <= this->base_->SPEED_MIN)
                            {
                                distTickRampLeft = this->base_->SPEED_MIN;
                            }
                        }
                        motorLeft.orderTick(distTickRampLeft);

                    }

                    if (motorRight.orderPositionTick() != 0)
                    {
                        //distance linéaire parcourue par la roue depuis le début du comptage en tick.
                        distanceTotalRight = std::abs(nbPulsesRight_);
                        //Régulation de la position (via le PID)
                        errorRightP = motorRight.orderPositionTick() - distanceTotalRight;


                
                        //!\todo A calculer une seule fois
                        //calcul de b, xdec
                        int b = this->base_->SPEED_MIN + (this->base_->RAMP_DEC * motorRight.orderPositionTick());
                        int xdec = (b - this->base_->SPEED_MIN) / (this->base_->RAMP_ACC + this->base_->RAMP_DEC);
                        //logger().debug() << "RIGHT : xdec=" << xdec << " b=" << b << utils::end;


                        //2 phases principales:
                        if (distanceTotalRight < xdec)
                        {
                            //phase d'accélération
                            //logger().debug() << "acc" << utils::end;
                            //distTickRampRight = distanceTotalRight * this->base_->RAMP_ACC + this->base_->SPEED_MIN;
                            distTickRampRight = distTickRampRightOld_ + this->base_->A_MAX;
                            distTickRampRightOld_ = distTickRampRight;
                            //saturation en vitesse
                            if (distTickRampRight >= this->base_->SPEED_MAX)
                            {
                                //logger().debug() << "satacc" << utils::end;
                                distTickRampRight = this->base_->SPEED_MAX;
                            }
                            yrampRight_ = distTickRampRight;
                        }else if (distanceTotalRight >= xdec)
                        {
                            //phase deceleration
                            //logger().debug() << "dec" << utils::end;
                            distTickRampRight = b - (distanceTotalRight * this->base_->RAMP_DEC);
                            //saturation en vitesse accmax
                            if(distTickRampRight > yrampRight_)
                            {
                                distTickRampRight = yrampRight_;
                            }
                            //saturation en vitesse max
                            if (distTickRampRight >= this->base_->SPEED_MAX)
                            {
                                //logger().debug() << "satdec" << utils::end;
                                distTickRampRight = this->base_->SPEED_MAX;

                            }else if (distTickRampRight <= this->base_->SPEED_MIN)
                            {
                                distTickRampRight = this->base_->SPEED_MIN;
                            }
                        }
                        motorRight.orderTick(distTickRampRight);
                    }
                    logger().info() << "Ramp - motorLeft.orderTick: " << distTickRampLeft
                            << "  errorLeftP: " << errorLeftP
                            << "  distanceTotalLeft: " << distanceTotalLeft
                            << "  motorRight.orderTick: " << distTickRampRight
                            << "  errorRightP: " << errorRightP
                            << "  distanceTotalRight: " << distanceTotalRight
                            << utils::end;

                    //arrivée à destination dès qu'on a une valeur negative a tester
                    if (errorLeftP <= 3.0 & errorRightP <= 3.0) //arret
                    {
                        logger().info() << "ARRET errorLeftP <= 3.0 & errorRightP <= 3.0" << utils::end;
                
                        this->base_->arrivedStopReset();
                    }
                }
         */
        //CORRECTION PID si pid activé sur les moteurs
        //!\deprecated : non utilisé avec MD25
        if (this->base_->pidSpeedEnabled() == true) {
            printf("pidSpeedEnabled\n");
            logger().debug() << "pidSpeedEnabled" << utils::end;
            if (motorLeft.orderTick() > 0) {
                //Régulation de la vitesse (via le PID)
                errorLeft = motorLeft.orderTick() - abs(distanceLeft);

                if (this->base_->orderWay() == pmx::BFORWARD) {
                    motorCodeLeft = this->pidLeft_.ComputePID(errorLeft);
                }else {
                    motorCodeLeft = this->pidLeftBack_.ComputePID(errorLeft);
                }

                //saturation de la puissance appliquee aux moteurs : motorCode
                if (motorCodeLeft < 0) {
                    motorCodeLeft = 0;
                }else if (motorCodeLeft > 127) {
                    motorCodeLeft = 127;
                }
            }

            if (motorRight.orderTick() > 0) {
                //Régulation de la vitesse (via le PID)
                errorRight = motorRight.orderTick() - abs(distanceRight);

                if (this->base_->orderWay() == pmx::BFORWARD) {
                    motorCodeRight = this->pidRight_.ComputePID(errorRight);
                }else {
                    motorCodeRight = this->pidRightBack_.ComputePID(errorRight);
                }
                //saturation de la puissance appliquee aux moteurs : motorCode
                if (motorCodeRight < 0) {
                    motorCodeRight = 0;
                }else if (motorCodeRight > 127) {
                    motorCodeRight = 127;
                }
            }

        }else //si pas de pid vitesse pidSpeedEnabled, conversion orderTick <=> motorCode:
        {
            if (this->base_->orderWay() == pmx::BFORWARD || this->base_->orderWay() == pmx::BTURNRIGHT) {
                //Conversion : pour un timeSpan=100ms motorcode=orderTick
                //Conversion : pour un timeSpan=50ms motorcode=orderTick*2
                motorCodeLeft = motorLeft.orderTick(); //*(100.0/PERIOD_PID);
            }else if (this->base_->orderWay() == pmx::BBACK || this->base_->orderWay() == pmx::BTURNLEFT) {
                motorCodeLeft = -motorLeft.orderTick(); //*(100.0/PERIOD_PID);
            }
            //saturation de la puissance appliquee aux moteurs : motorCode
            if (motorCodeLeft < -128) {
                motorCodeLeft = -128;
            }else if (motorCodeLeft > 127) {
                motorCodeLeft = 127;
            }

            //pour un timeSpan=100ms motorcode=orderTick
            if (this->base_->orderWay() == pmx::BFORWARD || this->base_->orderWay() == pmx::BTURNLEFT) {
                motorCodeRight = motorRight.orderTick(); //*(100.0/this->PERIOD_PID);
            }else if (this->base_->orderWay() == pmx::BBACK || this->base_->orderWay() == pmx::BTURNRIGHT) {
                motorCodeRight = -motorRight.orderTick(); //*(100.0/PERIOD_PID);
            }
            //saturation de la puissance appliquee aux moteurs : motorCode
            if (motorCodeRight < -128) {
                motorCodeRight = -128;
            }else if (motorCodeRight > 127) {
                motorCodeRight = 127;
            }
        }

        logger().debug() << "motorCodeLeft=" << motorCodeLeft
                << " motorCodeRight=" << motorCodeRight
                << utils::end;

        motorLeft.applyMotorCode(motorCodeLeft);
        motorRight.applyMotorCode(motorCodeRight);


        //logger().debug() << "test11" << utils::end;

        if (utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").isActive(utils::Level::DEBUG)) {
            utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug() << ";"
                    << "LEFT" << ";"
                    << orderTickLeftDbu << ";"
                    << distanceLeft << ";"
                    << motorCodeLeft << ";"
                    << errorLeft << ";"
                    << timeSpanReal << ";"
                    << distanceLeft * pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE * 1000000 / timeSpanReal << ";"
                    << distanceTotalLeft_ << ";"
                    << errorLeftP << ";"
                    << tickLeftPidP << ";"
                    << motorCodePidPosLeft << ";"
                    << xPosBase << ";"
                    << yPosBase << ";"
                    << anglePosBase << ";"
                    << utils::end;

            utils::LoggerFactory::logger("pmx::SpeedManagerFusion::logpid").debug() << ";"
                    << "RIGHT" << ";"
                    << orderTickRightDbu << ";"
                    << distanceRight << ";"
                    << motorCodeRight << ";"
                    << errorRight << ";"
                    << timeSpanReal << ";"
                    << distanceRight * pmx::PositionManager::DISTANCE_PER_MOTOR_PULSE * 1000000 / timeSpanReal << ";"
                    << distanceTotalRight_ << ";"
                    << errorRightP << ";"
                    << tickRightPidP << ";"
                    << motorCodePidPosRight << ";"
                    << xPosBase << ";"
                    << yPosBase << ";"
                    << anglePosBase << ";"
                    << utils::end;
        }
        motorLeft.oldOrderTick(motorLeft.orderTick());
        motorRight.oldOrderTick(motorRight.orderTick());

        lastNbPulsesLeft_ = nbPulsesLeft_;
        lastNbPulsesRight_ = nbPulsesRight_;

        //logger().debug() << "test12" << utils::end;
    }

    //logger().debug() << "test13" << utils::end;

    //TEST ERREUR I2C => ARRET du ROBOT
    int err = utils::Md25::instance().getNbErrors();
    if (err > 10) {
        logger().error() << "ERROR NO COMMUNICATION WITH MD25 : " << err << utils::end;
        this->base_->robot().firePulseEnabled(false);

        this->base_->robot().ledBar().reset();
        this->base_->robot().ledBar().startK2Mil(100, 25000, false);
        pmx::LedIndicator::instance().blink(30, 25000);
        this->base_->robot().ledBar().stopAndWait(true);
        this->base_->robot().ledBar().reset();
        this->base_->pidSpeedDesactivate();

        this->base_->robot().stop();
    }

    //logger().debug() << "test14" << utils::end;
}
