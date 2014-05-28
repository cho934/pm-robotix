/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "StateIADecisionMaker.hpp"

#include <math.h>

#include "../../common/c/ccbase.h"
#include "../../common/c/ia.h"
#include "../../common/cpp/Base.hpp"
#include "../../common/cpp/Logger.hpp"
#include "../../common/cpp/Robot.hpp"

pmx::IAutomateState*
pmx::StateIADecisionMaker::execute(Robot&, void *)
{
	//IAutomateState* result;

	//launch IA
	ia_start();

	return NULL;
}

int pousserT2()
{
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "pousserT2" << utils::end;
	robot.base().ArcRotate(-90, -270); //TODO Modif du sens pour la couleur
	robot.base().printPosition();
	cc_goToZone("zoneT2");
	robot.base().printPosition();

	//sortir le bras devant

	robot.base().movexyteta(0, 400, 1350, 0);

	//rentrer le bras devant

	//si adversaire alors return false

	return TRUE; //return true si ok sinon false si interruption
}

int pousserT3()
{
	pmx::Robot &robot = pmx::Robot::instance();
	pmx::StateIADecisionMaker::logger().debug() << "pousserT3" << utils::end;
	cc_goToZone("zoneT3");
	robot.base().printPosition();

	//robot.base().movexyteta(0, 1000, 1350, 0);
	//robot.base().printPosition();

	//sortir bras droit si rouge
	robot.base().movexyteta(1, 700, 1350, 0);
	robot.base().printPosition();
	//rentrer bras droit si rouge

	return TRUE; //return true si ok sinon false si interruption
}

boolean obj2()
{
	//logger().debug() << "Start Chronometer" << utils::end;
	cc_goToZone("zone 2");
	return TRUE;
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
	ia_createZone("zoneT2", 200, 1000, 400, 200, 400, 850, 90);
	ia_createZone("zoneT3", 800, 1200, 200, 400, 1100, 1350, 0);

	ia_setPath("depart", "zoneT2", 400, 850);
	ia_setPath("depart", "zoneT3", 500, 500);
	ia_setPath("zoneT2", "zoneT3", 800, 1350);

	ia_addAction("pousserT2", &pousserT2);
	ia_addAction("pousserT3", &pousserT3);

}

void pmx::StateIADecisionMaker::IASetupMatches()
{
	logger().debug() << "IASetupMatches" << utils::end;
	ia_createZone("depart", 0, 0, 100, 100, 100, 100, 0);
	ia_createZone("zone 1", 300, 0, 100, 100, 300, 200, 0);

	ia_setPath("depart", "zone 1", 200, 0);

	//ia_addAction("objectif 1", &obj1);
}
