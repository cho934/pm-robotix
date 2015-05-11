/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "StateIADecisionMaker.hpp"

#include <unistd.h>
#include <cstdio>

#include "../../common/c/ccbase.h"
#include "../../common/c/ia.h"
#include "../../common/c/motion.h"
#include "../../common/c/path_manager.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Chronometer.hpp"
#include "../../common/cpp/IrSensorsGroup.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxlObject.hpp"
#include "Data.hpp"

pmx::IAutomateState*
pmx::StateIADecisionMaker::execute(Robot&robot, void *data)
{
	pmx::StateIADecisionMaker::logger().info() << "execute" << utils::end;

	//IAutomateState* result;

	pmx::Data* sharedData = (pmx::Data*) data;
	TRAJ_STATE r;
	//detection adversaire
	robot.irSensorsGroup().startTimer();

	/*
	 //prendre balle et lever pince
	 robot.clamp().takeLeftElement();
	 //reculer de 2cm
	 robot.base().printPosition();
	 r = robot.base().move(-20);
	 robot.base().printPosition();

	 //reculer avec detection adverse jusqu'à B1
	 r = robot.base().movexyteta(1, 650, 1030, -155);
	 if (r != TRAJ_OK)
	 {
	 pmx::StateIADecisionMaker::logger().debug() << "==>TRAJ_COLLISION" << utils::end;
	 robot.base().printPosition();
	 return false;
	 }
	 robot.base().printPosition();

	 //prendre gobelet B1
	 r = robot.base().movexyteta(1, 830, 1130, -155);
	 if (r != TRAJ_OK)
	 {
	 pmx::StateIADecisionMaker::logger().debug() << "==>TRAJ_COLLISION" << utils::end;
	 robot.base().printPosition();
	 return false;
	 }
	 robot.base().printPosition();
	 */

	//sortir
	r = robot.base().movexyteta(0, 650, 1000, 0);
	if (r != TRAJ_OK)
	{
		//pmx::StateIADecisionMaker::logger().debug() << "==>TRAJ_COLLISION" << utils::end;
		robot.base().printPosition();
		return false;
	}
	robot.base().printPosition();

	//launch IA
	ia_start();

	robot.irSensorsGroup().stopTimer();

	robot.base().stop();
	robot.stopDevices();

	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		logger().info() << "sharedData->end90s=" << sharedData->end90s() << " time="
				<< robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
		robot.base().stop();
		usleep(300000);
	}

	robot.base().stop();
	robot.stop();

	return NULL;
}
/*
 int pousserT1() {

 pmx::Robot &robot = pmx::Robot::instance();
 pmx::StateIADecisionMaker::logger().debug() << "==>pousserT1" << utils::end;

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 TRAJ_STATE ts = cc_goToZone("zoneT1");
 if (ts != TRAJ_OK)
 return false;
 robot.base().printPosition();

 cc_setIgnoreRearCollision(false);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(0, 1000, 600, 0);

 return true;
 }

 int ii = 0;
 int pousserT2() {

 pmx::Robot &robot = pmx::Robot::instance();
 pmx::StateIADecisionMaker::logger().debug() << "==>pousserT2" << utils::end;

 if (ii <= 0) {
 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(true);
 robot.base().printPosition();
 if (cc_getMatchColor() == 0)
 robot.base().ArcRotate(90, 270); //TODO Modif du sens pour la couleur
 else
 robot.base().ArcRotate(-90, -270);

 ii++;
 }

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 cc_goToZone("zoneT2");
 robot.base().printPosition();

 //sortir le bras devant

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 TRAJ_STATE r = robot.base().movexyteta(0, 400, 1350, 0);
 if (r != TRAJ_OK) {
 pmx::StateIADecisionMaker::logger().debug() << "==>TRAJ_COLLISION" << utils::end;
 robot.base().printPosition();
 return false;
 }

 //rentrer le bras devant

 //si adversaire alors return false
 robot.base().printPosition();
 return true; //return true si ok sinon false si interruption
 }

 int pousserT3() {

 pmx::Robot &robot = pmx::Robot::instance();
 pmx::StateIADecisionMaker::logger().debug() << "==>pousserT3" << utils::end;

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 TRAJ_STATE ts = cc_goToZone("zoneT3");
 if (ts != TRAJ_OK)
 return false;
 robot.base().printPosition();

 //sortir bras droit si rouge
 if (!cc_getMatchColor()) {
 robot.servoDxlLeft().enable();
 robot.servoDxlLeft().turnMax();
 robot.servoDxlLeft().turnMax();
 robot.servoDxlLeft().freeMotion();
 } else {
 robot.servoDxlRight().enable();
 robot.servoDxlRight().turnMax();
 robot.servoDxlRight().turnMax();
 robot.servoDxlRight().freeMotion();
 }

 cc_setIgnoreRearCollision(false);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(1, 700, 1400, 0);
 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);

 if (ts != TRAJ_OK) {
 //rentre le bras
 if (!cc_getMatchColor()) {
 robot.servoDxlLeft().enable();
 robot.servoDxlLeft().turnMin();
 robot.servoDxlLeft().turnMin();
 robot.servoDxlLeft().freeMotion();
 } else {
 robot.servoDxlRight().enable();
 robot.servoDxlRight().turnMin();
 robot.servoDxlRight().turnMin();
 robot.servoDxlRight().freeMotion();
 }
 return false;
 }
 robot.base().printPosition();
 //rentrer bras droit si rouge
 if (!cc_getMatchColor()) {
 robot.servoDxlLeft().enable();
 robot.servoDxlLeft().turnMin();
 robot.servoDxlLeft().turnMin();
 robot.servoDxlLeft().freeMotion();
 } else {
 robot.servoDxlRight().enable();
 robot.servoDxlRight().turnMin();
 robot.servoDxlRight().turnMin();
 robot.servoDxlRight().freeMotion();
 }

 return true; //return true si ok sinon false si interruption
 }

 boolean tirSurB1() {

 pmx::Robot &robot = pmx::Robot::instance();
 pmx::StateIADecisionMaker::logger().debug() << "==>tirSurB1" << utils::end;
 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 TRAJ_STATE ts = cc_goToZone("zoneB1");
 if (ts != TRAJ_OK)
 return false;
 robot.base().printPosition();
 cc_rotateTo(-90);
 cc_rotateTo(-90);

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(0, cc_getRelativeX(cc_getX()), 480, -90);

 robot.base().printPosition();

 //tir des balles
 robot.servoDxlBallLaunch().enable();
 robot.servoDxlBallLaunch().turnMax();
 robot.servoDxlBallLaunch().turnMax();
 robot.servoDxlBallLaunch().freeMotion();

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(1, cc_getRelativeX(cc_getX()), 600, -90);

 return true;
 }

 boolean poseP() {

 pmx::Robot &robot = pmx::Robot::instance();
 pmx::StateIADecisionMaker::logger().debug() << "==>poseP" << utils::end;
 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(false);
 TRAJ_STATE ts = cc_goToZone("zonePoseP");
 if (ts != TRAJ_OK)
 return false;
 robot.base().printPosition();

 cc_setIgnoreRearCollision(true);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(0, cc_getRelativeX(cc_getX()), 140, -90);
 if (ts != TRAJ_OK)
 return false;
 robot.base().printPosition();

 //pose
 robot.servoDxlP6front().enable();
 robot.servoDxlP6front().turnMax();
 robot.servoDxlP6front().turnMax();
 robot.servoDxlP6front().turnMin();
 robot.servoDxlP6front().turnMin();

 //robot.servoDxlP6front().freeMotion();
 cc_setIgnoreRearCollision(false);
 cc_setIgnoreFrontCollision(true);
 ts = robot.base().movexyteta(1, cc_getRelativeX(cc_getX()), 400, -90);
 if (ts != TRAJ_OK)
 return false;
 return true;
 }

 boolean obj2() {
 //logger().debug() << "Start Chronometer" << utils::end;
 cc_goToZone("zone 2");
 return true;
 }
 */

