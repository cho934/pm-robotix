/*!
 * \file
 * \brief Implémentation de la classe LedBarTest.
 */

#include "../Common/Action/ButtonBar.hpp"
#include "ButtonBarTest.hpp"

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Log/Logger.hpp"


using namespace std;

void ButtonBarTest::run(int, char *[])
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	SRobotExtended &robot = SRobotExtended::instance();

	logger().info() << "Please press ENTER" << logs::end;
	robot.actions().buttonBar().waitPressed(BUTTON_ENTER_KEY);

	logger().info() << "Please press BACK" << logs::end;
	robot.actions().buttonBar().waitPressed(BUTTON_BACK_KEY);


	logger().info() << "Happy End." << logs::end;
}

