/*!
 * \file
 * \brief Implémentation de la classe StateWaitForReboot.
 */

#include "../Common/State/StateWaitForReboot.hpp"

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Action/ButtonBar.hpp"
#include "../Common/Action/LedBar.hpp"
#include "../Common/Action.Driver/AButtonDriver.hpp"
#include "../Common/Action.Driver/ALedDriver.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"

IAutomateState*
StateWaitForReboot::execute(Robot& r, void *data)
{
	logger().info() << "Start 1" << logs::end;
	Data* sharedData = (Data*) data;
	//SRobotExtended *robot = (SRobotExtended*) &r;
	SRobotExtended& robot = dynamic_cast<SRobotExtended&>(r);

	robot.actions.start(); //TODO impossible de déplacer dans Robot.cpp

	if (!sharedData->skipSetup())
	{
		logger().debug() << "startBlink" << logs::end;
		//robot.actions.ledBar().blink(3, 500000, LED_RED);
		robot.actions.ledBar().startBlink(1000, 50000, LED_GREEN, 0);

		logger().info() << "Please press SELECT..." << logs::end;
		robot.actions.buttonBar().waitPressed(BUTTON_ENTER_KEY);

		robot.actions.ledBar().stopAndWait(true);

	}

	/*

	 try
	 {
	 char currentPath[PATH_MAX];
	 getcwd(currentPath, PATH_MAX);

	 robot.configure("pmx.conf.txt");
	 logger().info() << "Current directory:" << currentPath << " : Configuration 'pmx.conf.txt' loaded."
	 << utils::end;
	 } catch (utils::ConfigurationException* exception)
	 {
	 logger().error() << "Error in the configuration file" << utils::end;
	 logger().error() << "Message: " << exception->what() << utils::end;
	 std::cerr << "Error !! " << exception->what() << std::endl;

	 robot.stop();
	 printf("StateWaitForReboot EXIT\n");
	 exit(60);
	 }

	 //skip setup
	 pmx::Data* sharedData = (pmx::Data*) data;
	 if(sharedData->skipSetup())
	 return this->getState("next");

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
	 }
	 }
	 }

	 robot.ledBar().startReset();
	 robot.ledBar().stopAndWait(true);
	 */

	//robot.actions.ledBar();
	robot.actions.ledBar().resetAll();

	return this->getState("next");
}
