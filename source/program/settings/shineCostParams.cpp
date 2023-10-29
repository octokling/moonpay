#include "shineCostParams.hpp"

#include "logger/Logger.hpp"
#include "nn/util.h"

SEAD_SINGLETON_DISPOSER_IMPL(shineCostParams)

typedef void (shineCostParams::*shineCostThreadFunc)(void);

shineCostParams::shineCostParams(){
    mHeap = sead::FrameHeap::create(0x100000, "ShineHeap", sead::HeapMgr::instance()->getCurrentHeap(), 8, sead::Heap::cHeapDirection_Forward, false);
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);
    
    this->mReadThread = new al::AsyncFunctorThread("ShineReadThread", al::FunctorV0M<shineCostParams*, shineCostThreadFunc>(this, &shineCostParams::openKeyboardP), 0, 0x2000, {0});

    mKeyboard = new Keyboard(nn::swkbd::GetRequiredStringBufferSize());
    this->mReadThread->start();
}

void shineCostParams::getShineCost(){
    //Logger::log("Les lunes coûterons %i pièces.\n", shineCostParams::openKeyboardP());
}

void shineCostParams::openKeyboardP(){
    nn::os::YieldThread(); // sleep the thread for the first thing we do so that game init can finish
    nn::os::SleepThread(nn::TimeSpan::FromSeconds(5));

    sInstance->mKeyboard->setHeaderText(u"Set the desired amount of moons.");
    sInstance->mKeyboard->setSubText(u"By default, moons cost 15 coins.");
    mServerIP = "885.258.365.145";

    sInstance->mKeyboard->openKeyboard(mServerIP.cstr(), [](nn::swkbd::KeyboardConfig& config) {
        config.keyboardMode = nn::swkbd::KeyboardMode::ModeNumeric;
        config.textMaxLength = 4;
        config.textMinLength = 1;
        config.isUseUtf8 = true;
        config.inputFormMode = nn::swkbd::InputFormMode::OneLine;
    });

    while (true) {
        if (sInstance->mKeyboard->isThreadDone()) {
            if(!sInstance->mKeyboard->isKeyboardCancelled())
                Logger::log("Resultat %i", ::atoi(sInstance->mKeyboard->getResult()));
            break;
        }
        nn::os::YieldThread(); // allow other threads to run
    }
}