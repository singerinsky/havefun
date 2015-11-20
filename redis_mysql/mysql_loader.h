#ifndef _MYSQL_LOADER_H_
#define _MYSQL_LOADER_H_
#include "mysql_connection.h"
#include <map>
#include <vector>
#include "string.h"
#include "mysql2redis.h"

struct StableStatus
{
    std::string table_name;
    std::map<std::string,std::string> all_column;
    std::vector<std::string> all_column_name;
    std::vector<std::string> all_column_type;
    std::string              key_field_name;
    int     table_csize;
    int     table_rsize;
};


typedef std::vector<StableStatus> DBTablesVec;

class cache_adapter
{
    public:
        virtual void add_data_to_cache() = 0;
};

class db_loader
{
    public:
       db_loader(){} 
       virtual bool start_load(Mysql2RedisDatabase* data) = 0;
       virtual bool read_table_status(const char* table_name) = 0;
       virtual bool read_db_status() = 0;
};

class mysql_loader:public db_loader
{
    public:
        mysql_loader(){}
        mysql_loader(const char* db_name,const char* ip_str,int port,const char* user_name,const char* pwd,const char* perfix="")
        {
            _db_name = db_name;
            _ip_str = ip_str;
            _port = port;
            _perfix = perfix;
            _user_name = user_name;
            _pwd = pwd;
            if(_perfix == "")_perfix = db_name;
        }

        bool init()
        {
           int rst = _conn.init(_ip_str.c_str(),_user_name.c_str(),_pwd.c_str(),_port);
           if(rst == 1)
           {
               fprintf(stderr,"error connect to mysql %s:%d",_ip_str.c_str(),_port);
               return false;
           }
           return true; 
        }

        ~mysql_loader(){};
        bool start_load(Mysql2RedisDatabase* data);
        //read table row size,column name
        bool read_table_status(const char* table_name);
        bool read_db_status(); 
        //process mysql 2 redis
        MySql2RedisTable *load_data_mysql2redis(const char* table_name);

    private:
        std::string _db_name;
        std::string _ip_str;
        std::string _perfix ;
        std::string _user_name;
        std::string _pwd;
        int         _port;
        std::map<std::string,StableStatus> allTable;
        MysqlConnection _conn;
};

#endif
