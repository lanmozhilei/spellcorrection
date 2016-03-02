//把Timer和TimerThread联系起来，最终实现外部函数体的实现
//主要做两件事，第一，把外部传入构造函数的回调函数传给Timer的回调函数，由定时器执行
//第二，创建定时器线程，并把定时器的start函数作为定时器的回调函数
#ifndef _WD_MYTIMERTHREAD_H
#define _WD_MYEIMERTHREAD_H

#include "Timer.h"
#include "TimerThread.h"

namespace wd
{
class MyTimerThread
{
public:
	typedef std::function<void()> Callback;

	MyTimerThread(int val, int interval, Callback cb);

	void start();
	void stop();

private:
	Timer timer_;
	TimerThread thread_;

};
}//end of namespace
#endif
