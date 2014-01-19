/*!
 * \file
 * \brief Implémentation de la classe OpponentDetector (utilisation CMUCAM).
 * \deprecated
 */

#include "OpponentDetector.hpp"
#include "Robot.hpp"

pmx::OpponentDetector::OpponentDetector(pmx::Robot & robot, ushort m, ushort shortDist, ushort mediumDist, ushort leftSide, ushort rightSide)
: ARobotElement(robot), active_(false), listenerStopped_(false),m_(m),
        shortDist_(shortDist), mediumDist_(mediumDist), leftSide_(leftSide),
        rightSide_(rightSide), received_(false), imminenteCollision_(false)
{}

pmx::OpponentListener::OpponentListener(pmx::OpponentDetector & opponent)
: opponent_(opponent)
{}
int t=0;
bool pmx::OpponentListener::execute(IRobotIn * robotIn)
{
    t++;//detecte tous les 10fois
    if(t!=10){
        t=0;
        return ! opponent_.stop();
    }
    logger().debug() << "execute " << utils::end;
    if (opponent_.active() == true)
    {
        //opponent_.received(false);
        //int leftSide = robotIn->getValue(opponent_.m(), opponent_.leftSide());
        //int rightSide = robotIn->getValue(opponent_.m(), opponent_.rightSide());
        int shortDist = robotIn->getValue(opponent_.m(), opponent_.shortDist());

        if( shortDist)//leftSide && rightSide &&
        {
            opponent_.imminenteCollision(true);
        }else
        {
            opponent_.imminenteCollision(false);
        }
        //opponent_.received(true);
    }else
    {
        //usleep(100);
    }
    return ! opponent_.stop(); //renvoi 0 pour supprimer le listener
}


void
pmx::OpponentDetector::addOpponentListener()
{
    this->stop(false);
    this->active(true);
    this->robot().addListener(new pmx::OpponentListener(*this));
}

