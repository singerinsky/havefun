#include "redis_connection.h"

bool RedisConnection::ProcessCommand(RedisCallBackObject* object)
{
	if(_connection == NULL)
	{
		printf("redis disconnection!");
		return false;
	}

	redisReply* reply = (redisReply*)redisCommand(_connection,object->GetDBStr().c_str());	
	if(reply == NULL)
	{
		printf("error exe %s",object->GetDBStr().c_str());
		return false;
	}

	object->CallBack(reply);
	freeReplyObject(reply);

	return true;
}
