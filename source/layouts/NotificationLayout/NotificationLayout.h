#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logger/Logger.hpp"

// TODO: kill layout if going through loading zone or paused

class NotificationLayout : public al::LayoutActor {
    public:
        NotificationLayout(const char* name, const al::LayoutInitInfo& initInfo);

        void appear() override;

        bool tryStart();
        bool tryEnd();

        void exeAppear();
        void exeWait();
        void exeEnd();

};

namespace {
    NERVE_HEADER(NotificationLayout, Appear)
    NERVE_HEADER(NotificationLayout, Wait)
    NERVE_HEADER(NotificationLayout, End)
}