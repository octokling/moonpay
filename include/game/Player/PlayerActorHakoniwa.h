#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Main Class for the PlayerActor (Mario)
 * Player Pose: TQGMSV
*  Vtable loc: 1D780C0
 */

#include "../Interfaces/IUseDimension.h"
#include "al/actor/ActorDimensionKeeper.h"
#include "al/actor/ActorInitInfo.h"
#include "PlayerActorBase.h"
#include "PlayerPuppet.h"
#include "PlayerInput.h"
#include "PlayerAnimator.h"
#include "HackCap.h"
#include "PlayerModelKeeper.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerConst.h"
#include "PlayerHackKeeper.h"
#include "PlayerInfo.h"
#include "PlayerModelChangerHakoniwa.h"
#include "PlayerFormSensorCollisionArranger.h"
#include "PlayerInitInfo.h"
#include "al/util/NerveUtil.h"

#include "Attacks/PlayerSpinCapAttack.h"

#define PACTORSIZE 0xC8

class PlayerJudgeDeadWipeStart;
class PlayerJudgePreInputJump;

class PlayerActorHakoniwa : public PlayerActorBase, public IUseDimension {
public:
    int getPortNo(void) const override;
    PlayerHackKeeper *getPlayerHackKeeper() const override;
    void attackSensor(al::HitSensor *target, al::HitSensor *source);
    void startDemoPuppetable(void);
    void startPlayerPuppet(void);
    void initPlayer(al::ActorInitInfo const&, PlayerInitInfo const&);
    void exeDemo();
    void exeJump();

    PlayerInfo *mPlayerInfo; // 0x128
    PlayerConst *mPlayerConst; // 0x130
    PlayerInput *mPlayerInput; //0x138
    PlayerTrigger *playerTrigger; // 0x140
    HackCap *mHackCap; // 0x148
    ActorDimensionKeeper *mDimKeeper; // 0x150
    PlayerModelKeeper *mPlayerModelKeeper; // 0x158
    PlayerModelChangerHakoniwa *mModelChanger; // 0x160
    PlayerAnimator *mPlayerAnimator; // 0x168
    PlayerColliderHakoniwa *mPlayerCollider; // 0x170
    PlayerPuppet *mPlayerPuppet; // 0x178
    // 0x180 PlayerAreaChecker
    // 0x188 WaterSurfaceFinder
    // 0x190 unk
    unsigned char padding_198[0x198 - 0x180];
    PlayerDamageKeeper *damageKeeper; // 0x198
    // 0x1A0 unk
    // 0x1A8 unk
    // 0x1B0 unk
    // 0x1B8 unk
    // 0x1C0 unk
    // 0x1C8 unk
    // 0x1D0 unk
    unsigned char padding_1D8[0x1D8 - 0x1A0];
    PlayerCounterIceWater *playerCounterIceWater; // 0x1D8
    // 0x1E0 unk
    // 0x1E8 unk
    // 0x1F0 unk
    // 0x1F8 PlayerBindKeeper
    unsigned char padding_208[0x208 - 0x1E0];
    PlayerHackKeeper *mHackKeeper; // 0x208
    PlayerFormSensorCollisionArranger *mCollArranger; // 0x210
    void *unkPtr2; // 0x218
    void *unkPtr3; // 0x220
    PlayerSpinCapAttack *mSpinCapAttack; // 0x228
    unsigned char padding_3D8[0x3D8 - 0x230];
    PlayerJudgeDeadWipeStart *playerJudgeDeadWipeStart;
    unsigned char padding_4a0[0x4a0-0x3e0];
    PlayerJudgePreInputJump *mPlayerJudgePreInputJump;
};

namespace {
    NERVE_HEADER(PlayerActorHakoniwa, Jump)
}

namespace {
    NERVE_IMPL(PlayerActorHakoniwa, Jump)
}
