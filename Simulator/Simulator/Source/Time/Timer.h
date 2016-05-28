#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer();
	void Start();
	void Stop();
	const unsigned long GetTimeElapsedInMilli() const;
private:
	unsigned long t1_;
	unsigned long t2_;
};

#endif