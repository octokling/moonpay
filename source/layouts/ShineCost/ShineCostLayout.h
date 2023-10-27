#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logger/Logger.hpp"

// TODO: kill layout if going through loading zone or paused

class ShineCostLayout : public al::LayoutActor {
    public:
        ShineCostLayout(const char* name, const al::LayoutInitInfo& initInfo);

        void appear() override;

        bool tryStart();
        bool tryEnd();

        void updateCost(int cost){ShineCostText = cost;};

        void exeAdd();
        void exeAppear();
        void exeWait();
        void exeEnd();

        int ShineCostText = 0;

};

namespace {
    NERVE_HEADER(ShineCostLayout, Appear)
    NERVE_HEADER(ShineCostLayout, Wait)
    NERVE_HEADER(ShineCostLayout, Add)
    NERVE_HEADER(ShineCostLayout, End)
}