#ifndef _WD_MUTEXlOck_H
#define _WD_MUTEXLOCK_H

#include "Noncopyable.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

namespace wd
{
#define TINY_CHECK(exp) \
	if(!(exp)) \
	{ \
		fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true,abort.\n", __FILE__, __LINE__); abort(); \
	}

class MutexLock : Nobcopyable
{
	friend class Condition;
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();

	bool isLocking() const 
	{ return isLocking_; }
	pthread_mutex_t *getMutexPtr()
	{ return &mutex_; }
private:
	void restoreMutexStatus() //提供给Condition的wait使用
	{isLocking_ = true;}

	pthread_mutex_t mutex_;
	bool isLocking_; //是否上锁
};

class MutexLockGuard : Noncopyable
{
public:
	MutexLockGuard(MutexLock &mutex) : mutex_(mutex)
	{ mutex_.lock(); }
	~MutexLockGuard()
	{ mutex_.unlock(); }
private:
	MutexLock &mutex_;
};
}//end of namespace
#endif
