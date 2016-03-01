#ifndef _WD_THREADPOOL_H
#define _WD_THREADPOOL_H

#include "Noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"

#include <queue>
#include <vector>
#include <functional>
#include <memory>

namespace wd
{
class MyDict;
class Task;

class ThreadPool : private Noncopyable
{
public:
	ThreadPool(size_t queueSize, size_t threadsNum, Cache &cache, MyDict &mydict);

	void start();

	void addTask();
	Task getTask();

	void runInThread(Cache &cache);

	void update();//更新Cache

private:
	mutable MutexLock mutex_;
	Condition empty_;
	Condition full_;

	size_t queueSize_;
	std::queue<Task> queue_;

	const size_t theadsNum_;
	std::vector<std::unique_ptr<Thread> > threads_;
	bool isExit_;

	Cache &cache_;
public:
	MyDict &mydict_;
};

}//end of namesapce
#endif
