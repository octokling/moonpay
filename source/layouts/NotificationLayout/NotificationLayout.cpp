#include "NotificationLayout.h"
#include <cstdio>
#include <cstring>
#include "al/string/StringTmp.h"
#include "prim/seadSafeString.h"
#include "al/util.hpp"
#include "logger/Logger.hpp"
#include "rs/util.hpp"

NotificationLayout::NotificationLayout(const char* name, const al::LayoutInitInfo& initInfo) : al::LayoutActor(name) {
    al::initLayoutActor(this, initInfo, "ShineCost", 0); 
    initNerve(&nrvNotificationLayoutEnd, 0);
}

void NotificationLayout::appear() {
    al::startAction(this, "Appear", 0);
    
    al::setNerve(this, &nrvNotificationLayoutAppear);

    al::LayoutActor::appear();
}

void NotificationLayout::exeAppear() {

    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvNotificationLayoutWait);
    }
}

void NotificationLayout::exeWait() {

    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }
    
}

void NotificationLayout::exeEnd() {

    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

bool NotificationLayout::tryEnd()
{
    if (!al::isNerve(this, &nrvNotificationLayoutEnd)) {
        al::setNerve(this, &nrvNotificationLayoutEnd);
        return true;
    }
    return false;
}

bool NotificationLayout::tryStart()
{

    if (!al::isNerve(this, &nrvNotificationLayoutWait) && !al::isNerve(this, &nrvNotificationLayoutAppear)) {
        appear();
        return true;
    }
    return false;
}

namespace {
    NERVE_IMPL(NotificationLayout, Appear)
    NERVE_IMPL(NotificationLayout, Wait)
    NERVE_IMPL(NotificationLayout, End)
}