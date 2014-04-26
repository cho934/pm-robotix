/*!
 * \file
 * \brief Implémentation de la classe Md25Test.
 */

#include "Md25Test.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::Md25Test::run(int, char *[])
{
	int speedL = 50;
	int speedR = 50;

	logger().info() << "--------------------" << utils::end;
	logger().info() << "Md25Test - Go" << utils::end;

	pmx::Robot robot;

	float bat = robot.md25().getBatteryVolts();
	logger().info() << "bat  = " << bat << utils::end;

	int soft = robot.md25().getSoftwareVersion();
	logger().info() << "soft = " << soft << utils::end;


	//config MD25
	robot.md25().setMode(MD25_MODE_0); //mode0 => 0-128-255
	robot.md25().setAccelerationRate(5); //Acc:1,2,3,5,10

	robot.md25().setCommand(MD25_ENABLE_SPEED_REGULATION);

	robot.md25().setCommand(MD25_RESET_ENCODERS);



	robot.md25().ensureSetSpeed(speedL, MD25_SPEED1_REG); //0=>255
	robot.md25().ensureSetSpeed(speedR, MD25_SPEED2_REG); //0=>255

	usleep(3000000);

	robot.md25().stopMotors();

	logger().info() << "End of RobotTest." << utils::end;
}

