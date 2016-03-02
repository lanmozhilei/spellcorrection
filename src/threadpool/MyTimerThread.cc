#include "MyTimerThread.h"

namespace wd
{
MyTimerThread::MyTimerThread(int val, int interval, Callback cb)
		:timer_(val,interval, cb),
		 thread_(std::bind(&Timer::start, &timer_))
{}

void MyTimerThread::start()
{
	thread_start();//创建定时器线程
}

void MyTimerThread::stop()
{
	timer_.stop();
	thread_.join();
}
}//end of namespace
