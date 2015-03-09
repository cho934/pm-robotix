#include "LedBar.hpp"

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "../../Common/Hex.hpp"

using namespace std;

LedBar::LedBar(int nb) :
		nbLed_(nb)
{
	leddriver = ALedDriver::create(nb);
}

LedBar::~LedBar()
{
	delete leddriver;
}

void LedBar::set(int pos, int color)
{
	leddriver->set(pos, color);
}

void LedBar::blink(uint nb, uint timeus, int color)
{
	for (uint i = 0; i <= nb; i++)
	{
		flash(pow(2, nbLed_) - 1, 0);
		usleep(timeus);
		if (i >= nb)
			break;
		flash(pow(2, nbLed_) - 1, color);
		usleep(timeus);
	}
}
void LedBar::flash(uint hexPosition, int color)
{
	hexPosition = pow(2, nbLed_) - 1;
	for (int i = 0; i <= nbLed_; i++)
	{
		if (((hexPosition >> i) & 0x01) == 1)
		{
			this->set(i, color);
		}
	}
}

void LedBar::blinkPin(int position, uint nb, uint timeus, int color)
{
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

void LedBar::alternate(uint nb, uint timeus, uint beginVal, uint endVal,
		int beginColor, int endColor)
{
	for (uint i = 1; i <= nb; i++)
	{
		flash(beginVal, beginColor);
		usleep(timeus);
		flash(endVal, endColor);
		i++;
		if (i > nb)
			break;
		usleep(timeus);
	}
}

void LedBar::k2mil(uint nb, uint timeus, int color)
{
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

