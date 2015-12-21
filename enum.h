#ifndef _ENUM_H_
#define _ENUM_H_

typedef int PLAYER_ID;
typedef int QUEST_ID;
typedef int NPC_ID;


enum QuestType
{
    eMainQuest,
    eBranchQuest,
};

enum QuestStatus
{
    eQuestUnAcceptAble,
    eQuestAcceptAble,
    eQuestAccepted,
    eQuestFinishable,
    eQuestFinished,
};

enum ObseverType
{
    ObseverType_KillNpc,
    ObseverType_GetItem,
    ObseverType_Max,
};

typedef int ObseverKey;

#endif
