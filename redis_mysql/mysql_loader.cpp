#include "mysql_loader.h"
#include <map>
#include <sstream>
#include "mysql2redis.h"

MySql2RedisTable* mysql_loader::load_data_mysql2redis(const char* table_name)
{
    auto itr = allTable.find(table_name);
    if(itr == allTable.end())
    {
        fprintf(stderr,"table %s status not read yet",table_name);
        return NULL; 
    }

    if(itr->second.key_field_name == "")
    {
        fprintf(stderr," %s no primarykey define ",table_name); 
        return NULL;
    }
    char sql[1024] = {0};
    snprintf(sql,1024,"select * from %s",table_name);
    bool rst = _conn.exec(sql);
    if(rst != 0)
    {
        fprintf(stderr,"load table %s data error",table_name); 
        return NULL;
    }
    
    MySql2RedisTable* redis_mysql = new MySql2RedisTable();
    memset(redis_mysql->table_name,0,100);
    snprintf(redis_mysql->table_name,100,"%s",table_name);
    redis_mysql->data_column_size = itr->second.table_csize;
    redis_mysql->data_row_size = itr->second.table_rsize;
    redis_mysql->mysql_fields = (char**)malloc(sizeof(char*)*redis_mysql->data_column_size);
    redis_mysql->rows = (MysqlRedisRow**)malloc(sizeof(MysqlRedisRow*)*redis_mysql->data_row_size);
    int i = 0;
    for(auto field_name:itr->second.all_column_name)
    {
        char* str_buff = new char(field_name.length());
        strcpy(str_buff,field_name.c_str());
        redis_mysql->mysql_fields[i] = str_buff;
        i++;
    }
   
    MysqlResult result = _conn.get_data_result();
    std::string per_key = this->_perfix;
    per_key.append("_").append(table_name).append("_");
    int row_index = 0;
    while(result.next())
    {
        std::string sstr;
        MysqlResultRow row = result.get_next_row(); 
        MysqlRedisRow * redisrow = new MysqlRedisRow();
        int index = 0;
        std::string new_key;
        for(auto type_itr:itr->second.all_column_name)
        {
            const char* row_c_data = row.get_src_data(index);
            sstr.append(type_itr).append(" ").append(row_c_data).append(" ");
            if(type_itr == itr->second.key_field_name)
            {
                new_key.append(per_key).append(row_c_data); 
            }
            index++;
        }
        sstr.erase(sstr.end()-1,sstr.end());
        //copy key to buff
        redisrow->key = new char[new_key.size() + 1];
        memset(redisrow->key,0,new_key.size()+1);
        //memcpy(redisrow->key,new_key.c_str(),new_key.length()+1);
        strcpy(redisrow->key,new_key.c_str());
        //strncpy(redisrow->key,new_key.c_str(),new_key.length());
        //copy data to buff
        const char** src_row_data = row.get_row_src_data();
        char** data_buff = (char**)malloc(sizeof(char*)*redis_mysql->data_column_size);
        for(int c =0; c< redis_mysql->data_column_size ;c++)
        {
            data_buff[c] = new char[strlen(src_row_data[c])+1]; 
            memcpy(data_buff[c],src_row_data[c],strlen(src_row_data[c])+1); 
        }
        redisrow->data = data_buff;

        redis_mysql->rows[row_index] = redisrow;
        //fprintf(stdout,"build new key:value [%s] [%s]\n",new_key.c_str(),sstr.c_str());
        row_index++;
    }

    return redis_mysql;
}

bool mysql_loader::start_load(Mysql2RedisDatabase* data_base)
{
    if(data_base == NULL)
    {
        fprintf(stderr,"Null Point!!!"); 
        return false;
    }
    bool read_db = read_db_status();
    if(!read_db)
    {
        fprintf(stderr,"error of read db!"); 
        return false;
    }
    snprintf(data_base->db_name,100,"%s",_db_name.c_str());
    data_base->table_size = allTable.size();
    if(data_base->table_size > MAX_TABLE_SIZE)
    {
        fprintf(stderr,"error too much table"); 
        return false;
    }

    int index = 0;
    for(auto itr:allTable)
    {
        MySql2RedisTable * table = load_data_mysql2redis(itr.second.table_name.c_str()); 
        if(table == NULL)
        {
            fprintf(stderr,"error of load table %s",itr.second.table_name.c_str()); 
            return false;
        }
        data_base->all_table[index] = table;
        index++;
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
    //get all row size of table
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
    snprintf(sql,1024,"desc %s;",table_name);
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
        std::string c_key = row.get_string(3);
   //     fprintf(stdout,"table %s : %s == %s is key %s \n",table_name,c_name.c_str(),c_type.c_str(),c_key.c_str());
        table_status.all_column[c_name] = c_type;
        table_status.all_column_name.push_back(c_name);
        table_status.all_column_type.push_back(c_type);
        //get primary key name
        if(c_key == "PRI")
        {
            table_status.key_field_name = c_name; 
        }
    }
    table_status.table_csize = table_status.all_column_type.size();
    allTable[table_name] = table_status;
    if(table_status.key_field_name == "")
    {
        fprintf(stderr,"can't find pri key in table %s",table_name); 
        return false;
    }

    return true;
}
        
bool mysql_loader::read_db_status()
{
    _conn.change_db("information_schema");
    char sql[1024]= {0};
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
        bool read_rst = read_table_status(table_name.c_str()); 
        if(read_rst == false)
        {
            fprintf(stderr,"read table %s status failed",table_name.c_str()); 
        }
    }

    return true;
}


