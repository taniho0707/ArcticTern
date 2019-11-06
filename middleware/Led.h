/**
 * @file Led.h
 */
#pragma once

#include "stm32f7xx_hal.h"
/* #include "Timer.h" */

#include <array>

enum class LedNumbers : uint8_t {
    LED0,
    LED1,
    LED2,
    LED3,
    LED4,
    LED5,
    LED6,
    LED7,
    TOP
};

struct LedFlickParams{
    uint32_t start_time = 0;
    float freq = 0;
    uint32_t time = 0;
};

class Led{
private:
    GPIO_TypeDef * gpio_port;
    uint16_t gpio_channel;

    I2C_HandleTypeDef hi2c1;
    DMA_HandleTypeDef hdma_i2c1_tx;

    uint8_t i2c_0c0d_data[2];

    std::array<LedFlickParams, 9> flick_params;

    Led();

public:
    void on(LedNumbers num);
    void off(LedNumbers num);

    bool isFlicking(LedNumbers num);

/// @params time. 0 to infinite
    void flickSync(LedNumbers num, float freq, uint16_t time);
    void flickAsync(LedNumbers num, float freq, uint16_t time);
    void flickStop(LedNumbers num);

    void interrupt();

    static Led* getInstance();

    HAL_StatusTypeDef status;
};
