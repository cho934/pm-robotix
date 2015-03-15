#include "LedBar.hpp"

#include <bitset>
#include <cmath>
#include <iostream>
#include  <iomanip>
#include  <stdlib.h>

#include "../Action.Driver/ALedDriver.hpp"
#include "../LogAppender/Logger.hpp"
#include "Actions.hpp"

using namespace std;

LedBar::LedBar(Actions & actions, int nb) :
		AActionsElement(actions), nbLed_(nb), actionStopped_(false), actionRunning_(false), position_(
				0), color_(0), nb_(0), timeus_(0), hex_(0), hexNext_(0)

{
	leddriver = ALedDriver::create(nb);
}

LedBar::~LedBar()
{
	delete leddriver;
}

LedBarAction::LedBarAction(LedBar & ledBar, LedBarActionName action) :
		ledBar_(ledBar), action_(action), lastTime_(0), i_(1), j_(1), k_(0), inc_(true)
{
	chrono_.start();
}

void LedBar::set(int pos, uint color)
{
	leddriver->setBit(pos, color);
}

void LedBar::blink(uint nb, uint timeus, uint color)
{
	for (uint i = 0; i <= nb; i++)
	{
		resetAll();
		usleep(timeus);
		if (i >= nb)
			break;

		flashAll(color);
		usleep(timeus);
	}
}

void LedBar::flash(uint hexPosition, uint color)
{
	leddriver->setBytes(hexPosition, color);
}

void LedBar::resetAll()
{
	flash(0xFFFF, LED_OFF);
	//flash(pow(2, nbLed_) - 1, 0);
}

void LedBar::flashAll(uint color)
{
	flash(0xFFFF, color);
	//flash(pow(2, nbLed_) - 1, color);
}

void LedBar::blinkPin(uint nb, uint timeus, int position, uint color)
{
	logger().debug() << "blinkPin" << logs::end;
	for (uint i = 1; i <= nb; i++)
	{
		this->set(position, color);
		usleep(timeus);
		this->set(position, 0);
		i++;
		if (i > nb)
			break;
		usleep(timeus);
	}
}

void LedBar::alternate(uint nb, uint timeus, uint beginVal, uint endVal, uint beginColor)
{
	logger().debug() << "alternate" << logs::end;
	for (uint i = 1; i <= nb; i++)
	{
		flash(beginVal, beginColor);
		usleep(timeus);
		flash(endVal, LED_OFF);
		i++;
		if (i > nb)
			break;
		usleep(timeus);
	}
}

void LedBar::k2mil(uint nb, uint timeus, uint color)
{
	logger().debug() << "k2mil" << logs::end;
	int j = -1;

	for (uint i = 1; i <= nb; i++)
	{
		//inc
		for (int k = 0; k <= nbLed_ - 1; k++)
		{
			set(k, color);
			if (j >= 0)
				if (j != k)
					set(j, 0);
			j = k;
			usleep(timeus);
		}
		//dec
		for (int k = nbLed_ - 1; k >= 0; k--)
		{
			set(k, color);
			if (j != k)
				set(j, 0);
			j = k;
			usleep(timeus);
		}
	}
	//off
	set(0, 0);
}

void LedBar::startSet(ushort index, uint color)
{
	logger().debug() << "startSet" << logs::end;
	this->actionStopped_ = false;
	this->position_ = index;
	this->color_ = color;
	//ajout de l'action de set dans la pile d'action
	this->actions().addAction(new LedBarAction(*this, LEDBARSET));
}

void LedBar::startReset()
{
	logger().debug() << "startReset" << logs::end;
	this->actionStopped_ = false;
	this->actions().addAction(new LedBarAction(*this, LEDBARRESET));
}

void LedBar::startFlash()
{
	logger().debug() << "startFlash" << logs::end;
	this->actionStopped_ = false;
	this->actions().addAction(new LedBarAction(*this, LEDBARFLASH));
}

void LedBar::startFlashValue(uint hexValue)
{
	logger().debug() << "startFlashValue" << logs::end;
	this->actionStopped_ = false;
	this->hex_ = hexValue;
	this->actions().addAction(new LedBarAction(*this, LEDBARFLASHVALUE));
}

void LedBar::startAlternate(uint nb, uint timeus, uint hexValue, uint hexValueNext, uint color,
		bool wait)
{
	logger().debug() << "startAlternate" << logs::end;
	while (this->actionRunning_)
	{
		usleep(1000);
	}
	this->actionStopped_ = false;
	this->nb_ = nb;
	this->timeus_ = timeus;
	this->hex_ = hexValue;
	this->hexNext_ = hexValueNext;
	this->color_ = color;
	this->actions().addAction(new LedBarAction(*this, LEDBARALTERNATE));
	if (wait)
	{
		while (!this->actionRunning_)
		{
			usleep(1000);
		}
		while (this->actionRunning_)
		{
			usleep(1000);
		}
	}
}

void LedBar::startBlink(uint nb, uint timeus, uint color, bool wait)
{
	while (this->actionRunning_)
	{
		usleep(1000);
	}
	this->actionStopped_ = false;
	this->nb_ = nb;
	this->timeus_ = timeus;
	this->color_ = color;
	this->actions().addAction(new LedBarAction(*this, LEDBARBLINK));
	if (wait)
	{
		while (!this->actionRunning_)
		{
			usleep(1000);
		}
		while (this->actionRunning_)
		{
			usleep(1000);
		}
	}
}

