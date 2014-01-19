/*!
 * \file
 * \brief Implémentation de la classe Elevator (Ascenceur).
 */

#include "Elevator.hpp"
#include "Robot.hpp"
#include "Macro.hpp"

pmx::Elevator::Elevator(pmx::Robot & robot, ushort dm, ushort pinactive, ushort pinway)
: ARobotElement(robot), dm_(dm), pinActive_(pinactive), pinWay_(pinway), actionStopped_(0)
{
}

pmx::ElevatorAction::ElevatorAction(pmx::Elevator & elevator, pmx::ElevatorActionName action)
: elevator_(elevator), action_(action), mode_(0), time_(0)
{
}

bool pmx::ElevatorAction::execute(IRobotOut * out)
{
    if (elevator_.stop())
    {
        return !elevator_.stop(); //l'action se supprime.
    }

    switch (this->action_)
    {
        case pmx::ELEVATORGOHIGH:
            out->setValue(elevator_.dm(), elevator_.pinWay(), false);
            out->setValue(elevator_.dm(), elevator_.pinActive(), true);
            elevator_.state(pmx::ELEVATORHIGH);
            return false; //renvoi 0 pour supprimer l'action
            break;
        case pmx::ELEVATORGOLOW:
            out->setValue(elevator_.dm(), elevator_.pinWay(), true);
            out->setValue(elevator_.dm(), elevator_.pinActive(), true);
            elevator_.state(pmx::ELEVATORLOW);
            return false; //renvoi 0 pour supprimer l'action
            break;
        case pmx::ELEVATORGOMIDDLE:
            if (mode_ == 0)
            {
                if(elevator_.state() == pmx::ELEVATORHIGH)
                {
                    //on descend
                    out->setValue(elevator_.dm(), elevator_.pinWay(), true);
                    out->setValue(elevator_.dm(), elevator_.pinActive(), true);
                    time_ = 1500000;
                }else
                {
                    //on monte
                    out->setValue(elevator_.dm(), elevator_.pinWay(), false);
                    out->setValue(elevator_.dm(), elevator_.pinActive(), true);
                    time_ = 1500000;
                }
                this->chrono_.start();
                mode_ = 1;
                return true;
            }
            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= time_)
            {
                //arret au milieu apres un temps defini
                out->setValue(elevator_.dm(), elevator_.pinActive(), false);
                out->setValue(elevator_.dm(), elevator_.pinWay(), false);
                mode_ = 0;
                elevator_.state(pmx::ELEVATORMIDDLE);
                return false;
            }
            return true;
            break;
        case pmx::ELEVATORNOPOSITION:
            out->setValue(elevator_.dm(), elevator_.pinActive(), false);
            out->setValue(elevator_.dm(), elevator_.pinWay(), false);
             break;
        case pmx::ELEVATORGOLITTLE:
            if (mode_ == 0)
            {
                if(elevator_.state() == pmx::ELEVATORHIGH)
                {
                    //on descend
                    out->setValue(elevator_.dm(), elevator_.pinWay(), true);
                    out->setValue(elevator_.dm(), elevator_.pinActive(), true);
                    time_ = 2500000;
                }else if(elevator_.state() == pmx::ELEVATORLOW)
                {
                    //on monte
                    out->setValue(elevator_.dm(), elevator_.pinWay(), false);
                    out->setValue(elevator_.dm(), elevator_.pinActive(), true);
                    time_ = 580000; //temps de montée de l'ascenseur
                }
                this->chrono_.start();
                mode_ = 1;
                return true;
            }
            if (mode_ == 1 && chrono_.getElapsedTimeInMicroSec() >= time_)
            {
                //arret au milieu apres un temps defini
                out->setValue(elevator_.dm(), elevator_.pinActive(), false);
                out->setValue(elevator_.dm(), elevator_.pinWay(), false);
                mode_ = 0;
                elevator_.state(pmx::ELEVATORLITTLE);
                return false;
            }
            return true;
            break;
        default:
            break;

    }
    return false; //l'action se supprime.
}

void
pmx::Elevator::goHighPosition()
{
    this->robot().addAction(new pmx::ElevatorAction(*this, pmx::ELEVATORGOHIGH));
}

void
pmx::Elevator::goLowPosition()
{
    this->robot().addAction(new pmx::ElevatorAction(*this, pmx::ELEVATORGOLOW));
}

void
pmx::Elevator::goMiddlePosition()
{
    this->robot().addAction(new pmx::ElevatorAction(*this, pmx::ELEVATORGOMIDDLE));
}

void
pmx::Elevator::goLittlePosition()
{
    this->robot().addAction(new pmx::ElevatorAction(*this, pmx::ELEVATORGOLITTLE));
}

void
pmx::Elevator::noPosition()
{
    this->robot().addAction(new pmx::ElevatorAction(*this, pmx::ELEVATORNOPOSITION));
}
