#include "redis_connection.h"
#include <glog/logging.h>
#include <gflags/gflags.h>



int RedisConnection::ProcessCommand(RedisCallBackObject* object)
{
	if(_connection == NULL)
	{
		printf("redis disconnection!");
		return -1;
	}

	redisReply* reply = (redisReply*)redisCommand(_connection,object->GetDBStr().c_str());	
	if(reply == NULL)
	{
		LOG(INFO)<<"error exe "<<object->GetDBStr();
		return -1;
	}

	//set command reply
	if(reply->type == REDIS_REPLY_STATUS && strcasecmp(reply->str,"OK")!= 0)
	{
		LOG(ERROR)<<"error of SET COMMAND :"<<object->GetDBStr().c_str();
	}else if(reply->type == REDIS_REPLY_ERROR)
	{	
		LOG(ERROR)<<"error of COMMAND"<<object->GetDBStr().c_str();
	}else
	{
		object->CallBack(reply);
	}
	freeReplyObject(reply);

	return true;
}
