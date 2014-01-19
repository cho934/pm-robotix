/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 * \todo problème lorque l'on fait plusieurs cycles, la vitesse du robot
 * augmente !! En fait le timer SpeedManagerFusion ne s'execute plus tous les
 * 150ms mais plus rapidement. => momentanément corrigé (313) : a surveiller.
 */

#include <cmath>
#include "StateWaitForStart.hpp"
#include "StateWaitForReboot.hpp"
#include "StateInitialize.hpp"
#include "StateAdjustRobotPosition.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::StateAdjustRobotPosition::execute(Robot& robot, void * )
{
    this->logger().info() << "start" << utils::end;
    //pmx::Data* sharedData = (pmx::Data*) data;

    logger().info() << "Adjust position in the correct board..." << utils::end;

    IAutomateState* result;
    
    
/*
    int motorcodeMin = 200; //motorcode
    double distanceCentreBack = 130.0; // en mm

    //tourner suivant la couleur
    robot.base().rampPositionEnabled(false);
    robot.base().pidPositionEnabled(true);
    robot.base().pidSpeedEnabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    if (robot.myColor() == pmx::PMXPURPLE)
    {
        robot.firePulseEnabled(true); //prise en compte des impulsions des codeurs.
        //tourner à gauche de 90°
        logger().info() << "turn left" << utils::end;
        robot.base().turn(pmx::BTURNLEFT, M_PI_2);
        while (robot.base().arrived() == false)
        {
            usleep(1000);
        }
        robot.firePulseEnabled(false);
    }else if (robot.myColor() == pmx::PMXRED)
    {
        //tourner à droite de 90°
        logger().info() << "turn right" << utils::end;
        robot.base().turn(pmx::BTURNRIGHT, M_PI_2);
        while (robot.base().arrived() == false)
        {
            usleep(1000);
        }
        robot.firePulseEnabled(false);
    }

    //reculer
    logger().info() << "back" << utils::end;
    //robot.base().motorLeft().applyWay(pmx::BACK);
    //robot.base().motorRight().applyWay(pmx::BACK);

    robot.leftBackContact().wait();
    robot.rightBackContact().wait();
    //while (!robot.base().motorLeft().wayApplied() || !robot.base().motorRight().wayApplied())
    //{
    //    usleep(50000);
    //}
    //usleep(200000);
    robot.firePulseEnabled(true); //prise en compte des impulsions des codeurs.
    robot.base().motorLeft().applyMotorCode(motorcodeMin);
    robot.base().motorRight().applyMotorCode(motorcodeMin);

    //attente d'un des contacts arrière
    while (!robot.leftBackContact().state() && !robot.rightBackContact().state())
    {
        usleep(1000);
    }
    if (robot.rightBackContact().state())
    {
        robot.base().motorRight().applyMotorCode(0);

        //attente d'un des contacts arrière
        while (!robot.leftBackContact().state())
        {
            usleep(1000);
        }
        robot.base().motorLeft().applyMotorCode(0);
    }else if (robot.leftBackContact().state())
    {
        robot.base().motorLeft().applyMotorCode(0);

        //attente d'un des contacts arrière
        while (!robot.rightBackContact().state())
        {
            usleep(1000);
        }
        robot.base().motorRight().applyMotorCode(0);
    }
    robot.firePulseEnabled(false); //prise en compte des impulsions des codeurs.
    robot.leftBackContact().stop(true);
    robot.rightBackContact().stop(true);

    //reinit de la position en y
    robot.position().y(distanceCentreBack, robot.myColor());
    robot.position().angle(M_PI_2, robot.myColor());
    robot.position().x(22.0);
    logger().info() << "reinit y : " << robot.position().y()
            << " angle : " << robot.position().angle() << utils::end;

    //avancer de 7cm
    logger().info() << "forward 70mm" << utils::end;
    //robot.base().motorLeft().applyWay(pmx::FORWARD);
    //robot.base().motorRight().applyWay(pmx::FORWARD);
    //usleep(200000);
    //while (!robot.base().motorLeft().wayApplied() || !robot.base().motorRight().wayApplied())
    //{
    //    usleep(50000);
    //}
    robot.base().rampPositionEnabled(false);
    robot.base().pidPositionEnabled(true);
    robot.base().pidSpeedEnabled(false);
    robot.base().vecteurCorrectionEnabled(true);
    robot.base().movexy(robot.position().x(), 200, pmx::BFORWARD, false);
    while (robot.base().arrived() == false)
    {
        usleep(10000);
    }

    logger().info() << "Arrived    x: " << robot.position().x() << " y: "
            << robot.position().y() << " angle: " << robot.position().angle()
            << utils::end;


    //tourner suivant la couleur
    robot.base().pidPositionEnabled(true);
    robot.base().pidSpeedEnabled(true);
    robot.base().vecteurCorrectionEnabled(false);
    if (robot.myColor() == pmx::PMXRED)
    {
        //tourner à gauche de 90°
        logger().info() << "turn left" << utils::end;
        robot.base().turn(pmx::BTURNLEFT, M_PI_2);
        while (robot.base().arrived() == false)
        {
            usleep(10000);
        }
        robot.firePulseEnabled(false);
    }else if (robot.myColor() == pmx::PMXPURPLE)
    {
        //tourner à droite de 90°
        logger().info() << "turn right" << utils::end;
        robot.base().turn(pmx::BTURNRIGHT, M_PI_2);
        while (robot.base().arrived() == false)
        {
            usleep(10000);
        }
        robot.firePulseEnabled(false);
    }
    //robot.base().pidSpeedDesactivate();
    robot.base().reset();

    //reculer
    logger().info() << "back2" << utils::end;
   
    //robot.base().motorLeft().applyWay(pmx::BACK);
    //robot.base().motorRight().applyWay(pmx::BACK);

    robot.leftBackContact().wait();
    robot.rightBackContact().wait();
    //while (!robot.base().motorLeft().wayApplied() || !robot.base().motorRight().wayApplied())
    //{
    //    usleep(50000);
    //}
    robot.firePulseEnabled(true); //prise en compte des impulsions des codeurs.
    robot.base().motorLeft().applyMotorCode(motorcodeMin);
    robot.base().motorRight().applyMotorCode(motorcodeMin);

    //attente d'un des contacts arrière
    while (!robot.leftBackContact().state() && !robot.rightBackContact().state())
    {
        usleep(1000);
    }
    if (robot.rightBackContact().state())
    {
        robot.base().motorRight().applyMotorCode(0);

        //attente d'un des contacts arrière
        while (!robot.leftBackContact().state())
        {
            usleep(1000);
        }
        robot.base().motorLeft().applyMotorCode(0);
    }else if (robot.leftBackContact().state())
    {
        robot.base().motorLeft().applyMotorCode(0);

        //attente d'un des contacts arrière
        while (!robot.rightBackContact().state())
        {
            usleep(1000);
        }
        robot.base().motorRight().applyMotorCode(0);
    }
    robot.firePulseEnabled(false); //prise en compte des impulsions des codeurs.
    robot.leftBackContact().stop(true);
    robot.rightBackContact().stop(true);

    //reinit de la position en x et de l'angle
    robot.position().x(distanceCentreBack);
    robot.position().angle(0, robot.myColor());
    logger().info() << "reinit x : " << robot.position().x() << utils::end;

    //robot.base().motorLeft().applyWay(pmx::FORWARD);
    //robot.base().motorRight().applyWay(pmx::FORWARD);
    //usleep(200000);
    //while (!robot.base().motorLeft().wayApplied() || !robot.base().motorRight().wayApplied())
    //{
    //    usleep(50000);
    //}
    
    //avancer à la position de départ
    //logger().info() << "y:" << robot.position().y() << " x:" << robot.position().x() << " angle:" << robot.position().angle() << utils::end;
    //logger().info() << "forward 200,200" << utils::end;
    //robot.base().movexy(200, robot.position().y(), pmx::BFORWARD);
    //logger().info() << "y:" << robot.position().y() << " x:" << robot.position().x() << " angle:" << robot.position().angle() << utils::end;
 *
    robot.base().pidSpeedDesactivate();
    robot.base().reset();

    logger().info() << "Position adjusted." << utils::end;


    robot.ledBar().k2Mil(50000);
    
    robot.rebootContact().wait();
    robot.colorContact().wait();
    usleep(50000); //attente de la prise en compte des états des contacts.
    bool stateColor;
    if (robot.myColor() == pmx::PMXPURPLE)
    {
        stateColor = robot.colorContact().state();
    }else if (robot.myColor() == pmx::PMXRED)
    {
        stateColor = !robot.colorContact().state();
    }
    //attente de l'appui enfoncé d'un des contacts ou un changement du bouton de couleur
    while (!stateColor && !robot.rebootContact().state())
    {
        usleep(10000);
        if (robot.myColor() == pmx::PMXPURPLE)
        {
            stateColor = robot.colorContact().state();
        }else if (robot.myColor() == pmx::PMXRED)
        {
            stateColor = !robot.colorContact().state();
        }
    }

    if (robot.rebootContact().state())
    {
        //attente du relachement du reboot
        while (robot.rebootContact().state())
        {
            usleep(10000);
        }

        result = new pmx::StateWaitForStart(); //si appui sur rebootContact
    }else
    {
        result = new pmx::StateInitialize(); //si changement de couleur
    }
    robot.colorContact().stop(true);
    robot.rebootContact().stop(true);
    robot.ledBar().stop(true);
    robot.ledBar().reset();
    */

    

    
/*
    logger().info() << "L&R to HIGH" << utils::end;
    robot.forkCenter().goHighPosition();
    robot.forkLeft().goHighPosition();
    robot.forkRight().goHighPosition();
    usleep(50*1000);
    robot.turnForkLeft().goHighPosition();
    robot.turnForkRight().goHighPosition();
    */

    logger().debug() << "Color=" << robot.myColor()
            << utils::end;
    
    robot.position().x(130);
    robot.position().y(600, robot.myColor());
    robot.position().angle(0, robot.myColor());

    logger().debug() << "Position x=" << robot.position().x()
            << " y=" << robot.position().y()
            << " a=" << robot.position().angle()
            << utils::end;

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);

    logger().info() << "Position adjusted." << utils::end;
    
    result = this->getState("next");

    return result;
}
