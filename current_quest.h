#ifndef _CURRENT_QUEST_H_
#define _CURRENT_QUEST_H_

#include <vector>
#include "enum.h"

class Obsever;
class IQuestAction;
class RoleQuest;
class quest_data;
class CurrentQuest
{
    public:
        typedef std::vector<IQuestAction*>  QUEST_ACTIONS;
        CurrentQuest(RoleQuest* role_quest,QUEST_ID quest_id):_quest_id(quest_id),_role_quest(role_quest)
        {
            _quest_type = eMainQuest;
            _quest_status = eQuestUnAcceptAble;
        }
        //初始化数据
        void init_quest_data();
        //开始
        void start();
        //结束
        void stop();
        //通知
        void on_notify(Obsever* obsever);
        //检查是否能完成
        bool check_finishable();
        //完成
        void finish();
        //保存到db
        void save_to_pb(quest_data* data);

        QuestStatus get_quest_status(){return _quest_status;}

    private:
        QUEST_ID    _quest_id;
        RoleQuest*  _role_quest;
        QuestType   _quest_type;
        QuestStatus _quest_status;
        QUEST_ACTIONS _all_quest_actions;
};

#endif
