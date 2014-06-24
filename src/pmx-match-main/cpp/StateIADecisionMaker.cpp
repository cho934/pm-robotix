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
pmx::StateIADecisionMaker::execute(Robot&robot, void *data) {
	//IAutomateState* result;

	pmx::Data* sharedData = (pmx::Data*) data;

	//detection adversaire
	robot.irSensorsGroup().startTimer();

	//launch IA
	ia_start();

	robot.irSensorsGroup().stopTimer();

	setPWM(0, 0);
	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		printf("sharedData->end90s=%d time=%f\n", sharedData->end90s(), robot.chronometerRobot().getElapsedTimeInSec());
		usleep(300000);
	}

	setPWM(0, 0);
	setPWM(0, 0);

	return NULL;
}
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

void pmx::StateIADecisionMaker::IASetupTableTest() {
	logger().debug() << "IASetupTableTest" << utils::end;

	ia_createZone("depart", 0, 0, 450, 800, 400, 520, 0);
	ia_createZone("zoneT2", 200, 1000, 400, 400, 400, 850, 90);
	ia_createZone("zoneT3", 800, 1200, 200, 400, 1000, 1350, 0);
	ia_createZone("zoneB1", 500, 600, 400, 400, 750, 600, -90);
	ia_createZone("zonePoseP", 1100, 0, 400, 400, 1100, 400, -90);
	ia_createZone("zoneT1", 800, 500, 200, 200, 500, 600, 0);

	ia_setPath("depart", "zoneT2", 400, 800);
	ia_setPath("depart", "zoneT3", 500, 600);
	ia_setPath("depart", "zoneB1", 500, 600);
	ia_setPath("depart", "zonePoseP", 1100, 690);
	ia_setPath("depart", "zoneT1", 500, 600);

	ia_setPath("zoneT2", "zoneT3", 800, 1350);
	ia_setPath("zoneT2", "zoneB1", 500, 600);
	ia_setPath("zoneT2", "zonePoseP", 1100, 690);
	ia_setPath("zoneT2", "zoneT1", 500, 600);

	ia_setPath("zoneT3", "zoneB1", 300, 900);
	ia_setPath("zoneT3", "zonePoseP", 300, 900);
	ia_setPath("zoneT3", "zoneT1", 500, 600);

	ia_setPath("zoneB1", "zonePoseP", 1000, 600);
	ia_setPath("zoneB1", "zoneT1", 500, 600);

	ia_setPath("zonePoseP", "zoneT1", 1000, 600);

	ia_addAction("pousserT2", &pousserT2);
	ia_addAction("pousserT3", &pousserT3);
	ia_addAction("pousserT1", &pousserT1);
	ia_addAction("poseP", &poseP);
	ia_addAction("tirSurB1", &tirSurB1);

}
void pmx::StateIADecisionMaker::IASetupHomologation() {
	logger().debug() << "IASetupHomologation" << utils::end;
	ia_createZone("depart", 0, 0, 450, 800, 400, 520, 0);
	ia_createZone("zoneT2", 200, 1000, 400, 400, 400, 850, 90);
	ia_createZone("zoneT3", 800, 1200, 200, 400, 1000, 1350, 0);
	ia_createZone("zoneB1", 500, 600, 400, 400, 750, 600, -90);
	ia_createZone("zonePoseP", 1350, 0, 400, 400, 1350, 400, -90);
	ia_createZone("zoneT1", 800, 500, 200, 200, 500, 600, 0);

	ia_setPath("depart", "zoneT2", 400, 800);
	ia_setPath("depart", "zoneT3", 500, 600);
	ia_setPath("depart", "zoneB1", 500, 600);
	ia_setPath("depart", "zonePoseP", 1100, 690);
	ia_setPath("depart", "zoneT1", 500, 600);

	ia_setPath("zoneT2", "zoneT3", 800, 1350);
	ia_setPath("zoneT2", "zoneB1", 500, 600);
	ia_setPath("zoneT2", "zonePoseP", 1100, 690);
	ia_setPath("zoneT2", "zoneT1", 500, 600);

	ia_setPath("zoneT3", "zoneB1", 300, 900);
	ia_setPath("zoneT3", "zonePoseP", 300, 900);
	ia_setPath("zoneT3", "zoneT1", 500, 600);

	ia_setPath("zoneB1", "zonePoseP", 1100, 600);
	ia_setPath("zoneB1", "zoneT1", 500, 600);

	ia_setPath("zonePoseP", "zoneT1", 1100, 600);

	ia_addAction("pousserT2", &pousserT2);
	ia_addAction("pousserT3", &pousserT3);
	ia_addAction("pousserT1", &pousserT1);
	ia_addAction("poseP", &poseP);
	ia_addAction("tirSurB1", &tirSurB1);

}

void pmx::StateIADecisionMaker::IASetupMatches() {
	logger().debug() << "IASetupMatches" << utils::end;
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
}
