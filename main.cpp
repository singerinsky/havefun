#include "stdio.h"
#include "string.h"
#include "car.h"
#include "queue.h"
#include <time.h>
#include <unistd.h>
#include "thread.h"
#include <thread>
#include "md5.h"
#include "redis_connection.h"
#include "player_object.h"
#include "db_thread.h"
#include "glog/logging.h"
#include <gflags/gflags.h>

#define TO_STR(T)	printf("%s",#T);

typedef CircleQueue<SpainLock> QUEUE;

void function_push(QUEUE* queue)
{
	std::string final_str;
	int i = 0;
	while(true&&(i != 1000))
	{
		int rst = queue->Push("123",3);
		if(rst != 0)
		{
			printf("push %d size:%d head%d tail%d current: %d\n",i,rst,queue->GetHead(),queue->GetTail(),queue->GetDataSize());
			final_str.append("123");
			i++;
			continue;
		}else
		{
			usleep(10);
		}
		
	}
	printf("push : i'm out final len%d\n",final_str.length());
	printf("md5 code:%s\n",md5(final_str.c_str()).c_str());
}

void function_pop(QUEUE* queue)
{
	std::string final_str;
	int i = 0;
	while(true&&(i != 1000))
	{
		char buffer[10];
		memset(buffer,0,10);
		
	//	int rst = queue->Pop(3,buffer,10);
		int rst = queue->ReadFront(3,buffer,10);
		if(rst != 0)
		{
			queue->Discard(rst);
			printf("pop %d size:%d head%d tail%d current:%d \n",i,rst,queue->GetHead(),queue->GetTail(),queue->GetDataSize());
			final_str.append(buffer);	
			i++;
			continue;
		}else
		{
			usleep(10);
		}
	}	
	printf("pop: i'm out, final len:%d\n",final_str.length());
	printf("md5 code:%s\n",md5(final_str.c_str()).c_str());
}


void redis_test()
{
	RedisConnection* connection = new RedisConnection("127.0.0.1",6379);
	bool rst = connection->Connect();
	if(rst)printf("connect success!");
	else printf("connect failed!");
	PlayerObject* player = new PlayerObject();
	connection->ProcessCommand(player);
	DBThread<RedisConnection,PlayerObject> _thread(connection);	
	_thread.Push(player);
	_thread.Start();
}

DEFINE_bool(daemon,false,"if start not daemon");
int main(int argc,char** argv)
{
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	FLAGS_logtostderr = true;
	LOG(INFO)<<"start mini ";
/*
	TO_STR(name);
	Car* pCard = Car::Create();
	printf("class %s id is %lld\n",pCard->GetClassName(),pCard->GetID());
	Car* pCard2 = Car::Create();
	printf("class %s id is %lld\n",pCard2->GetClassName(),pCard2->GetID());
	pCard->Release();

	CircleQueue<NullLock> queue;
	queue.Push("123",3);
	char buffer[1024];
	memset(buffer,0,1024);
	queue.Pop(2,buffer,1024);
	printf("%s\n",buffer);
	queue.Push("45",2);
	memset(buffer,0,1024);
	queue.Pop(3,buffer,1024);

	for(int i = 0;i<1000;i++)
	{
		while(queue.Push("acb",3) != 0);
		memset(buffer,0,1024);
		while(queue.Pop(7,buffer,1024) != 0)
		{
			printf("%s\n",buffer);
			memset(buffer,0,1024);
		}
	}
	
	QUEUE test_queue;
	
	//rstll::RstThread _thread(function);	
	std::thread _thread_push1(function_push,&test_queue);
	std::thread _thread_push2(function_push,&test_queue);
	std::thread _thread_pop3(function_pop,&test_queue);
	std::thread _thread_pop4(function_pop,&test_queue);
	_thread_push1.join();
	_thread_push2.join();
	_thread_pop3.join();
	_thread_pop4.join();
*/
	redis_test();
	return 1;
}
