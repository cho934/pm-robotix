//drivers...SIMULAUNCHER

#include "SoundDriver.hpp"

#include <string>

using namespace std;

ASoundDriver * ASoundDriver::create()
{
	return new SoundDriver();
}

SoundDriver::SoundDriver()
{
}

SoundDriver::~SoundDriver()
{
}

void SoundDriver::beep()
{
}

void SoundDriver::tone(unsigned frequency, unsigned ms)
{
}

void SoundDriver::play(const std::string &soundfile, bool bSynchronous = false)
{
}

void SoundDriver::speak(const std::string &text, bool bSynchronous = false)
{
}

unsigned int SoundDriver::volume()
{
	return 0;
}

void SoundDriver::set_volume(unsigned)
{
}
