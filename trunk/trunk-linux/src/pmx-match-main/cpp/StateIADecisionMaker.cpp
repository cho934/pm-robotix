/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "StateIADecisionMaker.hpp"

//#include <math.h>
#include <unistd.h>

#include "../../common/c/ccbase.h"
#include "../../common/c/ia.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"
#include "../../common/cpp/ServoMotorDxlObject.hpp"
#include "Data.hpp"

pmx::IAutomateState*
pmx::StateIADecisionMaker::execute(Robot&robot, void *data)
{
	//IAutomateState* result;

	pmx::Data* sharedData = (pmx::Data*) data;

	//launch IA
	ia_start();

	//wait the execution Wait90
	while (!sharedData->end90s() )//&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		printf("sharedData->end90s=%d time=%f\n", sharedData->end90s(), robot.chronometerRobot().getElapsedTimeInSec());
		usleep(300000);
	}

	return NULL;
}

int pousserT2()
{
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "==>pousserT2" << utils::end;

	robot.base().printPosition();
	if (cc_getMatchColor() == 0)
		robot.base().ArcRotate(90, 270); //TODO Modif du sens pour la couleur
	else
		robot.base().ArcRotate(-90, -270);

	//cc_goToZone("zoneT2");
	robot.base().printPosition();

	//sortir le bras devant

	robot.base().movexyteta(0, 400, 1350, 0);

	//rentrer le bras devant

	//si adversaire alors return false

	return true; //return true si ok sinon false si interruption
}

int pousserT3()
{
	printf("TEST0001\n");
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "==>pousserT3" << utils::end;
	printf("TEST0002\n");
	cc_goToZone("zoneT3");
	printf("TEST0003\n");
	robot.base().printPosition();
	printf("TEST0004\n");

	//robot.base().movexyteta(0, 1000, 1350, 0);
	//robot.base().printPosition();

	//sortir bras droit si rouge
	if (!cc_getMatchColor())
	{
		robot.servoDxlLeft().enable();
		robot.servoDxlLeft().turnMax();
		robot.servoDxlLeft().freeMotion();
	}
	else
	{
		robot.servoDxlRight().enable();
		robot.servoDxlRight().turnMax();
		robot.servoDxlRight().freeMotion();
	}

	robot.base().movexyteta(1, 700, 1350, 0);
	robot.base().printPosition();
	//rentrer bras droit si rouge
	if (!cc_getMatchColor())
	{
		robot.servoDxlLeft().enable();
		robot.servoDxlLeft().turnMin();
		robot.servoDxlLeft().freeMotion();
	}
	else
	{
		robot.servoDxlRight().enable();
		robot.servoDxlRight().turnMin();
		robot.servoDxlRight().freeMotion();
	}

	return true; //return true si ok sinon false si interruption
}

boolean tirSurB1()
{
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "==>tirSurB1" << utils::end;
	cc_goToZone("zoneB1");
	robot.base().printPosition();
	cc_rotateTo(-90);

	//tir des balles
	robot.servoDxlBallLaunch().enable();
	robot.servoDxlBallLaunch().turnMax();
	robot.servoDxlBallLaunch().turnMax();
		robot.servoDxlBallLaunch().freeMotion();

	return true;
}

boolean obj2()
{
	//logger().debug() << "Start Chronometer" << utils::end;
	cc_goToZone("zone 2");
	return true;
}

void pmx::StateIADecisionMaker::IASetupTableTest()
{
	logger().debug() << "IASetupTableTest" << utils::end;

	ia_createZone("depart", 0, 0, 100, 100, 100, 100, 0);
	ia_createZone("zone 1", 300, 600, 100, 100, 400, 600, 180);
	ia_createZone("zone 2", 800, 500, 200, 200, 700, 600, 0);

	ia_setPath("depart", "zone 1", 500, 600);
	ia_setPath("depart", "zone 2", 500, 600);
	ia_setPath("zone 1", "zone 2", 500, 600);
	ia_setPath("zone 2", "zone 1", 500, 600);

	//ia_addAction("objectif 1", &obj1);
	ia_addAction("objectif 2", &obj2);

}
void pmx::StateIADecisionMaker::IASetupHomologation()
{
	logger().debug() << "IASetupHomologation" << utils::end;
	ia_createZone("depart", 0, 0, 400, 690, 400, 520, 0);
	ia_createZone("zoneT2", 200, 1000, 400, 400, 400, 850, 90);
	ia_createZone("zoneT3", 800, 1200, 200, 400, 1000, 1400, 0);
	ia_createZone("zoneB1", 500, 600, 400, 400, 670, 600, -90);

	ia_setPath("depart", "zoneT2", 400, 650);
	ia_setPath("depart", "zoneT3", 500, 600);
	ia_setPath("depart", "zoneB1", 500, 600);
	ia_setPath("zoneT2", "zoneT3", 800, 1350);
	ia_setPath("zoneT2", "zoneB1", 500, 600);
	ia_setPath("zoneT3", "zoneB1", 500, 600);

	ia_addAction("pousserT2", &pousserT2);
	ia_addAction("pousserT3", &pousserT3);
	ia_addAction("tirSurB1", &tirSurB1);

}

void pmx::StateIADecisionMaker::IASetupMatches()
{
	logger().debug() << "IASetupMatches" << utils::end;
	ia_createZone("depart", 0, 0, 100, 100, 100, 100, 0);
	ia_createZone("zone 1", 300, 0, 100, 100, 300, 200, 0);

	ia_setPath("depart", "zone 1", 200, 0);

	//ia_addAction("objectif 1", &obj1);
}
