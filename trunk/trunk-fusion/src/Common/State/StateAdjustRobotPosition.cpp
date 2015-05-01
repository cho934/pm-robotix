/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 */

#include "StateAdjustRobotPosition.hpp"

#include "../../Log/Logger.hpp"
#include "Data.hpp"

IAutomateState*
StateAdjustRobotPosition::execute(Robot& robot, void *data)
{
	IAutomateState* result;

	this->logger().info() << "start" << logs::end;

	Data* sharedData = (Data*) data;

	/*
	 if (!sharedData->skipSetup())
	 {
	 robot.lcdBoard().setBacklight(LCD_ON);
	 robot.lcdBoard().clear();
	 robot.lcdBoard().print("PMX...Adjust Position !");
	 }

	 logger().debug() << "Adjust position in the correct board..." << utils::end;

	 logger().debug() << "Color=" << robot.myColor() << " cc_getMatchColor()=" << cc_getMatchColor() << utils::end;


	 robot.position().x(130);
	 robot.position().y(570, robot.myColor());
	 robot.position().angle(0, robot.myColor());


	 cc_setPosition(130, 465, 0.0, cc_getMatchColor());

	 logger().debug() << "codeurs ext: robot_getLeftExternalCounter=" << robot_getLeftExternalCounter() << " robot_getRightExternalCounter=" << robot_getRightExternalCounter() << " a="
	 << utils::end;


	 //Ecriture dans le SVG
	 utils::SvgWriter::writePosition(cc_getX(), cc_getY(), cc_getTheta(), utils::SVG_POS_ROBOT);

	 //skip setup
	 if (!sharedData->skipSetup())
	 {

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
	 */
	logger().debug() << "Position adjusted." << logs::end;

	result = this->getState("next");

	return result;
}
