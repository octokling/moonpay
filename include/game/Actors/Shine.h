#pragma once

#include "al/actor/ActorDimensionKeeper.h"
#include "../Info/QuestInfo.h"
#include "types.h"

#include "../Info/ShineInfo.h"
#include "../Interfaces/IUseDimension.h"
#include "al/LiveActor/LiveActor.h"

class Shine : public al::LiveActor , public IUseDimension {
    public:
        Shine(const char* actorName);

        ActorDimensionKeeper *getActorDimensionKeeper() const override;

        void offAppear();
        void onAppear();
        
        void getDirectWithDemo(void);
        void getDirect();
        void get();

        void onSwitchGet(void);
        
        bool isGot() const;

        void setGrandShine(void);

        void exeWait(void);

        bool isEndAppearGK() const;

        bool isWait() const;

        undefined padding[0x10];
        // 0x11C mIsEmptyShine
        ShineInfo *curShineInfo; // 0x120
        undefined padding_290[0x278 - 0x128];
        QuestInfo *shineQuestInfo; // 0x278
        void *unkPtr1; // 0x280
        ActorDimensionKeeper *mDimensionKeeper; // 0x288
        int shineId; // 0x290
};
