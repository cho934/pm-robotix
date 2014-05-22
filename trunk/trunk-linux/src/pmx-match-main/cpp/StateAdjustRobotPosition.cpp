/*!
 * \file
 * \brief Implémentation de la classe StateAdjustRobotPosition.
 * \todo problème lorque l'on fait plusieurs cycles, la vitesse du robot
 * augmente !! En fait le timer SpeedManagerFusion ne s'execute plus tous les
 * 150ms mais plus rapidement. => momentanément corrigé (313) : a surveiller.
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

	logger().info() << "Adjust position in the correct board..." << utils::end;

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
	logger().info() << "Position adjusted." << utils::end;

	result = this->getState("next");

	return result;
}
