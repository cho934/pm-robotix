/*!
 * \file
 * \brief Implémentation de la classe LcdTest..
 */

#include "LcdTest.hpp"
#include "../../common/cpp/Robot.hpp"

void robottest::LcdTest::run(int, char *[])
{
	logger().info() << "-------------------------------------------------" << utils::end;
	logger().info() << "LcdTest - " << utils::end;

	pmx::Robot &robot = pmx::Robot::instance();
	//robot.start(0);

	robot.lcdBoard().setBacklight(LCD_RED);

	robot.lcdBoard().clear();

	robot.lcdBoard().print("PMX");
	usleep(1000000);

	robot.lcdBoard().print("GO");

	while (1)
	{
		uint8_t buttons = robot.lcdBoard().readButtons();
		if (buttons)
		{
			robot.lcdBoard().clear();
			robot.lcdBoard().setCursor(0, 0);
			if (buttons & BUTTON_UP)
			{
				robot.lcdBoard().print("UP ");
				robot.lcdBoard().setBacklight(LCD_BLUE);
			}

			if (buttons & BUTTON_DOWN)
			{
				robot.lcdBoard().print("DOWN ");
				robot.lcdBoard().setBacklight(LCD_YELLOW);
			}
			if (buttons & BUTTON_LEFT)
			{
				robot.lcdBoard().print("LEFT ");
				robot.lcdBoard().setBacklight(LCD_GREEN);
			}
			if (buttons & BUTTON_RIGHT)
			{
				robot.lcdBoard().print("RIGHT ");
				robot.lcdBoard().setBacklight(LCD_TEAL);
			}
			if (buttons & BUTTON_SELECT)
			{
				robot.lcdBoard().print("SELECT ");
				robot.lcdBoard().setBacklight(LCD_VIOLET);
			}
		}
	}

	usleep(1000000);
	robot.lcdBoard().setBacklight(LCD_BLUE);
	robot.lcdBoard().clear();
	usleep(1000000);

	robot.stop();

	logger().info() << "End of RobotTest." << utils::end;
}

