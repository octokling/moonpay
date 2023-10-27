#pragma once

namespace al {
    class LiveActor;
}

class PlayerConst;

class IUsePlayerCollision;

class IJudge;

class PlayerCounterIceWater {
public:
    PlayerCounterIceWater(al::LiveActor *, const al::ActorInitInfo &, const PlayerConst *, const IUsePlayerCollision *,
                          IJudge *);

    void clearIceWaterCount();

    void updateCount(bool, bool);

    bool isTriggerDamage() const;

    void updateRecoveryCountImpl();

    void killIceEffect();

    al::LiveActor *player;
    PlayerConst *playerConst;
    IUsePlayerCollision *playerCollision;
    IJudge *judgeInWater;
    al::LiveActor *actor;
    int count;
    int unk;
    int coldLevel;
    bool unk2;
    bool isNotFirstTimeIceWater;
};