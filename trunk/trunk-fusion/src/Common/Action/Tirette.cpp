#include "Tirette.hpp"

#include <unistd.h>

using namespace std;

Tirette::Tirette(Actions & actions) :
		AActionsElement(actions)

{
	contactdriver = AContactDriver::create();
}

Tirette::~Tirette()
{
}

int Tirette::pressed()
{
	int temp = contactdriver->pressed();
	logger().debug() << "pressed = " << temp << logs::end;

	return temp;
}

void Tirette::monitor(int nb)
{
	logger().info() << "monitor" << logs::end;
	int n = 0;
	while (n <= nb)
	{
		while (!pressed())
		{
			usleep(10000);
		}
		logger().info() << "pressed" << logs::end;

		while (pressed())
		{
			usleep(10000);
		}
		logger().info() << "unpressed" << logs::end;
		n++;
	}
}

bool Tirette::waitPressed()
{
	while (!pressed())
	{
		usleep(10000);
	}
	return true;
}

bool Tirette::waitUnpressed()
{
	while (pressed())
	{
		usleep(10000);
	}
	return true;
}
