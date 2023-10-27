#pragma once

#include "game/StageScene/StageScene.h"
#include "al/util.hpp"
#include "lib.hpp"

enum EventList{
    NOTHING,
    ADD_COINS,
    SPAWN_CHEST_100COINS,
    DOUBLE_COINS1MIN,
    SHINECOST_MINISOLD,
    LOSE_DEAD_COINS,
    RECOVERPLAYER,
    TAKEDAMAGE,
    BLOCKCAPPY,
    LOSECOINCAPPY
};

class Event {
    public:
        Event(StageScene* stageScene);
        void tryStartCooldown();
        void tryEndCooldown();
        void update();

        void effectEvent();
        void updateEffectEvent();
        void calculLevel();
        //Events void

        /*int getActualFrameCooldown(){return actualFrameCooldown;};
        int getRandomFrameCooldown(){return randomFrameCooldown;};*/

        bool isCooldownInProcess(){return cooldownInProcess;};
    
        const char* getCurrentEventName();

        sead::FixedSafeString<0x40> getSceneName(){return EvStageScene->mName;};
        
        EventList selectAnEvent();


    private:
        void setEventToNothing();
        
        EventList LastEvent = NOTHING;

        StageScene* EvStageScene = nullptr;

        bool cooldownInProcess;
        
        int eventLevel = 1;
};

void installHooks();