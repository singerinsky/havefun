#include "redis_connection.h"

class PlayerObject:public RedisCallBackObject
{
	public:
		PlayerObject(){}
		~PlayerObject(){}
		int CallBack(redisReply* reply);
		std::string GetDBStr() ;
};


int PlayerObject::CallBack(redisReply* reply)
{
	printf("player %lld\n",reply->integer);
	printf("player %s\n",reply->str);
	return 0;
}

std::string PlayerObject::GetDBStr()
{
	return "GET player_1";
}
