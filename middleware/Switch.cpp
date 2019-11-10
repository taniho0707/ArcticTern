/**
 * @file Switch.cpp
 */

#include "Switch.h"

Switch::Switch() {
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    has_pushed[0] = 0;
    has_pushed[1] = 0;
}

bool Switch::isPushing(SwitchNumbers num) {
    if (num == SwitchNumbers::SW1) {
        return (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == 0 ? true : false);
    } else if (num == SwitchNumbers::SW2) {
        return (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0 ? true : false);
    }
}

bool Switch::hasPushed(SwitchNumbers num) {
    
}

void Switch::interrupt() {
    
}

Switch* Switch::getInstance() {
    static Switch instance;
    return &instance;
}
