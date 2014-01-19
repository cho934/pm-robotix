/*!
 * \file
 * \brief Implémentation de la classe PushBottleStrategy.
 */

#include "PushBottleStrategy.hpp"
#include "Robot.hpp"
#include "Data.hpp"
#include "Contract.hpp"

int
pmx::PushBottleStrategy::computeInterest(const pmx::Robot &, void * data)
{
    utils::Contract::isNotNull(data, "pmx::PushBottleStrategy::computeInterest - data is null");

    pmx::Data* sharedData = (pmx::Data*) data;
    if (sharedData->strategyPushGoldBar() == false)
    {
        return -1;
    }
    else
    {
        return 3;
    }
}



pmx::IAutomateState*
pmx::PushBottleStrategy::execute(pmx::Robot & robot, void * data)
{
    logger().info() << "start" << utils::end;
    pmx::Data* sharedData = (pmx::Data*) data;

    robot.base().pidSpeedEnabled(false);
    robot.base().rampPositionEnabled(false);
    robot.base().pidPositionEnabled(true);


    robot.base().vecteurCorrectionEnabled(true); //TODO!!!!!


    //debut avance
    robot.base().pidSpeedActivate();
    //robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.firePulseEnabled(false);

    this->logger().info() << "goTo(800.0,1500.0)" << utils::end;
    robot.goTo(800.0,1500.0);

    this->logger().info() << "goTo(1900.0,1500.0)" << utils::end;
    robot.goTo(1900.0,1500.0);
    this->logger().info() << "goTo(1900.0,1600.0)" << utils::end;
    robot.goTo(1900.0,1600.0);
    this->logger().info() << "movexyTeta(1900,1600,pmx::BFORWARD, -M_PI_2,false)" << utils::end;
    robot.base().movexyTeta(1900.0,1600.0,pmx::BFORWARD, -M_PI_2,false);

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "1", "blue", "30");

    this->logger().info() << "movexyTeta(1900,1897,pmx::BBACK,-M_PI_2,false)" << utils::end;
    robot.base().movexyTeta(1900.0,1897.0,pmx::BBACK,-M_PI_2,false);

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "2", "blue", "30");

    this->logger().info() << "movexyTeta(1900,1700,pmx::BFORWARD, -M_PI_2,false)" << utils::end;
    robot.base().movexyTeta(1900.0,1700.0,pmx::BFORWARD, -M_PI_2,false);

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "3", "blue", "30");

    //this->logger().info() << "movexyTeta(1900,1900,pmx::BBACK,-M_PI_2,false)" << utils::end;
    //robot.base().movexyTeta(1900,1900,pmx::BBACK,-M_PI_2,false);

    //Ecriture dans le SVG
    //utils::SvgWriter::writePosition(robot.position().x(),
    //    robot.position().y(),
    //    robot.position().angle(), utils::SVG_POS_ROBOT);
    //utils::SvgWriter::writeTextCustom(robot.position().x()+200,
    //    robot.position().y(),
    //    "4", "blue", "30");

    //ramassage de cds... et tout le tralala

    this->logger().info() << "ramassage de cds... et tout le tralala" << utils::end;
    this->logger().info() << "goToTeta(2080.0, 1340.0, pmx::BFORWARD, -M_PI)" << utils::end;
    robot.goToTeta(2080.0, 1340.0, pmx::BFORWARD, -M_PI);



    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "5", "blue", "30");

    this->logger().info() << "goTo(900.0,1340.0)" << utils::end;
    robot.goTo(900.0,1340.0);

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "6", "blue", "30");

    this->logger().info() << "goTo(300.0,800.0)" << utils::end;
    robot.goTo(300.0,800.0);

    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "7", "blue", "30");

    this->logger().info() << "movexy(500.0,900.0,pmx::BBACK,false)" << utils::end;
    robot.base().movexy(500.0,900.0,pmx::BBACK,false);



    //Ecriture dans le SVG
    utils::SvgWriter::writePosition(robot.position().x(),
        robot.position().y(),
        robot.position().angle(), utils::SVG_POS_ROBOT);
    utils::SvgWriter::writeTextCustom(robot.position().x()+200,
        robot.position().y(),
        "FIN", "blue", "30");

    this->logger().debug() << "fin" << utils::end;

    //fin avance
    //robot.base().pidSpeedStop();
    robot.base().pidSpeedDesactivate();
    robot.firePulseEnabled(false);


    this->logger().debug() << "return" << utils::end;





    //return this->getState("decisionMaker");
    return NULL; //fin du programme
}

