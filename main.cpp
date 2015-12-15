#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <glog/logging.h>

using std::setw;
#define TO_STR(T)	printf("%s",#T);

	
DEFINE_bool(daemon,false,"if start not daemon");
int main(int argc,char** argv)
{
	google::ParseCommandLineFlags(&argc,&argv,true);		
	google::InitGoogleLogging(argv[0]);
	FLAGS_logtostderr = true;
	LOG(INFO)<<"start mini ";
	
	//redis_test();
	//sleep(100);
	return 1;
}
