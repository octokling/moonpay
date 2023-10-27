#include "ShineCostLayout.h"
#include <cstdio>
#include <cstring>
#include "al/string/StringTmp.h"
#include "prim/seadSafeString.h"
#include "al/util.hpp"
#include "logger/Logger.hpp"
#include "rs/util.hpp"

ShineCostLayout::ShineCostLayout(const char* name, const al::LayoutInitInfo& initInfo) : al::LayoutActor(name) {
    al::initLayoutActor(this, initInfo, "ShineCost", 0); 
    initNerve(&nrvShineCostLayoutEnd, 0);
}

void ShineCostLayout::appear() {
    al::startAction(this, "Appear", 0);
    
    al::setNerve(this, &nrvShineCostLayoutAppear);

    al::LayoutActor::appear();
}


void ShineCostLayout::exeAdd() {

    if(al::isNerve(this, &nrvShineCostLayoutAdd)){
        Logger::log("exeAdd");
    }
}

void ShineCostLayout::exeAppear() {

    if (al::isActionEnd(this, 0)) {
        al::setNerve(this, &nrvShineCostLayoutWait);
    }
}

void ShineCostLayout::exeWait() {

    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait", 0);
    }

    char16_t* cost = (char16_t*)ShineCostText;
    al::setPaneStringFormat(this, "TxtCost", "%i", cost);
    
}

void ShineCostLayout::exeEnd() {

    if (al::isFirstStep(this)) {
        al::startAction(this, "End", 0);
    }

    if (al::isActionEnd(this, 0)) {
        kill();
    }
}

bool ShineCostLayout::tryEnd()
{
    if (!al::isNerve(this, &nrvShineCostLayoutEnd)) {
        al::setNerve(this, &nrvShineCostLayoutEnd);
        return true;
    }
    return false;
}

bool ShineCostLayout::tryStart()
{

    if (!al::isNerve(this, &nrvShineCostLayoutWait) && !al::isNerve(this, &nrvShineCostLayoutAppear)) {
        appear();
        return true;
    }
    return false;
}

namespace {
    NERVE_IMPL(ShineCostLayout, Appear)
    NERVE_IMPL(ShineCostLayout, Wait)
    NERVE_IMPL(ShineCostLayout, Add)
    NERVE_IMPL(ShineCostLayout, End)
}