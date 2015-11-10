#include "head.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include "mysql_loader.h"

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
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	FLAGS_logtostderr = true;
	LOG(INFO)<<"start mini ";
    test_mysql();
	
	//redis_test();
	//sleep(100);
	return 1;
}
