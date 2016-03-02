#include "TimerThead.h"

namespace wd
{
TimerThead::TimerThead(Callback cb)
	:pthid_(0),
	 isRunning_(false),
	 cb_(cb)
{}

TimerThead::~TimerThead()
{
	if(isRunning_)
	{
		pthread_detach(pthid_);//让线程脱离，交给系统管理回收
	}
}

void TimerThead::start()
{
	pthread_create(&pthid_, NULL, &TimerThead::runInThread,this);
	isRunning_ = true;
}

void TimerThead::join()
{
	pthread_join(pthid_, NULL);
	isRunning_ = false;
}

void *TimerThead::runInThread(void *arg)
{
	TimerThead *ptt = static_cast<TimerThead*>(arg);
	if(ptt->cb_)
	{
		ptt->cb_;
	}
	return NULL;
}
}
//end of namespace
