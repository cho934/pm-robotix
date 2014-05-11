/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/ConsoleAppender.hpp"
#include "../../common/cpp/MemoryAppender.hpp"
#include "../../common/cpp/FileAppender.hpp"
#include "../../common/cpp/SvgAppender.hpp"

void utils::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());

	add(utils::Level::ERROR, "", "console");

	add(utils::Level::INFO, "pmx::ServoMotorDxlObject", "console");

	add(utils::Level::INFO, "robottest::LedIndicatorTest", "console");
	add(utils::Level::INFO, "robottest::GroveColorTest", "console");
	add(utils::Level::INFO, "robottest::LedBarTest", "console");
	add(utils::Level::INFO, "robottest::ServoMotorStdTest", "console");
	add(utils::Level::INFO, "robottest::ExtEncoderTest", "console");
	add(utils::Level::INFO, "robottest::IrSensorsGroupTest", "console");
	add(utils::Level::INFO, "robottest::ServoMotorDxlTest", "console");
	add(utils::Level::INFO, "robottest::Md25Test", "console");
	add(utils::Level::INFO, "robottest::ArduinoTest", "console");
	add(utils::Level::INFO, "robottest::GpioBoardTest", "console");


	//add(utils::Level::DEBUG, "pmx::Robot", "console");
	//add(utils::Level::DEBUG, "pmx::GroveColorSensor", "console");
	//add(utils::Level::DEBUG, "pmx::ActionManager", "console");
	//add(utils::Level::DEBUG, "pmx::ExtEncoder", "console");
	//add(utils::Level::DEBUG, "pmx::IrSensor", "console");
	//add(utils::Level::DEBUG, "pmx::IrSensorsGroup", "console");
	//add(utils::Level::DEBUG, "pmx::ServoMotorDxlObject", "console");
	//add(utils::Level::DEBUG, "pmx::ServoMotorDxl", "console");
	//add(utils::Level::DEBUG, "pmx::GpioBoard", "console");
	//add(utils::Level::DEBUG, "pmx::Md25", "console");


}
