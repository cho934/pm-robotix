/*!
 * \file
 * \brief Implémentation de la classe ServoMotorStdLearnTest..
 */

#include "ServoMotorStdLearnTest.hpp"

#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxl.hpp"

void robottest::ServoMotorStdLearnTest::run(int argc, char *argv[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "ServoMotorStdLearnTest - learn servo position" << utils::end;

	int id = 0;
	int pos = 2048;
	int speed = 0;

	if (argc < 5)
	{
		std::cout << "USAGE: PMX_TEST " << argv[1] << " [ID:0-7] [position:0-4000] [speed:0-]"
				<< std::endl;
	}

	if (argc > 2)
	{
		id = atoi(argv[2]);
		std::cout << "id: " << atoi(argv[2]) << std::endl;
	}
	else
	{
		std::cout << "id: " << std::flush;
		std::cin >> id;
	}

	if (argc > 3)
	{
		pos = atoi(argv[3]);
		std::cout << "pos: " << atoi(argv[3]) << std::endl;
	}
	else
	{
		std::cout << "pos: " << std::flush;
		std::cin >> pos;
	}

	if (argc > 4)
	{
		speed = atoi(argv[4]);
		std::cout << "speed: " << atoi(argv[4]) << std::endl;
	}

	pmx::Robot &robot = pmx::Robot::instance();
	robot.start(0, 0);

	robot.clamp().setSpeed(id, speed);
	robot.clamp().setPosition(id, pos, 1);

	sleep(1);

	int cpos = robot.clamp().getPosition(id);
	logger().info() << "Current pos=" << cpos << utils::end;
	robot.clamp().setPosition(id, pos, 0);
	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

