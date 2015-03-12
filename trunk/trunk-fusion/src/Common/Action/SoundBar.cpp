#include "SoundBar.hpp"


using namespace std;

SoundBar::SoundBar()
{
	sounddriver = ASoundDriver::create();
}

SoundBar::~SoundBar()
{
	delete sounddriver;
}

void SoundBar::playPMX()
{

}
