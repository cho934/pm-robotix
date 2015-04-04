/*!
 * \file
 * \brief Implémentation de la classe Timer.
 */

#include "Timer.hpp"

#include <unistd.h>

#include "Logger.hpp"

utils::Timer::Timer(int timeSpanMax, int timeSpanMin, utils::ITimerListener* listener)
		: timeSpan_(timeSpanMax), timeSpanMin_(timeSpanMin), listener_(listener), stop_(false)
{

}

void utils::Timer::execute()
{
	int tps;

	logger().debug() << "utils::Timer::execute() : start : TimeSpan :" << timeSpan_ << utils::end;
	stop_ = false;

	chrono_.start();
	while (!stop_)
	{
		//pause jusqu'à la prochaine execution en us
		while (1)
		{
			tps = (timeSpan_ * 1000) - chrono_.getElapsedTimeInMicroSec();
			if (tps <= 0)
			{
				logger().debug() << "utils::Timer::after usleep break timeSpan=" << timeSpan_ << " "
						<< chrono_.getElapsedTimeInMicroSec() << utils::end;
				break;
			}
			if (timeSpanMin_ == 0)
			{
				usleep(tps);
				break;
			}
			else
			{
				usleep(timeSpanMin_);
			}
		}

		if (!stop_)
		{
			logger().debug() << "utils::Timer::runTask() :" << chrono_.getElapsedTimeInMicroSec() << utils::end;
			this->runTask(chrono_);
		}

		chrono_.start(); //reset du chrono
	}
	this->runTaskEnd(chrono_);
	chrono_.stop();
	logger().debug() << "utils::Timer::execute() : End" << utils::end;
}

void utils::Timer::runTask(Chronometer chrono)
{
	//logger().debug() << "utils::Timer::runTask()" << utils::end;
	this->listener_->onTimer(chrono);
}

void utils::Timer::runTaskEnd(Chronometer chrono)
{
	//logger().debug() << "utils::Timer::runEndTask()" << utils::end;
	this->listener_->onTimerEnd(chrono);
}
