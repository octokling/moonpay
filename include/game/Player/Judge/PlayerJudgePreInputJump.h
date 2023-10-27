#pragma once
#include "IJudge.h"

class PlayerConst;
class PlayerInput;

class PlayerJudgePreInputJump : public IJudge {
public:
    PlayerConst *playerConst; // 0x8
    PlayerInput *playerInput; // 0x10
    IJudge *playerSlopeJudge; // 0x18
    int flag; // 0x20
};
