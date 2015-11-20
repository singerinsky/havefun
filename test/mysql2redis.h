#ifndef _MYSQL2REDIS_H_
#define _MYSQL2REDIS_H_

struct MysqlRedisRow
{
    const char* key;
    const char** data;
};

struct MySql2RedisTable
{
    unsigned int data_column_size;
    unsigned int data_row_size;
    char         table_name[100];
    // 为每一行的数据
    MysqlRedisRow** rows;
    char**  mysql_fields; 
    MySql2RedisTable()
    {
        data_column_size = 0;
        data_row_size = 0;
    }
};

#define MAX_TABLE_SIZE 100
struct Mysql2RedisDatabase
{
    char    db_name[100];
    MySql2RedisTable* all_table[MAX_TABLE_SIZE];
    int     table_size;
};

/*
 *db_name :name of import db
 *ip_str:  ip of db locate
 *port : port of db connect to
 *user_name: db login name
 *pwd : db login password
 *
 */
extern "C"
{
    Mysql2RedisDatabase* load_database(const char* db_name,const char* ip_str,int port,const char* user_name,const char* pwd);
    void                 dump_data_base(Mysql2RedisDatabase*);
}

#endif
