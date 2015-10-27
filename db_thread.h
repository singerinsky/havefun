#ifndef _DB_THREAD_H_
#define _DB_THREAD_H_

#include <thread>
#include "queue.h"
#include "head.h"
#include <glog/logging.h>
#include <gflags/gflags.h>


template<class DB_CON,class DB_OBJECT>
class DBThread
{
	public:
		DBThread(DB_CON* t):_connection(t)
		{
			_work_flag = false;
		}

		void Stop(){_work_flag = false;}

		void Start()
		{
			_work_flag = true;
			_thread = new std::thread(&DBThread<DB_CON,DB_OBJECT>::Run,this);
			_thread->join();
		}
	
		void Run()
		{
			while(true)
			{
				DB_OBJECT* object = Pop();
				if(object == NULL)
				{
					if(_work_flag == false)
						break;
					usleep(10000);
					continue;
				}
				bool rst = _connection->ProcessCommand(object);
				if(rst == false)
				{
					LOG(INFO)<<"process command error!\n";
				}
			}
		}

		void Push(DB_OBJECT* object)
		{
			int rst = _queue.Push((char*)&object,sizeof(void*));
			if(rst == 0)printf("error push db object!\n");
		}

		DB_OBJECT* Pop()
		{
			DB_OBJECT* object = NULL;
			int rst = _queue.Pop(4,(char*)&object,4);
			//if(rst == 0)
			//printf("empty queue!\n");
			return object;
		}

	private:
		bool    _work_flag;
		DB_CON* _connection;
		std::thread* _thread;
		CircleQueue<NullLock> _queue;
};


#endif
