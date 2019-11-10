/**
 * @file Switch.h
 */
#pragma once

#include "stm32f7xx_hal.h"

enum class SwitchNumbers : uint8_t {
    SW1,
    SW2
};

class Switch {
private:
    uint8_t has_pushed[2];

    Switch();

public:
    bool isPushing(SwitchNumbers num);

    bool hasPushed(SwitchNumbers num);

    void interrupt();

    static Switch* getInstance();
};
