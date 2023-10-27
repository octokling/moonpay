#pragma once


class PlayerInput {
public:
    bool isMove(void) const;

    bool isMoveDeepDown(void) const;

    bool isMoveDeepDownNoSnap(void) const;

    bool isNoInput(void) const;

    bool isTriggerJump() const;

    bool isTriggerHackJump() const;

    al::LiveActor *actor;
};
