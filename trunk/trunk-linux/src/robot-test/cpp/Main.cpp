/*!
 * \file
 * \brief Ce fichier contient le programme principal pour le lancement des tests
 * sur le robot.
 */

#include <cstdlib>
#include <iostream>

#include "../../common/cpp/ConsoleUnitTestManager.hpp"
#include "ArduinoTest.hpp"
#include "ExtEncoderTest.hpp"
#include "GpioBoardTest.hpp"
#include "GroveColorTest.hpp"
#include "IrSensorsGroupTest.hpp"
#include "LedBarTest.hpp"
#include "LedIndicatorTest.hpp"
#include "Md25Test.hpp"
#include "Md25EncoderTest.hpp"
#include "FindPIDADTest.hpp"
#include "FindPIDTest.hpp"
#include "MoveLineVAccTest.hpp"
#include "MoveTest.hpp"
#include "MoveXYTest.hpp"
#include "ServoMotorDxlTest.hpp"
#include "ServoMotorStdTest.hpp"
#include "ServoMotorDxlLearnTest.hpp"
#include "LcdTest.hpp"
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
	//std::cout << "main robot-test Start" << std::endl;
	//const utils::Logger& logger = utils::LoggerFactory::logger("main");
	//logger.info("Lancement des tests unitaires");

	pmx::ConsoleUnitTestManager manager;

	manager.add(new robottest::LedIndicatorTest());
	manager.add(new robottest::LedBarTest());
	manager.add(new robottest::GroveColorTest());
	manager.add(new robottest::ExtEncoderTest());
	//manager.add(new robottest::ServoMotorStdTest());
	manager.add(new robottest::IrSensorsGroupTest());
	manager.add(new robottest::ServoMotorDxlTest());
	manager.add(new robottest::ServoMotorDxlLearnTest());
	manager.add(new robottest::ArduinoTest());
	manager.add(new robottest::GpioBoardTest());
	manager.add(new robottest::LcdTest());

	manager.add(new robottest::Md25Test());
	manager.add(new robottest::Md25EncoderTest());
	manager.add(new robottest::FindPIDADTest());
	manager.add(new robottest::FindPIDTest());
	manager.add(new robottest::MoveLineVAccTest());
	manager.add(new robottest::MoveTest());
	manager.add(new robottest::MoveXYTest());

	if (argc == 1)
	{
		manager.run(argv[0]);
	}
	else
	{
		manager.run(atoi(argv[1]), argc, argv);
	}

}
