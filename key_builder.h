#ifndef _KEY_BUILDER_H_
#define _KEY_BUILDER_H_

enum sub_type
{
    ROLE_TYPE = 1,
    GUILD_TYPE = 2,
    RANK_TYPE = 3,
}

std::string build_key(int server_id,int sub_type,int order_id)
{
    return "";
}

#endif
