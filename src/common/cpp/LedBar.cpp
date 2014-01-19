/*!
 * \file
 * \brief Implémentation de la classe LedBar.
 */

#include "LedBar.hpp"
#include "LedIndicator.hpp"
#include "Robot.hpp"

pmx::LedBar::LedBar(pmx::Robot & robot, ushort dm)
: ARobotElement(robot), dm_(dm), actionStopped_(false), position_(0), status_(0), nb_(0)
{}

pmx::LedBarAction::LedBarAction(pmx::LedBar & ledBar, pmx::LedBarActionName action)
: ledBar_(ledBar), action_(action), lastTime_(0), i_(0), j_(1), inc_(true)
{
    chrono_.start();
}

bool pmx::LedBarAction::execute(IRobotOut * out)
{
    //logger().debug() << "execute()" << utils::end;

    switch(this->action_)
    {
        case pmx::LEDBARSET :
            out->setValue(ledBar_.dm(), ledBar_.position(), ledBar_.status());
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARRESET :
            out->setValues(ledBar_.dm(), 0);
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARFLASH :
            out->setValues(ledBar_.dm(), 255);
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARBLINK :

            if(chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 50000)
            {
                out->setValues(ledBar_.dm(), (255 * (i_%2)));
                i_++;

                lastTime_ = chrono_.getElapsedTimeInMicroSec();
                if(i_ >= ledBar_.nb())
                {
                    ledBar_.stop(true);
                    ledBar_.nb(0);
                }
            }
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;

        case pmx::LEDBARK2MIL :
            
            if(chrono_.getElapsedTimeInMicroSec() >= lastTime_ + 50000)
            {
                out->setValue(ledBar_.dm(), i_, true);
                out->setValue(ledBar_.dm(), j_, false);
                j_ = i_;
                if(inc_)
                {
                    i_++;
                }else
                {
                    i_--;
                }
                if(i_ >= 7)
                {
                    i_ = 7;
                    inc_ = false;
                }
                if(i_ <= 0)
                {
                    i_ = 0;
                    inc_ = true;
                }
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
            }
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;


        default : logger().error() << "switch : mauvaise action requise !!" << utils::end;
            break;
    }
    return 0;
}

void pmx::LedBar::k2Mil()
{
    this->actionStopped_ = false;
    //ajout de l'action k2mil
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARK2MIL));
}

void pmx::LedBar::set(ushort position, bool status)
{
    this->position_ = position;
    this->status_ = status;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARSET));
}

void pmx::LedBar::reset()
{
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARRESET));
}

void pmx::LedBar::flash()
{
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARFLASH));
}

void pmx::LedBar::blink(int nb)
{
    this->nb_ = nb;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARBLINK));
}
