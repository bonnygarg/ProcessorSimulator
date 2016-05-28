#include "Timer.h"
#include <Windows.h>

Timer::Timer() :
	t1_(0),
	t2_(0)
{}

void Timer::Start()
{
	t1_ = GetTickCount();
}

void Timer::Stop()
{
	t2_ = GetTickCount();

}

const unsigned long Timer::GetTimeElapsedInMilli() const
{
	return (t2_-t1_);
}
