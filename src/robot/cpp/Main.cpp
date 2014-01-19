/*!
 * \file
 * \brief Ce fichier contient la méthode main() pour le programme principal.
 */

#include <iostream>
#include <dirent.h>
#include <math.h>

#include "Robot.hpp"
#include "StateWaitForReboot.hpp"
#include "LoggerFactory.hpp"
#include "Macro.hpp"

using namespace pmx;

/*!
 * \brief Méthode principale pour le lancement du robot.
 *
 * \return Code de retour du programme.
 */
int main(int argc, char** argv)
{
    const utils::Logger& logger = utils::LoggerFactory::logger("main");

    Robot robot;

    int mode = 0;
    int zap = 0;
    //prise en compte des arguments
    if (argc > 1)
    {
        mode = atoi(argv[1]);
        if(mode == 1)
        {
            robot.runMode(pmx::ROBOTHOMOLOGATION);
            logger.info() << "MODE HOMOLOGATION" << utils::end;
        }else
        {
            robot.runMode(pmx::ROBOTMATCHES);
            logger.info() << "MODE MATCHES" << utils::end;
        }
        
    }else
    {
        robot.runMode(pmx::ROBOTHOMOLOGATION);
        logger.info() << "MODE ROBOTHOMOLOGATION" << utils::end;
    }

    if (argc > 2)
    {
        zap = atoi(argv[2]);
    }

    robot.firePulseEnabled(false); //pour ne pas prendre en compte les impulsions des codeurs.
    
    logger.info() << "Start of the robot" << utils::end;
    robot.start();

    if(zap == 1)
    {
        robot.modeZap(1);
    }
    robot.base().pidSpeedDesactivate();
    robot.base().pidSpeedStart(); //lancement du thread timer de gestion PID
    robot.startAutomate(new pmx::automate::StateWaitForReboot());
    robot.stop();

    logger.info() << "Position :" << robot.position().x() << " " << robot.position().y() << " " << (robot.position().angle()*180)/M_PI << utils::end;
    
    logger.info() << "PMX - Happy end" << utils::end;
    return 0;
}
