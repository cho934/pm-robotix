/*!
 * \file
 * \brief Implémentation de la classe DistanceDetector.
 * \deprecated
 */

#include <cmath>
#include "DistanceDetector.hpp"
#include "Robot.hpp"

pmx::DistanceDetectorAction::DistanceDetectorAction(pmx::DistanceDetector & distanceDetector)
: distanceDetector_(distanceDetector)
{}

pmx::DistanceDetectorListener::DistanceDetectorListener(pmx::DistanceDetector & distanceDetector)
: distanceDetector_(distanceDetector)
{}

pmx::DistanceDetector::DistanceDetector(pmx::Robot & robot, ushort mu, ushort dm, ushort pin)
: ARobotElement(robot), active_(false), mu_(mu), dm_(dm), pin_(pin), distance_(0), distanceMm_(0), received_(false), activeListener_(false)
{
    logger().debug() << "DistanceDetector::DistanceDetector()" << utils::end;
}

bool pmx::DistanceDetectorAction::execute(IRobotOut * out)
{
    if (distanceDetector_.active() == true)
    {
        distanceDetector_.received(false);
        logger().debug() << "DistanceDetectorAction::active ok" << utils::end;
        out->setValue(distanceDetector_.dm(), distanceDetector_.pin(), true);
        out->setValue(distanceDetector_.dm(), distanceDetector_.pin(), false);
        
        distanceDetector_.active(false);
        //lancement de la récupération de la distance
        distanceDetector_.activeListener(true);
    }
    return true;
}

bool pmx::DistanceDetectorListener::execute(IRobotIn * robotIn)
{
    //TODO modifier l'activation comme sur le simplesensorListener
    if (distanceDetector_.activeListener() == true)
    {
        int valeur = robotIn->getValues(distanceDetector_.mu());
        logger().debug() << "DistanceDetectorListener:: val:" << valeur << utils::end;
        distanceDetector_.activeListener(false);
        
        distanceDetector_.distance(valeur); //0 à 255
        
        double distanceMillimetre = pow((valeur * 2.5 / 128.0), -1.1) * 270.0;
        distanceDetector_.distanceMm((int) distanceMillimetre);
        
        distanceDetector_.received(true);
    }
    return true;
}
