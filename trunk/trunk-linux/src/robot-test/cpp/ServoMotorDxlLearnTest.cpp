/*!
 * \file
 * \brief Implémentation de la classe ServoMotorDxlLearnTest..
 */

#include "ServoMotorDxlLearnTest.hpp"

#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxl.hpp"

void robottest::ServoMotorDxlLearnTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "ServoMotorDxlLearnTest - learn AX-12 position" << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	robot.start(0,0);

	long pos3 = pmx::ServoMotorDxl::instance().dxlGetPos(3);
	logger().info() << "levier gauche 3 :dxlGetPos= " << pos3 << utils::end;
	long pos5 = pmx::ServoMotorDxl::instance().dxlGetPos(5);
	logger().info() << "levier droit  5 :dxlGetPos= " << pos5 << utils::end;
	long pos7 = pmx::ServoMotorDxl::instance().dxlGetPos(7);
	logger().info() << "tir filet 7 :dxlGetPos= " << pos7 << utils::end;
	long pos8 = pmx::ServoMotorDxl::instance().dxlGetPos(8);
	logger().info() << "tir balle 8 :dxlGetPos= " << pos8 << utils::end;

	long pos4 = pmx::ServoMotorDxl::instance().dxlGetPos(4);
	logger().info() << " p4 :dxlGetPos= " << pos4 << utils::end;
	long pos6 = pmx::ServoMotorDxl::instance().dxlGetPos(6);
	logger().info() << " p6 front :dxlGetPos= " << pos6 << utils::end;


	long pos14 = pmx::ServoMotorDxl::instance().dxlGetPos(14);
		logger().info() << " p14 :dxlGetPos= " << pos14 << utils::end;


	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

