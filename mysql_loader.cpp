#include "mysql_loader.h"

bool mysql_loader::read_table_data(const char* table_name)
{
    auto itr = allTable.find(table_name);
    if(itr == allTable.end())
    {
        fprintf(stdout,"table %s status not read yet",table_name);
        return false; 
    }
    char sql[1024] = {0};
    snprintf(sql,1024,"select * from %s",table_name);
    bool rst = _conn.exec(sql);
    if(rst != 0)
    {
        fprintf(stdout,"load table %s data error",table_name); 
        return false;
    }
    
    MysqlResult result = _conn.get_data_result();
    if(result.next())
    {
        sstringstream sstr;
        MysqlResultRow row = result.get_next_row(); 
        int index = 0;
        for(auto type_itr:itr->second.all_column_type)
        {
            const char* row_c_data = row.get_src_data(index);
            sstr<<type_itr<<" "<<row_c_data;
        }
        int data_size = row.get_int(0);
        table_status.table_rsize = data_size;
        fprintf(stdout,"table %s rows number is %d\n",table_name,data_size);
    }

    return false;
}
