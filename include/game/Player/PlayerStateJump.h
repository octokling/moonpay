#pragma once
#include "al/nerve/ActorStateBase.h"

class PlayerStateJump : public al::ActorStateBase {
public:
    bool isEndJumpDownFallLand() const;
};