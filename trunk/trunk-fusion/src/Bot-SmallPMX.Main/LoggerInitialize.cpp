/*!
 * \file
 * \brief Ce fichier contient l'initialisation du système de Log.
 */

#include "../Log/Appender/FileAppender.hpp"
#include "../Log/Appender/SvgAppender.hpp"
#include "../Log/Appender/ConsoleAppender.hpp"
#include "../Log/Level.hpp"
#include "../Log/LoggerFactory.hpp"

void logs::LoggerFactory::initialize()
{
	add("console", new ConsoleAppender());
	//add("memory", new MemoryAppender());
	//add("file", new FileAppender("log.txt"));

	add(logs::Level::ERROR, "", "console");

	add(logs::Level::INFO, "LedBarTest", "console");
	add(logs::Level::INFO, "ButtonBarTest", "console");
	add(logs::Level::INFO, "TiretteTest", "console");
	add(logs::Level::INFO, "SoundBarTest", "console");
	add(logs::Level::INFO, "MotorTest", "console");
	add(logs::Level::INFO, "MoveTest", "console");
	add(logs::Level::INFO, "EncoderTest", "console");
	add(logs::Level::INFO, "SupportTest", "console");
	add(logs::Level::INFO, "DetectionTest", "console");
	add(logs::Level::INFO, "ServoTest", "console");

	add(logs::Level::INFO, "StateWaitForReboot", "console");
	add(logs::Level::INFO, "StateInitialize", "console");
	add(logs::Level::INFO, "StateAdjustRobotPosition", "console");
	add(logs::Level::INFO, "StateWaitForStart", "console");
	//add(logs::Level::DEBUG, "StateIADecisionMaker", "console");
	add(logs::Level::INFO, "Wait90SecondsAction", "console");
/*
	add(logs::Level::INFO, "Robot", "console");

	add(logs::Level::INFO, "LedBar", "console");
	add(logs::Level::INFO, "LedBarAction", "console");
	add(logs::Level::INFO, "SoundBar", "console");
	add(logs::Level::INFO, "SoundBarAction", "console");
	add(logs::Level::INFO, "ButtonBar", "console");
	add(logs::Level::INFO, "Tirette", "console");*/
	add(logs::Level::INFO, "DetectionSensor", "console");

	//DEBUG
	//add(logs::Level::DEBUG, "MotorControl", "console");
	//add(logs::Level::DEBUG, "ActionManager", "console");
	//add(logs::Level::DEBUG, "Actions", "console");
	//add(logs::Level::INFO, "Asserv", "console");

	//DRIVER
	//add(logs::Level::INFO, "LedDriver.SIMU", "console");
	//add(logs::Level::INFO, "SoundDriver.SIMU", "console");
	//add(logs::Level::INFO, "MotorDeviceDriver.EV3", "console");
	//add(logs::Level::INFO, "AsservDriver.EV3", "console");

}
