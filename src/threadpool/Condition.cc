#include "Condition.cc"
#include "MutexLock.h"
#include <assert.h>

namespace wd
{
Conditon::Condition(MutexLock &mutex)
	:mutex_(mutex)
{
	TINY_CHECK(!pthread_cond_init(&cond, NULL));
}

Condition::~Condition()
{
	TINY_CHECK(!pthread_cond_destroy(&cond_));
}

void Condition::wait()
{
	assert(mutex_.isLocking());//判断有没有上锁
	TINY_CHECK(!pthread_cond_wait(&cond_, mutex_.getMutexPtr()));
	mutex_.restoreMutexStatus();//还原状态
}

void Condition::notify()
{
	TINY_CHECK(!pthread_cond_signal(&cond_));
}

void Condition::notifyAll()
{
	TINY_CHECK(!pthread_cond_broadcast(&cond_));
}
}//end of namespace
