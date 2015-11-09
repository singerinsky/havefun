#include "head.h"
#include <iostream>
#include <sstream>
#include "data.pb.h"
#include <time.h>
#include <iomanip>
#include "mysql_loader.h"

using std::setw;
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
	DBThread<RedisConnection,RedisCallBackObject> *_thread = new DBThread<RedisConnection,RedisCallBackObject>(connection);	
	_thread->Push(player);
	
	stringstream os_str;	
	std::string  string_buff;
	player_info info,new_info;	
	info.set_player_id(89);
	info.set_player_name("guanlei");
	bool Srst = info.SerializeToString(&string_buff);	
	if(Srst)
	{
		new_info.ParseFromString(string_buff);
	}
	std::string final_db = "SET PLAYER_1 ";
	final_db.append(string_buff);
	PlayerObjectSave* _save = new PlayerObjectSave();
	_save->SetDBStr(final_db);
	_thread->Push(_save);
	LOG(INFO)<<"thread start!!!";	
	PlayerObjectRequire* _req= new PlayerObjectRequire();
	_req->SetDBStr("GET PLAYER_1");
	_thread->Push(_req);
	_thread->Start();
	LOG(INFO)<<"thread start!!!";	
}

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

void build_log_time()
{
    struct ::tm tm_time;
    time_t time_st = time(NULL);
    localtime_r(&time_st,&tm_time);
    // The logfile's filename will have the date/time & pid in it
    char time_pid_string[256];  // More than enough chars for time, pid, \0
    ostrstream time_pid_stream(time_pid_string, sizeof(time_pid_string));
    time_pid_stream.fill('0');
    time_pid_stream << 1900+tm_time.tm_year
        << setw(2) << 1+tm_time.tm_mon
        << setw(2) << tm_time.tm_mday
        << '-'
        << setw(2) << tm_time.tm_hour
        << setw(2) << tm_time.tm_min
        << setw(2) << tm_time.tm_sec
        << '.'
        << '\0';
    printf("----------> %s",time_pid_stream.str());

}

void test_mysql()
{
    //mysql_loader(const char* db_name,const char* ip_str,int port,const char* user_name,const char* pwd,const char* perfix="")
    mysql_loader * loader = new mysql_loader("gl","127.0.0.1",3306,"root","firefly");   
    bool rst = loader->init();
    LOG(INFO)<<"Load init mysql connection "<<rst;

    loader->start_load();
}
	
DEFINE_bool(daemon,false,"if start not daemon");
int main(int argc,char** argv)
{
    build_log_time();
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	FLAGS_logtostderr = true;
	LOG(INFO)<<"start mini ";
    test_mysql();
	
	//redis_test();
	//sleep(100);
	return 1;
}
