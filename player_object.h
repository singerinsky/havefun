#include "redis_connection.h"
#include "head.h"
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "data.pb.h"



class PlayerObject:public RedisCallBackObject
{
	public:
		int CallBack(redisReply* reply);
		std::string GetDBStr() ;
};

class PlayerObjectSave:public RedisCallBackObject
{
	public:
		int CallBack(redisReply* reply);
		std::string GetDBStr();
		void SetDBStr(std::string buildStr)
		{
			_buildStr = buildStr;
		}

	private:
		std::string _buildStr;
};

class PlayerObjectRequire:public RedisCallBackObject
{
	public:
		int CallBack(redisReply* reply);
		std::string GetDBStr();
		void SetDBStr(std::string buildStr)
		{
			_buildStr = buildStr;
		}
	private:
		std::string _buildStr;
};

int PlayerObject::CallBack(redisReply* reply)
{
	printf("player %lld\n",reply->integer);
	printf("player %s\n",reply->str);
	return 0;
}

std::string PlayerObject::GetDBStr()
{
	return "GET player_2";
}

int PlayerObjectSave::CallBack(redisReply* reply)
{
	LOG(INFO)<<"SAVE player object success";
	return 0;
}

std::string PlayerObjectSave::GetDBStr()
{
	return _buildStr;	
}

int PlayerObjectRequire::CallBack(redisReply* reply)
{
	if(reply->type == REDIS_REPLY_NIL)
	{
		LOG(INFO)<<"no PLAYER_1 DATA EXIST";
		return -1;
	}

	player_info info;
	std::string str(reply->str);
	info.ParseFromString(str);
	return 1;
}

std::string PlayerObjectRequire::GetDBStr()
{
	return "GET PLAYER_1";
}
