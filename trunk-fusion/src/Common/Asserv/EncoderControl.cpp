#include "EncoderControl.hpp"

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
