#pragma once

#include "al/camera/ICameraInput.h"

namespace al {
    class LiveActor;
}

class ProjectCameraInput : public al::ICameraInput {
public:
    ProjectCameraInput(al::LiveActor *actor);

    virtual bool isHoldSnapShotZoomIn() const override;
    virtual bool isHoldSnapShotZoomOut() const override;
    virtual bool isHoldSnapShotRollLeft() const override;
    virtual bool isHoldSnapShotRollRight() const override;

    virtual bool isTriggerReset() const override;
    virtual bool isHoldZoom() const override;
    virtual bool tryCalcSnapShotMoveStick(sead::Vector2f*) const override;
    virtual void calcGyroPose(sead::Vector3f* one, sead::Vector3f* two, sead::Vector3f* three) const override;
    virtual void calcInputStick(sead::Vector2f* out) const override;


    al::LiveActor *actor;
};
