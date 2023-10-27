#pragma once

#include "IJudge.h"

namespace al {
    class LiveActor;
}
class PlayerConst;

class PlayerJudgeDeadWipeStart : public IJudge {
public:
    al::LiveActor *player;
    PlayerConst *playerConst;
    unsigned int deathType;
};
