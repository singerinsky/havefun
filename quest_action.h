#ifndef _IQUEST_ACTOIN_H_
#define _IQUEST_ACTOIN_H_
#include "data.pb.h"

struct Obsever
{
    ObseverKey  obsever_key;
    ObseverType obsever_type;
    std::vector<int>    obsever_params;

    Obsever& operator = (const Obsever& obsever)
    {
        obsever_key = obsever.obsever_key; 
        obsever_type = obsever.obsever_type;
        obsever_params = obsever.obsever_params;
        return *this;
    }

    bool operator == (const Obsever& obsever)
    {
        if (!(obsever.obsever_type == obsever_type
                    && obsever.obsever_key == obsever_key
             ))
        {
            return false;
        }
        if (obsever.obsever_params.size() != obsever_params.size())
        {
            return false;
        }
        for (unsigned int i=0; i<obsever.obsever_params.size(); ++i)
        {
            if (obsever.obsever_params[i] != obsever_params[i])
            {
                return false;
            }
        }
        return true;
    }
};

class CurrentQuest;
class IQuestAction
{
    public:
        explicit IQuestAction(CurrentQuest* quest,quest_action_type type):_quest_belong(quest),_action_type(type)
    {}
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void on_notify(Obsever& obsever) = 0;
        virtual bool load(quest_action_data* data) = 0;
        virtual void save(quest_action_data* data) = 0;
        virtual bool check_action_finish() = 0;
    protected:
        CurrentQuest* _quest_belong;
        quest_action_type _action_type;
};

#endif
