#ifndef __RST_LOCK_H_
#define __RST_LOCK_H_

#include <pthread.h>
#include <assert.h>
#include <atomic>
#include <unistd.h>

class LockBase
{
public:
	LockBase(){}
	virtual ~LockBase(){};
	virtual bool Init() = 0;
	virtual void Lock() = 0;
	virtual void UnLock() = 0;
};

class NullLock:public LockBase
{
public:
	virtual ~NullLock()
	{
	}
	virtual bool Init(){return true;}
	virtual void Lock(){return;}
	virtual void UnLock(){return;}
};

class MutexLock:public LockBase
{
public:
	virtual ~ MutexLock(){
		pthread_mutex_destroy(&_mutex_t);
	}

	bool Init()
	{
		if(pthread_mutex_init(&_mutex_t,NULL) == 0)
		{
			return true;
		}
		return false;
	}

	void Lock()
	{ 
		pthread_mutex_lock(&_mutex_t);
	}
	void UnLock()
	{ 
		pthread_mutex_unlock(&_mutex_t);
	}
	

private:
	pthread_mutex_t _mutex_t;
};

template<class Lock>
class AutoLock
{
public:
	AutoLock(Lock* lock)
	{
		_lock = lock;
		_lock->Lock();
	}
	~AutoLock()
	{
		_lock->UnLock();
	}
private:
	Lock* _lock;
};

//spain lock use stdc++11 atomic_flag
class SpainLock:public LockBase
{
public:
	SpainLock()
	{
	}
	virtual ~SpainLock()
	{
		_lock.clear();	
	};
	virtual bool Init() 
	{
		return true;
	};
	virtual void Lock()
	{
		while(!_lock.test_and_set())
			usleep(10);
	}
	virtual void UnLock()
	{
		_lock.clear();
	}

private:
	std::atomic_flag _lock  = ATOMIC_FLAG_INIT;
};


#endif
