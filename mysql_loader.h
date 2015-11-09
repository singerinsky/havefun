#ifndef _MYSQL_LOADER_H_
#define _MYSQL_LOADER_H_
#include "mysql_connection.h"

extern "C" bool load_database(const char* db_name,const char* ip_str,int port);

struct StableStatus
{
    std::string table_name;
    std::map<std::string,std::string> all_column;
    std::vector<std::string> all_column_name;
    std::vector<std::string> all_column_type;
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
       virtual bool start_load() = 0;
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
        bool start_load();
        bool read_table_status(const char* );
        bool read_table_data(const char*);
        bool read_db_status(); 

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


bool mysql_loader::start_load()
{
    bool read_db = read_db_status();
    if(!read_db)
    {
        fprintf(stderr,"error of read db!"); 
        return false;
    }
    return true;    
}

bool mysql_loader::read_table_status(const char* table_name)
{
    char sql[1024] = {};
    snprintf(sql,1024,"select count(1) from %s;",table_name);
    printf("%s",sql);
    if(_conn.exec(sql) != 0)
    {
        fprintf(stderr,"get table %s row number error\n",table_name); 
        return false;
    }
    StableStatus table_status;
    table_status.table_name = table_name;
    MysqlResult result = _conn.get_data_result();
    if(result.next())
    {
        MysqlResultRow row = result.get_next_row(); 
        int data_size = row.get_int(0);
        table_status.table_rsize = data_size;
        fprintf(stdout,"table %s rows number is %d\n",table_name,data_size);
    }
    else
    {
        fprintf(stderr,"get table %s row number error\n",table_name); 
        return false;
    }
    
    memset(sql,0,1024);
    snprintf(sql,1024,"show columns from %s;",table_name);
    if(_conn.exec(sql) != 0)
    {
        fprintf(stdout,"get columns from table %s\n",table_name);
        return false;
    }
    result = _conn.get_data_result();
    while(result.next())
    {
        MysqlResultRow row = result.get_next_row(); 
        std::string c_name = row.get_string(0);
        std::string c_type = row.get_string(1);
        fprintf(stdout,"table %s : %s == %s \n",table_name,c_name.c_str(),c_type.c_str());
        table_status.all_column[c_name] = c_type;
        table_status.all_column_name.push_back(c_name);
        table_status.all_column_type.push_back(c_type);
    }

    return true;
}
        
bool mysql_loader::read_db_status()
{
    _conn.change_db("information_schema");
    char sql[1024]= {};
    snprintf(sql,1024, "select concat(round(sum(data_length/1024/1024),2),'MB') as data_size from tables where  table_schema='%s';",_db_name.c_str());
    if(_conn.exec(sql) != 0)
    {
        fprintf(stderr,"error of get datasize %s",_db_name.c_str()); 
        return false;
    }
    MysqlResult result = _conn.get_data_result();
    if(result.next())
    {
        MysqlResultRow row = result.get_next_row(); 
        float size_now = row.get_float(0);
        if(size_now >1000)
        {
            fprintf(stderr,"too large"); 
            return false;
        }
    }
    //_conn.change_db(_db_name.c_str());

    memset(sql,0,1024);
    snprintf(sql,1024,"SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = '%s'",_db_name.c_str());
    if(_conn.exec(sql) != 0)
    {
        fprintf(stderr,"error of get all table of db %s",_db_name.c_str()); 
        return false;
    }
    result = _conn.get_data_result();
    std::vector<string> all_tables;
    while(result.next())
    {
        MysqlResultRow row = result.get_next_row(); 
        std::string  table_name = row.get_string(0);
        all_tables.push_back(table_name);
        //printf("table %s",table_name.c_str());
    }
    //change db to we use
    _conn.change_db(_db_name.c_str());

    for(auto table_name:all_tables)
    {
        read_table_status(table_name.c_str()); 
    }

    return true;
}

#endif
