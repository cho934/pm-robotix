/*!
 * \file
 * \brief Implémentation de la classe StateWaitForStart.
 */

#include "../Common/State/StateWaitForStart.hpp"

#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/State/Data.hpp"
#include "../Common/State/Wait90SecondsAction.hpp"
#include "../Log/Logger.hpp"

IAutomateState*
StateWaitForStart::execute(Robot& r, void *data)
{
	logger().info() << "start 4" << logs::end;

	Data* sharedData = (Data*) data;
	//SRobotExtended *robot = (SRobotExtended*) &r;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);
	IAutomateState* result = NULL;

	if (!sharedData->skipSetup())
	{
		int col;
		if (robot.getMyColor() == PMXYELLOW)
		{
			robot.actions.ledBar().setOff(1);
			robot.actions.ledBar().set(0, LED_ORANGE);
			col = LED_ORANGE;
		}
		if (robot.getMyColor() == PMXGREEN)
		{
			robot.actions.ledBar().setOff(0);
			robot.actions.ledBar().set(1, LED_GREEN);
			col = LED_GREEN;
		}
		//lance le clignotement
		robot.actions.ledBar().startAlternate(9000, 100000, 0x03, 0x00, col, 0);

		logger().info() << "Please put the TIRETTE" << logs::end;
		robot.actions.tirette().waitPressed();
		logger().info() << "Wait for TIRETTE" << logs::end;
		robot.actions.tirette().waitUnpressed();

		if (robot.actions.buttonBar().pressed(BUTTON_DOWN_KEY))
		{
			robot.actions.ledBar().stopAndWait(true);
			return this->getState("rebootInitialize");
		}
	}
	else
	{
		logger().info() << "skipSetup..." << logs::end;

	}
	robot.actions.ledBar().stopAndWait(true);

	if (robot.getMyColor() == PMXNOCOLOR)
	{
		robot.actions.ledBar().set(0, LED_RED);
		robot.actions.ledBar().set(1, LED_RED);
	}
	if (robot.getMyColor() == PMXYELLOW)
	{
		robot.actions.ledBar().setOff(1);
		robot.actions.ledBar().set(0, LED_ORANGE);
	}
	if (robot.getMyColor() == PMXGREEN)
	{
		robot.actions.ledBar().setOff(0);
		robot.actions.ledBar().set(1, LED_GREEN);
	}

	/*
	 //skip setup
	 if (!sharedData->skipSetup()) {

	 robot.lcdBoard().setBacklight(LCD_ON);
	 robot.lcdBoard().clear();
	 robot.lcdBoard().print("PMX...");
	 if (robot.myColor() == pmx::PMXYELLOW) {
	 robot.lcdBoard().print("YELLOW");
	 } else if (robot.myColor() == pmx::PMXRED) {
	 robot.lcdBoard().print("RED");
	 }
	 robot.lcdBoard().setCursor(0, 1);
	 robot.lcdBoard().print("Wait for Start !");

	 //GPIOBOARD
	 robot.gpioBoard().setOnP0(0);

	 robot.ledBar().startAlternate(100000, 100000, 0x81, 0x3C, false);
	 //wait
	 uint8_t buttons = 0;
	 int in7 = 0;
	 in7 = robot.gpioBoard().getValueP1(7);
	 while (in7) //TODO ou pas de tir de ficelle
	 {
	 in7 = robot.gpioBoard().getValueP1(7);
	 buttons = robot.lcdBoard().readButtons();
	 //logger().info() << "in7=" << in7 << utils::end;
	 if (buttons) {
	 robot.ledBar().startReset();
	 robot.ledBar().stop(true);
	 ia_clear();
	 return this->getState("rebootInitialize");
	 }
	 usleep(200000);
	 }

	 robot.lcdBoard().clear();
	 robot.lcdBoard().print("PMX...GO GO GO !");

	 robot.ledBar().startReset();
	 robot.ledBar().stop(true);
	 robot.gpioBoard().setOffP0(0);
	 usleep(500000);

	 robot.lcdBoard().setBacklight(LCD_OFF);
	 }
	 */
	logger().info() << "Start Chronometer" << logs::end;
	//démarrage du chrono
	robot.chrono().start();

	//lancement de l'etape Wait90Seconds
	Wait90SecondsAction* action = new Wait90SecondsAction(robot, (void *) sharedData);

	action->start("Wait90SecondsAction");

	result = this->getState("decisionMaker");

	return result;
}
