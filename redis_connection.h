#ifndef _REDIS_CONNETION_H_
#define _REDIS_CONNETION_H_

#include "hiredis.h"
#include <string>
using namespace std;

class RedisCallBackObject
{
	public:
		virtual int CallBack(redisReply* reply) = 0;
		virtual std::string GetDBStr() = 0;
};

class RedisConnection
{
	public:
		RedisConnection(const char* host,int port):_server_host(host),_port(port)
		{

		}

		~RedisConnection()
		{
			redisFree(_connection);
		}
		
		bool Connect()
		{
			//2 seconds
			struct timeval timeout = {2,0};	
			_connection = redisConnectWithTimeout(_server_host.c_str(),_port,timeout);
			if(_connection == NULL || _connection->err)
			{
				if(_connection == NULL)
				{
					printf("allocate redis connect error!");
				}else
				{
					printf("erro %s",_connection->errstr);
					redisFree(_connection);
				}
				return false;	
			}
			return true;
		}

		bool ProcessCommand(RedisCallBackObject* object);

	private:
		std::string   _server_host;
		int	      _port;
		redisContext *_connection;	
};


#endif
