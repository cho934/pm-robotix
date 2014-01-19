/*!
 * \file
 * \brief Implémentation de la classe HstateTakePawn (Homologation).
 */

#include "HstateTakePawn.hpp"
#include "HstateMoveToPawn.hpp"
#include "Robot.hpp"
#include "HstateMoveToPawn.hpp"
#include "LedIndicator.hpp"
#include "HstateMoveToSquare.hpp"

pmx::IAutomateState*
pmx::automate::HstateTakePawn::execute(Robot& robot)
{
    this->logger().info() << "start" << utils::end;

    robot.firePulseEnabled(false);

    int motorcodemin = 400; //motorcode
    int motorcodemin2 = 250; //motorcode
    int distmin = 350;
    int distMinEnd = 70;
    int distmin2 = 160;

    robot.base().motorLeft().applyWay(pmx::FORWARD);
    robot.base().motorRight().applyWay(pmx::FORWARD);

    robot.pawnLeftIrSensor().active(true); //activation des calculs
    robot.pawnRightIrSensor().active(true); //activation des calculs
    robot.opponentIrSensor().active(true); //activation des calculs

    robot.firePulseEnabled(true); //ACTIVATION
    robot.base().motorLeft().applyMotorCode(motorcodemin);
    robot.base().motorRight().applyMotorCode(motorcodemin);

    int distPawnLeft;
    int distPawnRight;
    int pawntaken = 0;
    while(!pawntaken || robot.position().x() < 150 || robot.position().x() > 2850 || std::abs((int)robot.position().y()) > 1750) //\!todo mettre un timeout + limite basse y() !!
    {
        if (robot.opponentIrSensor().distanceMm() < 450) //test GP2150
        {
            logger().info() << "!!!! collision !!!! " << robot.opponentIrSensor().distanceMm() << "mm" << utils::end;
            robot.base().stop();

            //!\todo aller dans un etat
            sleep(1);
            continue;
        }

        distPawnLeft = robot.pawnLeftIrSensor().distanceMm();
        distPawnRight = robot.pawnRightIrSensor().distanceMm();

        logger().info() << " distPawnLeft : "
                << distPawnLeft
                << " distPawnRight: " << distPawnRight
                << utils::end;

        if((distPawnLeft<distMinEnd && distPawnRight<distMinEnd)
                ||(distPawnLeft<distMinEnd+30 && distPawnRight<distMinEnd)
                ||(distPawnLeft<distMinEnd && distPawnRight<distMinEnd+30) ) //ou 10 7 ou 7 10
        {
            //on est devant
            robot.firePulseEnabled(false);

            robot.base().pawnFound(false); //reset de la base
            //desactivation des ir
            robot.pawnLeftIrSensor().active(false); 
            robot.pawnRightIrSensor().active(false);

            robot.base().motorLeft().applyMotorCode(0);
            robot.base().motorRight().applyMotorCode(0);
            pmx::LedIndicator::instance().blink(10);

            //descendre l'ascenseur
            robot.elevator().goLowPosition();
            sleep(2);

            //avancer de 5cm
            robot.base().moveD(50,0);
            while (robot.base().arrived() == false) //boucle d'attente d'arrivée
            {
                usleep(10000);
            }
            //serrage pince
            robot.firePulseEnabled(false);
            robot.clamp().keepClose();
            while(robot.clamp().stateOpened() == 1)
            {
                usleep(10000);
            }

            robot.elevator().goLittlePosition();
            while(robot.elevator().state() != pmx::ELEVATORLITTLE)
            {
                usleep(5000);
            }
            
            pawntaken = 1; //Un pion pris par le robot


        }else if(distPawnLeft>distmin && distPawnRight>distmin)
        {
            robot.base().motorLeft().applyWay(pmx::FORWARD);
            robot.base().motorRight().applyWay(pmx::FORWARD);
            robot.firePulseEnabled(true); //ACTIVATION
            robot.base().motorLeft().applyMotorCode(motorcodemin);
            robot.base().motorRight().applyMotorCode(motorcodemin);
        }else if((distPawnLeft<distmin && distPawnRight>distmin) || (distPawnLeft>distmin && distPawnRight<distmin)) //si detecttion de un seul capteur < distmin
        {
            if(distPawnLeft>distPawnRight)
            {
                robot.base().motorLeft().applyMotorCode(0);
                //robot.base().motorLeft().applyWay(pmx::BACK);
                //robot.base().motorLeft().applyMotorCode(motorcodemin2-100);
                robot.firePulseEnabled(true); //ACTIVATION
                robot.base().motorRight().applyWay(pmx::FORWARD);
                robot.base().motorRight().applyMotorCode(motorcodemin2);
            }else if(distPawnLeft<distPawnRight)
            {
                robot.base().motorLeft().applyWay(pmx::FORWARD);
                robot.firePulseEnabled(true); //ACTIVATION
                robot.base().motorLeft().applyMotorCode(motorcodemin2);
                robot.base().motorRight().applyMotorCode(0);
                //robot.base().motorRight().applyWay(pmx::BACK);
                //robot.base().motorRight().applyMotorCode(motorcodemin2-100);
            }
        }else if((distPawnLeft<distmin2 ) || (distPawnRight<distmin2 )) //si detecttion de un seul capteur < distmin2
        {
            if(distPawnLeft-distPawnRight<-10)
            {
                robot.base().motorLeft().applyWay(pmx::FORWARD);
                robot.base().motorRight().applyWay(pmx::FORWARD);
                robot.firePulseEnabled(true); //ACTIVATION
                robot.base().motorLeft().applyMotorCode(0);
                robot.base().motorRight().applyMotorCode(motorcodemin2);
            }else if(distPawnLeft-distPawnRight>10)
            {
                robot.base().motorLeft().applyWay(pmx::FORWARD);
                robot.base().motorRight().applyWay(pmx::FORWARD);
                robot.firePulseEnabled(true); //ACTIVATION
                robot.base().motorLeft().applyMotorCode(motorcodemin2);
                robot.base().motorRight().applyMotorCode(0);
            }
            else
            {
                robot.base().motorLeft().applyWay(pmx::FORWARD);
                robot.base().motorRight().applyWay(pmx::FORWARD);
                robot.firePulseEnabled(true); //ACTIVATION
                robot.base().motorLeft().applyMotorCode(motorcodemin2);
                robot.base().motorRight().applyMotorCode(motorcodemin2);
            }
        }
    }
    robot.firePulseEnabled(false);

    logger().info() << "Go to HstateMoveToSquare " << utils::end;
    return new pmx::automate::HstateMoveToSquare();
}
