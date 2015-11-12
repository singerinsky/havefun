#ifndef _REDIS_FROM_MYSQL_H_
#define _REDIS_FROM_MYSQL_H_

struct MysqlData
{
    size_t all_data_size;
    char** keys;
    char** values;
}

extern "C" MysqlData* load_database(const char* db_name,const char* ip_str,int port);



#endif
