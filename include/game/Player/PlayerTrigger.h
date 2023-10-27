#pragma once

class PlayerTrigger {
public:
    enum class EActionTrigger {
        UNK0, UNK1, UNK2, UNK3, WATER_FREEZE
    };

    void set(EActionTrigger);

    bool isOn(EActionTrigger) const;
};