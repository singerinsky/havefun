#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <pthread.h>
#include <assert.h>

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

#define QUEUE_DEFAULT_LEN 10
template<class LockClass>
class CircleQueue
{
public:
	CircleQueue()
	{
	    _data = new char[QUEUE_DEFAULT_LEN];	
	    _lock.Init();
	    _head = 0;
	    _tail = 0;
	}
	
	

	~CircleQueue()
	{
	    delete[] _data;
	    _head = 0;
	    _tail = 0;
	}

	size_t GetHead(){return _head;}
	size_t GetTail(){return _tail;}

	int Push(const char* pData,size_t size)
	{
		assert(size > 0);
		if(size <= 0)
			return 0;
		//normal 

		AutoLock<LockClass> lock(&_lock);
		if(_tail >= _head)
		{
			//normal normal
			if(_tail + size < _totoal_size)
			{
				memcpy(_data+_tail,pData,size);	
				_tail += size;
				return size;
			}else if((_totoal_size - _tail + _head) > size)
			{
				memcpy(_data+_tail,pData,(_totoal_size - _tail));
				memcpy(_data,pData+(_totoal_size - _tail),(size -(_totoal_size - _tail)));
				_tail = size - (_totoal_size - _tail);
				return size;
			}else
			{
				//out of buffer
				return 0;
			}
		}else //if _tail == _head ,we consider no value in data
		{
			if(_head - _tail > size)
			{
				memcpy(_data + _tail,pData,size);
				_tail += size;
				return size;
			}else
			{
				return 0;
			}

		}
		
	}

	int ReadFront(size_t size,char* pData,size_t buff_size)
	{
		assert(buff_size >= size);
		if(buff_size < size)
			return 0;
		AutoLock<LockClass> lock(&_lock);
		size_t nDist = _tail + _totoal_size - _head;
		size_t nUsed = nDist >= _totoal_size ? (nDist - _totoal_size):nDist;
		if(size > nUsed)
			return 0;

		if(_head < _tail)
		{
			memcpy(pData,_data+_head,size);
			return size;
		}
		else 
		{
			if(_totoal_size - _head >= size)
			{
				memcpy(pData,_data+_head,size);
			}else
			{
				memcpy(pData,_data+_head,(_totoal_size-_head));
				memcpy(pData+(_totoal_size - _head),_data,(size - _totoal_size + _head) );
			}
			return size;
		}

	}

	int Discard(size_t size)
	{
		AutoLock<LockClass> lock(&_lock);
		if(_head <= _tail)
		{
			if(_tail - _head >= size)
			{
				_head += size;
				return size;
			}
			return 0;

		}
		else 
		{
			if(_totoal_size - _head + _tail >= size)
			{
				if(_totoal_size - _head >= size)
				{
					_head += size;
				}else
				{
					_head = size - _totoal_size + _head;
				}
				return size;
			}
			else 
			{
				return 0;
			}
		}
	}

	int Pop(size_t size,char* pData,size_t buff_size)
	{
		assert(buff_size >= size);
		if(buff_size < size)
			return 0;
		AutoLock<LockClass> lock(&_lock);

		if(_head <= _tail)
		{
			if(_tail - _head >= size)
			{
				memcpy(pData,_data+_head,size);
				_head += size;
				return size;
			}
			return 0;

		}
		else 
		{
			if(_totoal_size - _head + _tail >= size)
			{
				if(_totoal_size - _head >= size)
				{
					memcpy(pData,_data+_head,size);
					_head += size;
				}else
				{
					memcpy(pData,_data+_head,(_totoal_size-_head));
					memcpy(pData+(_totoal_size - _head),_data,(size - _totoal_size + _head) );
					_head = size - _totoal_size + _head;
				}
				return size;
			}else{
				return 0;
			}
		}
	}

	int	GetDataSize()
	{
		AutoLock<LockClass> lock(&_lock);
		size_t nDist = _tail + _totoal_size - _head;
		size_t nUsed = nDist >= _totoal_size ? (nDist - _totoal_size):nDist;
		return nUsed;	
	}

	void  Clear()
	{
		AutoLock<LockClass> lock(&_lock);
		_head = 0;
		_tail = 0;
	}

private:
	LockClass _lock;
	char*	  _data;
	size_t	  _head;
	size_t	  _tail;
	size_t    _totoal_size = QUEUE_DEFAULT_LEN;
};


#endif
