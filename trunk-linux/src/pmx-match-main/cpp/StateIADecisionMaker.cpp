/*!
 * \file
 * \brief Implémentation de la classe StateIADecisionMaker.
 */

#include "StateIADecisionMaker.hpp"

#include "../../common/c/ccbase.h"
//#include "../../common/c/global.h"
#include "../../common/c/ia.h"
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

int obj1()
{
	pmx::StateIADecisionMaker::logger().debug() << "obj1" << utils::end;
	cc_goToZone("zone 1");

	pmx::Robot &robot = pmx::Robot::instance();

	//cc_moveTo(80.0f);
	//si adversaire alors return false

	//cc_rotateLeft(90);

	//lancer les balles

	return TRUE; //return true si ok sinon autre chose
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

	ia_addAction("objectif 1", &obj1);
	ia_addAction("objectif 2", &obj2);

}
void pmx::StateIADecisionMaker::IASetupHomologation()
{
	logger().debug() << "IASetupHomologation" << utils::end;


}

void pmx::StateIADecisionMaker::IASetupMatches()
{
	logger().debug() << "IASetupMatches" << utils::end;



}
