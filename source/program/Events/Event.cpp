#include "Event.h"
#include "logger/Logger.hpp"
#include "helps/tryGets.h"
#include "sead/random/seadGlobalRandom.h"
#include "game/StageScene/StageSceneFunction.h"
#include "game/GameData/GameDataFunction.h"

EventList CurrentEvent = NOTHING;

int actualFrameCooldown = 0;
int randomFrameCooldown = 0;
int frameEventDuration = 0;

int lastRandomEvent = -1;

bool isLastEventHasCooldown = false;

int getRandomValue(int min, int max){
    int maxValue = max - min;
    sead::GlobalRandom::instance()->init();
    return (int)sead::GlobalRandom::instance()->getU32(maxValue) + min;
}

void Event::calculLevel(){
    int TotalMoon = GameDataFunction::getTotalShineNum(EvStageScene, -1);

    if(TotalMoon >= 25){
        eventLevel = (TotalMoon / 25) + 1;        
    }
    Logger::log("Niveau actuel : %i", eventLevel);
}

Event::Event(StageScene* stageScene){ // Init event
    EvStageScene = stageScene;
    Event::calculLevel();
    Logger::log("Event initialized !");
}

void Event::setEventToNothing(){
    LastEvent = CurrentEvent;
    CurrentEvent = EventList::NOTHING;
}

const char* Event::getCurrentEventName(){
    if(CurrentEvent == EventList::ADD_COINS){
        return "ADD_COINS";
    }else if(CurrentEvent == EventList::DOUBLE_COINS1MIN){
        return "DOUBLE_COINS1MIN";
    }else if(CurrentEvent == EventList::SHINECOST_MINISOLD){
        return "SHINECOST_MINISOLD";
    }else if(CurrentEvent == EventList::SPAWN_CHEST_100COINS){
        return "SPAWN_CHEST_100COINS";
    }else if(CurrentEvent == EventList::LOSE_DEAD_COINS){
        return "LOSE_DEAD_COINS";
    }else if(CurrentEvent == EventList::RECOVERPLAYER){
        return "RECOVERPLAYER";
    }else if(CurrentEvent == EventList::TAKEDAMAGE){
        return "TAKEDAMAGE";
    }else if(CurrentEvent == EventList::BLOCKCAPPY){
        return "BLOCKCAPPY";
    }else if(CurrentEvent == EventList::LOSECOINCAPPY){
        return "LOSECOINCAPPY";
    }
    return "Nothing";
};

EventList Event::selectAnEvent(){
    bool needToRandom = true;

    int random = -1;
    while(needToRandom){
        random = getRandomValue(0, 6);
        if(random != lastRandomEvent){
            lastRandomEvent = random;
            needToRandom = false;
        }
    }

    if(random == 0){
        frameEventDuration = 0;
        return EventList::ADD_COINS;
    }else if(random == 1){
        frameEventDuration = 4600;
        return EventList::DOUBLE_COINS1MIN;
    }else if(random == 2){
        frameEventDuration = 6000;
        return EventList::SHINECOST_MINISOLD;
    }else if(random == 3){
        frameEventDuration = 0;
        return EventList::LOSE_DEAD_COINS;
    }else if(random == 4){
        frameEventDuration = 0;
        return EventList::RECOVERPLAYER;
    }else if(random == 5){
        frameEventDuration = 0;
        return EventList::TAKEDAMAGE;
    }else if(random == 6){
        frameEventDuration = 0;
        return EventList::BLOCKCAPPY;
    }else if(random == 7){
        frameEventDuration = 0;
        return EventList::LOSECOINCAPPY;
    }else if(random == 8){
        frameEventDuration = 0;
        return EventList::SPAWN_CHEST_100COINS;
    }

    return EventList::NOTHING;
}

void Event::update(){
    if(cooldownInProcess == false) return;
    if(actualFrameCooldown == 0 && randomFrameCooldown == 0) Event::tryStartCooldown();

    Event::updateEffectEvent();

    if(frameEventDuration != 0){
        isLastEventHasCooldown = true;
        frameEventDuration--;
        //Logger::log("Cooldown event : %i\n", frameEventDuration);

    }else if(frameEventDuration == 0 && isLastEventHasCooldown){
        Event::setEventToNothing();
        isLastEventHasCooldown = false;
        
    }else if(actualFrameCooldown >= randomFrameCooldown){
        cooldownInProcess = false;
        actualFrameCooldown = 0;
        randomFrameCooldown = 0;
        CurrentEvent = Event::selectAnEvent();
        //Logger::log("Selected event : %s\n", Event::getCurrentEventName());
        Event::effectEvent();

    }else{
        actualFrameCooldown++;
        if(al::isPadTriggerZR(-1)){
            //Logger::log("Actual : %i Target : %i\n", actualFrameCooldown, randomFrameCooldown);
        }
    }
}

void Event::tryEndCooldown(){
    if(Event::cooldownInProcess == false) return;
    actualFrameCooldown = 0;
    randomFrameCooldown = 0;
    cooldownInProcess = false;
};

void Event::tryStartCooldown(){
    if(Event::cooldownInProcess == true) return;
    //randomFrameCooldown = getRandomValue(200, 300);
    randomFrameCooldown = getRandomValue(15000, 35000);
    cooldownInProcess = true;
};

void Event::updateEffectEvent(){

}

void Event::effectEvent(){
    GameDataHolder* mGameDataHolder = tryGetGameDataHolder();
    if(CurrentEvent == EventList::ADD_COINS){
        Event::setEventToNothing();
        mGameDataHolder->mGameDataFile->addCoin(10 * eventLevel);
    }else if(CurrentEvent == EventList::LOSE_DEAD_COINS){
        Event::setEventToNothing();
        PlayerActorBase* playerActor = tryGetPlayerActor(EvStageScene);
        StageSceneFunction::appearPlayerDeadCoin(playerActor);
        GameDataFunction::subCoin(EvStageScene->mHolder, 10);
    }else if(CurrentEvent == EventList::RECOVERPLAYER){
        Event::setEventToNothing();
        PlayerActorBase* playerActor = tryGetPlayerActor(EvStageScene);
        GameDataFunction::recoveryPlayer(playerActor);
    }else if(CurrentEvent == EventList::TAKEDAMAGE){
        Event::setEventToNothing();
        GameDataFunction::damagePlayer(EvStageScene->mHolder);
    }
}

void doubleCoin(GameDataFile* mGameDataFile, int addCoin){
    if(CurrentEvent == EventList::DOUBLE_COINS1MIN){
        mGameDataFile->addCoin(addCoin*2);
    }else{
        mGameDataFile->addCoin(addCoin);
    }
}



void installHooks(){
    exl::patch::CodePatcher(0x529C14).BranchInst(reinterpret_cast<void*>(doubleCoin));
}