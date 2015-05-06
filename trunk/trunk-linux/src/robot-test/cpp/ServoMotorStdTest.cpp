/*!
 * \file
 * \brief Implémentation de la classe ServoMotorStdTest.
 */

#include "ServoMotorStdTest.hpp"

#include <unistd.h>

#include "../../common/c/ccbase.h"
#include "../../common/c/motion.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoClamp.hpp"

void robottest::ServoMotorStdTest::run(int, char *[])
{
	logger().info() << "--------------------------------------------" << utils::end;
	logger().info() << "ServoMotorStdTest - Test servo" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();

	char currentPath[1024];
	getcwd(currentPath, 1024);
	robot.configure("robot-test.conf.txt");
	logger().info() << "configure " << currentPath << "/robot-test.conf.txt loaded" << utils::end;

	robot.base().setMatchColor(0);
	int asserv = 1;
	robot.start(0, asserv);
	cc_setPosition(0, 0, 0.0, cc_getMatchColor());
	motion_configureAlphaPID(0.0015f, 0.0008f, 0.000002f); //0.0008 0.00002 0.00003
	motion_configureDeltaPID(0.0005f, 0.0000f, 0.000000f); //0.0005 0.000008 0.000009 //0.0015 0.0008 0.000002


	//robot.clamp().init();

	robot.clamp().openLeftDoor();
	robot.clamp().openRightDoor();
	usleep(2000000);

	robot.clamp().closeAll();

	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();

	robot.base().movexyteta(0, 150, 0, 0);
	robot.clamp().takeLeftElement();
	robot.clamp().takeRightElement();
	sleep(1);
	robot.base().movexyteta(0, 300, 0, 0);

	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();
		robot.clamp().takeLeftElement();
	robot.clamp().takeRightElement();
	sleep(1);
	robot.base().movexyteta(0, 450, 0, 0);
	robot.clamp().readyToTakeLeftElement();
	robot.clamp().readyToTakeRightElement();
	robot.clamp().takeLeftElement();
	robot.clamp().takeRightElement();

	sleep(1);

	robot.base().movexyteta(0, 600, 0, 0);

	robot.clamp().pushLeft();
	robot.clamp().pushRight();

	usleep(200000);

	robot.base().movexyteta(1, 450, 0, 0);

	robot.clamp().closeAll();

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

