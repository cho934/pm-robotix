/*!
 * \file
 * \brief Implémentation de la classe OdometryPositionManager.
 */

#include <cmath>
#include <iostream>
#include "OdometryPositionManager.hpp"
#include "LoggerFactory.hpp"
#include "SvgWriter.hpp"
#include "ARobotElement.hpp"
#include "Robot.hpp"

pmx::OdometryPositionManager::OdometryPositionManager(pmx::Robot & robot, EncoderType encoder) : PositionManager(),
        ARobotElement(robot),
        countLeft_(0), countRight_(0), encoderUse_(encoder), freqOdo_(12), vdInit_(0)
{
    if (csv().level() >= utils::Level::DEBUG)
    {
        csv().debug() << ";alpha;delta;x;y;angle;countleft;countright" << utils::end;
    }
}

void
pmx::OdometryPositionManager::onLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer)
{
    //printf("OdometryPositionManager::onLeftPulse\n");
    int temp = 0;
    if(encoderUse_ == pmx::ENCODERFREE)
    {
        temp = freeEncoderValue;
    }else
    {
        temp = motorEncoderValue;
    }

    this->countLeft_ += temp;
    this->count_ += std::abs(temp);
    this->compute(utils::SVG_POS_GREEN, false);
}

void
pmx::OdometryPositionManager::onRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer)
{
    //printf("OdometryPositionManager::onRightPulse\n");
    int temp = 0;
    if(encoderUse_ == pmx::ENCODERFREE)
    {
        temp = freeEncoderValue;
    }else
    {
        temp = motorEncoderValue;
    }

    this->countRight_ += temp;
    this->count_ += std::abs(temp);
    this->compute(utils::SVG_POS_GREEN, false);
}

void
pmx::OdometryPositionManager::compute(utils::SvgPositionColor svgcolor, bool force) 
{
    //printf("OdometryPositionManager::compute\n");
    int deltaCount = this->count_ - this->countOld_;
    if(deltaCount >= this->freqOdo_ | force == true)
    {
        int deltaCountLeft = this->countLeft_ - countLeftOld_;
        int deltaCountRight = this->countRight_ - countRightOld_;
        
        // variation de l'angle ; ATTENTION ici pas de division par 2 car sinon l'angle de rotation sur soi-meme est divisé par 2 !
        double dAlpha = (deltaCountRight - deltaCountLeft) ; // / 2.0

        // variation de l'avancement
        double dDelta = (deltaCountRight + deltaCountLeft) / 2.0;

        double angle = 0, dX = 0, dY = 0, x = 0 , y = 0;

        if(encoderUse_ == pmx::ENCODERFREE)
        {
            // conversion en radian
            angle = this->position().angle() + (dAlpha * this->ANGLE_PER_FREE_PULSE); //this->position().angle() +

            // calcul des décalages selon X et Y
            dX = cos(angle) * dDelta;
            dY = sin(angle) * dDelta;

            // conversion de la position en millimètre
            x = this->position().x() + dX * this->DISTANCE_PER_FREE_PULSE;
            y = this->position().y() + dY * this->DISTANCE_PER_FREE_PULSE;

        }else
        {
            // conversion en radian
            angle = this->position().angle() + (dAlpha * this->ANGLE_PER_MOTOR_PULSE);

            // calcul des décalages selon X et Y
            dX = cos(angle) * dDelta;
            dY = sin(angle) * dDelta;

            // conversion de la position en millimètre
            x = this->position().x() + dX * this->DISTANCE_PER_MOTOR_PULSE;
            y = this->position().y() + dY * this->DISTANCE_PER_MOTOR_PULSE;

        }

        this->position_ = pmx::Position(x, y, angle);

        //Ecriture dans le SVG
        utils::SvgWriter::writePosition(position_.x(), position_.y(), position_.angle(), svgcolor);

        this->addAction();
        
        //log csv
        if (csv().isActive(utils::Level::DEBUG))
        {
            csv().debug()
                    << ";" << dAlpha
                    << ";" << dDelta
                    << ";" << position_.x()
                    << ";" << position_.y()
                    << ";" << position_.angle()
                    << ";" << deltaCountLeft
                    << ";" << deltaCountRight
                    << utils::end;
        }
        countRightOld_ += deltaCountRight;
        countLeftOld_ += deltaCountLeft;
        countOld_ += deltaCount;
    }
}



void
pmx::OdometryPositionManager::addAction()
{
    this->robot().addAction(new pmx::OdometryAction(*this, 0));
}

void
pmx::OdometryPositionManager::reset()
{
    vdInit_ = 0;
    freqOdo_ = pmx::Base::ODO_FREQ_MAX;
}

pmx::OdometryAction::OdometryAction(pmx::OdometryPositionManager & odometryPositionManager, int action)
: odometryPositionManager_(odometryPositionManager), action_(action), lastTime_(0)
{
    chrono_.start();
}

