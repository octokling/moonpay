#pragma once

#include "sead/heap/seadDisposer.h"
#include "keyboard.hpp"
#include "al/async/FunctorV0M.hpp"
#include "heap/seadFrameHeap.h"

class shineCostParams
{
    SEAD_SINGLETON_DISPOSER(shineCostParams)
    public:
        shineCostParams();
        int getShineCostInt(){ return shineCost;};
        void getShineCost();
    private:
        void openKeyboardP();

        Keyboard* mKeyboard = nullptr;
        int shineCost = 15;
        al::AsyncFunctorThread *mReadThread = nullptr;
        sead::FrameHeap *mHeap = nullptr;
        sead::FixedSafeString<0x10> mServerIP;
};
