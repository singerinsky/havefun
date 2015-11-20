#include "mysql2redis.h"
#include "mysql_loader.h"


Mysql2RedisDatabase* load_database(const char* db_name,const char* ip_str,int port,const char* user_name,const char* pwd)
{
    mysql_loader * loader = new mysql_loader(db_name,ip_str,port,user_name,pwd);   
    bool rst = loader->init();
    if(rst == false)
    {
        fprintf(stderr,"init loader error %s:%d:%s:%s:%s",db_name,port,ip_str,user_name,pwd); 
        return NULL;
    }
    Mysql2RedisDatabase* database = new Mysql2RedisDatabase();
    if(!loader->start_load(database))
    {
        return NULL; 
    }
    return database;
}

void dump_data_base(Mysql2RedisDatabase* data)
{
    fprintf(stdout,"db name is %s\n",data->db_name);
    fprintf(stdout,"have table %d\n",data->table_size);
    for(int i =0;i <data->table_size;i++)
    {
        fprintf(stdout,"table name:%s\n",data->all_table[i]->table_name);
        for(int r = 0;r < data->all_table[i]->data_row_size; r++)
        {
            fprintf(stdout,"|-[%s][",data->all_table[i]->rows[r]->key);
            for(int c = 0;c <data->all_table[i]->data_column_size; c++)
            {
                fprintf(stdout,"%s",data->all_table[i]->rows[r]->data[c]); 
            }
            fprintf(stdout,"]\n");
        }
    }
}
