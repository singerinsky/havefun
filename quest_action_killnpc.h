#ifndef _QUEST_ACTION_KILLNPC_H_
#define _QUEST_ACTION_KILLNPC_H_

#include "quest_action.h"

class quest_action_killnpc: public IQuestAction
{
    public:
        explicit quest_action_killnpc(CurrentQuest* quest,quest_action_type action_type,NPC_ID npc_id,int need_kill)
        {
            _belong_quest = quest;
            _action_type = action_type;
            _npc_id = npc_id;
            _need_kill_count = need_kill;
            _current_kill_count = 0;
        }
        virtual void start()
        {
        
        }

        virtual void stop() 
        {
        
        }

        virtual void on_notify(Obsever& obsever)
        {
            if(obsever.obsever_type !=  ObseverType_KillNpc)
            {
                return;    
            }

            if(obsever.obsever_params.size() != 2)
            {
                return; 
            }

            if(obsever.obsever_params[0] != _npc_id)
                return;
                
            _current_kill_count += obsever.obsever_params[1];
            if(check_action_finish())
            {
                if(_quest_belong->check_action_finish())
                {
                    _quest_belong->finish(); 
                }
            }

        }

        virtual bool check_action_finish()
        {
            if(_current_kill_count >= _need_kill_count)
                return true;
            return false;
        }

    private:
        NPC_ID _npc_id; 
        int    _need_kill_count;
        int    _current_kill_count;
};


#endif
