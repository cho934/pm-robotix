/*!
 * \file
 * \brief Ce fichier contient la méthode main() pour le programme principal.
 */

#include <iostream>
#include <dirent.h>

#include "Robot.hpp"
#include "StateWaitForReboot.hpp"
#include "LoggerFactory.hpp"

using namespace pmx;

/**
 * \brief Méthode principale pour le lancement du robot.
 *
 * \return Code de retour du programme.
 */
int main()
{
    const utils::Logger& logger = utils::LoggerFactory::logger("main");

    char currentPath[PATH_MAX];
    getcwd(currentPath, PATH_MAX); 
    logger.info() << "Current directory:" << currentPath << utils::end;

    Robot robot;
    
    logger.info() << "Start of the robot" << utils::end;
    
    try
    {
        robot.configure("/opt/pmx/robot.conf");
        logger.info() << "Configuration loaded" << utils::end;
    }
    catch(utils::ConfigurationException* exception)
    {
        logger.error() << "Error in the configuration file" << utils::end;
        logger.error() << "Message: " << exception->what() << utils::end;
        std::cerr << "Error !! " << exception->what() << std::endl;
        
        robot.stop();
        return 1;
    }
    
    robot.start();
    robot.startAutomate(new pmx::automate::StateWaitForReboot());
    robot.stop();
    
    logger.info() << "Happy end" << utils::end;
    return 0;
}
