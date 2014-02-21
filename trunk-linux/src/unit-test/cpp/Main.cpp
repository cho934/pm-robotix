/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * sur le robot.
 */

//extern "C" {
//#include "as_devices/as_i2c.h"
//}

#include <iostream>
#include "../../common/cpp/UnitTestManager.hpp"



/*!
 * \brief Méthode principale pour le lancement des tests sur le robot.
 *
 * \param argc
 *        Nombre d'arguments.
 * \param argv
 *        Arguments du programme (argv[0] est le nom de l'application).
 * \return Code de retour du programme.
 */
int main(int argc, char** argv)
{
    std::cout << "main unit-test Start" << std::endl;

    pmx::UnitTestManager manager;




    if (argc == 1)
	{
		manager.run();
	}
	else
	{
		manager.run(atoi(argv[1]), argc, argv);
	}

}
