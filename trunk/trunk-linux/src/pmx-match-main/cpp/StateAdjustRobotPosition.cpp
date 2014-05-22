/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 */

#include <cmath>
#include "StateWaitForStart.hpp"
#include "StateWaitForReboot.hpp"
#include "StateInitialize.hpp"
#include "StateAdjustRobotPosition.hpp"
#include "Robot.hpp"

pmx::IAutomateState*
pmx::StateAdjustRobotPosition::execute(Robot& robot, void *)
{
	IAutomateState* result;

	this->logger().info() << "start" << utils::end;
	//pmx::Data* sharedData = (pmx::Data*) data;

	robot.lcdBoard().setBacklight(LCD_ON);
	robot.lcdBoard().clear();
	robot.lcdBoard().print("PMX...Adjust Position !");

	logger().debug() << "Adjust position in the correct board..." << utils::end;

	logger().debug() << "Color=" << robot.myColor() << utils::end;

	/*
	 robot.position().x(130);
	 robot.position().y(600, robot.myColor());
	 robot.position().angle(0, robot.myColor());


	 logger().debug() << "Position x=" << robot.position().x() << " y=" << robot.position().y() << " a="
	 << robot.position().angle() << utils::end;


	 //Ecriture dans le SVG
	 utils::SvgWriter::writePosition(robot.position().x(), robot.position().y(), robot.position().angle(),
	 utils::SVG_POS_ROBOT);
	 */

	logger().info() << "=> Clic SELECT..." << utils::end;
	robot.lcdBoard().setCursor(0, 1);
	robot.lcdBoard().print("Clic SELECT...");
	robot.ledBar().startK2Mil(50000, 50000, false);
	//wait
	uint8_t buttons = 0;
	while (!(buttons & BUTTON_SELECT))
	{
		buttons = robot.lcdBoard().readButtons();
		if (buttons)
		{
			if (buttons & BUTTON_SELECT)
			{
				robot.lcdBoard().clear();
				robot.lcdBoard().setCursor(0, 0);
				robot.lcdBoard().print("NEXT ");
				//robot.lcdBoard().setBacklight(LCD_OFF);
			}
		}
	}

	robot.ledBar().startReset();
	robot.ledBar().stopAndWait(true);

	logger().debug() << "Position adjusted." << utils::end;

	result = this->getState("next");

	return result;
}
