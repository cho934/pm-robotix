/*!
 * \file
 * \brief Implémentation de la classe IrSensorsGroupTest.
 */

#include "IrSensorsGroupTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::IrSensorsGroupTest::run(int argc, char *argv[])
{

	int average, timeToExit;
	int timeSpan = 100;

	if (argc < 3)
	{
		std::cout << "USAGE: ROBOT_TEST " << argv[1]
				<< " [timeToExit(Sec)] [Average:4,8,16,32,1 for disabling] [option TimeSpan=100ms by default]"
				<< std::endl;
	}

	if (argc > 2)
	{
		timeToExit = atoi(argv[2]);
	}
	else
	{
		std::cout << "[timeToExit] : " << std::flush;
		std::cin >> timeToExit;
	}

	if (argc > 3)
	{
		average = atoi(argv[3]);
	}
	else
	{
		std::cout << "[Average:4,8,16,32,1 for disabling] : " << std::flush;
		std::cin >> average;
	}

	if (argc > 4)
	{
		timeSpan = atoi(argv[4]);
	}

	logger().info() << "----------------------------------------------------" << utils::end;
	logger().info() << "IrSensorsGroupTest - Detection by IR" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	robot.start();
	robot.chronometerRobot().start(); //Chronometre général (match) du robot

	logger().info() << "Start IrSensor Listener" << utils::end;

	//TODO change average

	logger().info() << " irLeft       :" << " pin:" << robot.irSensorsGroup().irLeft().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irLeft().voltage() << " Dist: " << robot.irSensorsGroup().irLeft().distanceMm()
			<< " mm " << (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "") << utils::end;

	logger().info() << " irCenter     :" << " pin:" << robot.irSensorsGroup().irCenter().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irCenter().voltage() << " Dist: "
			<< robot.irSensorsGroup().irCenter().distanceMm() << " mm "
			<< (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "") << utils::end;

	logger().info() << " irRight      :" << " pin:" << robot.irSensorsGroup().irRight().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irRight().voltage() << " Dist: " << robot.irSensorsGroup().irRight().distanceMm()
			<< " mm " << (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "") << utils::end;

	logger().info() << " irRearCenter :" << " pin:" << robot.irSensorsGroup().irRearCenter().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irRearCenter().voltage() << " Dist: "
			<< robot.irSensorsGroup().irRearCenter().distanceMm() << " mm "
			<< (robot.irSensorsGroup().irRearCenter().distanceMm() > 300 ? " MAX " : "") << utils::end;

	robot.irSensorsGroup().changeTimeSpan(timeSpan);
	robot.irSensorsGroup().startTimer();

	while (robot.chronometerRobot().getElapsedTimeInSec() <= timeToExit)
	{
		logger().info() << " irLeft    :"
				//<< " Volt: " << robot.irSensorsGroup().irLeft().voltage()
				<< " pin:" << robot.irSensorsGroup().irLeft().adcPin() << " Dist: "
				<< robot.irSensorsGroup().irLeft().distanceMm() << " mm "
				<< (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "") << utils::end;

		logger().info() << " irCenter  :"
				//<< " Volt: " << robot.irSensorsGroup().irCenter().voltage()
				<< " pin:" << robot.irSensorsGroup().irCenter().adcPin() << " Dist: "
				<< robot.irSensorsGroup().irCenter().distanceMm() << " mm "
				<< (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "") << utils::end;

		logger().info() << " irRight   :"
				//<< " Volt: " << robot.irSensorsGroup().irRight().voltage()
				<< " pin:" << robot.irSensorsGroup().irRight().adcPin() << " Dist: "
				<< robot.irSensorsGroup().irRight().distanceMm() << " mm "
				<< (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "") << utils::end;

		logger().info() << " irRearC   :"
				//<< " Volt: " << robot.irSensorsGroup().irRearCenter().voltage()
				<< " pin:" << robot.irSensorsGroup().irRearCenter().adcPin() << " Dist: "
				<< robot.irSensorsGroup().irRearCenter().distanceMm() << " mm "
				<< (robot.irSensorsGroup().irRearCenter().distanceMm() > 300 ? " MAX " : "") << utils::end;

		logger().info() << utils::end;
		logger().info() << utils::end;
		usleep(timeSpan * 1000);
	}

	robot.irSensorsGroup().stopTimer();

	logger().info() << " END irLeft    :" << " pin:" << robot.irSensorsGroup().irLeft().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irLeft().voltage() << " Dist: " << robot.irSensorsGroup().irLeft().distanceMm()
			<< " mm " << (robot.irSensorsGroup().irLeft().distanceMm() > 300 ? " MAX " : "") << utils::end;

	logger().info() << " END irCenter  :" << " pin:" << robot.irSensorsGroup().irCenter().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irCenter().voltage() << " Dist: "
			<< robot.irSensorsGroup().irCenter().distanceMm() << " mm "
			<< (robot.irSensorsGroup().irCenter().distanceMm() > 1500 ? " MAX " : "") << utils::end;

	logger().info() << " END irRight   :" << " pin:" << robot.irSensorsGroup().irRight().adcPin() << " Volt: "
			<< robot.irSensorsGroup().irRight().voltage() << " Dist: " << robot.irSensorsGroup().irRight().distanceMm()
			<< " mm " << (robot.irSensorsGroup().irRight().distanceMm() > 300 ? " MAX " : "") << utils::end;

	logger().info() << "Robot Stop" << utils::end;
	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