bool pmx::OdometryAction::execute(IRobotOut *)
{
    //logger().debug() << "execute" << utils::end;

    Robot & robot = this->odometryPositionManager_.robot();

    if (robot.base().vecteurCorrectionEnabled() == true & robot.base().arrived() == false)
    {
        if(robot.base().orderWay() == pmx::BTURNLEFT | robot.base().orderWay() == pmx::BTURNRIGHT)
        {
            //logger().debug() << "BTURNLEFT BTURNRIGHT" << utils::end;

            double diff = robot.base().angleDestination() - this->odometryPositionManager_.position().angle();
            //on garde diffangle dans les valeurs entre -pi et pi
            if (diff >= M_PI)
            {
                diff = diff - (M_PI * 2.0);
            }else if (diff <= -M_PI)
            {
                diff = diff + (M_PI * 2.0);
            }

            // plus de precision d'odomérie lorsque diff <= 0.26
            if ((robot.base().orderWay() == pmx::BTURNLEFT && diff <= 0.26)
                    || (robot.base().orderWay() == pmx::BTURNRIGHT && diff >= -0.26))
            {
                this->odometryPositionManager_.changeFrequency(pmx::Base::ODO_FREQ_MIN);
            }

            //Ecriture dans le SVG
            utils::SvgWriter::writePosition(this->odometryPositionManager_.position().x(),
                this->odometryPositionManager_.position().y(),
                this->odometryPositionManager_.position().angle(), utils::SVG_POS_ANGLE);


            logger().debug() << "BTURN : angleDest="
                        << robot.base().angleDestination() << " anglePos=" << this->odometryPositionManager_.position().angle()
                        << utils::end;

            //ARRET vecteurCorrectionEnabled
            if ((robot.base().orderWay() == pmx::BTURNLEFT && diff <= 0.015)
                    || (robot.base().orderWay() == pmx::BTURNRIGHT && diff >= -0.015))
            {
                logger().debug() << "vecteurCorrectionEnabled - Arrived (angleDest - anglePos <= 0) " 
                        << robot.base().angleDestination() << " " << this->odometryPositionManager_.position().angle()
                        << utils::end;
                robot.base().arrivedStopReset();
                return false;//l'action se supprime.
            }

        }
        if(robot.base().orderWay() == pmx::BFORWARD | robot.base().orderWay() == pmx::BBACK)
        {

            //Changement de repere (Generale => Base)
            //x2=x1*cos(a) + y1*sin(a)
            //y2=-x1*sin(a) + y1*cos(a)

            //pour la position actuelle
            double xBase = this->odometryPositionManager_.position().x() * cos(robot.base().angleOffset()) + this->odometryPositionManager_.position().y() * sin(robot.base().angleOffset());
            double yBase = -this->odometryPositionManager_.position().x() * sin(robot.base().angleOffset()) + this->odometryPositionManager_.position().y() * cos(robot.base().angleOffset());
            double angleBase = this->odometryPositionManager_.position().angle() + robot.base().angleOffset();
            
            //pour les coord de destination
            double xDestBase = robot.base().xDestination() * cos(robot.base().angleOffset()) + robot.base().yDestination() * sin(robot.base().angleOffset());
            double yDestBase = -robot.base().xDestination() * sin(robot.base().angleOffset()) + robot.base().yDestination() * cos(robot.base().angleOffset());

            double *v = new double[4];
            double vxBase = 0.0, vyBase = 0.0, vdBase = 0.0, vaBase = 0.0, vaBaseBack = 0.0;
            double diffvy = 0.0;
            robot.base().computeDestinationVector(v, xDestBase, yDestBase, xBase, yBase);
            vxBase = v[0];
            vyBase = v[1];
            vdBase = v[2];
            vaBase = v[3];
            delete[] v;

            diffvy = vyBase; //todo a confirmer
            
            if(this->odometryPositionManager_.vdInit() == 0.0 ) //init de vdOld
            {
                this->odometryPositionManager_.vdInit(vdBase);

            }

            logger().debug() << "vecteurCorrectionEnabled Base - vx=" << vxBase
                        << " vy=" << vyBase
                        << " vd=" << vdBase
                        << " va=" << vaBase
                        << " diffvy=" << diffvy
                        << utils::end;

            

            //ARRET vecteurCorrectionEnabled
            if ((vxBase <= 2.0 && robot.base().orderWay() == pmx::BFORWARD)
                | (vxBase >= -2.0 && robot.base().orderWay() == pmx::BBACK))
            {
                logger().debug() << "vecteurCorrectionEnabled - Arrived (vxBase <= 2.0) " << utils::end;
                robot.base().arrivedStopReset();
                return false;//l'action se supprime.
            }else
            {
                double motorCode = 20;
                double forward;
                
                if(robot.base().orderWay() == pmx::BFORWARD)
                    forward = 1.0;
                else 
                    forward = -1.0;
                

                if (vdBase <= 20.0) //plus de precision d'odomérie lorsque vd > 2cm
                {
                    this->odometryPositionManager_.changeFrequency(pmx::Base::ODO_FREQ_MIN);
                    logger().debug() << "                       ODO_FREQ_MIN"
                                << utils::end;
                }

                //tous les n mm
                if((this->odometryPositionManager_.vdInit() - vdBase) >= 10.0) //interval de correction
                {

                    //Ecriture dans le SVG
                    utils::SvgWriter::writePosition(this->odometryPositionManager_.position().x(),
                        this->odometryPositionManager_.position().y(),
                        this->odometryPositionManager_.position().angle(), utils::SVG_POS_BLUE);


                    //Correction vectorielle
                    double ecart = 0.06;
                    double coeff = 1.1;
                    double pourcentL = 1.0, pourcentR = 1.0;
                    //double ecartVectMode = 0.25;
                    int modif = 0;

                    

                    double diffAngle = robot.base().computeAngleToGo2(vaBase, angleBase);
                    logger().debug() << "                       pmx:     : " << "  angleBase=" << angleBase << "  vaBase= " << vaBase << "  diffAngle=" << diffAngle << utils::end;




                    if (robot.base().orderWay() == pmx::BBACK)
                    {
                        if(diffAngle >= 0.0)
                        {
                            diffAngle = diffAngle - M_PI;
                        }else if(diffAngle < 0.0)
                        {  
                            diffAngle = diffAngle + M_PI;
                        }
                        logger().debug() << "                       pmx::BBACK : " << "  angleBase=" << angleBase << "  vaBase= " << vaBase << "  diffAngle=" << diffAngle << utils::end;

                        if(vaBase >= 0.0)
                        {
                            vaBaseBack = vaBase - M_PI;
                        }else if(diffAngle < 0.0)
                        {  
                            vaBaseBack = vaBase + M_PI;
                        }

                    }

                    if(diffvy > 10.0 || diffvy < -10.0) // ecart de 1 cm alors on passe en mode correction sans PID position
                    {
                        logger().debug() << "          !!             diffvy  = "
                                << diffvy
                                << "  =>  pidSpeedDesactivate()" 
                                << utils::end;
                        //robot.base().pidSpeedDesactivate();
                    }

                    if ((diffAngle > ecart && robot.base().orderWay() == pmx::BFORWARD) //
                            || (diffAngle < -ecart && robot.base().orderWay() == pmx::BBACK)) //variation sur la droite //|| (diffAngle < M_PI - ecart && robot.base().orderWay() == pmx::BBACK)
                    {
                        pourcentL = 1.0 - (std::abs(diffAngle) * coeff); 
                        pourcentR = 1.0 + (std::abs(diffAngle) * coeff);

                        logger().debug() << "                       correction DROITE++ : " << "  angleBase=" << angleBase << "  vaBase= " << vaBase << "  diffAngle=" << diffAngle << utils::end;
                        modif = 1;

                    }else if ((diffAngle < -ecart && robot.base().orderWay() == pmx::BFORWARD) //
                            || (diffAngle > ecart && robot.base().orderWay() == pmx::BBACK)) //variation sur la gauche //|| (diffAngle > M_PI + ecart && robot.base().orderWay() == pmx::BBACK)
                    {
                        pourcentL = 1.0 + (std::abs(diffAngle) * coeff);
                        pourcentR = 1.0 - (std::abs(diffAngle) * coeff);

                        logger().debug() << "                       correction GAUCHE++ : " << "  angleBase=" << angleBase << " vaBase= " << vaBase << "  diffAngle=" << diffAngle << utils::end;
                        modif = 1;
                    }

                    if (0)//modif == 1 //!\TODO corriger le pb de correction de trajectoire
                    {
                        
                        int motorCodeLeft = pourcentL * motorCode * forward;
                        int motorCodeRight = pourcentR * motorCode * forward;

                        //saturation en vitesse minimum

                        if (std::abs(motorCodeLeft) < pmx::Base::SPEED_MIN)
                        {
                            if(motorCodeLeft >= 0)
                            {
                                motorCodeLeft = pmx::Base::SPEED_MIN;
                            }else
                            {
                                motorCodeLeft = -(pmx::Base::SPEED_MIN);
                            }
                        }
                        if (std::abs(motorCodeRight) < pmx::Base::SPEED_MIN)
                        {
                            if(motorCodeRight >= 0)
                            {
                                motorCodeRight = pmx::Base::SPEED_MIN;
                            }else
                            {
                                motorCodeRight = -(pmx::Base::SPEED_MIN);
                            }
                        }

                        if (motorCodeLeft < -128)
                        {
                            motorCodeLeft = -128;
                        }else if (motorCodeLeft > 127)
                        {
                            motorCodeLeft = 127;
                        }
                        if (motorCodeRight < -128)
                        {
                            motorCodeRight = -128;
                        }else if (motorCodeRight > 127)
                        {
                            motorCodeRight = 127;
                        }

                        logger().debug() << "                       motorCodeLeft motorCodeRight = "
                                << motorCodeLeft << " " << motorCodeRight
                                << "  L R = " << pourcentL << " " << pourcentR
                                << utils::end;
                        robot.base().motorLeft().applyMotorCode(motorCodeLeft);
                        robot.base().motorRight().applyMotorCode(motorCodeRight);

                    }
                    this->odometryPositionManager_.vdInit(vdBase);
                }
            }
        }
    }

    return false; //l'action se supprime.
}

