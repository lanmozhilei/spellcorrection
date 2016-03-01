#ifndef _WD_TIMER_H
#define _WD_TIMER_H

#include "Noncopyable.h"
#include <functional>

namespace wd
{
class Timer : Noncopyable
{
public:
	typedef std::function<void()> Callback;
	Timer(int val, int interval, Callback cb);
	~Timer();

	void start();
	void stop();
private:
	int timerfd_;
	int val_;
	int interval_;
	Callback cb_;
	bool isStarted_
};
}//end of namespace

#endif
