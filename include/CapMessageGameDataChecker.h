#pragma once

class CapMessageGameDataChecker
{
public:
    CapMessageGameDataChecker();
    void initByPlacementInfo(const al::ActorInitInfo&);
    void invalidateKidsMode();
    void invalidatePlayerSeparate();
    void invalidateGameClear();
    void enableNoCap();
    void enableGiantWanderBoss();
    void check(const al::IUseSceneObjHolder*) const;
};