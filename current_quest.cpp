#include "current_quest.h"
#include "quest_action.h"
#include "data.pb.h"
#include "role_quest.h"

void CurrentQuest::init_quest_data()
{
    
}

void CurrentQuest::start()
{
    for(auto itr:_all_quest_actions)
    {
        itr->start(); 
    }
}
//结束
void CurrentQuest::stop()
{
    for(auto itr:_all_quest_actions)
    {
        itr->stop(); 
    }
}

//通知
void CurrentQuest::on_notify(Obsever* obsever)
{
    for(auto& itr:_all_quest_actions)
    {
        itr->on_notify(*obsever); 
    }
}

//检查是否能完成
bool CurrentQuest::check_finishable()
{
    for(auto &itr:_all_quest_actions)
    {
        if(itr->check_action_finish() == false)
            return false;
    }
    return true;
}

//完成
void CurrentQuest::finish()
{
    _quest_status = eQuestFinished;
    //send quest award
}

void CurrentQuest::save_to_pb(quest_data* data)
{
    data->set_role_id(_role_quest->get_player_id());
    data->set_quest_id(_quest_id);
    data->set_quest_type(_quest_type);
    data->set_quest_status(_quest_status);
    for(auto itr:_all_quest_actions)
    {
        ::quest_action_data* action_data = data->add_actions();
        itr->save(action_data);
    }
}

bool CurrentQuest::load_from_pb(const quest_data* data)
{
    _quest_id = data->get_quest_id();
    _quest_status = data->get_quest_status();
    _quest_type = data->get_quest_type();
}
