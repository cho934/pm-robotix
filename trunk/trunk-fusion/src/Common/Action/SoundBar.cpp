#include "SoundBar.hpp"

#include <unistd.h>


using namespace std;

SoundBar::SoundBar()
{
	sounddriver = ASoundDriver::create();
}

SoundBar::~SoundBar()
{
	delete sounddriver;
}

void SoundBar::speakPMX()
{
	sounddriver->set_volume(10);
	sounddriver->speak("Hello PMX");
	sleep(2);
	sounddriver->speak("How are you today ?", true);

}
