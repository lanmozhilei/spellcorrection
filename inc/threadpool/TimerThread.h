#ifndef _WD_TIMERTHREAD_H
#define _WD_TIMERTHREAD_H

#include <functional>
#include <pthread.h>
#include "Noncopyable.h"

namespace wd
{
class TimerThread : Noncopyable
{
public:
	typedef std::funtion<void()> Callback;

	explicit TimerThread(Callback cb);
	~TimerThread();

	void start();
	void join();
private:
	static void* runInTrhead(void *arg);
private:
	pthread_t pthid_;
	bool isRunning_;
	Callback cb_;
};
};
#endif
