#include "redis_connection.h"

bool RedisConnection::ProcessCommand(const char* pCommand,RedisCallBackObject* object)
{
	if(_connection == NULL)
	{
		printf("redis disconnection!");
		return false;
	}
	return true;
}
