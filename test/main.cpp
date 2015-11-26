#include "head.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include "mysql2redis.h"

void test_mysql()
{
    //mysql_loader(const char* db_name,const char* ip_str,int port,const char* user_name,const char* pwd,const char* perfix="")
    Mysql2RedisDatabase* loader_db = load_database("gl","127.0.0.1",3306,"root","firefly");
    //dump_data_base(loader_db);
}
	
DEFINE_bool(daemon,false,"if start not daemon");
int main(int argc,char** argv)
{
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	FLAGS_logtostderr = true;
	LOG(INFO)<<"start mini ";
    test_mysql();
	
	//redis_test();
	//sleep(100);
	return 1;
}
