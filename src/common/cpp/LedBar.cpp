/*!
 * \file
 * \brief Implémentation de la classe LedBar.
 */

#include "LedBar.hpp"
#include "LedIndicator.hpp"
#include "Robot.hpp"

pmx::LedBar::LedBar(pmx::Robot & robot, ushort dm)
: ARobotElement(robot), dm_(dm), actionStopped_(false), actionRunning_(false), position_(0), status_(0),
nb_(0), timeus_(50000), hex_(0), hexNext_(0) {
}

pmx::LedBarAction::LedBarAction(pmx::LedBar & ledBar, pmx::LedBarActionName action)
: ledBar_(ledBar), action_(action), lastTime_(0), i_(1), j_(1), k_(0), inc_(true) {
    chrono_.start();
}

bool pmx::LedBarAction::execute(IRobotOut * out) {
    //logger().debug() << "execute()" << utils::end;


    switch (this->action_)
    {
        case pmx::LEDBARSET:
            out->setValue(ledBar_.dm(), ledBar_.position(), ledBar_.status());
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARRESET:
            out->setValues(ledBar_.dm(), 0);
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARFLASH:
            out->setValues(ledBar_.dm(), 255);
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARFLASHVALUE:
            out->setValues(ledBar_.dm(), ledBar_.hexValue());
            return 0; //suppression de l'action
            break;

        case pmx::LEDBARBLINK:
            ledBar_.actionRunning(true);
            if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long)ledBar_.timeus() || i_ == 1) {
                out->setValues(ledBar_.dm(), (255 * (i_ % 2)));
                i_++;

                lastTime_ = chrono_.getElapsedTimeInMicroSec();

            }
            if (i_ >= ledBar_.nb()+1) {
                ledBar_.stop(true);
                ledBar_.nb(0);
            }
            if (ledBar_.stop())
                ledBar_.actionRunning(false);
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;

        case pmx::LEDBARBLINKPIN:
            ledBar_.actionRunning(true);
            if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long)ledBar_.timeus() || i_ == 1) {
                //out->setValues(ledBar_.dm(), (255 * (i_ % 2)));
                out->setValue(ledBar_.dm(), ledBar_.position(), (i_ % 2));
                i_++;

                lastTime_ = chrono_.getElapsedTimeInMicroSec();

            }
            if (i_ >= ledBar_.nb()+1) {
                ledBar_.stop(true);
                ledBar_.nb(0);
            }
            if (ledBar_.stop())
                ledBar_.actionRunning(false);
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;

        case pmx::LEDBARALTERNATE:
            ledBar_.actionRunning(true);
            //logger().debug() << "LEDBARALTERNATE i=" << i_ << " t=" << ledBar_.timeus() << " nb=" << ledBar_.nb() << " h=" << ledBar_.hexValue() << " hh=" << ledBar_.hexValueNext() << utils::end;
            if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long)ledBar_.timeus() || i_ == 1) {
                if ((i_ % 2)) {
                    logger().debug() << "LEDBARALTERNATE i_ % 2 C3=" << ledBar_.hexValue() << utils::end;
                    out->setValues(ledBar_.dm(), ledBar_.hexValue());
                }else {
                    logger().debug() << "LEDBARALTERNATE not i_ % 2 3C=" << ledBar_.hexValueNext() << utils::end;
                    out->setValues(ledBar_.dm(), ledBar_.hexValueNext());
                }

                i_++;

                lastTime_ = chrono_.getElapsedTimeInMicroSec();

            }
            if (i_ >= ledBar_.nb()+1) {
                logger().debug() << "LEDBARALTERNATE stop" << utils::end;
                ledBar_.stop(true);
                ledBar_.nb(0);
            }
            if (ledBar_.stop())
                ledBar_.actionRunning(false);
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;

        case pmx::LEDBARK2MIL:
            ledBar_.actionRunning(true);
            if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long)ledBar_.timeus() || i_ == 1) {
                if (i_ >= ledBar_.nb() + 2) {
                    ledBar_.stop(true);
                    ledBar_.nb(0);
                }else {
                    out->setValue(ledBar_.dm(), k_, true);
                }
                out->setValue(ledBar_.dm(), j_, false);
                

                if ((k_ == 7 && !inc_) || (k_ == 0 && inc_))
                    i_++;
                j_ = k_;
                if (inc_) {
                    k_++;
                }else {
                    k_--;
                }
                if (k_ >= 7) {
                    k_ = 7;
                    inc_ = false;
                }
                if (k_ <= 0) {
                    k_ = 0;
                    inc_ = true;
                }
                lastTime_ = chrono_.getElapsedTimeInMicroSec();
            }

            if (ledBar_.stop())
                ledBar_.actionRunning(false);
            return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
            break;


        default: logger().error() << "switch : mauvaise action requise !!" << utils::end;
            break;
    }
    return false;
}

void pmx::LedBar::set(ushort position, bool status) {
    this->actionStopped_ = false;
    this->position_ = position;
    this->status_ = status;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARSET));
}

void pmx::LedBar::reset() {
    this->actionStopped_ = false;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARRESET));
}

void pmx::LedBar::flash() {
    this->actionStopped_ = false;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARFLASH));
}

void pmx::LedBar::flashValue(uint hexValue) {
    this->actionStopped_ = false;
    this->hex_ = hexValue;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARFLASHVALUE));
}

void pmx::LedBar::startAlternate(uint nb, uint timeus, uint hexValue, uint hexValueNext, bool wait) {
    while (this->actionRunning_) {
        logger().debug() << "startAlternate while !!" << utils::end;
        usleep(1000);
    }
    this->actionStopped_ = false;
    this->nb_ = nb;
    this->timeus_ = timeus;
    this->hex_ = hexValue;
    this->hexNext_ = hexValueNext;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARALTERNATE));
    if (wait) {
        while (!this->actionRunning_) {
            usleep(1000);
        }
        while (this->actionRunning_) {
            usleep(1000);
        }
    }
}

void pmx::LedBar::startBlink(uint nb, uint timeus, bool wait) {
    while (this->actionRunning_) {
        usleep(1000);
    }
    this->actionStopped_ = false;
    this->nb_ = nb;
    this->timeus_ = timeus;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARBLINK));
    if (wait) {
        while (!this->actionRunning_) {
            usleep(1000);
        }
        while (this->actionRunning_) {
            usleep(1000);
        }
    }
}

void pmx::LedBar::startBlinkPin(int position, uint nb, uint timeus, bool wait) {
    while (this->actionRunning_) {
        usleep(1000);
    }
    this->position_ = position;
    this->actionStopped_ = false;
    this->nb_ = nb;
    this->timeus_ = timeus;
    //ajout de l'action de set
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARBLINKPIN));
    if (wait) {
        while (!this->actionRunning_) {
            usleep(1000);
        }
        while (this->actionRunning_) {
            usleep(1000);
        }
    }
}

void pmx::LedBar::startK2Mil(uint nb, uint timeus, bool wait) {
    while (this->actionRunning_) {
        usleep(1000);
    }
    this->actionStopped_ = false;
    this->timeus_ = timeus;
    this->nb_ = nb;
    //ajout de l'action k2mil
    this->robot().addAction(new pmx::LedBarAction(*this, pmx::LEDBARK2MIL));
    if (wait) {
        while (!this->actionRunning_) {
            usleep(1000);
        }
        while (this->actionRunning_) {
            usleep(1000);
        }
    }
}
