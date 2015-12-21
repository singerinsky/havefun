#ifndef _ROLE_QUEST_H_
#define _ROLE_QUEST_H_

#include "enum.h"
#include "quest_action.h"
#include <set>

class CurrentQuest;
class RoleQuest
{
    public:
        typedef std::map<QUEST_ID,CurrentQuest*> CQuestMap;

    public:
        RoleQuest(PLAYER_ID player_id):_player_id(player_id)
    {
    }
        ~RoleQuest(){}
        //检查是否可以接受
        bool check_acceptable_quest(QUEST_ID quest_id);
        //取消任务
        void cancel_quest(QUEST_ID quest_id);
        //接受任务
        void accept_quest(QUEST_ID quest_id);
        //添加可接受任务
        void add_acceptable_quest(QUEST_ID quest_id);
        //移除可接受任务
        void rm_acceptable_quest(QUEST_ID quest_id);
        //检查是否能够完成
        bool check_quest_can_finish(QUEST_ID quest_id);
        //完成任务
        bool finish_quest(QUEST_ID quest_id);
        //通知
        void on_action_notify(Obsever& ob);
        //更新是否有新的任务可接
        std::vector<QUEST_ID> update_accepteable_quest(QUEST_ID quest_finished);
        PLAYER_ID get_player_id()
        {
            return _player_id; 
        }

    private:
        PLAYER_ID   _player_id;
        CQuestMap   _current_quests;
        std::set<QUEST_ID> _finished_quests;
};

#endif
