/*!
 * \file
 * \brief Implémentation de la classe Md25Test.
 */

#include "../../common/cpp/Md25.hpp"
#include "Md25Test.hpp"

#include <cstdlib>
#include <iostream>

#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::Md25Test::run(int argc, char *argv[])
{
	float bat = 0;
	int soft = 0;
	long encoder1 = 0;
	long encoder2 = 0;
	int reg = 1;

	int powerR, powerL, dist, acc;

	if (argc < 7)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1]
				<< " [powerL(1)(0=>128=>255)] [powerR(2)(0=>128 =>255)] [dist(tick)] [Acc:1,2,3,5,10] [Regulation:0,1]"
				<< std::endl;
	}

	if (argc > 2)
	{
		powerL = atoi(argv[2]);
		std::cout << "speedL(1): " << atoi(argv[2]) << std::endl;
	}
	else
	{
		//demande de la distance x
		std::cout << "powerL(1): " << std::flush;
		std::cin >> powerL;
	}

	if (argc > 3)
	{
		powerR = atoi(argv[3]);
		std::cout << "powerR(2): " << atoi(argv[3]) << std::endl;
	}
	else
	{
		//demande de la distance y
		std::cout << "speedR(2): " << std::flush;
		std::cin >> powerR;
	}

	if (argc > 4)
	{
		dist = atoi(argv[4]);
		std::cout << "dist: " << atoi(argv[4]) << std::endl;
	}
	else
	{
		//demande de la vitesse moteur droit à appliquer
		std::cout << "dist: " << std::flush;
		std::cin >> dist;
	}

	if (argc > 5)
	{
		acc = atoi(argv[5]);
		std::cout << "acc: " << atoi(argv[5]) << std::endl;
	}
	else
	{
		//demande de la vitesse moteur droit à appliquer
		std::cout << "acc: " << std::flush;
		std::cin >> acc;
	}
	if (acc != 1 && acc != 2 && acc != 3 && acc != 5 && acc != 10)
		acc = 5;

	if (argc > 6)
	{
		reg = atoi(argv[6]);
		std::cout << "reg: " << atoi(argv[6]) << std::endl;
	}
	else
	{
		//demande de la vitesse moteur droit à appliquer
		std::cout << "reg: " << std::flush;
		std::cin >> reg;
	}

	logger().info() << "--------------------" << utils::end;
	logger().info() << "Md25Test - Go" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	bat = robot.md25().getBatteryVolts();
	soft = robot.md25().getSoftwareVersion();
	logger().info() << "bat  = " << bat << " soft = " << soft << utils::end;

	utils::Chronometer chrono;
	chrono.start();

	long now = chrono.getElapsedTimeInMicroSec();
	//long prec = now;

	//config MD25 //TODO mettre dans setup MD25
	robot.md25().setMode(MD25_MODE_0); //mode0 => 0->128->255  ;  mode1 => -128+127
	robot.md25().setAccelerationRate(acc); //Acc:1,2,3,5,10

	robot.md25().setCommand(MD25_ENABLE_SPEED_REGULATION);

	if (reg == 1)
		robot.md25().setCommand(MD25_ENABLE_SPEED_REGULATION);
	else
		robot.md25().setCommand(MD25_DISABLE_SPEED_REGULATION);

	robot.md25().setCommand(MD25_RESET_ENCODERS);
	usleep(500);

	logger().info() << "Go to : dist(tick)=" << dist << " dist(mm)= " << utils::end;

	logger().info() << " MD25_SPEED1_REG powerL=" << powerL << " MD25_SPEED2_REG powerR=" << powerR << utils::end;

	robot.md25().ensureSetSpeed(powerR, MD25_SPEED1_REG); //0=>255
	robot.md25().ensureSetSpeed(powerL, MD25_SPEED2_REG); //0=>255

	while (abs(encoder1) < abs(dist) && abs(encoder2) < abs(dist))
	{

		encoder1 = robot.md25().ensureGetEncoder(0, MD25_ENCODER1_REG);
		encoder2 = robot.md25().ensureGetEncoder(0, MD25_ENCODER2_REG);

		logger().info() << "MD25:getEncoder1 R: " << encoder1 << " \t getEncoder2 L: " << encoder2 << utils::end;
		usleep(200000);

	}
	logger().info() << "End - stopMotors" << utils::end;
	now = chrono.getElapsedTimeInMicroSec();
	robot.md25().stopMotors();

	usleep(1000000);

	encoder1 = robot.md25().ensureGetEncoder(0, MD25_ENCODER1_REG);
	encoder2 = robot.md25().ensureGetEncoder(0, MD25_ENCODER2_REG);

	logger().info() << "MD25:getEncoder1: " << encoder1 << " getEncoder2: " << encoder2 << utils::end;
	logger().info() << "Arrived : dist(tick)=" << dist << " dist(mm)= " << dist << utils::end;

	logger().info() << "End of RobotTest." << utils::end;
}

