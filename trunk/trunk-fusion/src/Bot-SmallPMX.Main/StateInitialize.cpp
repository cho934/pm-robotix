/*!
 * \file
 * \brief Implémentation de la classe StateInitialize.
 */

#include "../Common/State/StateInitialize.hpp"

#include <unistd.h>

#include "../Bot-SmallPMX/SActionsExtended.hpp"
#include "../Bot-SmallPMX/SRobotExtended.hpp"
#include "../Common/Action/ButtonBar.hpp"
#include "../Common/Action/LedBar.hpp"
#include "../Common/Action.Driver/AButtonDriver.hpp"
#include "../Common/Action.Driver/ALedDriver.hpp"
#include "../Common/Robot.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"

class IAutomateState;

IAutomateState*
StateInitialize::execute(Robot& r, void *data)
{
	this->logger().info() << "start 2" << logs::end;
	Data* sharedData = (Data*) data;
	SRobotExtended* robot = (SRobotExtended*) &r;

	if (!sharedData->skipSetup())
	{

		logger().info() << "Please choose color..." << logs::end;
		while (!robot->actions.buttonBar().pressed(BUTTON_ENTER_KEY)
				|| robot->getMyColor() == PMXNOCOLOR)
		{
			if (robot->actions.buttonBar().pressed(BUTTON_RIGHT_KEY))
			{
				robot->setMyColor(PMXYELLOW);

				logger().debug() << "=> YELLOW..." << logs::end;
			}
			if (robot->actions.buttonBar().pressed(BUTTON_LEFT_KEY))
			{
				robot->setMyColor(PMXGREEN);
				logger().debug() << "=> GREEN..." << logs::end;
			}
			if (robot->actions.buttonBar().pressed(BUTTON_UP_KEY))
			{
				logger().debug() << "=> Initialize mechanical..." << logs::end;

				robot->actions.supportSystem().straighten(900, 1500);
				usleep(300000);
				robot->actions.supportSystem().incline(900, 1500);
				//pause avec le tracksystem
				robot->actions.trackSystem().moveForward(800, 0);
				//pause avec le redcarpetsystem
				robot->actions.redcarpetSystem().leftDeploy();
				robot->actions.redcarpetSystem().rightDeploy();
				robot->actions.trackSystem().stopMotor();
				//sleep(1);

				robot->actions.supportSystem().straighten(900, 1500);

			}
			if (robot->actions.buttonBar().pressed(BUTTON_BACK_KEY))
			{
				robot->actions.supportSystem().stopMotor();
				robot->actions.redcarpetSystem().releaseAll();
			}
			if (robot->actions.buttonBar().pressed(BUTTON_DOWN_KEY))
			{
				robot->actions.supportSystem().resetPosition(2);
				robot->actions.supportSystem().straighten(900, 1500);
			}

			if (robot->getMyColor() == PMXNOCOLOR)
			{
				robot->actions.ledBar().set(0, LED_RED);
				robot->actions.ledBar().set(1, LED_RED);
			}
			if (robot->getMyColor() == PMXYELLOW)
			{
				robot->actions.ledBar().setOff(1);
				robot->actions.ledBar().set(0, LED_ORANGE);
			}
			if (robot->getMyColor() == PMXGREEN)
			{
				robot->actions.ledBar().setOff(0);
				robot->actions.ledBar().set(1, LED_GREEN);
			}

			usleep(800);
		}

	}
	else
	{
		logger().info() << "skipSetup..." << logs::end;
		if (robot->getMyColor() == PMXNOCOLOR)
		{
			robot->actions.ledBar().set(0, LED_RED);
			robot->actions.ledBar().set(1, LED_RED);
		}
		if (robot->getMyColor() == PMXYELLOW)
		{
			robot->actions.ledBar().setOff(1);
			robot->actions.ledBar().set(0, LED_ORANGE);
		}
		if (robot->getMyColor() == PMXGREEN)
		{
			robot->actions.ledBar().setOff(0);
			robot->actions.ledBar().set(1, LED_GREEN);
		}
	}

	if (robot->getMyColor() == PMXGREEN)
		logger().info() << "color is : GREEN" << logs::end;
	if (robot->getMyColor() == PMXYELLOW)
		logger().info() << "color is : YELLOW" << logs::end;
	if (robot->getMyColor() == PMXNOCOLOR)
	{
		logger().error() << "color is : NOCOLOR" << logs::end;
		exit(0);
	}

	//bool error = false;
	/*
	 if (!sharedData->skipSetup()) {
	 robot.lcdBoard().setBacklight(LCD_ON);
	 robot.lcdBoard().clear();
	 robot.lcdBoard().print("PMX...Initialize !");
	 }

	 //skip setup
	 if (!sharedData->skipSetup()) {
	 logger().debug() << "Initialize color..." << utils::end;

	 //prise en compte de la couleur de match
	 logger().debug() << "=> Choose PMX COLOR..." << utils::end;
	 robot.lcdBoard().setCursor(0, 1);
	 robot.lcdBoard().print("COLOR ?");
	 robot.ledBar().startK2Mil(50000, 50000, false);

	 robot.myColorIs(pmx::PMXNOCOLOR);

	 //wait
	 uint8_t buttons = robot.lcdBoard().readButtons();
	 while (!(buttons & BUTTON_SELECT) || robot.myColor() == pmx::PMXNOCOLOR) {
	 buttons = robot.lcdBoard().readButtons();
	 if (buttons) {
	 if (buttons & BUTTON_LEFT) {
	 robot.lcdBoard().setCursor(0, 1);
	 robot.lcdBoard().print("COLOR YELLOW ");
	 robot.myColorIs(pmx::PMXYELLOW);
	 logger().info() << "=> YELLOW..." << utils::end;
	 }
	 if (buttons & BUTTON_RIGHT) {
	 robot.lcdBoard().setCursor(0, 1);
	 robot.lcdBoard().print("COLOR RED     ");
	 robot.myColorIs(pmx::PMXRED);
	 logger().info() << "=> RED..." << utils::end;
	 }
	 if (buttons & BUTTON_SELECT) {
	 logger().info() << "=> SELECT..." << utils::end;
	 //robot.lcdBoard().clear();
	 //robot.lcdBoard().setCursor(0, 0);
	 //robot.lcdBoard().print("NEXT ");
	 //robot.lcdBoard().setBacklight(LCD_OFF);
	 }
	 if (buttons & BUTTON_DOWN) {
	 logger().info() << "Initialize P4 P6..." << utils::end;

	 robot.servoDxlP6front().enable();
	 robot.servoDxlP6front().turnMin();
	 robot.servoDxlP6front().turnMin();

	 robot.servoDxlP4().enable();
	 robot.servoDxlP4().turnMin();
	 robot.servoDxlP4().turnMin();

	 robot.servoDxlP14().enable();
	 robot.servoDxlP14().turnMin();
	 robot.servoDxlP14().turnMin();

	 robot.servoDxlP6front().turnMax();
	 robot.servoDxlP6front().turnMax();
	 robot.servoDxlP6front().freeMotion();

	 logger().info() << "Initialize mechanical..." << utils::end;
	 robot.servoDxlP4().turnMax();
	 robot.servoDxlP4().turnMax();
	 robot.servoDxlP4().freeMotion();

	 robot.servoDxlLeft().enable();
	 robot.servoDxlLeft().turnMin();
	 robot.servoDxlLeft().turnMax();
	 robot.servoDxlLeft().turnMin();
	 robot.servoDxlLeft().freeMotion();

	 robot.servoDxlRight().enable();
	 robot.servoDxlRight().turnMin();
	 robot.servoDxlRight().turnMax();
	 robot.servoDxlRight().turnMin();
	 robot.servoDxlRight().freeMotion();

	 robot.servoDxlBallLaunch().enable();
	 robot.servoDxlBallLaunch().turnMin();
	 robot.servoDxlBallLaunch().turnMax();
	 robot.servoDxlBallLaunch().turnMin();
	 robot.servoDxlBallLaunch().freeMotion();

	 robot.servoDxlFiletLaunch().enable();
	 robot.servoDxlFiletLaunch().turnMin();
	 robot.servoDxlFiletLaunch().turnMax();
	 robot.servoDxlFiletLaunch().turnMin();
	 robot.servoDxlFiletLaunch().freeMotion();

	 logger().info() << "End Initialize mechanical." << utils::end;
	 }
	 if (buttons & BUTTON_UP) {
	 logger().info() << "Initialize mechanical..." << utils::end;
	 robot.servoDxlLeft().enable();
	 robot.servoDxlLeft().turnMin();
	 robot.servoDxlLeft().freeMotion();

	 robot.servoDxlRight().enable();
	 robot.servoDxlRight().turnMin();
	 robot.servoDxlRight().freeMotion();

	 robot.servoDxlBallLaunch().enable();
	 robot.servoDxlBallLaunch().turnMin();
	 robot.servoDxlBallLaunch().freeMotion();

	 robot.servoDxlFiletLaunch().enable();
	 robot.servoDxlFiletLaunch().turnMin();
	 robot.servoDxlFiletLaunch().freeMotion();

	 robot.servoDxlP14().enable();
	 robot.servoDxlP14().turnMin();
	 robot.servoDxlP14().turnMin();

	 robot.servoDxlP6front().enable();
	 robot.servoDxlP6front().turnMin();
	 robot.servoDxlP6front().freeMotion();

	 robot.servoDxlP4().enable();
	 robot.servoDxlP4().turnMin();
	 robot.servoDxlP4().freeMotion();

	 logger().info() << "End Initialize mechanical." << utils::end;
	 }
	 }
	 }


	 robot.ledBar().startReset();
	 robot.ledBar().stop(true);
	 logger().debug() << "End Initialize color." << utils::end;
	 }

	 if (robot.myColor() == pmx::PMXRED)
	 logger().info() << "color: RED" << utils::end;
	 if (robot.myColor() == pmx::PMXYELLOW)
	 logger().info() << "color: YELLOW" << utils::end;
	 if (robot.myColor() == pmx::PMXNOCOLOR) {
	 logger().error() << "color: NOCOLOR" << utils::end;
	 exit(0);
	 }

	 //Ajout des stratégies
	 if (robot.myRunningMode() == pmx::ROBOTMATCHES) {
	 logger().debug() << "ROBOTMATCHES" << utils::end;
	 //configure IA
	 sharedData->decisionMaker->IASetupMatches();
	 robot.lcdBoard().print("PMX MATCH GO !");
	 } else if (robot.myRunningMode() == pmx::ROBOTHOMOLOGATION) {
	 logger().debug() << "ROBOTHOMOLOGATION" << utils::end;
	 //configure IA
	 sharedData->decisionMaker->IASetupHomologation();

	 robot.lcdBoard().print("HOMOLOGATION GO !");
	 } else if (robot.myRunningMode() == pmx::ROBOTTABLETEST) {
	 logger().debug() << "ROBOTTABLETEST" << utils::end;
	 //configure IA
	 sharedData->decisionMaker->IASetupTableTest();
	 robot.lcdBoard().print("TABLE TEST GO !");
	 }
	 */
	return this->getState("next");
}
