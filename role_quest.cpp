#include "role_quest.h"
#include "current_quest.h"


bool RoleQuest::check_acceptable_quest(QUEST_ID quest_id)
{
    return true;
}

//取消任务
void RoleQuest::cancel_quest(QUEST_ID quest_id)
{


}

//接受任务
void RoleQuest::accept_quest(QUEST_ID quest_id)
{


}

//添加可接受任务
void RoleQuest::add_acceptable_quest(QUEST_ID quest_id)
{

}

//移除可接受任务
void RoleQuest::rm_acceptable_quest(QUEST_ID quest_id)
{

}

//检查是否能够完成
bool RoleQuest::check_quest_can_finish(QUEST_ID quest_id)
{
    return false;
}

//完成任务
bool RoleQuest::finish_quest(QUEST_ID quest_id)
{
    return false;
}

//通知
void RoleQuest::on_action_notify(Obsever& ob)
{ 
    for(auto itr:_current_quests)
    {
        if(itr.second->get_quest_status() == eQuestAccepted || itr.second->get_quest_status() == eQuestFinishable)
        {
            itr.second->on_notify(&ob);        
        }
    }
}

std::vector<QUEST_ID> update_accepteable_quest(QUEST_ID quest_finished)
{
    std::vector<QUEST_ID> quest_vec;
    return quest_vec;
}
