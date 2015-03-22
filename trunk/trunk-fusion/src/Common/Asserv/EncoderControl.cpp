#include "EncoderControl.hpp"

#include <unistd.h>

#include "../LogAppender/Logger.hpp"
#include "../Asserv.Driver/AAsservDriver.hpp"
#include "Asserv.hpp"

using namespace std;

EncoderControl::EncoderControl(Asserv & asserv) :
		AAsservElement(asserv)
{
	asservdriver = AAsservDriver::create();
}

EncoderControl::~EncoderControl()
{
	delete asservdriver;
}

long EncoderControl::getLeftEncoder()
{
	return asservdriver->getLeftInternalEncoder();
}

long EncoderControl::getRightEncoder()
{
	return asservdriver->getRightInternalEncoder();
}