void LedBar::startBlinkPin(uint nb, uint timeus, int position, uint color, bool wait)
{
	while (this->actionRunning_)
	{
		usleep(1000);
	}
	this->position_ = position;
	this->actionStopped_ = false;
	this->nb_ = nb;
	this->timeus_ = timeus;
	this->color_ = color;
	this->actions().addAction(new LedBarAction(*this, LEDBARBLINKPIN));
	if (wait)
	{
		while (!this->actionRunning_)
		{
			usleep(1000);
		}
		while (this->actionRunning_)
		{
			usleep(1000);
		}
	}
}

void LedBar::startK2mil(uint nb, uint timeus, uint color, bool wait)
{
	while (this->actionRunning_)
	{
		usleep(1000);
	}
	this->actionStopped_ = false;
	this->timeus_ = timeus;
	this->nb_ = nb;
	this->color_ = color;
	this->actions().addAction(new LedBarAction(*this, LEDBARK2MIL));
	if (wait)
	{
		while (!this->actionRunning_)
		{
			usleep(1000);
		}
		while (this->actionRunning_)
		{
			usleep(1000);
		}
	}
}



bool LedBarAction::execute()
{
	switch (this->action_)
	{
	case LEDBARSET:
		ledBar_.set(ledBar_.position(), ledBar_.color());
		return 0; //suppression de l'action
		break;

	case LEDBARRESET:
		ledBar_.resetAll();
		return 0; //suppression de l'action
		break;

	case LEDBARFLASH:
		ledBar_.flashAll();
		return 0; //suppression de l'action
		break;

	case LEDBARFLASHVALUE:
		ledBar_.flash(ledBar_.hexValue(), ledBar_.color());
		return 0; //suppression de l'action
		break;

	case LEDBARALTERNATE:
		ledBar_.actionRunning(true);
		if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long) ledBar_.timeus() || i_ == 1)
		{
			if ((i_ % 2))
			{
				ledBar_.flash(ledBar_.hexValue(), ledBar_.color());
			}
			else
			{
				ledBar_.flash(ledBar_.hexValueNext(), ledBar_.color());
			}
			i_++;
			lastTime_ = chrono_.getElapsedTimeInMicroSec();
		}
		if (i_ >= ledBar_.nb() + 1)
		{
			ledBar_.stop(true);
			ledBar_.nb(0);
		}
		if (ledBar_.stop())
			ledBar_.actionRunning(false);
		return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
		break;

	case LEDBARBLINK:
		ledBar_.actionRunning(true);
		if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long) ledBar_.timeus() || i_ == 1)
		{
			ledBar_.flash((255 * (i_ % 2)), ledBar_.color());
			i_++;
			lastTime_ = chrono_.getElapsedTimeInMicroSec();
		}
		if (i_ >= ledBar_.nb() + 1)
		{
			ledBar_.stop(true);
			ledBar_.nb(0);
		}
		if (ledBar_.stop())
			ledBar_.actionRunning(false);
		return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
		break;

	case LEDBARBLINKPIN:
			ledBar_.actionRunning(true);
			if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long) ledBar_.timeus() || i_ == 1)
			{
				//pmx::LedIndicator::instance().set(ledBar_.position(), (i_ % 2));
				//out->setValue(ledBar_.dm(), ledBar_.position(), (i_ % 2));

				ledBar_.set(ledBar_.position(), (i_ % 2) * ledBar_.color());
				i_++;

				lastTime_ = chrono_.getElapsedTimeInMicroSec();

			}
			if (i_ >= ledBar_.nb() + 1)
			{
				ledBar_.stop(true);
				ledBar_.nb(0);
			}
			if (ledBar_.stop())
				ledBar_.actionRunning(false);
			return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
			break;

	case LEDBARK2MIL:
			ledBar_.actionRunning(true);
			if (chrono_.getElapsedTimeInMicroSec() >= lastTime_ + (long) ledBar_.timeus() || i_ == 1)
			{
				if (i_ >= ledBar_.nb() + 2)
				{
					ledBar_.stop(true);
					ledBar_.nb(0);
				}
				else
				{
					ledBar_.set(k_,ledBar_.color());
				}

				ledBar_.setOff(j_);

				if ((k_ == ledBar_.nb()-1 && !inc_) || (k_ == 0 && inc_))
					i_++;
				j_ = k_;
				if (inc_)
				{
					k_++;
				}
				else
				{
					k_--;
				}
				if (k_ >= ledBar_.nb()-1)
				{
					k_ = ledBar_.nb()-1;
					inc_ = false;
				}
				if (k_ <= 0)
				{
					k_ = 0;
					inc_ = true;
				}
				lastTime_ = chrono_.getElapsedTimeInMicroSec();
			}

			if (ledBar_.stop())
				ledBar_.actionRunning(false);
			return !ledBar_.stop(); //renvoi 0 pour supprimer l'action
			break;


	default:
		logger().error() << "Bad execute command !!" << logs::end;
		return false;
		break;
	}
	return false;
}