int takeL1()
{
	TRAJ_STATE ts = TRAJ_INIT_NONE;
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "==> takeL1" << utils::end;

	cc_setIgnoreRearCollision(true);
	cc_setIgnoreFrontCollision(true);

	do
	{
		pmx::StateIADecisionMaker::logger().debug() << "==> goToZone(zoneL1)" << utils::end;
		ts = cc_goToZone("zoneL1");
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	pmx::StateIADecisionMaker::logger().debug() << "==> avancer sur L1 et le prendre" << utils::end;
	//avancer sur L1 et le prendre
	do
	{
		ts = robot.base().movexyteta(0, 760, 650, -90);
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	robot.clamp().readyToTakeLeftElement();
	robot.clamp().takeLeftElement();

	return true; //return true si ok sinon false si interruption
}

int takeR1R2()
{
	TRAJ_STATE ts = TRAJ_INIT_NONE;
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "==> takeR1R2" << utils::end;

	robot.base().printPosition();
	do
	{
		pmx::StateIADecisionMaker::logger().debug() << "==> goToZone(zoneR1R2)" << utils::end;
		ts = cc_goToZone("zoneR1R2");
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	//Prise du gobelet + R1
	do
	{
		ts = robot.base().movexyteta(0, 240, 300, -135);
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	robot.clamp().readyToTakeRightElement();
	robot.clamp().takeRightElement();

	//prise R2
	do
	{
		ts = robot.base().movexyteta(0, cc_getX(), cc_getY(), -45);
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	robot.clamp().readyToTakeRightElement();
	robot.clamp().takeRightElement();

	//1er clap
	do
	{
		ts = robot.base().movexyteta(0, cc_getX(), cc_getY(), -45);
	} while (ts != TRAJ_OK);
	robot.base().printPosition();
	if (robot.myColor() == pmx::PMXGREEN)
		robot.servoDxlLeft().turnMax();
	if (robot.myColor() == pmx::PMXYELLOW)
		robot.servoDxlRight().turnMax();

//2ème clap
	do
	{
		ts = robot.base().movexyteta(0, 850, 220, 90);
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	//recalage
	do
	{
		ts = robot.base().movexyteta(1, 850, 120, 90); //128?
	} while (ts != TRAJ_OK);
	robot.base().printPosition();
	cc_setPosition(850.0, 0.0, 90.0, cc_getMatchColor());
	do
	{
		ts = robot.base().movexyteta(0, 850, 200, 45); //128?
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	//take R3
	do
	{
		ts = robot.base().movexyteta(0, 1000, 300, 90); //128?
	} while (ts != TRAJ_OK);
	robot.base().printPosition();

	//depose R

	return true; //return true si ok sinon false si interruption
}

void pmx::StateIADecisionMaker::IASetupHomologation()
{
	logger().debug() << "IASetupHomologation" << utils::end;

	ia_createZone("depart", 0, 800, 400, 400, 0, 1000, 180);
	ia_createZone("zoneL1", 850, 600, 100, 100, 790, 858, -90);
	ia_createZone("zoneR1R2", 0, 0, 400, 400, 280, 550, -90);

	ia_setPath("depart", "zoneL1", 790, 860);
	ia_setPath("depart", "zoneR1R2", 600, 600);

	ia_setPath("zoneL1", "zoneR1R2", 600, 550);

	ia_addAction("takeL1", &takeL1);
	ia_addAction("takeR1R2", &takeR1R2);

}

void pmx::StateIADecisionMaker::IASetupTableTest()
{
	logger().debug() << "IASetupTableTest" << utils::end;

	ia_createZone("depart", 0, 800, 400, 400, 0, 1000, 180);
	ia_createZone("zoneL1", 850, 600, 100, 100, 760, 860, -90);
	//ia_createZone("zoneR1R2", 0, 0, 400, 400, 400, 550, -120);
	ia_createZone("zoneR1R2", 0, 0, 400, 400, 370, 400, -135);

	ia_setPath("depart", "zoneL1", 770, 860);
	ia_setPath("depart", "zoneR1R2", 600, 600);

	ia_setPath("zoneL1", "zoneR1R2", 600, 600);

	ia_addAction("takeL1", &takeL1);
	ia_addAction("takeR1R2", &takeR1R2);

}

void pmx::StateIADecisionMaker::IASetupMatches()
{
	logger().debug() << "IASetupMatches" << utils::end;
	/*
	 ia_createZone("depart", 0, 0, 400, 690, 400, 520, 0);
	 ia_createZone("zoneT2", 200, 1000, 400, 400, 400, 850, 90);
	 ia_createZone("zoneT3", 800, 1200, 200, 400, 1000, 1400, 0);
	 ia_createZone("zoneB1", 500, 600, 400, 400, 750, 600, -90);

	 ia_setPath("depart", "zoneT2", 400, 650);
	 ia_setPath("depart", "zoneT3", 500, 600);
	 ia_setPath("depart", "zoneB1", 500, 600);
	 ia_setPath("zoneT2", "zoneT3", 800, 1350);
	 ia_setPath("zoneT2", "zoneB1", 500, 600);
	 ia_setPath("zoneT3", "zoneB1", 750, 900);
	 ia_setPath("zoneT3", "zoneT2", 800, 1350);

	 ia_addAction("pousserT2", &pousserT2);
	 ia_addAction("pousserT3", &pousserT3);
	 ia_addAction("tirSurB1", &tirSurB1);

	 //ia_addAction("objectif 1", &obj1);

	 */
}
