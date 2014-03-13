/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * unitaires directement sans utiliser l'objet Robot.
 */

#include <iostream>
#include "../../common/cpp/ConsoleUnitTestManager.hpp"


#include "ApfGpioIn.hpp"
#include "ApfGpioOut.hpp"
#include "ApfAdcIn.hpp"
#include "ApfDacOut.hpp"
#include "ApfFpgaServo.hpp"
#include "ApfI2cWithGroveColor.hpp"
#include "ApfSpiWithLs7366.hpp"
#include "ApfI2cWithMd25.hpp"
#include "ApfUartWithAX12.hpp"
#include "ApfI2cWithArduino.hpp"
#include "ApfI2cWithGpio.hpp"

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
    std::cout << "apf-test Start" << std::endl;

    pmx::ConsoleUnitTestManager manager;

    manager.add(new test::ApfGpioIn());
    manager.add(new test::ApfGpioOut());
    manager.add(new test::ApfAdcIn());
    manager.add(new test::ApfDacOut());
    manager.add(new test::ApfFpgaServo());
    manager.add(new test::ApfI2cWithGroveColor());
    manager.add(new test::ApfI2cWithMd25());
    manager.add(new test::ApfSpiWithLs7366());
    manager.add(new test::ApfUartWithAX12());
    manager.add(new test::ApfI2cWithArduino());
    manager.add(new test::ApfI2cWithGpio());


    if (argc == 1)
	{
		manager.run();
	}
	else
	{
		manager.run(atoi(argv[1]), argc, argv);
	}

}
